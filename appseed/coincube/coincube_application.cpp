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


   bool application::init_instance()
   {

      System.factory().creatable_small < ::coincube::pane_view >();
      System.factory().creatable_small < ::coincube::document >();
      System.factory().creatable_small < ::coincube::frame >();
      System.factory().creatable_small < ::coincube::main_frame >();
      System.factory().creatable_small < ::coincube::view >();

      if(!::multimedia::application::init_instance())
         return false;

      set_local_data_key_modifier();

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


   int32_t application::exit_application()
   {

      return ::core::application::exit_application();

   }


   void application::on_request(::create * pcreate)
   {

      m_ptemplateHelloMultiverseMain->request_create(pcreate);

      if(!pcreate->m_spCommandLine->m_varFile.is_empty())
      {

         m_ptemplateHelloMultiverseView->request_create(pcreate);

      }

   }


} // namespace coincube




extern "C"
::aura::library * game_coincube_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::coincube::application >(papp, "game");

}





