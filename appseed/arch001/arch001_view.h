#pragma once




namespace coincube
{


   class document;


   class CLASS_DECL_GAME_COINCUBE view :
      virtual public ::user::impact,
      virtual public ::backview::user::interaction
   {
   public:

      ::visual::dib_sp           m_dibCoin;
      ::visual::dib_sp           m_dibMony;
      ::visual::dib_sp           m_dibMon2;

      spa(coin)               m_money;

      sp(::multimedia::sound_track)      m_psound;
      bool                    m_bGame;
      int                     m_iCount;
      int                     m_iPhase;

      string                  m_strServer;
      mutex                   m_mutexWork;
      mutex                   m_mutexDraw;
      mutex                   m_mutexSwap;

      ::draw2d::dib_sp        m_dibBk;
      ::draw2d::dib_sp        m_dib1;
      ::draw2d::dib_sp        m_dib2;
      bool                    m_bDib1;

      ::visual::fastblur      m_dib;
      ::draw2d::dib_sp        m_dibColor;
      ::visual::dib_sp        m_dibWork;

      ::draw2d::font_sp       m_font;
      string                  m_strHelloMultiverse;
      int32_t                 m_iErrorAiFont;
      void *                  m_faceAi; // FT_Face m_faceAi;


      ::rect                  m_rectSpace;
      ::rect                  m_rectCheckSpace;

      byte                    m_bBkAlpha;


      cube                    m_pot;


      point                   m_ptFinal;


      view(::aura::application * papp);
	   virtual ~view();

   #ifdef DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif





      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::dib * pdib);

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint);

      ::user::document * get_document();


      virtual void layout();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnNewGame);

      void credit();

      virtual void new_game();

   };


} // namespace coincube




