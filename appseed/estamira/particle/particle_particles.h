#pragma once


namespace particle
{


   class CLASS_DECL_ESTAMIRA data
   {
   public:


      array < vec4 >    m_pos;
      array < vec4 >    m_col;
      array < vec4 >    m_startCol;
      array < vec4 >    m_endCol;
      array < vec4 >    m_vel;
      array < vec4 >    m_acc;
      array < vec4 >    m_time;
      bool_array        m_active;

      size_t m_count{ 0 };
      size_t m_countActive{ 0 };
      size_t m_countLife;
      size_t m_counter;


      data() { }
      explicit data(size_t maxCount) { generate(maxCount); }
      ~data() { }

      data(const data &) = delete;
      data &operator=(const data &) = delete;

      void generate(size_t maxSize);
      void kill(size_t id);
      void wake(size_t id);
      void swapData(size_t a, size_t b);

      static void copyOnlyActive(const data *source, data *destination);
      static size_t computeMemoryUsage(const data &p);


   };


   namespace  generator
   {


      class CLASS_DECL_ESTAMIRA generator :
         virtual public ::object
      {
      public:


         generator(::aura::application * papp) : ::object(papp) { }
         virtual ~generator() { }


         virtual void generate(double dt, data *p, size_t startId, size_t endId) = 0;


      };


   } // namespace generator

   class CLASS_DECL_ESTAMIRA emitter :
      virtual public object
   {
   public:


      spa(generator::generator) m_generatora;
      float m_emitRate{ 0.0 };


      emitter(::aura::application * papp) : ::object(papp) { }
      virtual ~emitter() { }

      // calls all the generator and at the end it activates (wakes) particle
      virtual void emit(double dt, data *p);

      void addGenerator(generator::generator * gen) { m_generatora.add(gen); }


   };

   class CLASS_DECL_ESTAMIRA updater :
      virtual public object
   {
   public:
      updater(::aura::application * papp) : ::object(papp) { }
      virtual ~updater() { }

      virtual void update(double dt, data *p) = 0;
   };

   class CLASS_DECL_ESTAMIRA system :
      virtual public object
   {
   public:


      data m_particles;
      data m_particlesActive;

      size_t m_count;

      spa(emitter) m_emittera;
      spa(updater) m_updatera;


      explicit system(::aura::application * papp, size_t maxCount, size_t lifeCount);
      virtual ~system() { }

      system(const system &) = delete;
      system &operator=(const system &) = delete;

      virtual void update(double dt);
      virtual void reset();

      virtual size_t numAllParticles() const { return m_particles.m_count; }
      virtual size_t numActiveParticles() const { return m_particles.m_countActive; }

      void addEmitter(emitter * em) { m_emittera.add(em); }
      void addUpdater(updater * up) { m_updatera.add(up); }

      data *finalData() { return &m_particles; }

      static size_t computeMemoryUsage(const system &p);


   };


} // namespace particle




