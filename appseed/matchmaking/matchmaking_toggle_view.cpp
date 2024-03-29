#include "framework.h"


namespace matchmaking
{


   toggle_view::toggle_view(::aura::application * papp):
      object(papp),
      ::user::interaction(papp),
      ::user::button(papp)
   {

      m_ptopview = NULL;

   }
   toggle_view::~toggle_view()
   {


   }

   void toggle_view::install_message_routing(::message::sender * psender)
   {

      ::user::impact::install_message_routing(psender);
      ::user::button::install_message_routing(psender);

   }


   void toggle_view::on_update(::user::impact * pSender,LPARAM lHint,object* phint)
   {

      ::user::impact::on_update(pSender,lHint,phint);

   }


   bool toggle_view::keyboard_focus_is_focusable()
   {

      return ::user::button::keyboard_focus_is_focusable() ;

   }


} // namespace matchmaking













