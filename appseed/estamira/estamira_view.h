#pragma once


namespace estamira
{


   class document;


   class CLASS_DECL_ESTAMIRA view :
      virtual public ::user::impact
   {
   public:


      sp(::multimedia::sound_track)    m_psound;

      bool                             m_bGame;
      int                              m_iCount;
      int                              m_iPhase;

      string                           m_strServer;
      mutex                            m_mutexWork;
      mutex                            m_mutexDraw;
      mutex                            m_mutexSwap;

      ::draw2d::dib_sp                 m_dibBk;
      ::draw2d::dib_sp                 m_dib1;
      ::draw2d::dib_sp                 m_dib2;
      bool                             m_bDib1;

      ::visual::fastblur               m_dib;
      ::draw2d::dib_sp                 m_dibColor;
      ::visual::dib_sp                 m_dibWork;

      ::draw2d::font_sp                m_font;
      string                           m_strHelloMultiverse;


      ::rect                           m_rectSpace;
      ::rect                           m_rectCheckSpace;

      byte                             m_bBkAlpha;

      point                            m_ptFinal;


      view(::aura::application * papp);
      virtual ~view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual void install_message_routing(::message::sender * psender) override;

      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint) override;

      ::user::document * get_document();


      virtual void on_layout() override;

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);


      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);

      virtual bool keyboard_focus_is_focusable() override;

   };


} // namespace estamira




