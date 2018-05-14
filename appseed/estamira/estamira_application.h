#pragma once


namespace estamira
{


   class CLASS_DECL_ESTAMIRA application :
      virtual public ::multimedia::application
   {
   public:


      sp(::estamira::game)                m_pgame;


      sp(particle::renderer_factory)      m_prendererfactory;

      sp(particle::effect::factory)       m_peffectfactory;

      //spa(effect::effect)     m_effecta;

      //sp(effect::effect)      m_peffect;

      //index m_iCurrentEffect;



      application();
      virtual ~application();


      virtual bool init_instance() override;
      virtual void term_instance() override;
      virtual particle::renderer_factory & renderer_factory();


   };


} // namespace estamira





