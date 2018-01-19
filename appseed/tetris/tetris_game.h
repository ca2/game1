#pragma once


namespace tetris
{



   class game :
      virtual public ::estamira::game,
      virtual public _TetrisInterface
   {
   public:

      class Thread:
         virtual public thread
      {
      public:

         game * m_ptetris;

         Thread(::aura::application * papp);

         virtual void run() override;

      };


      ::tetris::view * m_pparent;
      int2a cells;
      int2a cellsOverride;
      int2a offCells;
      int cellSizeInPixels;
      int widthInCells,heightInCells;
      int widthInPixels,heightInPixels;
      int curX,curY,curType,curRotation;
      //::draw2d::dib_sp m_dib;
      bool canMove;
      bool atPause;
      bool atGame;
      bool isMoving;
      bool isDropping;
      bool isKilling;
      bool Toggle;
      bool refresh;
      long delay;
      Thread * m_pthread;
      double score;
      int level;
      int thisLevelFlashes;
      int killed;
      int aux;
      int pauseAux;



      game(::aura::application * papp, int widthInCells_,
           int heightInCells_,
           int cellSizeInPixels_,
           ::tetris::view * pview);

      void init(int widthInCells_,
                int heightInCells_,
                int cellSizeInPixels_);

      void initPaint();



      void Score(int type,int arg);

      ::size preferredSize();

      void run();

      virtual void on_key_down(::user::e_key ekey) override;

      virtual bool start(::user::interaction * pui);


      void startBlock();





      virtual int hit_test(point pt);



      void moveDown();

      virtual void moveLeft(index iChar) override;

      virtual void moveRight(index iChar) override;

      void rotate(bool ClockWising);

      void drop();

      virtual bool get_char_rect(LPRECT lprect, index iChar, bool bPlatformCall) override;

      void killRows();


      void flashLineOnly(int y,int times,float delay);
      virtual bool canMoveDown(int iChar);

      virtual bool canMoveLeft(int iChar);

      virtual bool canMoveRight( int iChar);

      bool canRotate(bool ClockWise);



      bool isValidPosition(int testX,int testY,int testType,int testRotation);

      bool isOutOfLimits(int testX,int testY);



      void drawBlock(int mode);

      void drawCell(int x,int y,int color);

      //void myPaint();




      virtual void _001OnDraw(::draw2d::graphics * pgraphics);




   };


} // namespace tetris




