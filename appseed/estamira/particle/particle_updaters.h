#pragma once


namespace particle
{


   namespace updaters
   {


      class CLASS_DECL_ESTAMIRA EulerUpdater : public updater
      {
      public:
         vec4 m_globalAcceleration;
      public:
         EulerUpdater(::aura::application * papp) : ::object(papp), updater(papp), m_globalAcceleration(0.0) { }

         virtual void update(double dt, data *p) override;
      };

      // collision with the floor :) todo: implement a collision model
      class CLASS_DECL_ESTAMIRA FloorUpdater : public updater
      {
      public:
         float m_floorY;
         float m_bounceFactor;
      public:
         FloorUpdater(::aura::application * papp) : ::object(papp), updater(papp), m_floorY(0.0), m_bounceFactor(0.5f) { }

         virtual void update(double dt, data *p) override;
      };

      class CLASS_DECL_ESTAMIRA AttractorUpdater : public updater
      {
      protected:
         array<vec4> m_attractors; // .w is force
      public:
         AttractorUpdater(::aura::application * papp) : ::object(papp), updater(papp) {}
         virtual void update(double dt, data *p) override;

         size_t collectionSize() const { return m_attractors.size(); }
         void add(const vec4 &attr) { m_attractors.add(attr); }
         vec4 &get(size_t id) { return m_attractors[id]; }
      };

      class CLASS_DECL_ESTAMIRA BasicColorUpdater : public updater
      {
      public:
         BasicColorUpdater(::aura::application * papp) : ::object(papp), updater(papp) {}
         virtual void update(double dt, data *p) override;
      };

      class CLASS_DECL_ESTAMIRA PosColorUpdater : public updater
      {
      public:
         vec4 m_minPos;
         vec4 m_maxPos;
      public:

         PosColorUpdater(::aura::application * papp) : ::object(papp), updater(papp), m_minPos(0.0), m_maxPos(1.0)  {}


         virtual void update(double dt, data *p) override;
      };

      class CLASS_DECL_ESTAMIRA VelColorUpdater : public updater
      {
      public:
         vec4 m_minVel;
         vec4 m_maxVel;
      public:
         VelColorUpdater(::aura::application * papp) : ::object(papp), updater(papp), m_minVel(0.0), m_maxVel(1.0) { }

         virtual void update(double dt, data *p) override;
      };

      class CLASS_DECL_ESTAMIRA BasicTimeUpdater : public updater
      {
      public:
         BasicTimeUpdater(::aura::application * papp) : ::object(papp), updater(papp) {}
         virtual void update(double dt, data *p) override;
      };


   } // namespace updaters


} // namespace particle




