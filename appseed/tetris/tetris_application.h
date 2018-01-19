#pragma once


namespace tetris
{


   class CLASS_DECL_GAME_TETRIS application :
      virtual public ::estamira::application
   {
   public:


      sp(::user::single_document_template)  m_ptemplateTetrisMain;
      sp(::user::single_document_template)  m_ptemplateTetrisView;


      application();
      virtual ~application();


      virtual bool init_instance() override;
      virtual void term_instance() override;

      virtual void on_request(::create * pcreate);


   };


} // namespace tetris





