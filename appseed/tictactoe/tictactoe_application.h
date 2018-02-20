#pragma once


namespace tictactoe
{


   class CLASS_DECL_GAME_TICTACTOE application :
      public ::estamira::application
   {
   public:


      sp(::user::single_document_template)  m_ptemplateTicTacToeMain;
      sp(::user::single_document_template)  m_ptemplateTicTacToeView;


      application();
      virtual ~application();


      virtual bool init_instance() override;
      virtual void term_instance() override;

      virtual void on_request(::create * pcreate);


   };


} // namespace tictactoe





