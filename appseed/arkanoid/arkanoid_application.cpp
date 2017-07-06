#include "framework.h"


namespace arkanoid
{


   application::application()
   {

      m_strAppName            = "arkanoid";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;


      m_etype                 = type_normal;

      m_strHelloMultiverse             = "Hello Tetris!!";

      //m_bMultiverseChat = false;
   }


   application::~application()
   {
   }


   bool application::initialize_application()
   {

      System.factory().creatable_small < ::arkanoid::pane_view >();
      System.factory().creatable_small < ::arkanoid::document >();
      System.factory().creatable_small < ::arkanoid::frame >();
      System.factory().creatable_small < ::arkanoid::view >();

      if(!::hellomultiverse::application::initialize_application())
         return false;

	   ::user::single_document_template* pDocTemplate;
	   pDocTemplate = new ::user::single_document_template(
         this,
		   "frame",
		   System.type_info < ::arkanoid::document > (),
		   System.type_info < ::arkanoid::frame > (),       // top level SDI frame::user::interaction_impl
		   System.type_info < ::arkanoid::pane_view > ());
      add_document_template(pDocTemplate);
      m_ptemplateTetrisMain = pDocTemplate;
	   pDocTemplate = new ::user::single_document_template(
         this,
		   "frame",
         System.type_info < ::arkanoid::document > (),
		   System.type_info < ::arkanoid::frame > (),       // top level SDI frame::user::interaction_impl
		   System.type_info < ::arkanoid::view > ());
      add_document_template(pDocTemplate);
      m_ptemplateTetrisView = pDocTemplate;

      return true;

   }


   int32_t application::exit_application()
   {

      return ::core::application::exit_application();

   }


   void application::on_request(::create * pcreate)
   {

      m_ptemplateTetrisMain->open_document_file(pcreate);

      if(!pcreate->m_spCommandLine->m_varFile.is_empty())
      {
         m_ptemplateTetrisView->open_document_file(pcreate);
      }

   }

} // namespace arkanoid




extern "C"
::aura::library * game_arkanoid_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::arkanoid::application >(papp, "game");

}


