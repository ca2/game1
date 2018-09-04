#pragma once


namespace particle
{


   namespace effect
   {


      class CLASS_DECL_ESTAMIRA fountain : public effect
      {
      public:

         sp(class system) m_psystem;
         sp(renderer)   m_prenderer;
         sp(generator::position::box) m_posGenerator;
         sp(generator::color::basic) m_colGenerator;
         sp(updaters::EulerUpdater) m_eulerUpdater;
         int m_cx; int m_cy;
         sp(updaters::FloorUpdater) m_floorUpdater;

         fountain(::aura::application * papp, int cx, int cy) : ::object(papp), effect(papp), m_cx(cx), m_cy(cy) { }
         ~fountain() { }

         virtual bool initialize_color_generator(generator::color::basic * pcolorbasic);


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

      class CLASS_DECL_ESTAMIRA random_color_range_fountain : public fountain
      {
      public:

         enum e_color
         {
            color_red_yellow,
            color_blue_cyan,
            color_green_yellow,
            color_blue_magenta,
            color_count
         };

         random_color_range_fountain(::aura::application * papp, int cx, int cy) : ::object(papp), fountain(papp, cx, cy) { }

         virtual bool initialize_color_generator(generator::color::basic * pcolorbasic);

      };

      class CLASS_DECL_ESTAMIRA gold_color_fountain : public fountain
      {
      public:

         gold_color_fountain(::aura::application * papp, int cx, int cy) : ::object(papp), fountain(papp, cx, cy) { }

         virtual bool initialize_color_generator(generator::color::basic * pcolorbasic);

      };

   } // namespace effect


} // namespace particle

