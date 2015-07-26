#pragma once


namespace tetris
{


   class CLASS_DECL_GAME_TETRIS application :
      virtual public ::hellomultiverse::application,
      virtual public ::html::application
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


} // namespace tetris





