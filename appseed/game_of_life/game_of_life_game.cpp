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


   game::game(::aura::application * papp) :
      object(papp),
      ::estamira::game(papp)
   {

      m_bOnPause = true;

   }


   game::~game()
   {

      for (int i = 0; i<m_iAmount; i++)
      {

         delete[] m_field[i];

         delete[] m_cells[i];

      }

      delete[] m_field;

      delete[] m_cells;

   }


   void game::push_cell(unsigned int x, unsigned int y)
   {
      if (!m_cells[x][y].is_alive())
      {
         m_cellptraAlive.push_back(&m_cells[x][y]);
         m_cells[x][y].set_state(1);
      }
      else
      {
         int i = 0;
         for (auto it = m_cellptraAlive.begin(); it<this->m_cellptraAlive.end();  i++)
         {
            if (m_cellptraAlive[i]->x == x && m_cellptraAlive[i]->y == y)
            {
               it = m_cellptraAlive.erase(it);
            }
            else
            {
               it++;
            }
         };
         m_cells[x][y].set_state(0);
      }
   }


   cell * game::get_cell(unsigned int x, unsigned int y)
   {
      return &m_cells[x][y];
   }



   void game::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      for (int i = 0; i < m_iAmount; i++)
      {

         for (int j = 0; j < m_iAmount; j++)
         {

            pgraphics->fill_solid_rect(m_field[i][j].m_rect, m_field[i][j].m_cr);

         }

      }

   }


   void game::initialize(int iAmount)
   {

      m_iAmount = iAmount;

      m_iSize = WINDOWSIZE / iAmount;

      m_field = new RectangleShape*[iAmount];

      m_cells = new cell*[iAmount];

      for (int i = 0; i < iAmount; i++)
      {

         m_field[i] = new RectangleShape[iAmount];

         m_cells[i] = new cell[iAmount];

         for (int j = 0; j < iAmount; j++)
         {

            m_cells[i][j].set_rect(&m_field[i][j]);

            m_cells[i][j].x = i;

            m_cells[i][j].y = j;

         }
      }

      clear();

   }




   bool game::start(::user::interaction * pui)
   {

      if (!::estamira::game::start(pui))
      {

         return false;

      }

      //   sf::ContextSettings settings;
      // settings.antialiasingLevel = 0;
      //sf::RenderWindow window(sf::VideoMode(WINDOWSIZE, WINDOWSIZE), "Life", sf::Style::Titlebar | sf::Style::Close, settings);
      //window.setKeyRepeatEnabled(false);
      //sf::Event event;
      //int amount = 150;
      //window.clear(sf::Color::Blue);
      int amount = 150;
      m_iCellSize = WINDOWSIZE / amount;
      initialize(amount);


      fork([&]()
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
            Sleep(100);
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
      //   sf::RenderWindow window(sf::VideoMode(WINDOWSIZE, WINDOWSIZE), "Life", sf::Style::Titlebar | sf::Style::Close, settings);
      //   window.setKeyRepeatEnabled(false);
      //   sf::Event event;
      //   int amount = 150;
      //   window.clear(sf::Color::Blue);
      //   int size = WINDOWSIZE / amount;
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

      //cell.setFillColor(sf::Color(255, 255, 255));
      //if (size>1) cell.setOutlineThickness(-0.5);
      //cell.setOutlineColor(sf::Color(0, 0, 0));
      for (int i = 0; i < m_iAmount; i++)
      {
         for (int j = 0; j < m_iAmount; j++)
         {

            m_field[i][j].m_rect = ::rect_dim(i * m_iSize, j * m_iSize, m_iSize, m_iSize);

            m_field[i][j].m_cr = ARGB(255, 255, 255, 255);

            m_cells[i][j].set_state(0);

         }

      }

   }


   void game::update()
   {

      auto uncheckedCells = m_cellptraAlive;

      array < cell * > dyingCells;

      m_iStep++;

      m_cellptraAlive.remove_all();

      while (!uncheckedCells.empty())
      {

         cell * pcell = uncheckedCells.pop();

         if (pcell->is_alive())
         {

            pcell->resetNeighbours();

            for (int i = -1; i <= 1; i++)
            {

               for (int j = -1; j <= 1; j++)
               {

                  if ((i != 0 || j != 0) && i + pcell->x >= 0 && j + pcell->y >= 0 && i + pcell->x<m_iAmount && j + pcell->y<m_iAmount)
                  {

                     cell * pcellCur = &m_cells[pcell->x + i][pcell->y + j];

                     if (pcellCur->is_alive())
                     {

                        pcell->add_neighbour();

                     }
                     else if (pcellCur->get_step() != this->m_iStep)
                     {

                        uncheckedCells.add(pcellCur);

                     }

                  }

               }

            }

            if (pcell->getNeighbours() < 2 || pcell->getNeighbours() > 3)
            {

               dyingCells.add(pcell);

            }
            else
            {

               m_cellptraAlive.add(pcell);

            }

            pcell->update_step(m_iStep);

            pcell->resetNeighbours();

         }
         else
         {

            pcell->resetNeighbours();

            for (int i = -1; i <= 1; i++)
            {

               for (int j = -1; j <= 1; j++)
               {

                  if ((i != 0 || j != 0) && i + pcell->x >= 0 && j + pcell->y >= 0 && i + pcell->x < m_iAmount && j + pcell->y < m_iAmount)
                  {

                     if (m_cells[pcell->x + i][pcell->y + j].is_alive())
                     {

                        pcell->add_neighbour();

                     }

                  }
               }

            }

            if (pcell->getNeighbours()>2)
            {

               this->m_cellptraAlive.push_back(pcell);

            }

            pcell->update_step(m_iStep);

            pcell->resetNeighbours();

         }

      }

      for(auto & cell : m_cellptraAlive)
      {

         cell->set_state(1);

      }

      for(auto & cell : dyingCells)
      {

         cell->set_state(0);

      }

   }


   point game::point_to_cell(point pt)
   {

      return point(pt.x/ m_iSize, pt.y/m_iSize);

   }

   void game::mouse_down(point pt)
   {

      point ptCell = point_to_cell(pt);

      push_cell(ptCell.x, ptCell.y);



   }



} // namespace game_of_life



