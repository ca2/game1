#include "framework.h"


namespace game_of_life
{


   pane_view::pane_view(::aura::application * papp) :
      ::object(papp),
      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {

   }


   pane_view::~pane_view()
   {

   }


   void pane_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }



   void pane_view::install_message_routing(::message::sender * pinterface)
   {
      ::userex::pane_tab_view::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);

   }


   void pane_view::_001OnCreate(::message::message * pobj)
   {
      if(pobj->previous())
         return;

      set_tab("Options", "options");
      set_tab("game_of_life", ::game_of_life::PaneViewHelloMultiverse);
      set_tab("Open", "file_manager");

      set_cur_tab_by_id(::game_of_life::PaneViewHelloMultiverse);

   }




   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {

      if (pcreatordata->m_id == "options")
      {

         m_pdocOptions = Application.create_child_form(NULL, pcreatordata->m_pholder);

         m_pdocOptions->open_document("matter://options.html");

         return;

      }

      switch(pcreatordata->m_id)
      {

      case PaneViewHelloMultiverse:
      {
         sp(::game_of_life::document) pdoc =  (Application.m_ptemplateHelloMultiverseView->open_document_file(get_app(), NULL, true, pcreatordata->m_pholder));
         if(pdoc != NULL)
         {
            sp(::user::impact) pview = pdoc->get_view(0);
            m_pview = pview;
            pview->on_update(NULL, 0, NULL);
            if(pview != NULL)
            {
               sp(::game_of_life::frame) pframe = (pview->GetParentFrame());
               if(pframe != NULL)
               {
                  pcreatordata->m_pdoc = pdoc;
                  pcreatordata->m_pwnd = pframe;
                  pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
               }
            }
         }
      }
      break;

      default:
         break;

      }

      ::userex::pane_tab_view::on_create_view(pcreatordata);

   }


   void pane_view::on_show_view()
   {

      ::userex::pane_tab_view::on_show_view();

      string strId = get_view_id();

      if (strId == "options")
      {

         ::user::impact * pview = m_pdocOptions->get_view(0);

         ::user::plain_edit * pedit = dynamic_cast < ::user::plain_edit *> (pview->get_child_by_id("amount"));

         sp(game) pgame = Application.m_pgame;

         string str;

         str.Format("%d", pgame->m_iAmount);

         pedit->_001SetText(str, ::action::source_sync);

      }

   }

   void pane_view::on_control_event(::user::control_event * pevent)
   {

      if (m_pdocOptions != NULL && pevent->get_form() == m_pdocOptions->get_view(0) && pevent->m_puie != NULL)
      {

         if (pevent->m_eevent == ::user::event_after_change_text)
         {

            if (pevent->m_actioncontext.is_user_source())
            {

               ::user::impact * pview = m_pdocOptions->get_view(0);

               ::user::plain_edit * pedit = dynamic_cast < ::user::plain_edit *> (pview->get_child_by_id("amount"));

               if (pedit != NULL)
               {

                  sp(game) pgame = Application.m_pgame;

                  string str;

                  pedit->_001GetText(str);

                  int iAmount = atoi(str);

                  if (iAmount < 16)
                  {

                     iAmount = 16;

                  }
                  else if (iAmount > WINDOWSIZE / 2)
                  {

                     iAmount = WINDOWSIZE / 2;

                  }

                  pgame->set_amount(iAmount);

               }

            }

         }

      }

   }


} // namespace game_of_life



