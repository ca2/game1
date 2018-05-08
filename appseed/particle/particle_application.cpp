#include "framework.h"


namespace particle
{


   application::application()
   {

      m_strAppId              = "game/particle";
      m_strAppName            = "game/particle";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;


   }


   application::~application()
   {
   }


   bool application::init_instance()
   {

      int iDefaultParticleCount = 100;
      int iDefaultParticleLifeCount = 100;

      m_prendererfactory = canew(class renderer_factory(this));
      m_peffectfactory = canew(effect::factory(this));

      sp(effect::effect) peffect;

      peffect = m_peffectfactory->create("tunnel");
      peffect->initialize(iDefaultParticleCount, iDefaultParticleLifeCount);
      peffect->initializeRenderer();
      m_effecta.add(peffect);

      peffect = m_peffectfactory->create("attractors");
      peffect->initialize(iDefaultParticleCount, iDefaultParticleLifeCount);
      peffect->initializeRenderer();
      m_effecta.add(peffect);

      peffect = m_peffectfactory->create("fountain");
      peffect->initialize(iDefaultParticleCount, iDefaultParticleLifeCount);
      peffect->initializeRenderer();
      m_effecta.add(peffect);

      m_iCurrentEffect = 2;

      m_peffect = m_effecta[m_iCurrentEffect];


      System.factory().creatable_small < ::particle::pane_view >();
      System.factory().creatable_small < ::particle::document >();
      System.factory().creatable_small < ::particle::frame >();
      System.factory().creatable_small < ::particle::main_frame >();
      System.factory().creatable_small < ::particle::view >();

      if(!::estamira::application::init_instance())
         return false;

      set_local_data_key_modifier();

      ::user::single_document_template* pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "frame",
      System.type_info < ::particle::document > (),
      System.type_info < ::particle::main_frame > (),       // top level SDI frame::user::interaction_impl
      System.type_info < ::particle::pane_view > ());
      add_document_template(pDocTemplate);
      m_ptemplateParticleMain = pDocTemplate;

      pDocTemplate = new ::user::single_document_template(
      this,
      "frame",
      System.type_info < ::particle::document > (),
      System.type_info < ::particle::frame > (),       // top level SDI frame::user::interaction_impl
      System.type_info < ::particle::view > ());
      add_document_template(pDocTemplate);
      m_ptemplateParticleView = pDocTemplate;

      return true;

   }


   void application::term_instance()
   {

      m_peffectfactory.release();
      m_prendererfactory.release();

      ::estamira::application::term_instance();

   }


   void application::on_request(::create * pcreate)
   {

      m_ptemplateParticleMain->request_create(pcreate);

      if(!pcreate->m_spCommandLine->m_varFile.is_empty())
      {

         m_ptemplateParticleView->request_create(pcreate);

      }

   }


   renderer_factory & application::renderer_factory()
   {

      return *m_prendererfactory;

   }

} // namespace particle




extern "C"
::aura::library * game_particle_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::particle::application >(papp, "game/particle");

}


