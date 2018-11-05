#include "framework.h"
#include <math.h>


namespace particle
{


   namespace effect
   {


      bool attractor::initialize(size_t numParticles, size_t lifeCount)
      {
         //
         // particles
         //
         const size_t NUM_PARTICLES = numParticles == 0 ? 250000 : numParticles;
         m_psystem = canew(class system(get_app(), NUM_PARTICLES, lifeCount));

         //
         // common
         //
         m_colGenerator = canew(generator::color::basic(get_app()));
         m_colGenerator->m_minStartCol = vec4{ 0.99, 0.99, 0.99, 1.0 };
         m_colGenerator->m_maxStartCol = vec4{ 0.99, 0.99, 1.0, 1.0 };
         m_colGenerator->m_minEndCol = vec4{ 0.99, 0.99, 0.99, 0.0 };
         m_colGenerator->m_maxEndCol = vec4{ 0.99, 0.99, 1.0, 0.25 };

         auto velGenerator = canew(generator::velocity::sphere(get_app()));
         velGenerator->m_minVel = 0.1f;
         velGenerator->m_maxVel = 0.1f;

         auto timeGenerator = canew(generator::time::basic(get_app()));
         timeGenerator->m_minTime = 1.6f;
         timeGenerator->m_maxTime = 4.0f;

         //
         // emitter 1:
         //
         auto particleEmitter = canew(emitter(get_app()));
         {
            particleEmitter->m_emitRate = (float)NUM_PARTICLES*0.1f;

            // pos:
            m_posGenerators.add(canew(generator::position::box(get_app())));
            m_posGenerators.last().m_pos = vec4{ 0.0, 0.0, -0.25, 0.0 };
            m_posGenerators.last().m_maxStartPosOffset = vec4{ 0.0, 0.0, 0.0, 0.0 };
            particleEmitter->addGenerator(m_posGenerators[0]);

            particleEmitter->addGenerator(m_colGenerator);
            particleEmitter->addGenerator(velGenerator);
            particleEmitter->addGenerator(timeGenerator);
         }
         m_psystem->addEmitter(particleEmitter);

         //
         // emitter 2:
         //
         auto particleEmitter2 = canew(emitter(get_app()));
         {
            particleEmitter2->m_emitRate = (float)NUM_PARTICLES*0.1f;

            m_posGenerators.add(canew(generator::position::box(get_app())));
            m_posGenerators.last().m_pos = vec4{ 0.0, 0.0, 0.25, 0.0 };
            m_posGenerators.last().m_maxStartPosOffset = vec4{ 0.0, 0.0, 0.0, 0.0 };
            particleEmitter2->addGenerator(m_posGenerators[1]);

            particleEmitter2->addGenerator(m_colGenerator);
            particleEmitter2->addGenerator(velGenerator);
            particleEmitter2->addGenerator(timeGenerator);
         }
         m_psystem->addEmitter(particleEmitter2);

         //
         // emitter 3:
         //
         auto particleEmitter3 = canew(emitter(get_app()));
         {
            particleEmitter3->m_emitRate = (float)NUM_PARTICLES*0.1f;

            m_posGenerators.add(canew(generator::position::box  (get_app())));
            m_posGenerators.last().m_pos = vec4{ 0.0, 0.0, 0.25, 0.0 };
            m_posGenerators.last().m_maxStartPosOffset = vec4{ 0.0, 0.0, 0.0, 0.0 };
            particleEmitter3->addGenerator(m_posGenerators[2]);

            particleEmitter3->addGenerator(m_colGenerator);
            particleEmitter3->addGenerator(velGenerator);
            particleEmitter3->addGenerator(timeGenerator);
         }
         m_psystem->addEmitter(particleEmitter3);

         //
         // updaters:
         //
         auto timeUpdater = canew(updaters::BasicTimeUpdater(get_app()));
         m_psystem->addUpdater(timeUpdater);

         auto colorUpdater = canew(updaters::VelColorUpdater(get_app()));
         colorUpdater->m_minVel = vec4{ -0.5f, -0.5f, -0.5f, 0.0f };
         colorUpdater->m_maxVel = vec4{ 2.0f, 2.0f, 2.0f, 2.0f };
         m_psystem->addUpdater(colorUpdater);

         m_attractors = canew(updaters::AttractorUpdater(get_app()));
         m_attractors->add(vec4{ 0.0, 0.0, 0.75, 1.0 });
         m_attractors->add(vec4{ 0.0, 0.0, -0.75, 1.0 });
         m_attractors->add(vec4{ 0.0, 0.75, 0.0, 1.0 });
         m_attractors->add(vec4{ 0.0, -0.75, 0.0, 1.0 });
         m_psystem->addUpdater(m_attractors);

         auto eulerUpdater = canew(updaters::EulerUpdater(get_app()));
         eulerUpdater->m_globalAcceleration = vec4{ 0.0, 0.0, 0.0, 0.0 };
         m_psystem->addUpdater(eulerUpdater);

         m_zScale = 1.0f;

         return true;
      }

