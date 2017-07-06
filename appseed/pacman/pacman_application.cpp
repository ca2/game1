#include "framework.h"

//#include "ft2build.h"
//#include FT_FREETYPE_H

namespace pacman
{


   application::application()
   {

//      m_ptoggle               = NULL;
      m_ppacman               = NULL;

      m_strAppName            = "pacman";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;
      m_iConsole = 0;

      m_etype                 = type_normal;

      m_strHelloMultiverse             = "Hello PacMan!!";

      //m_bMultiverseChat = false;

//      m_ptoggle = NULL;

   }


   application::~application()
   {
   }


   bool application::initialize_application()
   {

#ifdef WINDOWS

      //int32_t error = FT_Init_FreeType((FT_Library *)&System.m_ftlibrary);
      //if(error)
      //{
      //   TRACE("an error occurred during Free Type library initialization");
      //   return false;
      //}

#endif

      System.factory().creatable_small < ::pacman::pane_view >();
      System.factory().creatable_small < ::pacman::document >();
      System.factory().creatable_small < ::pacman::frame >();
      System.factory().creatable_small < ::pacman::view >();

      if(!::multimedia::application::initialize_application())
         return false;

      if(!::hellomultiverse::application::initialize_application())
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


   int32_t application::exit_application()
   {

      return ::core::application::exit_application();

   }


   void application::on_request(::create * pcreate)
   {

      start();

      m_ptemplatePacManMain->open_document_file(pcreate);

      if(!pcreate->m_spCommandLine->m_varFile.is_empty())
      {
         m_ptemplatePacManView->open_document_file(pcreate);
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

         //m_ptoggle = psplit->create_view < ::hellomultiverse::toggle_view >(NULL,::null_rect(),psplit->get_pane_holder(0),"toggle_view");
         psplit->create_view < ::hellomultiverse::toggle_view >(NULL,::null_rect(),psplit->get_pane_holder(0),"toggle_view");

         m_pview = psplit->create_view < view >(NULL,::null_rect(),psplit->get_pane_holder(1),"pacman_view3");

         m_psplit = psplit;

      }

   }


   bool application::BaseOnControlEvent(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::event_button_clicked)
      {

         if(pevent->m_puie->m_id == "toggle_view")
         {


            Application.change_console(++Application.m_iConsole);

            pevent->m_bProcessed = true;
            pevent->m_bRet = true;


            return true;

         }


      }

      return false;

   }

   void application::start()
   {

      m_pconsolewindow = create_console(m_iConsole);

      m_ppacman = new pacman(m_pconsolewindow);



      //      m_ppacman->reset();

      //sp(frame) pframe = GetTopLevelFrame();

      //pframe->m_sizeView.cx = m_ppacman->widthInPixels+ 80;
      //pframe->m_sizeView.cy = m_ppacman->heightInPixels + 80 + 10 + m_ppreview->m_dib->m_size.cy;

      //sp(frame) pframe1 = GetParentFrame();

      //pframe1->m_sizeView = pframe->m_sizeView;

      m_ppacman->begin();

   }

   void application::change_console(int iIndex)
   {

      ::console::window * pwindowOld = m_pconsolewindow;

      ::console::window * pwindow = create_console(iIndex % 3);

      m_ppacman->::console::window_composite::m_p = pwindow;
      m_ppacman->::console::window_composite::cout.m_spfile = pwindow->cout.m_spfile;
      m_ppacman->m_player.::console::window_composite::m_p = pwindow;
      m_ppacman->m_player.::console::window_composite::cout.m_spfile = pwindow->cout.m_spfile;
      for(auto ghost : m_ppacman->ghosts)
      {
         ghost->::console::window_composite::m_p = pwindow;
         ghost->::console::window_composite::cout.m_spfile = pwindow->cout.m_spfile;
      }
      for(auto pellet : m_ppacman->pellets)
      {
         pellet->::console::window_composite::m_p = pwindow;
         pellet->::console::window_composite::cout.m_spfile = pwindow->cout.m_spfile;
      }

      m_pconsolewindow = pwindow;

      m_ppacman->restart();

      pwindowOld->release();

   }

   ::console::window * application::create_console(int iIndex)
   {

      if(iIndex == 0)
      {

         return new console(this,size(16,16));

      }
      else if(iIndex == 1)
      {


         return new dib_console(this,size(16,16));

      }
      else if(iIndex == 2)
      {

         return Application.alloc<::console::window>(System.type_info<::console::window >());

      }
      else
      {

         return new console(this,size(16,16));

      }

   }

} // namespace pacman




extern "C"
::aura::library * game_pacman_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::pacman::application >(papp, "game");

}


