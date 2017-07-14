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


   bool application::initialize_application()
   {

      System.factory().creatable_small < ::tictactoe::pane_view >();
      System.factory().creatable_small < ::tictactoe::document >();
      System.factory().creatable_small < ::tictactoe::frame >();
      System.factory().creatable_small < ::tictactoe::main_frame >();
      System.factory().creatable_small < ::tictactoe::view >();

      if(!::core::application::initialize_application())
         return false;

      m_dataid += ".local://";

	   ::user::single_document_template* pDocTemplate;
	   pDocTemplate = new ::user::single_document_template(
         this,
		   "frame",
		   System.type_info < ::tictactoe::document > (),
		   System.type_info < ::tictactoe::main_frame > (),       // top level SDI frame::user::interaction_impl
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


} // namespace tictactoe




extern "C"
::aura::library * game_tictactoe_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::tictactoe::application >(papp, "game");

}



namespace tictactoe
{


   CLASS_DECL_GAME_TICTACTOE e_check toggle(e_check echeck)
   {

      return echeck == check_x ? check_o : check_x;

   }


} // namespace tictactoe



