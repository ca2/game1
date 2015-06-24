#include "framework.h"


namespace pacman
{

   void pacman::moveghosts()
   {
      // check for ghost mode changes
      if(m_player.super == SUPERMAX)
      {
         m_player.killcount = 0;
         for(int i = 0; i < 4; i++)
         {
            if(ghosts[i].mode != 'd')
               ghosts[i].color = ::console::BLUE;
            if(ghosts[i].mode == 's' || ghosts[i].mode == 'c')
               ghosts[i].mode = 'r';
         }
         showall();
      }
      if(m_player.left == 235 && ghosts[PINKY].mode == 'w')
         ghosts[PINKY].mode = 'e';
      if(m_player.left == 200 && ghosts[INKY].mode == 'w')
         ghosts[INKY].mode = 'e';
      if(m_player.left == 165 && ghosts[CLYDE].mode == 'w')
         ghosts[CLYDE].mode = 'e';
      for(int i = 0; i < 4; i++)
         ghosts[i].move(m_player.y,m_player.x);
      showall();
      checkfordeath();
   }

   void pacman::updatetimers()
   {
      // handle super pacman
      if(m_player.super)
      {
         m_player.super--;
         if(m_player.super <= 112 && m_player.super % 28 == 0)
         {
            for(int i = 0; i < 4; i++)
               if(ghosts[i].color == ::console::BLUE)
                  ghosts[i].color = ::console::WHITE;
            showall();
         }
         if(m_player.super <= 98 && (m_player.super + 14) % 28 == 0)
         {
            for(int i = 0; i < 4; i++)
               if(ghosts[i].color == ::console:: WHITE && ghosts[i].mode != 'd' && ghosts[i].mode != 'n')
                  ghosts[i].color = ::console::BLUE;
            showall();
         }
         if(!m_player.super)
         {
            for(int i = 0; i < 4; i++)
            {
               if(ghosts[i].mode != 'd' && ghosts[i].mode != 'n')
                  ghosts[i].color = ghosts[i].colorinit;
               if(ghosts[i].mode == 'r')
               {
                  ghosts[i].modeold = ghosts[i].mode;
                  ghosts[i].mode = 'c';
               }
            }
            showall();
         }
      }
      // handle flashing 1UP
      if(oneuptimer)
         oneuptimer--;
      else
      {
         if(oneupcolor == ::console::WHITE)
            oneupcolor = ::console::BLACK;
         else
            oneupcolor = ::console::WHITE;
         SetTextColor(oneupcolor);
         SetCursorPosition(-3,3);
         cout << "1UP";
         oneuptimer = ONEUPMAX;
      }
      // handle flashing super pellets
      if(pellettimer)
         pellettimer--;
      else
      {
         if(pelletcolor == ::console::WHITE)
            pelletcolor = ::console::BLACK;
         else
            pelletcolor = ::console::WHITE;
         SetTextColor(pelletcolor);
         for(int i = 0; i < 4; i++)
            pellets[i].print();
         showall();
         pellettimer = PELLETMAX;
      }
      // handle ghost chase/scatter mode
      if(ghostmode)
      {
         ghostmode--;
         if(ghostmode == MODEMAX / 4)
            for(int i = 0; i < 4; i++)
               if(ghosts[i].mode == 'c')
                  ghosts[i].mode = 's';
      }
      else
      {
         for(int i = 0; i < 4; i++)
            if(ghosts[i].mode == 's')
               ghosts[i].mode = 'c';
         ghostmode = MODEMAX;
      }
      Sleep(15);
   }

   void pacman::checkfordeath()
   {
      for(int i = 0; i < 4; i++)
         if(m_player.x == ghosts[i].x && m_player.y == ghosts[i].y && ghosts[i].mode != 'd' && ghosts[i].mode != 'n')
         {
            if(ghosts[i].mode != 'r')
               m_player.dead();
            else
            {
               m_player.printkillscore();
               ghosts[i].dead();
            }
         }
   }

   void pacman::showall()
   {
      m_player.show();
      for(int i = 0; i < 4; i++)
         ghosts[i].show();
   }

   void pacman::hideall()
   {
      m_player.hide();
      for(int i = 0; i < 4; i++)
         ghosts[i].hide();
   }

   void pacman::initall()
   {
      m_player.y = m_player.yinit;
      m_player.x = m_player.xinit;
      m_player.color = ::console::YELLOW;
      m_player.icon = ICONS[1];
      m_player.dirold = 'a';
      m_player.wait = 0;
      m_player.super = 0;
      for(int i = 0; i < 4; i++)
      {
         ghosts[i].y = ghosts[i].yinit;
         ghosts[i].x = ghosts[i].xinit;
         ghosts[i].color = ghosts[i].colorinit;
         ghosts[i].mode = 'w';
         ghosts[i].wait = 0;
      }
      ghosts[BLINKY].mode = 'c';
      ghosts[BLINKY].modeold = 'c';
      if(m_player.left <= 235)
         ghosts[PINKY].mode = 'e';
      if(m_player.left <= 200)
         ghosts[INKY].mode = 'e';
      if(m_player.left <= 165)
         ghosts[CLYDE].mode = 'e';
   }


} // namespace pacman




