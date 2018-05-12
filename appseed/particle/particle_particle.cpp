#include "framework.h"


#define  DRAW 1
#define  UNDRAW 0

#define  TOTALPOSITIONS 4
#define  TOTALSHIFTS 8
#define  TOTALFLASHES 15

#define  SCOREPERROW 100.0
#define  ADDPERROW 0.17
#define  ROWSPERLEVEL 20.0
#define  ADDROWSPERLEVEL 0.25
#define  DROPADDUNIT 0.2

#define  ROWTYPE 1
#define  DROPUNITTYPE 2

#define  DELAYPERLEVEL .85



namespace particle
{

   particle::particle(::aura::application * papp) :
      ::object(papp),
      m_ball(papp),
      m_dibBrick(allocer())
   {

      int wBrick = 60;
      int hBrick = 20;

      if(m_dibBrick->create(wBrick, hBrick))
      {
         ::rect r(0, 0, wBrick, wBrick);
         ::count c = 4;
         m_dibBrick->get_graphics()->fill_solid_rect(r, ARGB(255, 128, 140, 160));
         for (index i = 0; i < c; i++)
         {
            int a = ((i + 1) * 123) / c;
            m_dibBrick->get_graphics()->draw3d_rect(r, ARGB(a, 200, 200, 255), ARGB(a, 0, 0, 155));
            r.deflate(1, 1);
         }

      }

      windowWidth = 800;
      windowHeight = 600;

      m_psound = canew(::multimedia::sound_track(get_app()));
      m_psound->audio_plugin_initialize();

      for (int i = 0; i < 64; i++)
      {
         m_psound->sound_plugin("bounce", true);
         m_psound->sound_plugin("destroy", true);
         m_psound->sound_plugin("paddle", true);
      }

      reset();


   }


   void particle::testCollision(Paddle& mPaddle, Ball& mBall)
   {

      if (!mPaddle.intersects(mBall))
      {

         return;

      }

      mBall.m_v.y = -mBall.ballVelocity;

      if (mBall.m_rect.center().x < mPaddle.m_rect.center().x)
      {

         mBall.m_v.x = -mBall.ballVelocity;

      }
      else
      {

         mBall.m_v.x = mBall.ballVelocity;

      }

      m_psound->queue("wait:paddle");

   }




   particle::Ball::Ball(::aura::application * papp) :
      //m_brush(papp->allocer())
      m_dibBall0(papp->allocer()),
      m_dibBall(papp->allocer())
   {

      if (m_dibBall0.load_from_matter("yellow_ball.png"))
      {

         if (m_dibBall->create(ballRadius, ballRadius))
         {


            m_dibBall->get_graphics()->StretchBlt(rect(0, 0, ballRadius, ballRadius), m_dibBall0->get_graphics(), rect(null_point(), m_dibBall0->m_size));

         }

      }

      m_v.x = ballVelocity;
      m_v.y = ballVelocity;
   }

   void particle::Ball::init(float mX, float mY)
   {

      m_rect.left = mX - ballRadius;
      m_rect.top = mY - ballRadius;
      m_rect.right = mX + ballRadius;
      m_rect.bottom = mY + ballRadius;
      //m_brush->create_solid(ARGB(255,255,0,0));


   }

   void particle::Ball::update(float dt, particle * pparticle)
   {

      bool bHit = false;
      if (m_rect.left < 0)
      {
         m_v.x = ballVelocity;
         bHit = true;
      }
      else if (m_rect.right > pparticle->windowWidth)
      {
         m_v.x = -ballVelocity;
         bHit = true;
      }

      if (m_rect.top < 0)
      {
         m_v.y = ballVelocity;
         bHit = true;
      }
      else if (m_rect.bottom > pparticle->windowHeight)
      {
         m_v.y = -ballVelocity;
         bHit = true;
      }

      if (bHit)
      {
         pparticle->m_psound->queue("wait:bounce");
      }
      else
      {
         output_debug_string(".");
      }
      m_rect.offset(m_v.x * dt, m_v.y * dt);

   }


   void particle::Ball::draw(::draw2d::graphics * pgraphics)
   {

      pgraphics->StretchBlt(m_rect.left, m_rect.top, m_rect.width(), m_rect.height(), m_dibBall->get_graphics(), 0, 0, m_dibBall->m_size.cx, m_dibBall->m_size.cy, SRCCOPY);

   }

   void particle::Element::draw(::draw2d::graphics * pgraphics)
   {

      pgraphics->fill_solid_rect(m_rect, m_cr);

   }



