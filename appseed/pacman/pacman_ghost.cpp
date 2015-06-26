#include "framework.h"


namespace pacman
{


   ghost::ghost(pacman * ppacman):
      console_composite(ppacman->m_p),
      level(ppacman->level),
      m_ppacman(ppacman)
   {

   }

   // move the ghost based on the current mode every time the wait timer reaches 0
   void ghost::move(int playery,int playerx)
   {
      if(wait)
         wait--;
      else
      {
         switch(mode)
         {
            // if 'waiting'
            // bounce up and down
         case 'w':
         {
            hide();
            if(y == GATEY + 2)
               y++;
            else
               y--;
            show();
            wait = GHOSTMAX;
            break;
         }
         // if 'exiting'
         // make a path to get out of the gate
         // after exiting the gate if the player is super pacman, 'run'
         // otherwise, 'chase'
         case 'e':
         {
            hide();
            wait = GHOSTMAX;
            if(y > GATEY + 1)
               y--;
            else if(x < GATEX)
               x++;
            else if(x > GATEX)
               x--;
            else if(y != GATEY - 1)
            {
               y--;
               _008SetCursorPos(GATEY + 3,GATEX + 1);
               cout << level[GATEY][GATEX + 1];
            }
            else
            {
               modeold = mode;
               if(color == ::console::BLUE)
                  mode = 'r';
               else
                  mode = 'c';
               dirold = 'w';
               wait = 0;
            }
            show();
            break;
         }
         // if 'entering'
         // enter the ghost house, then 'exit'
         case 'n':
         {
            if(y != GATEY + 1)
            {
               dir = 's';
               changecoords();
               _008SetCursorPos(GATEY + 3,GATEX + 1);
               cout << level[GATEY][GATEX + 1];
               wait = DEADMAX;
            }
            else
            {
               color = colorinit;
               mode = 'e';
               wait = GHOSTMAX;
            }
            break;
         }
         // if 'scattering'
         // move in a random direction
         case 's':
         {
            getopposite();
            if(modeold == 'e')
               modeold = mode;
            if(mode != modeold)
            {
               dir = diropp;
               changecoords();
               modeold = mode;
            }
            else
               randomdirection();
            dirold = dir;
            wait = GHOSTMAX;
            break;
         }
         // if 'chasing'
         // target the player
         case 'c':
         {
            getopposite();
            if(modeold == 'e')
               modeold = mode;
            if(mode != modeold)
            {
               dir = diropp;
               changecoords();
               modeold = mode;
            }
            else
            {
               down = y < playery;
               up = y > playery;
               right = x < playerx;
               left = x > playerx;
               targetobject();
            }
            dirold = dir;
            wait = GHOSTMAX;
            break;
         }
         // if 'running'
         // avoid the player
         case 'r':
         {
            getopposite();
            if(modeold == 'e')
               modeold = mode;
            if(mode != modeold)
            {
               dir = diropp;
               changecoords();
               modeold = mode;
            }
            else
            {
               down = !(y < playery);
               up = !(y > playery);
               right = !(x < playerx);
               left = !(x > playerx);
               targetobject();
            }
            dirold = dir;
            wait = RUNMAX;
            break;
         }
         // if 'dead'
         // target the ghost house gate
         // when the gate is reached, 'enter'
         case 'd':
         {
            getopposite();
            if(y != GATEY - 1 || x != GATEX)
            {
               down = y < GATEY - 1;
               up = y > GATEY - 1;
               right = x < GATEX;
               left = x > GATEX;
               targetobject();
            }
            else
               mode = 'n';
            dirold = dir;
            wait = DEADMAX;
         }
         }
      }
   }

   void ghost::targetobject()
   {
      int good = 0;
      char gooddirs[4] ={' ',' ',' ',' '};
      bool favorabledirs[4] ={up,left,down,right};
      for(int i = 0; i < 4; i++)
      {
         dir = ALLDIRS[i];
         if(favorabledirs[i] && testforcollision() == false && dir != diropp)
         {
            gooddirs[good] = dir;
            good++;
         }
      }
      if(good == 0)
         randomdirection();
      else
      {
         dir = gooddirs[rand() % good];
         changecoords();
      }
   }

   void ghost::randomdirection()
   {
      getopposite();
      // pick a random direction that results in no collision
      do
      {
         // pick a randon direction that is not opposite of the previous direction
         do
         {
            dir = ALLDIRS[rand() % 4];
         } while(dir == diropp);
      } while(testforcollision() == true);
      changecoords();
   }

   bool ghost::testforcollision()
   {
      // if the character in front of the ghost is a space, move in the appropriate direction
      switch(dir)
      {
      case 'a':
      {
         // if travelling through the tunnel
         if(x == 0 || strchr(NOCOLLISIONTILES,level[y][x - 1]))
            return false;
         break;
      }
      case 'd':
      {
         // if travelling through the tunnel
         if(x == LEVELWIDTH - 1 || strchr(NOCOLLISIONTILES,level[y][x + 1]))
            return false;
         break;
      }
      case 'w':
      {
         if(strchr(NOCOLLISIONTILES,level[y - 1][x]))
            return false;
         break;
      }
      case 's':
      {
         if(strchr(NOCOLLISIONTILES,level[y + 1][x]))
            return false;
         break;
      }
      }
      return true;
   }

   void ghost::changecoords()
   {
      hide();
      if(dir == 'a')
      {
         if(x == 0)
            x = LEVELWIDTH - 1;
         else
            x--;
      }
      if(dir == 'd')
      {
         if(x == LEVELWIDTH - 1)
            x = 0;
         else
            x++;
      }
      if(dir == 'w')
         y--;
      if(dir == 's')
         y++;
      show();
   }

   void ghost::getopposite()
   {
      if(dirold == 'a')
         diropp = 'd';
      if(dirold == 'd')
         diropp = 'a';
      if(dirold == 'w')
         diropp = 's';
      if(dirold == 's')
         diropp = 'w';
   }

   void ghost::dead()
   {
      color =::console::WHITE;
      modeold = mode;
      mode = 'd';
      m_ppacman->play_sound("wait:eatghost");
      Sleep(184);
   }

   void ghost::show()
   {
      SetTextColor(color);
      _008SetCursorPos(y,x);
      if(dynamic_cast <console *> (m_p) != NULL)
      {
         cout << char(150);
      }
      else
      {
         cout << 'M';
      }
      if(mode == 'd')
      {
         m_ppacman->play_sound("intermission");
      }
      else
      {
         synch_lock sl(&m_ppacman->m_psound->m_mutex);
         if(m_ppacman->m_psound->m_str == "intermission")
         {
            m_ppacman->play_sound("");
         }
      }
   }

   void ghost::hide()
   {
      SetTextColor(::console::WHITE);
      if(level[y][x] == 'o')
         SetTextColor(m_ppacman->pelletcolor);
      _008SetCursorPos(y,x);
      cout << level[y][x];
   }


} // namespace pacman




