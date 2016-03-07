#pragma once


namespace matchmaking
{


   class CLASS_DECL_APP_CORE_MATCHMAKING toggle_view:
      virtual public ::user::impact,
      virtual public ::user::button
   {
   public:


      top_view *           m_ptopview;


      toggle_view(::aura::application * papp);
      virtual ~toggle_view();


      virtual void install_message_handling(::message::dispatch * pdispatch);


      virtual void on_update(::user::impact * pSender,LPARAM lHint,object* phint);


      virtual bool keyboard_focus_is_focusable();


   };


} // namespace matchmaking




