#pragma once


namespace coincube
{


   class CLASS_DECL_GAME_COINCUBE application :
      virtual public ::estamira::application
   {
   public:
      
      
      sp(::user::single_document_template)  m_ptemplateHelloMultiverseMain;
      sp(::user::single_document_template)  m_ptemplateHelloMultiverseView;


      application();
      virtual ~application();


      virtual bool initialize_application();
      virtual int32_t  exit_application() override;

      virtual void on_request(::create * pcreate);


   };


} // namespace coincube





