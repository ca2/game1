#pragma once


namespace matchmaking
{


   class CLASS_DECL_APP_CORE_MATCHMAKING lobby :
      virtual public ::user::impact
   {
   public:

      ::draw2d::font_sp    m_font;
      ::draw2d::font_sp    m_font2;
      rect                 m_rect1;
      rect                 m_rect2;
      rect                 m_rect3;
      rect                 m_rect4;
      rect                 m_rect5;
      int                  m_iHover;

      lobby(::aura::application * papp);
      virtual ~lobby();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual void install_message_handling(::message::dispatch * pdispatch);


      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint);

      document * get_document();

      virtual void draw_member(
         ::draw2d::graphics * pgraphics,
         int iButton,
         rect & rectButton,
         string str1,
         string str2,
         COLORREF cr1,
         COLORREF cr2);


      virtual void on_layout();

      DECL_GEN_SIGNAL(_001OnLayout);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);


      int hit_test(point pt);

      virtual bool in_anime();

      virtual int64_t add_ref()
      {
         return ::object::add_ref();
      }
      virtual int64_t dec_ref()
      {
         return ::object::dec_ref();
      }


   };


} // namespace matchmaking





















