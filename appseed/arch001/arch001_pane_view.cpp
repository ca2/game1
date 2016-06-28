#include "framework.h"


namespace arch001
{

   pane_view::pane_view(::aura::application * papp) :
      ::object(papp),
      ::user::tab(papp),
      
      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {


   }

   pane_view::~pane_view()
   {
   }


#ifdef DEBUG
   void pane_view::assert_valid() const
   {
	   ::user::impact::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
	   ::user::impact::dump(dumpcontext);
   }
#endif //DEBUG


   void pane_view::install_message_handling(::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);

	   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);

   }


   void pane_view::_001OnCreate(signal_details * pobj)
   {
      if(pobj->previous())
         return;

      set_tab("arch001", ::arch001::PaneViewHelloMultiverse);
      set_tab("Open", "file_manager");

      set_cur_tab_by_id(::arch001::PaneViewHelloMultiverse);

   }




   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      switch(pcreatordata->m_id)
      {
      case PaneViewHelloMultiverse:
         {
            sp(::arch001::document) pdoc =  (Application.m_ptemplateHelloMultiverseView->open_document_file(NULL, true, pcreatordata->m_pholder));
            if(pdoc != NULL)
            {
               sp(::user::impact) pview = pdoc->get_view(0);
               pview->on_update(NULL, 0, NULL);
               if(pview != NULL)
               {
                  sp(::arch001::frame) pframe = (pview->GetParentFrame());
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




} // namespace arch001