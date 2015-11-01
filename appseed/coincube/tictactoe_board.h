#pragma once



namespace tictactoe
{

   class CLASS_DECL_GAME_TICTACTOE  board:
      public array < array < e_check > >
   {
      public:


      board(::aura::application * papp);
      virtual ~board();
      
      
      void reset();
      bool is_free(int x, int y);



      e_check match(int i,int j);
      e_check match();


      bool is_full();


   };



} // namespace tictactoe



