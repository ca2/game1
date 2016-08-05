#pragma once 


namespace sokoban
{



   class level:
      virtual public ::object
   {
   public:


      int         m_iLevel;
      int         m_iWidth;
      stringa     m_stra;

      string      m_strMove;
      int         m_iRedo;



      level(::aura::application * papp);


      virtual bool initialize();

      void draw(::draw2d::graphics * pgraphics, asset * passet, int yOffset);

      bool can_move_up();
      bool can_move_down();
      bool can_move_left();
      bool can_move_right();

      bool move_up(bool bRedo);
      bool move_down(bool bRedo);
      bool move_left(bool bRedo);
      bool move_right(bool bRedo);

      char bl(int x,int y);

      bool bl(int x,int y, char ch);

      bool find_player(int & x,int & y);


      bool is_solved();

      void record(char ch);

      void undo();
      void redo();

      bool move(char ch,bool bRedo);

      bool _undo(char ch);
      bool _undo_up(bool bPush);
      bool _undo_down(bool bPush);
      bool _undo_left(bool bPush);
      bool _undo_right(bool bPush);

   };


} // namespace sokoban




