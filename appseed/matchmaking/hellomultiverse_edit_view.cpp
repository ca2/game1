#include "framework.h"


namespace hellomultiverse
{


   edit_view::edit_view(::aura::application * papp):
      object(papp),
      ::user::interaction(papp),
      ::user::plain_edit(papp)
   {
      
      m_ptopview = NULL;
 
   }

   edit_view::~edit_view()
   {

   }
   void edit_view::install_message_handling(::message::dispatch * pdispatch)
   {

      ::user::show < ::user::plain_edit >::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_CREATE,pdispatch,this,&edit_view::_001OnCreate);

   }


   void edit_view::_001OnCreate(signal_details * pobj)
   {
      SCAST_PTR(::message::create,pcreate,pobj);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;


      m_ptopview = GetTypedParent < top_view >();
   }


   void edit_view::on_update(::user::impact * pSender,LPARAM lHint,object* phint)
   {

   }


   void edit_view::_001OnAfterChangeText(::action::context actioncontext)
   {

      if(actioncontext.is_source(::action::source_sync))
         return;

      if(m_ptopview == NULL)
         return;

      view * pview = dynamic_cast < ::hellomultiverse::view * > (m_ptopview->GetTypedParent<::user::split_view>()->get_child_by_id("hellomultiverse_view"));

      if(pview != NULL)
      {


         string strText;

         _001GetText(strText);

         {

            synch_lock sl(&pview->m_mutexText);

            pview->data_set("cur_text",strText);

            pview->m_strNewHelloMultiverse = strText;

         }

         pview->post_message(WM_USER + 1984 + 77 + 2);

      }

   }


   /*bool edit_view::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && IsWindowVisible();

   }

   bool edit_view::IsWindowVisible()
   {

      return ::user::show < ::user::plain_edit >::IsWindowVisible() && !GetTopLevel()->frame_is_transparent();

   }


   int64_t edit_view::add_ref()
   {
      return ::object::add_ref();
   }
   int64_t edit_view::dec_ref()
   {
      return ::object::dec_ref();
   }


*/
} // namespace hellomultiverse




