#include "framework.h"

#include "ft2build.h"
#include FT_FREETYPE_H

namespace pacman
{


   application::application()
   {

      m_ppacman = NULL;

      m_strAppName            = "pacman";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;
      m_iConsole = 2;

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

      start();

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

         m_psplit = psplit;

      }

   }


   bool application::BaseOnControlEvent(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::event_button_clicked)
      {

         if(pevent->m_puie == m_ptoggle)
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
      m_ppacman->::console::window_composite::cout.m_spbuffer = pwindow->cout.m_spbuffer;
      m_ppacman->m_player.::console::window_composite::m_p = pwindow;
      m_ppacman->m_player.::console::window_composite::cout.m_spbuffer = pwindow->cout.m_spbuffer;
      for(auto ghost : m_ppacman->ghosts)
      {
         ghost->::console::window_composite::m_p = pwindow;
         ghost->::console::window_composite::cout.m_spbuffer = pwindow->cout.m_spbuffer;
      }
      for(auto pellet : m_ppacman->pellets)
      {
         pellet->::console::window_composite::m_p = pwindow;
         pellet->::console::window_composite::cout.m_spbuffer = pwindow->cout.m_spbuffer;
      }

      m_pconsolewindow = pwindow;

      m_ppacman->restart();

      ::aura::del(pwindowOld);

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

         return System.alloc<::console::window>(System.type_info<::console::window >());

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


