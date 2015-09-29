#include "framework.h"


namespace tictactoe
{


   arbitrator::arbitrator(::aura::application * papp):
      object(papp),
      m_board(papp),
      m_evReady(papp)
   {

      m_dwBreaker = 984;

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

      m_pplayerX = pplayerX;

      m_pplayerO = pplayerO;

      m_pplayerX->m_parbitrator = this;

      m_pplayerO->m_parbitrator = this;

      e_check echeckPlayer  = bXFirst ? check_x : check_o;

      point pt;

      while(true)
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


         } while(m_board.is_free(pplayerCurrent->m_ptLast.x,pplayerCurrent->m_ptLast.y));


         Sleep(m_dwBreaker);

         m_board[pplayerCurrent->m_ptLast.x][pplayerCurrent->m_ptLast.y] = echeckPlayer;

         e_check echeck = check_winner();

         if(echeck != check_none)
            return echeck;

         echeckPlayer = toggle(echeckPlayer);

      }
      

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


} // namespace tictactoe



