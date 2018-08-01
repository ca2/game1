/*
* life.cpp
*
* Copyright 2018 proph <prorocktwitch@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
* MA 02110-1301, USA.
*
*
*/

/*
Adapted to ca2 framework: camilo@ca2.email, camilocc@gmail.com

*/
#include "framework.h"


namespace game_of_life
{


   void cell::io(stream & stream)
   {

      stream(m_iAliveNeighbours);
      stream(m_chState);
      stream(m_rect->m_chColor);
      stream(m_iStep);

   }

   void cell::setState(char st)
   {
      m_chState = st;
      int color = 255 * (1 - st);
      if (m_rect) m_rect->m_chColor= color;
   }
   char cell::isAlive()
   {
      return m_chState;
   }
   void cell::addNeighbour()
   {
      m_iAliveNeighbours++;
   }
   void cell::resetNeighbours()
   {
      m_iAliveNeighbours = 0;
   }
   char cell::getNeighbours()
   {
      return m_iAliveNeighbours;
   }

   void cell::setRect(RectangleShape* rect)
   {
      m_rect = rect;
   }
   RectangleShape* cell::getRect()
   {
      return m_rect;
   }

   game::game(::aura::application * papp) :
      object(papp),
      ::estamira::game(papp)
   {

      m_iGameMaxSize = 600;



      m_field = new RectangleShape*[m_iGameMaxSize];

      m_cells = new cell*[m_iGameMaxSize];

      for (int i = 0; i < m_iGameMaxSize; i++)
      {

         m_field[i] = new RectangleShape[m_iGameMaxSize];

         m_cells[i] = new cell[m_iGameMaxSize];

         for (int j = 0; j < m_iGameMaxSize; j++)
         {

            m_cells[i][j].setRect(&m_field[i][j]);

            m_cells[i][j].x = i;

            m_cells[i][j].y = j;

         }
      }

      set_amount(150, false);

      load();

   }

   void game::set_amount(int iAmount, bool bSave)
   {

      synch_lock sl(m_pmutex);

      if (iAmount < 16)
      {

         iAmount = 16;

      }
      else if (iAmount > m_iGameMaxSize)
      {

         iAmount = m_iGameMaxSize;

      }

      m_iAmount = iAmount;

      m_iWindowSize = WINDOWSIZE;

      m_iCellSize = m_iWindowSize / m_iAmount;

      if (m_iCellSize <= 3)
      {

         m_iCellSize = 3;

         m_iWindowSize = m_iCellSize * m_iAmount;

      }



   }


   game::~game()
   {

      save_file();
      destroy();

   }


   void game::load()
   {

      ::estamira::game::load_file();

   }


   void game::save()
   {

      ::estamira::game::save_file();

   }


   void game::destroy()
   {

      synch_lock sl(m_pmutex);

      ::multithreading::post_quit(m_pthread);


      for (int i = 0; i < m_iAmount; i++)
      {

         if (m_field)
         {

            delete[] m_field[i];

         }

         if (m_cells)
         {

            delete[] m_cells[i];

         }

      }

      if (m_field)
      {

         delete[] m_field;

      }

      if (m_cells)
      {

         delete[] m_cells;

      }

      m_field = NULL;

      m_cells = NULL;

   }

   void game::io(stream & stream)
   {

      stream(m_iGameMaxSize);
      stream(m_iAmount);

      try
      {
         if (is_storing())
         {
            for (int i = 0; i < m_iGameMaxSize; i++)
            {


               for (int j = 0; j < m_iGameMaxSize; j++)
               {

                  //               stream(m_cells[i][j]);

                  stream.m_spfile->write(&m_cells[i][j].m_iAliveNeighbours,1);
                  stream.m_spfile->write(&m_cells[i][j].m_chState, 1);
                  stream.m_spfile->write(&m_cells[i][j].m_rect->m_chColor, 1);
                  stream.m_spfile->write(&m_cells[i][j].m_iStep, 4);


               }
            }
         }
         else
         {
            for (int i = 0; i < m_iGameMaxSize; i++)
            {


               for (int j = 0; j < m_iGameMaxSize; j++)
               {

                  //               stream(m_cells[i][j]);

                  stream.m_spfile->read(&m_cells[i][j].m_iAliveNeighbours, 1);
                  stream.m_spfile->read(&m_cells[i][j].m_chState, 1);
                  stream.m_spfile->read(&m_cells[i][j].m_rect->m_chColor, 1);
                  stream.m_spfile->read(&m_cells[i][j].m_iStep, 4);


               }
            }


         }

         ::count c;

         if (is_storing())
         {

            c = m_aliveCells.get_count();

            stream(c);

            for (index i = 0; i < c; i++)
            {

               index x = m_aliveCells[i]->x;

               index y = m_aliveCells[i]->y;

               stream(x);

               stream(y);

            }

         }
         else
         {
            stream(c);

            for (index i = 0; i < c; i++)
            {

               index x;

               index y;

               stream(x);

               stream(y);

               if (!stream.fail())
               {

                  m_aliveCells.add(&m_cells[x][y]);

               }

            }

         }

      }
      catch (...)
      {

      }

      if (!stream.is_storing())
      {

         set_amount(m_iAmount, false);

      }

   }


