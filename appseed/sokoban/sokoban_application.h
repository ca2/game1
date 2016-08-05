#pragma once


namespace sokoban
{


   class CLASS_DECL_APP_CORE_SOKOBAN application :
      virtual public ::hellomultiverse::application
   {
   public:
      
      
      sp(::user::single_document_template)  m_ptemplateTetrisMain;
      sp(::user::single_document_template)  m_ptemplateTetrisView;


      application();
      virtual ~application();


      virtual bool initialize_instance();
      virtual int32_t  exit_instance();

      virtual void on_request(sp(::create) pcreatecontext);


   };


} // namespace sokoban





