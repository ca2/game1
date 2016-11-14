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


      virtual bool initialize_application();
      virtual int32_t  exit_application() override;

      virtual void on_request(sp(::create) pcreatecontext);


   };


} // namespace arch001





