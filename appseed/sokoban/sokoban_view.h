#pragma once



namespace sokoban
{

   
   class document;


   class CLASS_DECL_APP_CORE_SOKOBAN view :
      virtual public ::user::impact
   {
   public:


      asset       m_asset;

//      _SokobanPreview *        m_ppreview;
      //_sokoban *               m_psokoban;

      ::visual::fastblur      m_dib;
      bool                    m_bDibLayout;
      int                     m_xDib;
      
      
      
      ::draw2d::font_sp       m_font;


      ::rect                  m_rectSpace;
      ::rect                  m_rectCheckSpace;

      string                  m_strScore;
      string                  m_strLevel;

      int                     m_iHoverLevel;

      int                     m_iSideBarWidth;

      bool                    m_bDisableInput;
      double                  m_dGotoLevel;
      int                     m_iScrollStart;

      ::draw2d::font_sp       m_font1;

      view(::aura::application * papp);
	   virtual ~view();

   #ifdef DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif



      virtual void install_message_routing(::message::sender * psender);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint);

      document * get_document();
      
      void render();

      void start();
      

      virtual void on_layout();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      virtual void _001OnTimer(::timer * ptimer);


      virtual bool keyboard_focus_is_focusable();

      int hit_test_level(point pt);

      void go_to_level(int iLevel);

      void go_to_next_level();

   };

   
} // namespace sokoban




