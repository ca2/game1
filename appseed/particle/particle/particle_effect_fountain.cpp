#include "framework.h"
#include <math.h>


namespace particle
{


   namespace effect
   {


      bool fountain::initialize(size_t numParticles, size_t lifeCount)
      {
         //
         // particles
         //
         const size_t NUM_PARTICLES = numParticles == 0 ? 10000 : numParticles;
         m_psystem = canew(class system(get_app(), NUM_PARTICLES, lifeCount));

         //
         // emitter:
         //
         auto particleEmitter = canew(emitter(get_app()));
         {
            particleEmitter->m_emitRate = (float)NUM_PARTICLES*0.25f;

            // pos:
            m_posGenerator = canew(generator::position::box(get_app()));
            m_posGenerator->m_pos = vec4(m_cx, 0.0, m_cy, 0.0 );
            m_posGenerator->m_maxStartPosOffset = vec4{ 0.0, 0.0, 0.0, 0.0 };
            particleEmitter->addGenerator(m_posGenerator);

            m_colGenerator = canew(generator::color::basic(get_app()));
            m_colGenerator->m_minStartCol = vec4{ 1.0, 0.0, 0.1, 1.0 };
            m_colGenerator->m_maxStartCol = vec4{ 1.0, 1.0, 0.4, 1.0 };
            m_colGenerator->m_minEndCol = vec4{ 1.0, 0.0, 0.1, 0.0 };
            m_colGenerator->m_maxEndCol = vec4{ 1.0, 1.0, 0.4, 0.0 };
            particleEmitter->addGenerator(m_colGenerator);

            auto velGenerator = canew(generator::velocity::basic(get_app()));
            velGenerator->m_minStartVel = vec4{ -10.f, 0.f, -10.f, 0.0f };
            velGenerator->m_maxStartVel = vec4{ 10.f, 0.f, 10.f, 0.0f };
            particleEmitter->addGenerator(velGenerator);

            auto timeGenerator = canew(generator::time::basic(get_app()));
            timeGenerator->m_minTime = 3.0f;
            timeGenerator->m_maxTime = 4.0f;
            particleEmitter->addGenerator(timeGenerator);
         }
         m_psystem->addEmitter(particleEmitter);

         auto timeUpdater = canew(updaters::BasicTimeUpdater(get_app()));
         m_psystem->addUpdater(timeUpdater);

         auto colorUpdater = canew(updaters::BasicColorUpdater(get_app()));
         m_psystem->addUpdater(colorUpdater);

         m_eulerUpdater = canew(updaters::EulerUpdater(get_app()));
         m_eulerUpdater->m_globalAcceleration = vec4{ 0.0, -20.0, 0.0, 0.0 };
         m_psystem->addUpdater(m_eulerUpdater);

         m_floorUpdater = canew(updaters::FloorUpdater(get_app()));
         m_psystem->addUpdater(m_floorUpdater);

         return true;
      }

      bool fountain::initializeRenderer()
      {
         m_prenderer = Application.renderer_factory().create("impl");
         m_prenderer->generate(NULL, m_psystem, false);

         return true;
      }

      void fountain::clean()
      {
         if (m_prenderer) m_prenderer->destroy();
      }

      void fountain::addUI()
      {
         //ui::AddTweakColor4f("start col min", &m_colGenerator->m_minStartCol.x, "group=effect");
         //ui::AddTweakColor4f("start col max", &m_colGenerator->m_maxStartCol.x, "group=effect");
         //ui::AddTweakColor4f("end col min", &m_colGenerator->m_minEndCol.x, "group=effect");
         //ui::AddTweakColor4f("end col max", &m_colGenerator->m_maxEndCol.x, "group=effect");
         //ui::AddTweak("gravity", &m_eulerUpdater->m_globalAcceleration.y, "group=effect min=-20 max=0 step=0.05");
         //ui::AddTweak("bounce", &m_floorUpdater->m_bounceFactor, "group=effect min=0 max=1 step=0.05");
      }

      void fountain::removeUI()
      {
         //ui::RemoveVar("start col min");
         //ui::RemoveVar("start col max");
         //ui::RemoveVar("end col min");
         //ui::RemoveVar("end col max");
         //ui::RemoveVar("gravity");
         //ui::RemoveVar("bounce");
      }

      void fountain::update(double dt)
      {
         static double time = 0.0;
         time += dt;

         m_posGenerator->m_pos.x = 0.1f*sin((float)time*2.5f);
         m_posGenerator->m_pos.z = 0.1f*cos((float)time*2.5f);
      }

      void fountain::cpuUpdate(double dt)
      {
         m_psystem->update(dt);
      }

      void fountain::gpuUpdate(double dt)
      {
         m_prenderer->update(NULL, NULL);
      }

      void fountain::render(::draw2d::graphics * pgraphics, float cx, float cy)
      {
         m_prenderer->render(pgraphics, cx, cy, m_psystem);
      }


   } // namespace effect


} // namespace particle