   void game::update()
   {
      synch_lock sl(m_pmutex);
      std::vector<cell*> uncheckedCells = m_aliveCells;
      std::vector<cell*> dyingCells;
      m_iStep++;
      m_aliveCells.clear();
      while (!uncheckedCells.empty())
      {
         cell* cell = uncheckedCells.last();
         uncheckedCells.pop_back();
         if (cell->isAlive())
         {
            cell->resetNeighbours();
            for (int i = -1; i <= 1; i++)
            {
               for (int j = -1; j <= 1; j++)
               {
                  if ((i != 0 || j != 0) && i + cell->x >= 0 && j + cell->y >= 0 && i + cell->x<m_iAmount && j + cell->y<m_iAmount)
                  {
                     ::game_of_life::cell* curCell = &this->m_cells[cell->x + i][cell->y + j];
                     if (curCell->isAlive()) cell->addNeighbour();
                     else if (curCell->getStep() != m_iStep)uncheckedCells.push_back(curCell);
                  };
               }
            }
            if (cell->getNeighbours()<2 || cell->getNeighbours()>3) dyingCells.push_back(cell);
            else m_aliveCells.push_back(cell);
            cell->updateStep(m_iStep);
            cell->resetNeighbours();
         }
         else
         {
            cell->resetNeighbours();
            for (int i = -1; i <= 1; i++)
            {
               for (int j = -1; j <= 1; j++)
               {
                  if ((i != 0 || j != 0) && i + cell->x >= 0 && j + cell->y >= 0 && i + cell->x<m_iAmount && j + cell->y<m_iAmount) if (this->m_cells[cell->x + i][cell->y + j].isAlive()) cell->addNeighbour();
               }

            }
            if (cell->getNeighbours() == 3)
            {
               m_aliveCells.push_back(cell);
            }
            cell->updateStep(m_iStep);
            cell->resetNeighbours();
         }
      }
      for (auto & n : m_aliveCells)
      {
         n->setState(1);
      }
      for (auto & n : dyingCells)
      {
         n->setState(0);
      }
   }
//int main(void)
//{
//   sf::ContextSettings settings;
//   settings.antialiasingLevel = 0;
//   sf::RenderWindow window(sf::VideoMode(m_iWindowSize, m_iWindowSize), "Life", sf::Style::Titlebar | sf::Style::Close, settings);
//   window.setKeyRepeatEnabled(false);
//   sf::Event event;
//   int amount = 60;
//   window.clear(sf::Color::Blue);
//   int size = m_iWindowSize / amount;
//   game curGame(amount);
//   int drawnAlready = 0;
//   bool onPause = true;
//   sf::Clock clock;
//   while (window.isOpen())
//   {
//      while (window.pollEvent(event))
//      {
//         if (event.type == sf::Event::Closed)
//            window.close();
//         if (event.type == sf::Event::MouseButtonPressed && onPause)
//         {
//            int x, y;
//            x = (int)event.mouseButton.x / size;
//            y = (int)event.mouseButton.y / size;
//            curGame.push_cell(x, y);
//         }
//         if (event.type == sf::Event::KeyPressed)
//         {
//            if (event.key.code == sf::Keyboard::Space) onPause = !onPause;
//            if (event.key.code == sf::Keyboard::Backspace)
//            {
//               onPause = 1;
//               curGame.Clear();
//            };
//
//         }
//
//      };
//      if (clock.getElapsedTime()>sf::milliseconds(20))
//      {
//         if (drawnAlready)
//         {
//            if (!onPause)  curGame.Update();
//         }
//         else
//         {
//            drawnAlready = 1;
//            curGame.Clear();
//         }
//         window.clear();
//         curGame.Draw(&window);
//
//         clock.restart();
//      }
//      window.display();
//
//   };
//   return 0;
//}

