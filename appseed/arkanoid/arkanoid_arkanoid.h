#pragma once


namespace arkanoid
{


   class arkanoid :
      virtual public object
   {
   public:
      float blockWidth{60.f},blockHeight{20.f};


      // Copyright (c) 2013-2015 Vittorio Romeo
      // License: Academic Free License ("AFL") v. 3.0
      // AFL License page: http://opensource.org/licenses/AFL-3.0

      int windowWidth,windowHeight;
      int countBlocksX{11},countBlocksY{4};
      sp(::multimedia::sound_track)       m_psound;
      ::draw2d::dib_sp                    m_dibBrick;

      struct Element
      {

         ::rect m_rect;

         COLORREF m_cr;

         void draw(::draw2d::graphics * pgraphics);
         
         inline bool intersects(const Element & e)
         {
            return m_rect.intersects(e.m_rect);
         }

      };

      struct Ball : public Element
      {
         //CircleShape shape;
         ::pointd m_v;
         //::draw2d::brush_sp m_brush;
         ::visual::dib_sp m_dibBall0;
         ::visual::dib_sp m_dibBall;
         float ballRadius = 12.0f;
         float	ballVelocity{16.f};

         Ball(::aura::application * papp);
         
         void init(float mX, float mY);
         void update(float dt, arkanoid * parkanoid);
         void draw(::draw2d::graphics * pgraphics);

      };



      struct Paddle: public Element
      {

         ::pointd m_v;
         float paddleWidth;
         float paddleHeight;
         float paddleVelocity;
         int iLeft;

         Paddle();

         void init(float mX, float mY);

         void update(float dt, arkanoid * parkanoid);

         void key_left_up(arkanoid * parkanoid);

         void key_right_up(arkanoid * parkanoid);

         void key_down(arkanoid * parkanoid);

      };


      struct Brick: public Element
      {

         bool destroyed;

         float blockWidth;
         float blockHeight;

         Brick();

         Brick(float mX, float mY, float w, float h);


         void draw(::draw2d::graphics * pgraphics, arkanoid * parkanoid);


      };

      Ball                 m_ball;
      Paddle               m_paddle;
      array < Brick >      m_bricks;


      arkanoid(::aura::application * papp);


      void testCollision(Paddle& mPaddle, Ball& mBall);

      void testCollision(Brick& mBrick, Ball& mBall);

      void reset();

      void draw(::draw2d::graphics * pdib);

   };


} // namespace arkanoid




