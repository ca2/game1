#include "framework.h"


namespace  pacman
{


   void pacman::run()
   {
start:
      try
      {
         srand((unsigned int) time(0));
         //      SetConsoleTitle("PAC++MAN");
         SetWindowSize(LEVELHEIGHT + 4,LEVELWIDTH);
         SetCursorVisibility(false);
         m_player.hiscore = 0;
         m_evRestart.ResetEvent();
         mainloop();
      }
      catch(::pacman::restart *p )
      {
         esp671 esp(p);
         goto start;
      }
      delete m_p;

   }

   void pacman::restart()
   {
      m_evRestart.SetEvent();
   }

   void pacman::mainloop()
   {
      m_player.score = 0;
      m_player.lives = 3;
      for(int levelnum = 1; levelnum <= 255 && thread_get_run(); levelnum++)
      {
         loadlevel();
         // while there are still dots on the screen,
         while(m_player.left != 0 && thread_get_run())
         {
            {
//               synch_lock sl(&m_mutex);
               m_player.move();
               moveghosts();
            }
            updatetimers();
         }
         nextlevel();
      }
   }


} // namespace pacman



