#pragma once




namespace arch001
{


   class document;


   class CLASS_DECL_GAME_ARCH001 view :
      virtual public ::backview::user::impact
   {
   public:

      //::visual::dib_sp           m_dibCoin;
      //::visual::dib_sp           m_dibMony;
      //::visual::dib_sp           m_dibMon2;
      //game                          m_game;

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


      point                   m_ptFinal;



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

      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);

      virtual bool keyboard_focus_is_focusable() override;

   };


} // namespace arch001




