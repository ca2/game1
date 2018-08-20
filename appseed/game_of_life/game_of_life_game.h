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


#pragma once


#define WINDOWSIZE 600



namespace game_of_life
{

   enum e_state : char
   {
      
      state_hatching,
      state_surviving,
      state_dying,
      state_dying2,
      state_dying3,
      state_dying4,
      state_dead,

   };

   class cell//is meant to be a part of two-dimensional array, looks like i'm retarded
   {
   public:
      char m_iAliveNeighbours = 0;
      char m_chState = 0;
      e_state m_estate = state_dead;
      short x;
      short y;
      int m_iStep = 0;


      void updateStep(int iStep) { this->m_iStep = iStep; };
      int getStep() { return this->m_iStep; }
      void setState(char st);
      char isAlive();
      void addNeighbour();
      void resetNeighbours();
      char getNeighbours();


   };

   class CLASS_DECL_GAME_GAME_OF_LIFE game :
      virtual public ::estamira::game
   {
   public:
      
      bool     m_bProper;
      
      int      m_iDying;
      int m_iGameMaxSize;
      array<cell*> m_aliveCells;
      array<cell*> m_dyingCells;
      array<cell> m_cells;
      int m_iAmount;
      int m_iCellSize;
      int m_iStep = 0;
      int m_iWindowSize;
      sp(::thread)            m_pthread;
      bool m_bOnPause;

      game(::aura::application * papp);
      virtual ~game();

      void destroy();
      virtual void mouse_down(point pt) override;
      virtual void on_key_down(::user::e_key ekey) override;
      point point_to_cell(point pt);
      virtual bool start(::user::impact * pview) override;

      virtual void on_new_game() override;

      virtual void load() override;
      virtual void save() override;

      ::file::path get_file_path();
      void clear();
      void set_amount(int amount, bool bSave = true);
      void update();
      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;
      void push_cell(unsigned int x, unsigned int y);
      cell * get_cell(unsigned int x, unsigned int y) { return &this->m_cells[x+ y *m_iGameMaxSize]; };
      rect get_rect(unsigned int x, unsigned int y) { return rect_dim(x * m_iCellSize, y * m_iCellSize, m_iCellSize, m_iCellSize); };

      virtual void io(stream & stream) override;

   };


} // namespace game_of_life




