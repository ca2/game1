#pragma once


namespace arkanoid
{


   class CLASS_DECL_APP_CORE_ARKANOID application :
      virtual public ::estamira::application
   {
   public:
      
      
      sp(::user::single_document_template)  m_ptemplateTetrisMain;
      sp(::user::single_document_template)  m_ptemplateTetrisView;


      application();
      virtual ~application();


      virtual bool init_instance();
      virtual int32_t  exit_application() override;

      virtual void on_request(::create * pcreate);


   };


} // namespace arkanoid





