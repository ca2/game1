#include "framework.h"


namespace tetris
{


   application::application()
   {

      m_strAppId              = "game/tetris";
      m_strAppName            = "game/tetris";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;


   }


   application::~application()
   {
   }


   bool application::init_instance()
   {

      System.factory().creatable_small < ::tetris::pane_view >();
      System.factory().creatable_small < ::tetris::document >();
      System.factory().creatable_small < ::tetris::frame >();
      System.factory().creatable_small < ::tetris::view >();

      if (!::estamira::application::init_instance())
      {

         return false;

      }

      set_local_data_key_modifier();

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


   void application::term_instance()
   {

      ::core::application::term_instance();

   }


   void application::on_request(::create * pcreate)
   {

      m_ptemplateTetrisMain->request_create(pcreate);

      if(!pcreate->m_spCommandLine->m_varFile.is_empty())
      {

         m_ptemplateTetrisView->request_create(pcreate);

      }

   }


} // namespace tetris




extern "C"
::aura::library * game_tetris_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::tetris::application >(papp, "game/tetris");

}


