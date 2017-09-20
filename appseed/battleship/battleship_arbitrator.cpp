#include "framework.h"


namespace tictactoe
{


   arbitrator::arbitrator(::aura::application * papp):
      object(papp),
      m_board(papp),
      m_evReady(papp)
   {

      m_dwBreaker = 0;

      m_bRun = true;

      m_bEndOnFull = true;

   }


   arbitrator::~arbitrator()
   {


   }


   void arbitrator::launch(player * pplayerX,player * pplayerO,bool bXFirst)
   {

      ::fork(get_app(),[=]()
         {

            arbitrate(pplayerX,pplayerO,bXFirst);

         }
      );

   }


   e_check arbitrator::arbitrate(player * pplayerX,player * pplayerO, bool bXFirst)
   {

      m_board.reset();

      m_bRun = true;

      m_pplayerX = pplayerX;

      m_pplayerO = pplayerO;

      m_pplayerX->m_parbitrator = this;

      m_pplayerO->m_parbitrator = this;

      e_check echeckPlayer  = bXFirst ? check_x : check_o;

      point pt;

      while(m_bRun)
      {

         player * pplayerCurrent = get_player(echeckPlayer);

         m_pplayerX->m_echeck = check_x;

         do
         {

            m_evReady.ResetEvent();

            {

               single_lock sl(&m_evReady);

               pplayerCurrent->play();

               sl.lock();

            }

            if(!m_bRun)
               return check_none;



         } while(m_board.is_free(pplayerCurrent->m_ptLast.x,pplayerCurrent->m_ptLast.y));

         if(!m_bRun)
            return check_none;

         Sleep(m_dwBreaker);


         if(!m_bRun)
            return check_none;

         m_board[pplayerCurrent->m_ptLast.x][pplayerCurrent->m_ptLast.y] = echeckPlayer;

         e_check echeck = check_winner();

         if(m_bEndOnFull)
         {

            if(m_board.is_full())
               return echeck;

         }
         else
         {
            
            if(echeck != check_none)
               return echeck;

         }

         echeckPlayer = toggle(echeckPlayer);

      }
      
      return check_none;

   }


   e_check arbitrator::check_winner()
   {

      e_check echeck = m_board.match();

      if(echeck != check_none)
         return echeck;

      if(m_board.is_full())
         return check_draw;

      return check_none;


   }

   
   player * arbitrator::get_player(e_check echeck)
   {

      if(echeck == check_x)
      {
         
         return m_pplayerX;

      }
      else
      {

         return m_pplayerO;

      }

   }


   void arbitrator::post_stop()
   {

      m_bRun = false;

      m_evReady.SetEvent();

      Sleep(100);

   }


} // namespace tictactoe



