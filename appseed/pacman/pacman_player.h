#pragma once



namespace pacman
{

   class pacman;

   class player :
      virtual public console_composite
   {
   public:
      int y,x;
      int yold,xold;
      int yinit,xinit;
      int wait;
      int left;
      int score;
      int scoreinc;
      int hiscore;
      int lives;
      int super;
      int killcount;
      int color;
      char momentum;
      char dir;
      char dirold;
      char icon;
      LEVEL & level;
      pacman * m_ppacman;

      player(pacman * ppacman);

      void move();
      void getdirection();
      bool testforcollision();
      bool testforcollision(char d);
      void printscore();
      void printlives();
      void printkillscore();
      void dead();
      void show();
      void hide();
      
   };


} // namespace pacman




