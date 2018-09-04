#pragma once


namespace particle
{


   namespace effect
   {


      class CLASS_DECL_ESTAMIRA tunnel : public effect
      {
      private:

         sp(class system) m_psystem;
         renderer  *                      m_prenderer;

         sp(generator::position::round)   m_posGenerator;

         sp(generator::color::basic)      m_colGenerator;

      public:
         tunnel(::aura::application * papp) : ::object(papp), effect(papp) { }
         ~tunnel() { }

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

         ::count numAllParticles() override { return m_psystem->numAllParticles(); }
         ::count numActiveParticles() override { return m_psystem->numActiveParticles(); }
         
      };


   } // namespace effect


} // namespace particle




