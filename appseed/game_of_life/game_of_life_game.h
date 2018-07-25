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

#pragma once


#define WINDOWSIZE 600

template < typename TYPE >
class array2d :
   virtual public array < TYPE >
{
public:

   int m_iScan;

   array < TYPE > & operator [](index x)
   {

      return array < TYPE >(&m_pData[x * m_iScan], m_iScan);

   }


};


namespace game_of_life
{


   class RectangleShape
   {
   public:


      rect           m_rect;
      COLORREF       m_cr;


   };


   class cell //is meant to be a part of two-dimensional array, looks like i'm retarded (Prorock)
   {
   public:


      char              m_chAliveNeighbours;
      char              m_chState;
      RectangleShape *  m_prect;
      int               m_iStep;
//    point             m_pt;
      int               x;
      int               y;




      cell()
      {

         m_chAliveNeighbours = 0;
         m_chState = 0;
         m_iStep = 0;

      }


      void update_step(int iStep)
      {

         m_iStep = iStep;

      }


      int get_step()
      {

         return m_iStep;

      }


      void set_state(char chState)
      {

         COLORREF color = ARGB(255, 255, 255, 255);

         if (m_iStep != 0)
         {

            if (!m_chState)
            {

               if (chState)
               {

                  color = ARGB(255, 170, 20, 170);

               }

            }
            else
            {

               if (chState)
               {

                  color = ARGB(255, 0, 0, 0);

               }
               else
               {

                  color = ARGB(255, 30, 172, 20);

               }

            }

         }
         else
         {

            //if (st) color *= sf::Color(0, 0, 0);

            if (chState)
            {

               color = ARGB(255, 0, 0, 0);

            }

         }

         m_chState = chState;

         m_prect->m_cr = color;

      }


      char is_alive()
      {

         return m_chState != 0;

      }


      void add_neighbour()
      {

         m_chAliveNeighbours++;

      }


      void resetNeighbours()
      {

         m_chAliveNeighbours = 0;

      }


      char getNeighbours()
      {

         return m_chAliveNeighbours;

      }


      void set_rect(RectangleShape * pshape)
      {

         m_prect = pshape;

      }


      rect & get_rect()
      {

         return m_prect->m_rect;

      }


   };


   class CLASS_DECL_GAME_GAME_OF_LIFE game :
      virtual public ::estamira::game
   {
   public:



      array < cell * >        m_cellptraAlive;
      int                     m_iAmount;
      int                     m_iSize;
      int                     m_iStep;
      int                     m_iCellSize;
      bool                    m_bOnPause;
      RectangleShape **       m_field;
      cell **                 m_cells;


      game(::aura::application * papp);
      virtual ~game();


      void push_cell(unsigned int x, unsigned int y);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

      void initialize(int amount);

      virtual void mouse_down(point pt) override;

      point point_to_cell(point pt);
      cell * get_cell(unsigned int x, unsigned int y);
      void clear();
      void update();
      virtual bool start(::user::interaction * pui);

   };


} // namespace game_of_life



