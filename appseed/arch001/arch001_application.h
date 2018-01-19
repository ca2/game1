#pragma once


namespace arch001
{


   class CLASS_DECL_GAME_ARCH001 application :
      virtual public ::estamira::application
   {
   public:


      sp(::user::single_document_template)  m_ptemplateHelloMultiverseMain;
      sp(::user::single_document_template)  m_ptemplateHelloMultiverseView;


      application();
      virtual ~application();


      virtual bool init_instance() override;
      virtual void term_instance() override;

      virtual void on_request(::create * pcreate);


   };


} // namespace arch001





