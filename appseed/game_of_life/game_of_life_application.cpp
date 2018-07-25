#include "framework.h"


namespace game_of_life
{


   application::application()
   {

      m_strAppId              = "game/game_of_life";
      m_strAppName            = "game/game_of_life";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;

   }


   application::~application()
   {
   }


   bool application::init_instance()
   {

      System.factory().creatable_small < ::game_of_life::pane_view >();
      System.factory().creatable_small < ::game_of_life::document >();
      System.factory().creatable_small < ::game_of_life::frame >();
      System.factory().creatable_small < ::game_of_life::main_frame >();
      System.factory().creatable_small < ::game_of_life::view >();

      if(!::multimedia::application::init_instance())
         return false;

      set_local_data();

      ::user::single_document_template* pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "frame",
      System.type_info < ::game_of_life::document > (),
      System.type_info < ::game_of_life::main_frame > (),       // top level SDI frame::user::interaction_impl
      System.type_info < ::game_of_life::pane_view > ());
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseMain = pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "frame",
      System.type_info < ::game_of_life::document > (),
      System.type_info < ::game_of_life::frame > (),       // top level SDI frame::user::interaction_impl
      System.type_info < ::game_of_life::view > ());
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseView = pDocTemplate;

      return true;

   }


   void application::term_instance()
   {

      ::estamira::application::term_instance();

   }


   void application::on_request(::create * pcreate)
   {

      m_ptemplateHelloMultiverseMain->request_create(pcreate);

      if(!pcreate->m_spCommandLine->m_varFile.is_empty())
      {

         m_ptemplateHelloMultiverseView->request_create(pcreate);

      }

   }


} // namespace game_of_life




extern "C"
::aura::library * game_game_of_life_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::game_of_life::application >(papp, "game/game_of_life");

}





