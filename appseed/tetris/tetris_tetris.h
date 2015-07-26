#pragma once 


namespace tetris
{



   class _Tetris :
      virtual public _TetrisInterface
   {
   public:

      class Thread:
         virtual public thread
      {
      public:

         _Tetris * m_ptetris;

         Thread(::aura::application * papp);

         virtual int32_t run();

      };


      ::tetris::view * m_pparent;
      int2a cells;
      int2a offCells;
      int cellSizeInPixels;
      int widthInCells,heightInCells;
      int widthInPixels,heightInPixels;
      int curX,curY,curType,curRotation;
      ::draw2d::dib_sp m_dib;
      bool canMove;
      bool atPause;
      bool atGame;
      bool isMoving;
      bool isDropping;
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



      _Tetris(int widthInCells_,
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



      void start();


      void startBlock();









      void moveDown();

      void moveLeft();



      void moveRight();

      void rotate(bool ClockWising);

      void drop();


      void killRows();


      void flashLineOnly(int y,int times,float delay);
      bool canMoveDown();

      bool canMoveLeft();

      bool canMoveRight();

      bool canRotate(bool ClockWise);



      bool isValidPosition(int testX,int testY,int testType,int testRotation);

      bool isOutOfLimits(int testX,int testY);



      void drawBlock(int mode);

      void drawCell(int x,int y,int color);

      //void myPaint();




      void paint();
      



   };


} // namespace tetris




