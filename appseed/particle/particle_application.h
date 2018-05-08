#pragma once


namespace particle
{


   class CLASS_DECL_GAME_PARTICLE application :
      virtual public ::estamira::application
   {
   public:


      sp(::user::single_document_template)  m_ptemplateParticleMain;
      sp(::user::single_document_template)  m_ptemplateParticleView;


      sp(renderer_factory)    m_prendererfactory;

      sp(effect::factory)     m_peffectfactory;

      spa(effect::effect)     m_effecta;

      sp(effect::effect)      m_peffect;

      index m_iCurrentEffect;

      application();
      virtual ~application();


      virtual bool init_instance() override;
      virtual void term_instance() override;

      virtual void on_request(::create * pcreate);

      virtual renderer_factory & renderer_factory();

   };


} // namespace particle





