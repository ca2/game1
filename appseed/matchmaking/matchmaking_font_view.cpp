#include "framework.h"


namespace hellomultiverse
{


   font_view::font_view(::aura::application * papp):
      object(papp),
      ::user::split_layout(papp),
      ::user::split_view(papp),
      place_holder_container(papp)
   {

      m_pview = NULL;

      m_ptopview = NULL;

   }


   font_view::~font_view()
   {

   }


   void font_view::assert_valid() const
   {

      ::user::split_view::assert_valid();

   }


   void font_view::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void font_view::on_update(::user::impact * pSender,LPARAM lHint,object* phint)
   {
      ::user::split_view::on_update(pSender,lHint,phint);
   }


   void font_view::on_create_views()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(orientation_horizontal);

      set_position(0,24);

      initialize_split_layout();

      m_ptopview = create_view < top_view >(NULL,::null_rect(),get_pane_holder(0),"top_view");

      if(m_ptopview == NULL)
      {

         System.simple_message_box(NULL,"Could not create folder edit view");

      }

      //SetPane(0,m_ptopview,false);

      m_pview = create_view < ::user::font_list_view >(NULL,::null_rect(),get_pane_holder(1),"font_list_view");

      if(m_pview == NULL)
      {

         System.simple_message_box(NULL,"Could not create file list ::user::impact");

      }


   }


   bool font_view::BaseOnControlEvent(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::event_button_clicked)
      {

         if(pevent->m_puie->m_id == "switcher_toggle")
         {

            sp(view) pview = m_pview;

            pview->m_prender->m_bLite = !pview->m_prender->m_bLite;

         }
         //else if(pevent->m_puie->m_id == "hellomultiverse_toggle")
         //{

         //   if(m_pview->m_prender->m_bLite && !Application.m_bLoadAiFont)
         //   {

         //      Application.load_ai_font();

         //   }

         //   m_pview->m_prender->m_bLite = !m_pview->m_prender->m_bLite;


         //   m_pview->layout();

         //}

      }
      else if(pevent->m_eevent == ::user::event_after_change_cur_sel)
      {

         if(m_pview == pevent->m_puie)
         {

            if(GetTypedParent < pane_view >()->m_pviewLast != NULL)
            {

               string strFont = m_pview->get_cur_sel_face_name();

               if(strFont.has_char())
               {

                  GetTypedParent < pane_view >()->m_pviewLast->m_strNewFont = strFont;

                  GetTypedParent < pane_view >()->m_pviewLast->layout();

               }

            }

         }

      }



      return true;

   }

} // namespace hellomultiverse



