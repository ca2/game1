#pragma once


namespace sokoban
{


   class CLASS_DECL_APP_CORE_SOKOBAN application :
      virtual public ::estamira::application
   {
   public:
      
      
      sp(::user::single_document_template)  m_ptemplateSokobanMain;
      sp(::user::single_document_template)  m_ptemplateSokobanView;


      application();
      virtual ~application();


      virtual bool initialize_application();
      virtual int32_t  exit_application() override;

      virtual void on_request(sp(::create) pcreatecontext);


   };


} // namespace sokoban





