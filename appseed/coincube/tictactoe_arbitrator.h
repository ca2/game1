#pragma once




namespace tictactoe
{



   class CLASS_DECL_GAME_TICTACTOE arbitrator:
      virtual public object
   {
   public:


      e_check                 m_echeck;

      player *                m_pplayerX;
      player *                m_pplayerO;


      DWORD                   m_dwBreaker;

      board                   m_board;

      manual_reset_event      m_evReady;

      e_check                 m_echeckWinner;

      bool                    m_bRun;

      bool                    m_bEndOnFull;


      arbitrator(::aura::application * papp);
      virtual ~arbitrator();


      void launch(player * pplayerX,player * pplayerO,bool bXFirst);


      // return winner 
      e_check arbitrate(player * pplayerX, player * pplayerO, bool bXFirst);

      e_check check_winner();


      player * get_player(e_check echeck);


      virtual void post_stop();


   };


} // namespace tictactoe




