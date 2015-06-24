#include "framework.h"

#include "ft2build.h"
#include FT_FREETYPE_H

namespace pacman
{


   application::application()
   {

      m_strAppName            = "pacman";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;
      m_i = 0;

      m_etype                 = type_normal;

      m_strHelloMultiverse             = "Hello PacMan!!";

      //m_bMultiverseChat = false;

      m_ptoggle = NULL;

   }


   application::~application()
   {
   }


   bool application::initialize_instance()
   {

#ifdef WINDOWS

      int32_t error = FT_Init_FreeType((FT_Library *)&System.m_ftlibrary);
      if(error)
      {
         TRACE("an error occurred during Free Type library initialization");
         return false;
      }

#endif

      System.factory().creatable_small < ::pacman::pane_view >();
      System.factory().creatable_small < ::pacman::document >();
      System.factory().creatable_small < ::pacman::frame >();
      System.factory().creatable_small < ::pacman::view >();
      System.factory().creatable_small < ::pacman::view2 >();
#ifndef WINDOWS
      System.factory().creatable_small < ::pacman::view3 >();
#endif

      if(!::multimedia::application::initialize_instance())
         return false;

      if(!::hellomultiverse::application::initialize_instance())
         return false;

      m_dataid +=".local://";

	   ::user::single_document_template* pDocTemplate;
	   pDocTemplate = new ::user::single_document_template(
         this,
		   "frame",
		   System.type_info < ::pacman::document > (),
		   System.type_info < ::pacman::frame > (),       // top level SDI frame::user::interaction_impl
		   System.type_info < ::pacman::pane_view > ());
      add_document_template(pDocTemplate);
      m_ptemplatePacManMain = pDocTemplate;
	   pDocTemplate = new ::user::single_document_template(
         this,
		   "frame",
         System.type_info < ::pacman::document > (),
		   System.type_info < ::pacman::frame > (),       // top level SDI frame::user::interaction_impl
		   System.type_info < ::user::split_view > ());
      add_document_template(pDocTemplate);
      m_ptemplatePacManView = pDocTemplate;

      return true;

   }


   int32_t application::exit_instance()
   {

      return ::core::application::exit_instance();

   }


   void application::on_request(sp(::create) pcreatecontext)
   {

      m_ptemplatePacManMain->open_document_file(pcreatecontext);

      if(!pcreatecontext->m_spCommandLine->m_varFile.is_empty())
      {
         m_ptemplatePacManView->open_document_file(pcreatecontext);
      }

   }

   void application::on_create_split_view(::user::split_view * psplit)
   {

      if(psplit->get_document()->get_document_template() == m_ptemplatePacManView)
      {


         if(psplit->get_pane_count() > 0)
            return;

         psplit->SetPaneCount(2);

         psplit->SetSplitOrientation(orientation_horizontal);

         psplit->set_position(0,24);

         psplit->initialize_split_layout();

         m_ptoggle = psplit->create_view < ::hellomultiverse::toggle_view >(NULL,::null_rect(),psplit->get_pane_holder(0),"toggle_view");

         m_pview = psplit->create_view < view >(NULL,::null_rect(),psplit->get_pane_holder(1),"pacman_view3");

         m_i = 0;

         m_psplit = psplit;

      }

   }


   bool application::BaseOnControlEvent(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::event_button_clicked)
      {

         if(pevent->m_puie == m_ptoggle)
         {

            view * pview = m_pview;

            int iCount = 3;
            
            if(m_i % iCount  == 0)
            {

               m_pview = m_psplit->create_view < view >(NULL,::null_rect(),m_psplit->get_pane_holder(1),"pacman_view");

            }
            else if(m_i % iCount == 1)
            {

               m_pview = m_psplit->create_view < view2 >(NULL,::null_rect(),m_psplit->get_pane_holder(1),"pacman_view2");

            }
            else if(m_i % iCount == 2)
            {

               m_pview = m_psplit->create_view < view3 >(NULL,::null_rect(),m_psplit->get_pane_holder(1),"pacman_view3");

            }

            m_i++;

            m_pview->SetFocus();

            pview->DestroyWindow();

//            ::release(pview);

            pevent->m_bProcessed = true;

            return true;

         }


      }

      return false;

   }




} // namespace pacman




extern "C"
::aura::library * app_core_pacman_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::pacman::application >(papp, "app-core");

}


