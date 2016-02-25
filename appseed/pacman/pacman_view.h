#pragma once



namespace pacman
{


   class document;


   class CLASS_DECL_APP_CORE_PACMAN view :
      virtual public user::impact
   {
   public:


//      _PacManPreview *        m_ppreview;

      ::visual::fastblur      m_dib;
      bool                    m_bDibLayout;
      int                     m_xDib;

      bool                    m_bHarderControl;

      ::draw2d::font_sp       m_font;


      ::rect                  m_rectSpace;
      ::rect                  m_rectCheckSpace;

      string                  m_strScore;
      string                  m_strLevel;

      //



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

      void render();

      void attach();


      virtual void layout();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);


      virtual bool keyboard_focus_is_focusable();


   };


} // namespace pacman




