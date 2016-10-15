#include "framework.h"


namespace matchmaking
{


   main::main(::aura::application * papp) :
      object(papp),
      ::user::split_layout(papp),
      ::user::split_view(papp),
      place_holder_container(papp)
   {

      m_plobby = NULL;
      m_pview = NULL;

   }


   main::~main()
   {

   }


   void main::assert_valid() const
   {

      ::user::split_view::assert_valid();

   }


   void main::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void main::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {
      ::user::split_view::on_update(pSender, lHint, phint);
   }


   void main::on_create_views()
   {

      if (get_pane_count() > 0)
         return;

      int iPane;

      SetPaneCount(2);

      SetSplitOrientation(orientation_horizontal);

      set_position(0, 200);

      initialize_split_layout();

      m_plobby = create_view < lobby >(NULL, ::null_rect(), get_pane_holder(0), "top_view");

      if (m_plobby == NULL)
      {

         System.simple_message_box(NULL, "Could not create folder edit view");

      }


      


      //m_pview = create_view < lite_view >();

      m_pview = create_view < view >(NULL, ::null_rect(), get_pane_holder(1), "matchmaking_view");

      if (m_pview == NULL)
      {

         System.simple_message_box(NULL, "Could not create file list ::user::impact");

      }



   }



   bool main::BaseOnControlEvent(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::event_button_clicked)
      {

         if (pevent->m_puie->m_id == "matchmaking_toggle")
         {

            if (m_pview->m_prender->m_bLite && !Application.m_bLoadAiFont)
            {

               Application.load_ai_font();

            }

            m_pview->m_prender->m_bLite = !m_pview->m_prender->m_bLite;


            m_pview->on_layout();

         }

      }

      return true;

   }




} // namespace matchmaking