   particle::Paddle::Paddle()
   {

      paddleWidth = 120.f;
      paddleHeight = 20.f;
      paddleVelocity = 23.f;
      m_cr = ARGB(255, 255, 0, 0);
      iLeft = 0;

   }


   void particle::Paddle::init(float mX, float mY)
   {

      m_rect.left = mX;
      m_rect.top = mY;
      m_rect.right = mX + paddleWidth;
      m_rect.bottom = mY + paddleHeight;
   }

   void particle::Paddle::update(float dt, particle * pparticle)
   {

      m_rect.offset(m_v.x * dt, m_v.y * dt);
      if (iLeft> 0 && m_rect.left > 0)
         m_v.x = -paddleVelocity;
      else if (iLeft< 0 && m_rect.right && pparticle->windowWidth)
         m_v.x = paddleVelocity;
      else
         m_v.x = 0;

   }

   void particle::Paddle::key_left_up(particle * pparticle)
   {

      iLeft = 1;
   }

   void particle::Paddle::key_right_up(particle * pparticle)
   {
      iLeft = -1;

   }

   void particle::Paddle::key_down(particle * pparticle)
   {

      iLeft = 0;

   }



   particle::Brick::Brick()
   {

      destroyed = false;

      blockWidth = 60.f;
      blockHeight= 20.f ;

   }

   particle::Brick::Brick(float mX, float mY, float w, float h)
   {
      blockWidth = 60.f;
      blockHeight = 20.f;
      destroyed = false;
      blockWidth = w;
      blockHeight = h;
      m_rect.left = mX;
      m_rect.top = mY;
      m_rect.right = mX + blockWidth;
      m_rect.bottom = mY + blockHeight;
      m_cr = ARGB(255, 128, 128, 200);
   }


   void particle::Brick::draw(::draw2d::graphics * pgraphics, particle * pparticle)
   {


      pgraphics->draw(m_rect, pparticle->m_dibBrick->get_graphics());

   }

   void particle::testCollision(Brick& mBrick, Ball& mBall)
   {

      if (!mBrick.intersects(mBall))
         return;

      mBrick.destroyed = true;

      int iCount = System.math().RandRange(20, 40);

      sp(effect::effect) peffect = canew(effect::random_color_range_fountain(get_app(), mBall.m_rect.center().x, mBall.m_rect.center().y));
      peffect->initialize(200, iCount);
      peffect->initializeRenderer();
      m_effecta.add(peffect);

      float overlapLeft = mBall.m_rect.right - mBrick.m_rect.left;
      float overlapRight = mBrick.m_rect.right - mBall.m_rect.left;
      float overlapTop = mBall.m_rect.bottom - mBrick.m_rect.top;
      float overlapBottom = mBrick.m_rect.bottom - mBall.m_rect.top;

      bool ballFromLeft(fabs(overlapLeft) < fabs(overlapRight));
      bool ballFromTop(fabs(overlapTop) < fabs(overlapBottom));

      float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
      float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

      if (fabs(minOverlapX) < fabs(minOverlapY))
         mBall.m_v.x = ballFromLeft ? -mBall.ballVelocity : mBall.ballVelocity;
      else
         mBall.m_v.y = ballFromTop ? -mBall.ballVelocity : mBall.ballVelocity;
   }

   void particle::reset()
   {

      m_ball.init(windowWidth / 2, windowHeight / 2);

      m_paddle.init(windowWidth / 2, windowHeight - 50);

      for (int x = 0; x < countBlocksX; x++)
      {

         for (int y = 0; y < countBlocksY; y++)
         {

            m_bricks.fadd((x + 1) * (blockWidth + 3) + 22, (y + 2) * (blockHeight + 3), blockWidth, blockHeight);

         }

      }

   }


   void particle::draw(::draw2d::graphics * pgraphics)
   {

      double dt = 60.0 / 60.0;

      m_ball.update(dt, this);

      m_paddle.update(dt, this);

      testCollision(m_paddle, m_ball);

      ::count cTotalDestroyed = 0;

      for (auto & brick : m_bricks)
      {

         testCollision(brick, m_ball);

      }

      cTotalDestroyed += m_bricks.pred_remove([](const Brick& mBrick) { return mBrick.destroyed; });

      int iSound = MIN(cTotalDestroyed, 3);

      fork([this, iSound]()
      {

         for (int i = 0; i < iSound; i++)
         {

            m_psound->queue("wait:destroy");

            Sleep(20);

         }

      });


      m_ball.draw(pgraphics);

      m_paddle.draw(pgraphics);

      m_bricks.each([this, &pgraphics](Brick& mBrick)
      {

         return mBrick.draw(pgraphics, this);

      });


   }



} // namespace particle












