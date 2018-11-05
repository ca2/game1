#include "framework.h"


namespace particle
{


   namespace effect
   {


      bool tunnel::initialize(size_t numParticles, size_t lifeCount)
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
            particleEmitter->m_emitRate = (float)NUM_PARTICLES*0.45f;

            // pos:
            m_posGenerator = canew(generator::position::round(get_app()));
            m_posGenerator->m_center = vec4{ 0.0, 0.0, 0.0, 0.0 };
            m_posGenerator->m_radX = 0.15f;
            m_posGenerator->m_radY = 0.15f;
            particleEmitter->addGenerator(m_posGenerator);

            m_colGenerator = canew(generator::color::basic(get_app()));
            m_colGenerator->m_minStartCol = vec4{ 0.7, 0.0, 0.7, 1.0 };
            m_colGenerator->m_maxStartCol = vec4{ 1.0, 1.0, 1.0, 1.0 };
            m_colGenerator->m_minEndCol = vec4{ 0.5, 0.0, 0.6, 0.0 };
            m_colGenerator->m_maxEndCol = vec4{ 0.7, 0.5, 1.0, 0.0 };
            particleEmitter->addGenerator(m_colGenerator);

            auto velGenerator = canew(generator::velocity::basic(get_app()));
            velGenerator->m_minStartVel = vec4{ 0.0f, 0.0f, 0.15f, 0.0f };
            velGenerator->m_maxStartVel = vec4{ 0.0f, 0.0f, 0.45f, 0.0f };
            particleEmitter->addGenerator(velGenerator);

            auto timeGenerator = canew(generator::time::basic(get_app()));
            timeGenerator->m_minTime = 1.0;
            timeGenerator->m_maxTime = 3.5;
            particleEmitter->addGenerator(timeGenerator);
         }
         m_psystem->addEmitter(particleEmitter);

         auto timeUpdater = canew(updaters::BasicTimeUpdater(get_app()));
         m_psystem->addUpdater(timeUpdater);

         auto colorUpdater = canew(updaters::BasicColorUpdater(get_app()));
         //colorUpdater->m_minPos = vec4{ -1.0f };
         //colorUpdater->m_maxPos = vec4{ 1.0f };
         m_psystem->addUpdater(colorUpdater);

         auto eulerUpdater = canew(updaters::EulerUpdater(get_app()));
         eulerUpdater->m_globalAcceleration = vec4{ 0.0, 0.0, 0.0, 0.0 };
         m_psystem->addUpdater(eulerUpdater);

         return true;
      }

      bool tunnel::initializeRenderer()
      {
         m_prenderer = Application.renderer_factory().create("impl");
         m_prenderer->generate(NULL, m_psystem, false);

         return true;
      }

      void tunnel::clean()
      {
         if (m_prenderer) m_prenderer->destroy();
      }

      void tunnel::addUI()
      {
         //ui::AddTweakColor4f("start col min", &m_colGenerator->m_minStartCol.x, "group=effect");
         //ui::AddTweakColor4f("start col max", &m_colGenerator->m_maxStartCol.x, "group=effect");
         //ui::AddTweakColor4f("end col min", &m_colGenerator->m_minEndCol.x, "group=effect");
         //ui::AddTweakColor4f("end col max", &m_colGenerator->m_maxEndCol.x, "group=effect");
      }

      void tunnel::removeUI()
      {
         //ui::RemoveVar("start col min");
         //ui::RemoveVar("start col max");
         //ui::RemoveVar("end col min");
         //ui::RemoveVar("end col max");
      }

      void tunnel::update(double dt)
      {
         static double time = 0.0;
         time += dt;

         m_posGenerator->m_center.x = 0.1f*sin((float)time*2.5f);
         m_posGenerator->m_center.y = 0.1f*cos((float)time*2.5f);
         m_posGenerator->m_radX = 0.15f + 0.05f*sin((float)time);
         m_posGenerator->m_radY = 0.15f + 0.05f*sin((float)time)*cosf((float)time*0.5f);
      }

      void tunnel::cpuUpdate(double dt)
      {
         m_psystem->update(dt);
      }

      void tunnel::gpuUpdate(double dt)
      {
         m_prenderer->update(NULL, NULL);
      }

      void tunnel::render(::draw2d::graphics * pgraphics, float cx, float cy)
      {
         m_prenderer->render(pgraphics, cx, cy, m_psystem);
      }


   } // namespace effect


} // namespace particle




