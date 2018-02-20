#pragma once



namespace arkanoid
{


   class document;


   class CLASS_DECL_GAME_ARKANOID view :
      public ::user::impact
   {
   public:


      arkanoid *              m_parkanoid;

      ::visual::fastblur      m_dib;
      bool                    m_bDibLayout;
      int                     m_xDib;



      ::draw2d::font_sp       m_font;


      ::rect                  m_rectSpace;
      ::rect                  m_rectCheckSpace;

      string                  m_strScore;
      string                  m_strLevel;

      //



      view(::aura::application * papp);
      virtual ~view();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;




      virtual void install_message_routing(::message::sender * psender);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint);

      ::user::document * get_document();

      void render();

      void start();


      virtual void on_layout();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      DECL_GEN_SIGNAL(_001OnNewGame);

      virtual bool keyboard_focus_is_focusable();


   };


} // namespace arkanoid




