#include "framework.h"


namespace tetris
{


   application::application()
   {

      m_strAppName            = "tetris";
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

      System.factory().creatable_small < ::tetris::pane_view >();
      System.factory().creatable_small < ::tetris::document >();
      System.factory().creatable_small < ::tetris::frame >();
      System.factory().creatable_small < ::tetris::view >();

      if(!::hellomultiverse::application::initialize_application())
         return false;


      m_dataid += ".local://";

	   ::user::single_document_template* pDocTemplate;
	   pDocTemplate = new ::user::single_document_template(
         this,
		   "frame",
		   System.type_info < ::tetris::document > (),
		   System.type_info < ::tetris::frame > (),       // top level SDI frame::user::interaction_impl
		   System.type_info < ::tetris::pane_view > ());
      add_document_template(pDocTemplate);
      m_ptemplateTetrisMain = pDocTemplate;
	   pDocTemplate = new ::user::single_document_template(
         this,
		   "frame",
         System.type_info < ::tetris::document > (),
		   System.type_info < ::tetris::frame > (),       // top level SDI frame::user::interaction_impl
		   System.type_info < ::tetris::view > ());
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

} // namespace tetris




extern "C"
::aura::library * game_tetris_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::tetris::application >(papp, "game");

}


