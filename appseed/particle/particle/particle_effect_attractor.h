#pragma once


namespace particle
{


   namespace effect
   {


      class attractor : public effect
      {
      public:


         sp(class system) m_psystem;
         sp(renderer)   m_prenderer;
         spa(generator::position::box) m_posGenerators; //
         sp(generator::color::basic) m_colGenerator;
         sp(updaters::AttractorUpdater) m_attractors;
         float m_zScale;


         attractor(::aura::application * papp) : :: object(papp), effect(papp) { }
         ~attractor() { }

         bool initialize(size_t numParticles, size_t lifeCount) override;
         bool initializeRenderer() override;
         void reset() override { m_psystem->reset(); }
         void clean() override;
         void addUI() override;
         void removeUI() override;

         void update(double dt) override;
         void cpuUpdate(double dt) override;
         void gpuUpdate(double dt) override;
         void render(::draw2d::graphics * pgraphics, float cx, float cy) override;

         int numAllParticles() override { return m_psystem->numAllParticles(); }
         int numActiveParticles() override { return m_psystem->numActiveParticles(); }
      };


   } // namespace effect


} // namespace particle


