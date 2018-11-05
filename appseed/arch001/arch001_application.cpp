#include "framework.h"


namespace arch001
{


   application::application()
   {

      m_strAppId              = "game/arch001";
      m_strAppName            = "game/arch001";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;

   }


   application::~application()
   {
   }


   bool application::init_instance()
   {

      System.factory().creatable_small < ::arch001::pane_view >();
      System.factory().creatable_small < ::arch001::document >();
      System.factory().creatable_small < ::arch001::frame >();
      System.factory().creatable_small < ::arch001::main_frame >();
      System.factory().creatable_small < ::arch001::view >();

      if(!::multimedia::application::init_instance())
         return false;

      set_local_data();

      ::user::single_document_template* pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "frame",
      System.type_info < ::arch001::document > (),
      System.type_info < ::arch001::main_frame > (),       // top level SDI frame::user::interaction_impl
      System.type_info < ::arch001::pane_view > ());
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseMain = pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "frame",
      System.type_info < ::arch001::document > (),
      System.type_info < ::arch001::frame > (),       // top level SDI frame::user::interaction_impl
      System.type_info < ::arch001::view > ());
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


} // namespace arch001




extern "C"
::aura::library * game_arch001_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::arch001::application >(papp, "game/arch001");

}





