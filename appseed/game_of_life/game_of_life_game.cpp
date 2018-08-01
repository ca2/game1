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


   void cell::setState(char st)
   {
      m_chState = st;
      //int color = 255 * (1 - st);
      //      m_chColor = color;
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


   game::game(::aura::application * papp) :
      object(papp),
      ::estamira::game(papp)
   {

      m_iGameMaxSize = 600;



      m_cells.set_size(m_iGameMaxSize * m_iGameMaxSize);

      set_amount(m_iGameMaxSize, false);

      clear();

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



   }

   void game::io(stream & stream)
   {

      //stream(m_iGameMaxSize);
      stream(m_iAmount);
      stream(m_iStep);

      try
      {
         if (is_storing())
         {
            stream.write(m_cells.get_data(), sizeof(cell) *m_cells.size());
         }
         else
         {
            stream.read(m_cells.get_data(), sizeof(cell) *m_cells.size());

         }


      }
      catch (...)
      {

      }

      if (!stream.is_storing())
      {

         set_amount(m_iAmount, false);

      }

      for(index i = 0; i < m_iAmount; i++)
      {
         for (index j = 0; j < m_iAmount; j++)
         {

            if(get_cell(i, j)->isAlive())
            {
               m_aliveCells.add(get_cell(i, j));
            }

         }
      }

   }




   void game::update()
   {
      synch_lock sl(m_pmutex);
      array<cell*> uncheckedCells = m_aliveCells;
      array<cell*> dyingCells;
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

                     ::game_of_life::cell* curCell = get_cell(cell->x + i, cell->y + j);

                     if (curCell->isAlive())
                     {
                        cell->addNeighbour();
                     }
                     else if (curCell->getStep() != m_iStep)
                     {
                        uncheckedCells.push_back(curCell);
                     }
                  }
               }
            }
            if (cell->getNeighbours() < 2 || cell->getNeighbours() > 3)
            {
               dyingCells.push_back(cell);
            }
            else
            {
               m_aliveCells.push_back(cell);
            }
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
                  if ((i != 0 || j != 0) && i + cell->x >= 0 && j + cell->y >= 0 && i + cell->x < m_iAmount && j + cell->y < m_iAmount)
                  {
                     if (get_cell(cell->x + i, cell->y + j)->isAlive())
                     {
                        cell->addNeighbour();
                     }
                  }
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
            rect r = get_rect(i,j);
            r.deflate(1, 1, 0, 0);
            char chColor = 255 * (1 - get_cell(i, j)->m_chState);
            pgraphics->fill_solid_rect(r, ARGB(255, chColor, chColor, chColor));

         }

      }

   }


   void game::push_cell(unsigned int x, unsigned int y)
   {
      if (!get_cell(x, y)->isAlive())
      {
         m_aliveCells.add(get_cell(x, y));
         get_cell(x, y)->setState(1);
      }
      else
      {
         int i = 0;
         for (auto it = m_aliveCells.begin(); it < m_aliveCells.end(); it++, i++)
         {
            if (m_aliveCells[i]->x == x && m_aliveCells[i]->y == y)
               m_aliveCells.erase(it);
         };
         get_cell(x, y)->setState(0);
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




      return true;

   }


   void game::clear()
   {

      for (int i = 0; i < m_iAmount; i++)
      {
         for (int j = 0; j < m_iAmount; j++)
         {

            get_cell(i, j)->m_iStep = 0;

            get_cell(i, j)->setState(0);

            get_cell(i, j)->x = i;

            get_cell(i, j)->y = j;

         }

      }
   }


   void game::on_new_game()
   {

      m_bOnPause = true;


   }




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

         synch_lock sl(m_pmutex);

         m_bOnPause = !m_bOnPause;

         if (!m_bOnPause)
         {
            for (int i = 0; i < m_iAmount; i++)
            {
               for (int j = 0; j < m_iAmount; j++)
               {

                  get_cell(i, j)->m_iStep = 0;

               }

            }
            m_iStep = 0;
         }

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