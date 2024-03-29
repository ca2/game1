#pragma once




namespace coincube
{


   class document;


   class CLASS_DECL_GAME_COINCUBE view :
      virtual public ::backview::user::impact
   {
   public:

      ::visual::dib_sp                    m_dibCoin;
      ::visual::dib_sp                    m_dibMony;
      ::visual::dib_sp                    m_dibMon2;
      double                              m_dGrow;

      spa(coin)                           m_money;

      sp(::multimedia::sound_track)       m_psound;
      bool                                m_bGame;
      int                                 m_iCount;
      int                                 m_iPhase;

      string                              m_strServer;
      mutex                               m_mutexWork;
      mutex                               m_mutexDraw;
      mutex                               m_mutexSwap;

      ::draw2d::dib_sp                    m_dibBk;
      ::draw2d::dib_sp                    m_dib1;
      ::draw2d::dib_sp                    m_dib2;
      bool                                m_bDib1;

      ::visual::fastblur                  m_dib;
      ::draw2d::dib_sp                    m_dibColor;
      ::visual::dib_sp                    m_dibWork;
      ::rect                              m_rectSpace;
      ::rect                              m_rectCheckSpace;
      byte                                m_bBkAlpha;
      cube                                m_pot;
      point                               m_ptFinal;
      ::particle::effect::array           m_effecta;


      view(::aura::application * papp);
      virtual ~view();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;






      virtual void install_message_routing(::message::sender * psender);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint);

      ::user::document * get_document();


      virtual void on_layout();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnNewGame);

      void credit();

      virtual void new_game();

   };


} // namespace coincube




