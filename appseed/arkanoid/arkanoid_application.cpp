#include "framework.h"


namespace arkanoid
{


   application::application()
   {

      m_strAppId              = "game/arkanoid";
      m_strAppName            = "game/arkanoid";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;


   }


   application::~application()
   {
   }


   bool application::init_instance()
   {

      System.factory().creatable_small < ::arkanoid::pane_view >();
      System.factory().creatable_small < ::arkanoid::document >();
      System.factory().creatable_small < ::arkanoid::frame >();
      System.factory().creatable_small < ::arkanoid::view >();

      if(!::estamira::application::init_instance())
         return false;

      set_local_data_key_modifier();

      ::user::single_document_template* pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "frame",
      System.type_info < ::arkanoid::document > (),
      System.type_info < ::arkanoid::frame > (),       // top level SDI frame::user::interaction_impl
      System.type_info < ::arkanoid::pane_view > ());
      add_document_template(pDocTemplate);
      m_ptemplateArkanoidMain = pDocTemplate;

      pDocTemplate = new ::user::single_document_template(
      this,
      "frame",
      System.type_info < ::arkanoid::document > (),
      System.type_info < ::arkanoid::frame > (),       // top level SDI frame::user::interaction_impl
      System.type_info < ::arkanoid::view > ());
      add_document_template(pDocTemplate);
      m_ptemplateArkanoidView = pDocTemplate;

      return true;

   }


   void application::term_instance()
   {

      ::core::application::term_instance();

   }


   void application::on_request(::create * pcreate)
   {

      m_ptemplateArkanoidMain->request_create(pcreate);

      if(!pcreate->m_spCommandLine->m_varFile.is_empty())
      {

         m_ptemplateArkanoidView->request_create(pcreate);

      }

   }


} // namespace arkanoid




extern "C"
::aura::library * game_arkanoid_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::arkanoid::application >(papp, "game/arkanoid");

}


