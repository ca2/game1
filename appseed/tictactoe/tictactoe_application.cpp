#include "framework.h"


namespace tictactoe
{


   application::application()
   {

      m_strAppId              = "game/tictactoe";
      m_strAppName            = "game/tictactoe";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;

   }


   application::~application()
   {
   }


   bool application::init_instance()
   {

      System.factory().creatable_small < ::tictactoe::pane_view >();
      System.factory().creatable_small < ::tictactoe::document >();
      System.factory().creatable_small < ::tictactoe::frame >();
      System.factory().creatable_small < ::tictactoe::main_frame >();
      System.factory().creatable_small < ::tictactoe::view >();

      if(!::core::application::init_instance())
         return false;

      set_local_data_key_modifier();

      ::user::single_document_template* pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "frame",
      System.type_info < ::tictactoe::document > (),
      System.type_info < ::tictactoe::main_frame > (),       // top level SDI frame::user::interaction_impl
      System.type_info < ::tictactoe::pane_view > ());
      add_document_template(pDocTemplate);
      m_ptemplateTicTacToeMain = pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "frame",
      System.type_info < ::tictactoe::document > (),
      System.type_info < ::tictactoe::frame > (),       // top level SDI frame::user::interaction_impl
      System.type_info < ::tictactoe::view > ());
      add_document_template(pDocTemplate);
      m_ptemplateTicTacToeView = pDocTemplate;

      return true;

   }


   void application::term_instance()
   {

      ::core::application::term_instance();

   }


   void application::on_request(::create * pcreate)
   {

      m_ptemplateTicTacToeMain->request_create(pcreate);

      if(!pcreate->m_spCommandLine->m_varFile.is_empty())
      {

         m_ptemplateTicTacToeView->request_create(pcreate);

      }

   }


} // namespace tictactoe




extern "C"
::aura::library * game_tictactoe_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::tictactoe::application >(papp, "game/tictactoe");

}



namespace tictactoe
{


   CLASS_DECL_GAME_TICTACTOE e_check toggle(e_check echeck)
   {

      return echeck == check_x ? check_o : check_x;

   }


} // namespace tictactoe



