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


   bool application::initialize_instance()
   {

      System.factory().creatable_small < ::tetris::pane_view >();
      System.factory().creatable_small < ::tetris::document >();
      System.factory().creatable_small < ::tetris::frame >();
      System.factory().creatable_small < ::tetris::view >();

      if(!::hellomultiverse::application::initialize_instance())
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


   int32_t application::exit_instance()
   {

      return ::core::application::exit_instance();

   }


   void application::on_request(sp(::create) pcreatecontext)
   {

      m_ptemplateTetrisMain->open_document_file(pcreatecontext);

      if(!pcreatecontext->m_spCommandLine->m_varFile.is_empty())
      {
         m_ptemplateTetrisView->open_document_file(pcreatecontext);
      }

   }

} // namespace tetris




extern "C"
::aura::library * game_tetris_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::tetris::application >(papp, "game");

}


