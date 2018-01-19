﻿#include "framework.h"


namespace tetris
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


   void pane_view::install_message_routing(::message::sender * pinterface)
   {
      ::userex::pane_tab_view::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);

   }


   void pane_view::_001OnCreate(::message::message * pobj)
   {
      if(pobj->previous())
         return;

      set_tab("Tetris!!",::tetris::PaneViewTetris);
      set_tab("Open", "file_manager");
      set_tab("Help",::tetris::PaneViewHelp);

      set_cur_tab_by_id(::tetris::PaneViewTetris);

   }




   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {

      switch(pcreatordata->m_id)
      {
      case PaneViewTetris:
      {

         Application.m_ptemplateTetrisView->open_document_file(NULL,true,pcreatordata->m_pholder);

      }
      break;
      case PaneViewHelp:
      {
         ::user::document * pdoc = Application.create_child_form(NULL, pcreatordata->m_pholder);
         pdoc->open_document("matter://help.html");
         pcreatordata->m_eflag.unsignalize(::user::view_creator_data::flag_hide_all_others_on_show);

      }
      break;
      default:
         break;
      }
      ::userex::pane_tab_view::on_create_view(pcreatordata);
   }




} // namespace tetris
