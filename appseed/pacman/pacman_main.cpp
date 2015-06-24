#include "framework.h"


namespace  pacman
{

   //int main()
   int pacman::run()
   {
      srand(time(0));
      m_psound = new ::pacman::sound(get_app());
//      SetConsoleTitle("PAC++MAN");
      SetWindowSize(LEVELHEIGHT + 4,LEVELWIDTH);
      SetCursorVisibility(false);
      m_player.hiscore = 0;
      mainloop();
      delete m_p;
      return 0;
   }

   void pacman::mainloop()
   {
      m_player.score = 0;
      m_player.lives = 3;
      for(int levelnum = 1; levelnum <= 255 && m_bRun; levelnum++)
      {
         loadlevel();
         // while there are still dots on the screen,
         while(m_player.left != 0 && m_bRun)
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