      bool attractor::initializeRenderer()
      {
         m_prenderer = Application.renderer_factory().create("impl");
         m_prenderer->generate(NULL, m_psystem, false);

         return true;
      }

      void attractor::clean()
      {
         if (m_prenderer) m_prenderer->destroy();
      }

      void attractor::addUI()
      {
         //ui::AddTweakColor4f("start col min", &m_colGenerator->m_minStartCol.x, "group=effect");
         //ui::AddTweakColor4f("start col max", &m_colGenerator->m_maxStartCol.x, "group=effect");
         //ui::AddTweakColor4f("end col min", &m_colGenerator->m_minEndCol.x, "group=effect");
         //ui::AddTweakColor4f("end col max", &m_colGenerator->m_maxEndCol.x, "group=effect");
         //ui::AddTweak("z scale", &m_zScale, "min=0.0 max=1.0 step=0.05 group=effect");
         //for (size_t i = 0; i < m_attractors->collectionSize(); ++i)
         //   ui::AddTweak(("attr " + std::to_string(i + 1)).c_str(), &(m_attractors->get(i)).w, "min=-1.0 max=1.0 step=0.05 group=effect");
      }

      void attractor::removeUI()
      {
         //ui::RemoveVar("start col min");
         //ui::RemoveVar("start col max");
         //ui::RemoveVar("end col min");
         //ui::RemoveVar("end col max");
         //ui::RemoveVar("z scale");
         //for (size_t i = 0; i < m_attractors->collectionSize(); ++i)
         //   ui::RemoveVar(("attr " + std::to_string(i + 1)).c_str());
      }

      void attractor::update(double dt)
      {
         static double time = 0.0;
         time += dt;

         m_posGenerators[0]->m_pos.x = 0.15f*sinf((float)time*2.5f);
         m_posGenerators[0]->m_pos.y = 0.15f*cosf((float)time*2.5f);
         m_posGenerators[0]->m_pos.z = m_zScale * 0.25f*cosf((float)time*2.5f);

         m_posGenerators[1]->m_pos.x = -0.15f*sinf((float)time*2.f);
         m_posGenerators[1]->m_pos.y = 0.15f*cosf((float)time*2.f);
         m_posGenerators[1]->m_pos.z = m_zScale * 0.25f*cosf((float)time*1.5f);

         m_posGenerators[2]->m_pos.x = -0.15f*sinf((float)time*1.5f);
         m_posGenerators[2]->m_pos.y = 0.15f*cosf((float)time*2.5f);
         m_posGenerators[2]->m_pos.z = m_zScale * 0.25f*cosf((float)time*1.75f);
      }

      void attractor::cpuUpdate(double dt)
      {
         m_psystem->update(dt);
      }

      void attractor::gpuUpdate(double dt)
      {
         m_prenderer->update(NULL, NULL);
      }

      void attractor::render(::draw2d::graphics * pgraphics, float cx, float cy)
      {
         m_prenderer->render(pgraphics, cx, cy, m_psystem);
      }


   } // namespace effect


} // namespace particle



