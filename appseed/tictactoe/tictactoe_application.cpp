#include "framework.h"


namespace tictactoe
{


   application::application()
   {

      m_strAppName            = "tictactoe";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;

   }


   application::~application()
   {
   }


   bool application::initialize_instance()
   {

      System.factory().creatable_small < ::tictactoe::pane_view >();
      System.factory().creatable_small < ::tictactoe::document >();
      System.factory().creatable_small < ::tictactoe::frame >();
      System.factory().creatable_small < ::tictactoe::view >();

      if(!::core::application::initialize_instance())
         return false;

      m_dataid += ".local://";

	   ::user::single_document_template* pDocTemplate;
	   pDocTemplate = new ::user::single_document_template(
         this,
		   "frame",
		   System.type_info < ::tictactoe::document > (),
		   System.type_info < ::tictactoe::frame > (),       // top level SDI frame::user::interaction_impl
		   System.type_info < ::tictactoe::pane_view > ());
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseMain = pDocTemplate;
	   pDocTemplate = new ::user::single_document_template(
         this,
		   "frame",
         System.type_info < ::tictactoe::document > (),
		   System.type_info < ::tictactoe::frame > (),       // top level SDI frame::user::interaction_impl
		   System.type_info < ::tictactoe::view > ());
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseView = pDocTemplate;

      return true;

   }


   int32_t application::exit_instance()
   {

      return ::core::application::exit_instance();

   }


   void application::on_request(sp(::create) pcreatecontext)
   {

      m_ptemplateHelloMultiverseMain->open_document_file(pcreatecontext);

      if(!pcreatecontext->m_spCommandLine->m_varFile.is_empty())
      {
         m_ptemplateHelloMultiverseView->open_document_file(pcreatecontext);
      }

   }

} // namespace tictactoe




extern "C"
::aura::library * get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::tictactoe::application >(papp, "app-core");

}


