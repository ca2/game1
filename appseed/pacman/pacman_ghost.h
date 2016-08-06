#pragma once


namespace pacman
{


   class ghost :
      virtual public console_composite
   {
   public:
      int y,x;
      int yinit,xinit;
      int wait;
      int color;
      int colorinit;
      char dir;
      char dirold;
      char diropp;
      char mode;
      char modeold;
      bool up;
      bool left;
      bool down;
      bool right;
      LEVEL & level;
      pacman * m_ppacman;
      bool m_bIntermission;


      ghost(pacman * ppacman);

      void move(int,int);
      void targetobject();
      void randomdirection();
      bool testforcollision();
      void changecoords();
      void getopposite();
      void dead();
      void show();
      void hide();
   };

 
} //   namespace pacman