   void game::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      pgraphics->fill_solid_rect_dim(0, 0, m_iWindowSize + 1, m_iWindowSize + 1, ARGB(255, 255, 255, 255));

      ::draw2d::pen_sp pen(allocer());

      pen->create_solid(1.0, ARGB(250, 180, 180, 180));
      pgraphics->SelectObject(pen);
      for (int i = 0; i <= m_iAmount; i++)
      {
         pgraphics->move_to(0, i * m_iCellSize);
         pgraphics->line_to(m_iWindowSize, i * m_iCellSize);
      }
      for (int j = 0; j <= m_iAmount; j++)
      {
         pgraphics->move_to(j * m_iCellSize, 0);
         pgraphics->line_to(j * m_iCellSize, m_iWindowSize);
      }

      for (int i = 0; i < m_iAmount; i++)
      {
         for (int j = 0; j < m_iAmount; j++)
         {
            rect r = m_field[i][j].m_rect;
            r.deflate(1, 1, 0, 0);
            char chColor = m_field[i][j].m_chColor;
            pgraphics->fill_solid_rect(r, ARGB(255, chColor, chColor, chColor));

         }

      }

   }


   void game::push_cell(unsigned int x, unsigned int y)
   {
      if (!m_cells[x][y].isAlive())
      {
         m_aliveCells.add(&m_cells[x][y]);
         m_cells[x][y].setState(1);
      }
      else
      {
         int i = 0;
         for (auto it = m_aliveCells.begin(); it < m_aliveCells.end(); it++, i++)
         {
            if (m_aliveCells[i]->x == x && m_aliveCells[i]->y == y)
               m_aliveCells.erase(it);
         };
         m_cells[x][y].setState(0);
      }
   }


   bool game::start(::user::impact * pview)
   {

      if (!::estamira::game::start(pview))
      {

         return false;

      }

      on_new_game();


      m_pthread = fork([&]()
      {
         int drawnAlready = 0;
         while (::get_thread_run())
         {
            //if (drawnAlready)
            {
               // if (!m_bOnPause&&FPS != sf::milliseconds(0))std::cout << 1 / FPS.asSeconds() << std::endl;
               if (!m_bOnPause)  update();
            }
            //else
            //{
            //drawnAlready = 1;
            //curGame.Clear();
            //}
            Sleep(300);
         }

      });


      //      return 0;

      //remove_all_characters();

      //add_new_character("male");

      //auto * p = add_new_character("male");

      //p->m_ekeyLeft = ::user::key_z;
      //p->m_ekeyRight = ::user::key_x;
      //p->m_ekeyUp = ::user::key_s;

      //   sf::ContextSettings settings;
      //   settings.antialiasingLevel = 0;
      //   sf::RenderWindow window(sf::VideoMode(m_iWindowSize, m_iWindowSize), "Life", sf::Style::Titlebar | sf::Style::Close, settings);
      //   window.setKeyRepeatEnabled(false);
      //   sf::Event event;
      //   int amount = 150;
      //   window.clear(sf::Color::Blue);
      //   int size = m_iWindowSize / amount;
      //   Game curGame(amount);
      //   sf::Time FPS;
      //   int drawnAlready = 0;
      //   bool m_bOnPause = true;
      //   sf::Clock clock;
      //   while (window.isOpen())
      //   {
      //      while (window.pollEvent(event))
      //      {
      //         if (event.type == sf::Event::Closed)
      //            window.close();
      //         if (event.type == sf::Event::MouseButtonPressed && m_bOnPause)
      //         {
      //            int x, y;
      //            x = (int)event.mouseButton.x / size;
      //            y = (int)event.mouseButton.y / size;
      //            curGame.push_cell(x, y);
      //         }
      //         if (event.type == sf::Event::KeyPressed)
      //         {
      //            if (event.key.code == sf::Keyboard::Space) m_bOnPause = !m_bOnPause;
      //            //   if (event.key.code==sf::Keyboard::Backspace)
      //            //   {
      //            //      m_bOnPause=1;
      //            //       curGame.Clear();
      //            //   };

      //         }

      //      };
      //      FPS = clock.getElapsedTime();

      //      if (FPS>sf::milliseconds(16))
      //      {
      //         if (drawnAlready)
      //         {
      //            if (!m_bOnPause&&FPS != sf::milliseconds(0))std::cout << 1 / FPS.asSeconds() << std::endl;
      //            if (!m_bOnPause)  curGame.Update();
      //         }
      //         else
      //         {
      //            drawnAlready = 1;
      //            curGame.Clear();
      //         }
      //         window.clear();
      //         curGame.Draw(&window);

      //         clock.restart();
      //      }
      //      window.display();


      return true;

   }


   void game::clear()
   {

      for (int i = 0; i < m_iAmount; i++)
      {
         for (int j = 0; j < m_iAmount; j++)
         {

            m_field[i][j].m_rect = ::rect_dim(i * m_iCellSize, j * m_iCellSize, m_iCellSize, m_iCellSize);

            m_field[i][j].m_chColor = 255;

            m_cells[i][j].m_iStep = 0;

            m_cells[i][j].setState(0);



         }

      }
   }

   void game::on_new_game()
   {

      m_bOnPause = true;


   }


   //void game::update()
   //{

   //   auto uncheckedCells = m_cellptraAlive;

   //   array < cell * > dyingCells;

   //   m_iStep++;

   //   m_cellptraAlive.remove_all();

   //   while (!uncheckedCells.empty())
   //   {

   //      cell * pcell = uncheckedCells.pop();

   //      if (pcell->is_alive())
   //      {

   //         pcell->resetNeighbours();

   //         for (int i = -1; i <= 1; i++)
   //         {

   //            for (int j = -1; j <= 1; j++)
   //            {

   //               if ((i != 0 || j != 0) && i + pcell->x >= 0 && j + pcell->y >= 0 && i + pcell->x<m_iAmount && j + pcell->y<m_iAmount)
   //               {

   //                  cell * pcellCur = &m_cells[pcell->x + i][pcell->y + j];

   //                  if (pcellCur->is_alive())
   //                  {

   //                     pcell->add_neighbour();

   //                  }
   //                  else if (pcellCur->get_step() != this->m_iStep)
   //                  {

   //                     uncheckedCells.add(pcellCur);

   //                  }

   //               }

   //            }

   //         }

   //         if (pcell->getNeighbours() < 2 || pcell->getNeighbours() > 3)
   //         {

   //            dyingCells.add(pcell);

   //         }
   //         else
   //         {

   //            m_cellptraAlive.add(pcell);

   //         }

   //         pcell->update_step(m_iStep);

   //         pcell->resetNeighbours();

   //      }
   //      else
   //      {

   //         pcell->resetNeighbours();

   //         for (int i = -1; i <= 1; i++)
   //         {

   //            for (int j = -1; j <= 1; j++)
   //            {

   //               if ((i != 0 || j != 0) && i + pcell->x >= 0 && j + pcell->y >= 0 && i + pcell->x < m_iAmount && j + pcell->y < m_iAmount)
   //               {

   //                  if (m_cells[pcell->x + i][pcell->y + j].is_alive())
   //                  {

   //                     pcell->add_neighbour();

   //                  }

   //               }
   //            }

   //         }

   //         if (pcell->getNeighbours()>2)
   //         {

   //            this->m_cellptraAlive.push_back(pcell);

   //         }

   //         pcell->update_step(m_iStep);

   //         pcell->resetNeighbours();

   //      }

   //   }

   //   for (auto & cell : m_cellptraAlive)
   //   {

   //      cell->set_state(1);

   //   }

   //   for (auto & cell : dyingCells)
   //   {

   //      cell->set_state(0);

   //   }

   //}


   point game::point_to_cell(point pt)
   {

      return point(pt.x / m_iCellSize, pt.y / m_iCellSize);

   }
   ::file::path game::get_file_path()
   {

      ::file::path path = ::dir::appdata() / "gamestate.dat";

      return path;


   }


   void game::on_key_down(::user::e_key ekey)
   {

      if (ekey == ::user::key_space)
      {

         m_bOnPause = !m_bOnPause;

      }
      else if (ekey == ::user::key_delete)
      {

         clear();

      }

   }


   void game::mouse_down(point pt)
   {

      if (m_bOnPause)
      {

         point ptCell = point_to_cell(pt);

         push_cell(ptCell.x, ptCell.y);

      }

   }


} // namespace game_of_life