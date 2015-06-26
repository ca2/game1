#include "framework.h"

char levelmap[LEVELHEIGHT][LEVELWIDTH + 1] =
{
"1555555555555~~5555555555552",
"6............^^............6",
"6.!%%@.!%%%@.^^.!%%%@.!%%@.6",
"67^  ^.^   ^.^^.^   ^.^  ^86",
"6.#%%$.#%%%$.#$.#%%%$.#%%$.6",
"6..........................6",
"6.!%%@.!@.!%%%%%%@.!@.!%%@.6",
"6.#%%$.^^.#%%@!%%$.^^.#%%$.6",
"6......^^....^^....^^......6",
"355552.^#%%@ ^^ !%%$^.155554",
"     6.^!%%$ #$ #%%@^.6     ",
"     6.^^    B     ^^.6     ",
"     6.^^ 155&&552 ^^.6     ",
"555554.#$ 6      6 #$.355555",
"      .   6I   C 6   .      ",
"555552.!@ 6  P   6 !@.155555",
"     6.^^ 35555554 ^^.6     ",
"     6.^^          ^^.6     ",
"     6.^^ !%%%%%%@ ^^.6     ",
"155554.#$ #%%@!%%$ #$.355552",
"6............^^............6",
"6.!%%@.!%%%@.^^.!%%%@.!%%@.6",
"6.#%@^.#%%%$.#$.#%%%$.^!%$.6",
"69..^^.......X .......^^..06",
"[%@.^^.!@.!%%%%%%@.!@.^^.!%]",
"[%$.#$.^^.#%%@!%%$.^^.#$.#%]",
"6......^^....^^....^^......6",
"6.!%%%%$#%%@.^^.!%%$#%%%%@.6",
"6.#%%%%%%%%$.#$.#%%%%%%%%$.6",
"6..........................6",
"3555555555555555555555555554"
};

namespace pacman
{

   void pacman::loadlevel()
   {
//      synch_lock sl(&m_mutex);
      SetScreenColor(::console::BLACK);
      char curcharacter;
      SetTextColor(::console::WHITE);
      _008SetCursorPos(-3,3);
      cout << "1UP";
      _008SetCursorPos(-3,9);
      cout << "HIGH SCORE";
      m_player.scoreinc = 0;
      m_player.printscore();
      _008SetCursorPos(0,0);
      m_player.left = 0;
      for(int y = 0; y < LEVELHEIGHT; y++)
      {
         for(int x = 0; x < LEVELWIDTH; x++)
         {
            curcharacter = levelmap[y][x];
            SetTextColor(::console::DARKBLUE);
            switch(curcharacter)
            {
            case 'X':
            {
               m_player.yinit = y;
               m_player.xinit = x;
               level[y][x] = ' ';
               break;
            }
            case 'B':
            {
               ghosts[BLINKY].yinit = y;
               ghosts[BLINKY].xinit = x;
               ghosts[BLINKY].colorinit = ::console::RED;
               ghosts[BLINKY].diropp = 's';
               level[y][x] = ' ';
               break;
            }
            case 'P':
            {
               ghosts[PINKY].yinit = y;
               ghosts[PINKY].xinit = x;
               ghosts[PINKY].colorinit = ::console::MAGENTA;
               level[y][x] = ' ';
               break;
            }
            case 'I':
            {
               ghosts[INKY].yinit = y;
               ghosts[INKY].xinit = x;
               ghosts[INKY].colorinit = ::console::CYAN;
               level[y][x] = ' ';
               break;
            }
            case 'C':
            {
               ghosts[CLYDE].yinit = y;
               ghosts[CLYDE].xinit = x;
               ghosts[CLYDE].colorinit = ::console::YELLOW;
               level[y][x] = ' ';
               break;
            }
            case '7':
            {
               pellets[0].y = y;
               pellets[0].x = x;
               SetTextColor(::console::WHITE);
               level[y][x] = 'o';
               m_player.left++;
               break;
            }
            case '8':
            {
               pellets[1].y = y;
               pellets[1].x = x;
               SetTextColor(::console::WHITE);
               level[y][x] = 'o';
               m_player.left++;
               break;
            }
            case '9':
            {
               pellets[2].y = y;
               pellets[2].x = x;
               SetTextColor(::console::WHITE);
               level[y][x] = 'o';
               m_player.left++;
               break;
            }
            case '0':
            {
               pellets[3].y = y;
               pellets[3].x = x;
               SetTextColor(::console::WHITE);
               level[y][x] = 'o';
               m_player.left++;
               break;
            }
            case '.':
            {
               SetTextColor(::console::WHITE);
               level[y][x] = char(250);
               m_player.left++;
               break;
            }
            case ' ':
            {
               level[y][x] = curcharacter;
               break;
            }
            case '&':
            {
               SetTextColor(::console::WHITE);
               curcharacter = '%';
            }
            }
            if(curcharacter == '1')
               level[y][x] = char(201);
            else if(curcharacter == '2')
               level[y][x] = char(187);
            else if(curcharacter == '3')
               level[y][x] = char(200);
            else if(curcharacter == '4')
               level[y][x] = char(188);
            else if(curcharacter == '5')
               level[y][x] = char(205);
            else if(curcharacter == '6')
               level[y][x] = char(186);
            else if(curcharacter == '!')
               level[y][x] = char(218);
            else if(curcharacter == '@')
               level[y][x] = char(191);
            else if(curcharacter == '#')
               level[y][x] = char(192);
            else if(curcharacter == '$')
               level[y][x] = char(217);
            else if(curcharacter == '%')
               level[y][x] = char(196);
            else if(curcharacter == '^')
               level[y][x] = char(179);
            else if(curcharacter == '~')
               level[y][x] = char(209);
            else if(curcharacter == '[')
               level[y][x] = char(199);
            else if(curcharacter == ']')
               level[y][x] = char(182);
            cout << level[y][x];
         }
         _008SetCursorPos(y + 1,0);
      }
      play_sound("wait:beginning");
      initall();
      showall();
      m_player.printlives();
      Sleep(1984);
      printready();
      multi_lock ml({&m_evRestart,&m_psound->m_eventEnd});

      if(ml.lock(duration::infinite(), false).signaled_index() == 0)
      {
         throw ::pacman::restart();
      }
   }

   void pacman::nextlevel()
   {
      Sleep(1000);
      hideall();
      _008SetCursorPos(12,13);
      cout << "  ";
      for(int i = 0; i < 4; i++)
      {
         SetScreenColor(::console::WHITE,3);
         m_player.show();
         Sleep(200);
         SetScreenColor(::console::DARKBLUE,3);
         m_player.show();
         Sleep(200);
      }
      _008SetCursorPos(0,0);
      initall();
   }

   void pacman::printready()
   {
      SetTextColor(::console::YELLOW);
      _008SetCursorPos(17,11);
      cout << "READY!";
      Sleep(2000);
      _008SetCursorPos(17,11);
      cout << "      ";
   }

   void pacman::gameover()
   {
      play_sound("wait:death");
      _008SetCursorPos(17,9);
      SetTextColor(::console::RED);
      cout << "GAME  OVER";
      Sleep(1000);
      mainloop();
   }


} // namespace pacman





