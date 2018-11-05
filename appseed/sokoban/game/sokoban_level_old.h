#pragma once 


#include <math.h>


namespace sokoban
{



   class _sokoban
   {
   public:
      float blockWidth{60.f},blockHeight{20.f};


      // Copyright (c) 2013-2015 Vittorio Romeo
      // License: Academic Free License ("AFL") v. 3.0
      // AFL License page: http://opensource.org/licenses/AFL-3.0

      int windowWidth{800},windowHeight{600};
      int countBlocksX{11},countBlocksY{4};

      struct Ball
      {
         //CircleShape shape;
         ::rect m_rect;
         ::pointd m_v;
         //::draw2d::brush_sp m_brush;
         ::visual::dib_sp m_dib;
         float ballRadius = 10.0f;
         float	ballVelocity{16.f};

         Ball(::aura::application * papp,float mX,float mY):
            //m_brush(papp->allocer())
            m_dib(papp->allocer())
         {
            m_rect.left = mX - ballRadius;
            m_rect.top = mY - ballRadius;
            m_rect.right = mX + ballRadius;
            m_rect.bottom = mY + ballRadius;
            //m_brush->create_solid(ARGB(255,255,0,0));
            m_dib.load_from_matter("yellow_ball.png");
            m_v.x = ballVelocity;
            m_v.y = ballVelocity;
         }

         void update(float dt,_sokoban * psokoban)
         {

            if(m_rect.left < 0) m_v.x = ballVelocity;
            else if(m_rect.right > psokoban->windowWidth) m_v.x = -ballVelocity;

            if(m_rect.top < 0) m_v.y = ballVelocity;
            else if(m_rect.bottom > psokoban->windowHeight) m_v.y = -ballVelocity;

            m_rect.offset(m_v.x * dt,m_v.y * dt);

         }


         void draw(::draw2d::dib * pdib)
         {

            //pdc->SelectObject(m_brush);

            //pdc->FillEllipse(m_rect);

            pdc->StretchBlt(m_rect.left,m_rect.top,m_rect.width(),m_rect.height(),m_dib->get_graphics(),0,0,m_dib->m_size.cx,m_dib->m_size.cy,SRCCOPY);

         }

      };


      struct Rectangle
      {
         
         ::rect m_rect;

         COLORREF m_cr;
         
         void draw(::draw2d::dib * pdib)
         {

            pdc->FillSolidRect(m_rect, m_cr);

         }

      };


      struct Paddle: public Rectangle
      {

         ::pointd m_v;
         float paddleWidth{120.f},paddleHeight{20.f},paddleVelocity{23.f};
         int iLeft;

         Paddle(float mX,float mY)
         {
            m_rect.left = mX;
            m_rect.top = mY;
            m_rect.right = mX + paddleWidth;
            m_rect.bottom = mY + paddleHeight;
            m_cr = ARGB(255,255,0,0);
            iLeft = 0;
         }

         void update(float dt,_sokoban * psokoban)
         {

            m_rect.offset(m_v.x * dt,m_v.y * dt);
            if(iLeft> 0 && m_rect.left > 0)
               m_v.x = -paddleVelocity;
            else if(iLeft< 0 && m_rect.right && psokoban->windowWidth)
               m_v.x = paddleVelocity;
            else
               m_v.x = 0;

         }

         void key_left_up(_sokoban * psokoban)
         {
            
            iLeft = 1;
         }

         void key_right_up(_sokoban * psokoban)
         {
            iLeft = -1;

         }

         void key_down(_sokoban * psokoban)
         {

            iLeft = 0;

         }

      };


      struct Brick: public Rectangle
      {
         
         bool destroyed{false};

         float blockWidth{60.f},blockHeight{20.f};

         Brick() { }

         Brick(float mX,float mY, float w, float h)
         {
            blockWidth = w;
            blockHeight = h;
            m_rect.left = mX;
            m_rect.top = mY;
            m_rect.right = mX + blockWidth;
            m_rect.bottom = mY + blockHeight;
            m_cr = ARGB(255,255,255,255);
         }


         void draw(::draw2d::dib * pdib)
         {

            ::rect r = m_rect;
            ::count c = 4;
            for(index i = 0; i < c; i++)
            {
               int a = ((c - i) * 123) / c;
               r.inflate(1,1);
               pdc->Draw3dRect(r,ARGB(a,49,184,255),ARGB(a,49,184,255));
            }

            Rectangle::draw(pdc);

         }


      };

      Ball ball;
      Paddle paddle;
      array<Brick> bricks;



      template<class T1,class T2> bool isIntersecting(T1& mA,T2& mB)
      {
         ::rect r;
         return r.intersect(mA.m_rect, mB.m_rect);
      }


      void testCollision(Paddle& mPaddle,Ball& mBall)
      {

         if(!isIntersecting(mPaddle,mBall))
         {

            return;

         }

         mBall.m_v.y = -mBall.ballVelocity;

         if(mBall.m_rect.center().x < mPaddle.m_rect.center().x)
         {

            mBall.m_v.x = -mBall.ballVelocity;

         }
         else
         {

            mBall.m_v.x = mBall.ballVelocity;

         }

      }


      void testCollision(Brick& mBrick,Ball& mBall)
      {
         
         if(!isIntersecting(mBrick,mBall))
            return;

         mBrick.destroyed = true;

         float overlapLeft = mBall.m_rect.right - mBrick.m_rect.left;
         float overlapRight = mBrick.m_rect.right - mBall.m_rect.left;
         float overlapTop = mBall.m_rect.bottom - mBrick.m_rect.top;
         float overlapBottom = mBrick.m_rect.bottom - mBall.m_rect.top;

         bool ballFromLeft(fabs(overlapLeft) < fabs(overlapRight));
         bool ballFromTop(fabs(overlapTop) < fabs(overlapBottom));

         float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
         float minOverlapY{ballFromTop ? overlapTop : overlapBottom};

         if(abs(minOverlapX) < abs(minOverlapY))
            mBall.m_v.x = ballFromLeft ? -mBall.ballVelocity : mBall.ballVelocity;
         else
            mBall.m_v.y = ballFromTop ? -mBall.ballVelocity : mBall.ballVelocity;
      }

      void reset()
      {

         for(int iX{0}; iX < countBlocksX; ++iX)
            for(int iY{0}; iY < countBlocksY; ++iY)
               bricks.fadd((iX + 1) * (blockWidth + 3) + 22,(iY + 2) * (blockHeight + 3),blockWidth,blockHeight);

      }

      _sokoban(::aura::application * papp) :
         ball(papp, windowWidth / 2,windowHeight / 2),
         paddle(windowWidth / 2,windowHeight - 50)
      {

         reset();


      }

      void draw(::draw2d::dib * pdib)
      {
         //window.clear(Color::Black);

         //if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;

         double dt = 60.0 / 60.0;

         ball.update(dt, this);
         paddle.update(dt, this);
         testCollision(paddle,ball);
         for(auto& brick : bricks) testCollision(brick,ball);
         bricks.remove_pred([](const Brick& mBrick){ return mBrick.destroyed; });


         ball.draw(pdc);
         paddle.draw(pdc);
         bricks.each([=](Brick& mBrick){ return mBrick.draw(pdc); });

      }

   };


} // namespace sokoban




