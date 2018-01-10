#pragma once


namespace matchmaking
{


   class CLASS_DECL_APP_CORE_MATCHMAKING edit_view:
      virtual public ::user::show < ::user::plain_edit >
   {
   public:


      top_view * m_ptopview;


      edit_view(::aura::application * papp);
      virtual ~edit_view();

      virtual void _001OnAfterChangeText(::action::context actioncontext);

      void on_update(::user::impact * pSender,LPARAM lHint,object* phint);

      virtual void install_message_routing(::message::sender * psender);

      DECL_GEN_SIGNAL(_001OnCreate);
      //bool keyboard_focus_is_focusable();

      //virtual int64_t add_ref();

      //virtual int64_t dec_ref();

      //bool IsWindowVisible() override;

   };


} // namespace matchmaking




