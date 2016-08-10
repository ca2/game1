#include "framework.h"


namespace sokoban
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

      set_tab("Hello", ::sokoban::PaneViewHelloMultiverse);
      set_tab("Sokoban!!",::sokoban::PaneViewTetris);
      set_tab("Open", "file_manager");
      set_tab("Help",::sokoban::PaneViewHelp);

      set_cur_tab_by_id(::sokoban::PaneViewTetris);

   }




   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      switch(pcreatordata->m_id)
      {
      case PaneViewHelloMultiverse:
         {
         Application.m_ptemplateHelloMultiverseView->open_document_file(NULL,true,pcreatordata->m_pholder);


      }
         break;
      case PaneViewTetris:
      {
         Application.m_ptemplateTetrisView->open_document_file(NULL,true,pcreatordata->m_pholder);
         pcreatordata->m_eflag.unsignalize(::user::view_creator_data::flag_hide_all_others_on_show);

      }
      break;
      case PaneViewHelp:
      {
         ::user::document * pdoc = Session.userex()->create_child_form(NULL, pcreatordata->m_pholder);
         pdoc->open_document("matter://help.html");
         pcreatordata->m_eflag.unsignalize(::user::view_creator_data::flag_hide_all_others_on_show);

      }
      break;
      default:
         break;
      }
      ::userex::pane_tab_view::on_create_view(pcreatordata);
   }




} // namespace sokoban