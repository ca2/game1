#pragma once


namespace particle
{


   class CLASS_DECL_GAME_PARTICLE application :
      virtual public ::estamira::application
   {
   public:


      sp(::user::single_document_template)  m_ptemplateParticleMain;
      sp(::user::single_document_template)  m_ptemplateParticleView;


      application();
      virtual ~application();


      virtual bool init_instance() override;
      virtual void term_instance() override;

      virtual void on_request(::create * pcreate);

   };


} // namespace particle





