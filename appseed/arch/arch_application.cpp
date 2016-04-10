#include "framework.h"


namespace coincube
{


   application::application()
   {

      m_strAppName            = "coincube";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;

   }


   application::~application()
   {
   }


   bool application::initialize_instance()
   {

      System.factory().creatable_small < ::coincube::pane_view >();
      System.factory().creatable_small < ::coincube::document >();
      System.factory().creatable_small < ::coincube::frame >();
      System.factory().creatable_small < ::coincube::main_frame >();
      System.factory().creatable_small < ::coincube::view >();

      if(!::multimedia::application::initialize_instance())
         return false;

      m_dataid += ".local://";

	   ::user::single_document_template* pDocTemplate;
	   pDocTemplate = new ::user::single_document_template(
         this,
		   "frame",
		   System.type_info < ::coincube::document > (),
		   System.type_info < ::coincube::main_frame > (),       // top level SDI frame::user::interaction_impl
		   System.type_info < ::coincube::pane_view > ());
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseMain = pDocTemplate;
	   pDocTemplate = new ::user::single_document_template(
         this,
		   "frame",
         System.type_info < ::coincube::document > (),
		   System.type_info < ::coincube::frame > (),       // top level SDI frame::user::interaction_impl
		   System.type_info < ::coincube::view > ());
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

} // namespace coincube




extern "C"
::aura::library * game_coincube_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::coincube::application >(papp, "game");

}





