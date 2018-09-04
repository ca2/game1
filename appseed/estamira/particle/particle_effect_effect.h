#pragma once


namespace particle
{


   namespace effect
   {


      class CLASS_DECL_ESTAMIRA effect : virtual public ::object
      {
      public:
         static const size_t DEFAULT_PARTICLE_NUM_FLAG = 0;	// for initialize method
         //enum Name { };
      public:
         effect(::aura::application * papp) : ::object(papp) { }
         virtual ~effect() { }

         // creates the effect with desired num of particles, (0 means default for the effect)
         virtual bool initialize(size_t numParticles, size_t lifeCount) = 0;
         virtual bool initializeRenderer() = 0;
         virtual void reset() = 0;
         virtual void clean() = 0;
         virtual void addUI() = 0;
         virtual void removeUI() = 0;

         virtual void update(double dt) = 0;
         virtual void cpuUpdate(double dt) = 0;
         virtual void gpuUpdate(double dt) = 0;
         virtual void render(::draw2d::graphics * pgraphics, float cx, float cy) = 0;

         virtual ::count numAllParticles() = 0;
         virtual ::count numActiveParticles() = 0;

      };

      class CLASS_DECL_ESTAMIRA factory :
         virtual public ::object
      {
      public:

         factory(::aura::application * papp) : ::object(papp) {}

         effect * create(const char *name);


      };


   } // namespace effect


} // namespace particle



