#include "framework.h"
#include <math.h>


namespace pacman
{


   player::player(pacman * ppacman):
      ::console::window_composite(ppacman->m_p),level(ppacman->level),m_ppacman(ppacman)
   {

   }


   // check for user input every time the wait timer reaches 0
   void player::move()
   {
      if(wait)
      {
         show();
         wait--;
      }
      else
      {
         getdirection();
         if(testforcollision() == false)
         {
            // replace old coordinates with a space
            SetCursorPosition(yold,xold);
            cout << level[yold][xold];
            // if the player picked up a pellet
            if(level[y][x] != ' ')
            {
               if(level[y][x] == 'o')
               {
                  m_ppacman->play_sound("wait:eatfruit");
                  scoreinc = 50;
                  super = SUPERMAX;
               }
               else
               {
                  scoreinc = 10;
               }
               printscore();
               level[y][x] = ' ';
               left--;
            }
            show();
            dirold = dir;
            wait = PACMANMAX;
            m_ppacman->checkfordeath();
         }
         m_ppacman->play_sound("chomp");
         if(m_ppacman->m_evRestart.wait(millis(0)).signaled())
         {
            throw restart();
         }

      }
   }

   void player::getdirection()
   {
      dir = 'x';
      // check if the user has entered 'w', 'a', 's' or 'd'
      //if(_kbhit())
        // dir = tolower(_getch());
      dir = tolower(m_ppacman->get_char());
      // if not, try moving in the same direction as before
      if(!strchr(ALLDIRS,dir))
         dir = dirold;
   }

   bool player::testforcollision()
   {

      if(!testforcollision(dir))
      {
         return false;
      }
      if(!testforcollision(dirold))
      {
         dir = dirold;
         return false;
      }

      return true;

   }

   bool player::testforcollision(char d)
   {
      // save old coordinates
      xold = x;
      yold = y;
      // if the character in front of the player is a space, move in the appropriate direction
      switch(d)
      {
      case 'a':
      {
         // if travelling through the tunnel
         if(x == 0)
         {
            x = LEVELWIDTH - 1;
            icon = ICONS[1];
         }
         else if(strchr(NOCOLLISIONTILES,level[y][x - 1]))
         {
            x--;
            icon = ICONS[1];
         }
         break;
      }
      case 'd':
      {
         // if travelling through the tunnel
         if(x == LEVELWIDTH - 1)
         {
            x = 0;
            icon = ICONS[3];
         }
         else if(strchr(NOCOLLISIONTILES,level[y][x + 1]))
         {
            x++;
            icon = ICONS[3];
         }
         break;
      }
      case 'w':
      {
         if(strchr(NOCOLLISIONTILES,level[y - 1][x]))
         {
            y--;
            icon = ICONS[0];
         }
         break;
      }
      case 's':
      {
         if(strchr(NOCOLLISIONTILES,level[y + 1][x]))
         {
            y++;
            icon = ICONS[2];
         }
      }
      }
      // if coordinates were not changed, there was a collision
      if(x == xold && y == yold)
         return true;
      return false;
   }

   void player::printscore()
   {
      // gain a life every time the score crosses a multiple of 10000
      if(score / 10000 < (score + scoreinc) / 10000)
      {
         lives++;
         printlives();
      }
      score += scoreinc;
      SetTextColor(::console::WHITE);
      SetCursorPosition(-2,0);
      string str;
      if(score == 0)
      {
         str.Format("%7d",0);
         //cout << setw(7) << "00";
         cout << str;
      }
      else
      {
         str.Format("%7d",score);
         //cout << setw(7) << score;
         cout << str;
      }
      if(score > hiscore)
      {
         hiscore = score;
         //cout << setw(11) << hiscore;
         str.Format("%11d",hiscore);
         cout << str;
      }
   }

   void player::printlives()
   {
      SetTextColor(color);
      SetCursorPosition(LEVELHEIGHT,2);
      for(int i = 1; i < lives; i++)
         cout << ICONS[1] << " ";
      cout << " ";
   }

   void player::printkillscore()
   {
      killcount++;
      scoreinc = 200 * pow(2.0,killcount - 1);
      int length = floor(log10((double) scoreinc)) + 1;
      int killx = x - 1;
      if(x == 0)
         killx = x;
      if(x > LEVELWIDTH - length)
         killx = LEVELWIDTH - length;
      SetTextColor(::console::CYAN);
      SetCursorPosition(y,killx);
      cout << scoreinc;
      printscore();
      Sleep(750);
      SetCursorPosition(y,killx);
      for(int i = killx; i < killx + length; i++)
      {
         SetTextColor(::console::DARKBLUE);
         if(level[y][i] == char(250))
            SetTextColor(::console::WHITE);
         if(level[y][i] == 'o')
            SetTextColor(m_ppacman->pelletcolor);
         cout << level[y][i];
      }
      show();
   }

   void player::dead()
   {
      //Sleep(284);
      m_ppacman->play_sound("wait:death");
      m_ppacman->hideall();
      if(dynamic_cast <console *> (m_p) != NULL)
      {
         const char ICONS_DEAD2[3]   ={'*', 'v','\''};
         for(int i = 0; i < 3; i++)
         {
            icon = ICONS_DEAD2[i];
            show();
            Sleep(384);
         }

      }
      else
      {
         //Sleep(1000);
         for(int i = 0; i < 10; i++)
         {
            icon = ICONS[i % 4];
            show();
            Sleep(100);
         }
      }
      hide();
      Sleep(500);
      lives--;
      if(lives != 0)
      {
         m_ppacman->initall();
         m_ppacman->showall();
         printlives();
         dirold = 'a';
         m_ppacman->printready();
         m_ppacman->m_psound->m_eventEnd.wait();
      }
      else
         m_ppacman->gameover();
   }

   void player::show()
   {
      SetTextColor(color);
      SetCursorPosition(y,x);
      if(wait >= PACMANMAX / 2)
      {
         cout << '*';
      }
      else
      {
         cout << icon;
      }
   }

   void player::hide()
   {
      SetCursorPosition(y,x);
      cout << level[y][x];
   }



} // namespace player




