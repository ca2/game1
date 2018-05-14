#include "framework.h"


namespace particle
{


   void data::generate(size_t maxSize)
   {
      m_count = maxSize;
      m_countActive = 0;

      m_pos.set_size(maxSize);
      m_col.set_size(maxSize);
      m_startCol.set_size(maxSize);
      m_endCol.set_size(maxSize);
      m_vel.set_size(maxSize);
      m_acc.set_size(maxSize);
      m_time.set_size(maxSize);
      m_active.set_size(maxSize);
   }

   void data::kill(size_t id)
   {
      //if (m_countActive > 0) // maybe this if can be removed?
      {
         m_active[id] = false;
         swapData(id, m_countActive - 1);
         m_countActive--;
      }
   }

   void data::wake(size_t id)
   {
      if (m_countActive < m_count) // maybe this if can be removed?
      {
         m_active[id] = true;
         //swapData(id, m_countActive);
         m_countActive++;
      }
   }

   void data::swapData(size_t a, size_t b)
   {
      /*std::swap(m_pos[a], m_pos[b]);
      std::swap(m_col[a], m_col[b]);
      std::swap(m_startCol[a], m_startCol[b]);
      std::swap(m_endCol[a], m_endCol[b]);
      std::swap(m_vel[a], m_vel[b]);
      std::swap(m_acc[a], m_acc[b]);
      std::swap(m_time[a], m_time[b]);
      std::swap(m_active[a], m_active[b]);*/
      m_pos[a] = m_pos[b];
      m_col[a] = m_col[b];
      m_startCol[a] = m_startCol[b];
      m_endCol[a] = m_endCol[b];
      m_vel[a] = m_vel[b];
      m_acc[a] = m_acc[b];
      m_time[a] = m_time[b];
      //m_active[a] = m_active[b];*/
   }

   void data::copyOnlyActive(const data *source, data *destination)
   {
      assert(source->m_count == destination->m_count);

      size_t id = 0;
      for (size_t i = 0; i < source->m_countActive; ++i)
      {
         //if (source->m_active[i])
         {
            destination->m_pos[id] = source->m_pos[i];
            destination->m_col[id] = source->m_col[i];
            destination->m_startCol[id] = source->m_startCol[i];
            destination->m_endCol[id] = source->m_endCol[i];
            destination->m_vel[id] = source->m_vel[i];
            destination->m_acc[id] = source->m_acc[i];
            destination->m_time[id] = source->m_time[i];
            destination->m_active[id] = true;
            id++;
         }
      }

      destination->m_countActive = id;
   }

   size_t data::computeMemoryUsage(const data &p)
   {
      return p.m_count * (7 * sizeof(vec4)+sizeof(bool)) + sizeof(size_t)* 2;
   }

   ////////////////////////////////////////////////////////////////////////////////
   // emitter class

   void emitter::emit(double dt, data *p)
   {
      const size_t maxNewParticles = static_cast<size_t>(dt*m_emitRate);
      const size_t startId = p->m_countActive;
      const size_t endId = std::min(startId + maxNewParticles, p->m_count-1);

      for (auto &gen : m_generatora)
         gen->generate(dt, p, startId, endId);

      for (size_t i = startId; i < endId; ++i)
      {
         if (p->m_countLife == 0 || p->m_counter++ < p->m_countLife)
         {
            p->wake(i);

         }
      }
   }

   ////////////////////////////////////////////////////////////////////////////////
   // system class

   ////////////////////////////////////////////////////////////////////////////////
   system::system(::aura::application * papp, size_t maxCount, size_t lifeCount) :
      ::object(papp)
   {
      m_count = maxCount;
      m_particles.m_counter = 0;
      m_particles.m_countLife = lifeCount;
      m_particles.generate(maxCount);
      m_particlesActive.generate(maxCount);

      for (size_t i = 0; i < maxCount; ++i)
         m_particles.m_active[i] = false;
   }

   void system::update(double dt)
   {
      for (auto & em : m_emittera)
      {
         em->emit(dt, &m_particles);
      }

      for (size_t i = 0; i < m_count; ++i)
      {
         m_particles.m_acc[i] = vec4(0.0f);
      }

      for (auto & up : m_updatera)
      {
         up->update(dt, &m_particles);
      }

      //data::copyOnlyActive(&m_particles, &m_particlesActive);
   }

   void system::reset()
   {
      m_particles.m_countActive = 0;
   }

   size_t system::computeMemoryUsage(const system &p)
   {
      return 2 * data::computeMemoryUsage(p.m_particles);
   }


} // namespace particle



