#include "framework.h"


#ifndef M_PI
#define M_PI 		3.1415926535897932384626433832795f
#define M_2_PI 		6.28318530717958647692528676655901f		// PI*2
#endif


namespace particle
{


   namespace generator
   {


      namespace position
      {


         void box::generate(double dt, data *p, size_t startId, size_t endId)
         {
            vec4 posMin{ m_pos.x - m_maxStartPosOffset.x, m_pos.y - m_maxStartPosOffset.y, m_pos.z - m_maxStartPosOffset.z, 1.0 };
            vec4 posMax{ m_pos.x + m_maxStartPosOffset.x, m_pos.y + m_maxStartPosOffset.y, m_pos.z + m_maxStartPosOffset.z, 1.0 };

            for (size_t i = startId; i < endId; ++i)
            {
               p->m_pos[i] = linear_rand(posMin, posMax);
            }
         }

         void round::generate(double dt, data *p, size_t startId, size_t endId)
         {
            for (size_t i = startId; i < endId; ++i)
            {
               double ang = linear_rand(0.0, M_PI*2.0);
               p->m_pos[i] = m_center + vec4(m_radX*sin(ang), m_radY*cos(ang), 0.0, 1.0);
            }
         }

      } // namespace position


      namespace color
      {

         void basic::generate(double dt, data *p, size_t startId, size_t endId)
         {
            for (size_t i = startId; i < endId; ++i)
            {
               p->m_startCol[i] = linear_rand(m_minStartCol, m_maxStartCol);
               p->m_endCol[i] = linear_rand(m_minEndCol, m_maxEndCol);
            }
         }

      } // namespace color

      namespace velocity
      {

         void basic::generate(double dt, data *p, size_t startId, size_t endId)
         {
            for (size_t i = startId; i < endId; ++i)
            {
               p->m_vel[i] = linear_rand(m_minStartVel, m_maxStartVel);
            }
         }

         void sphere::generate(double dt, data *p, size_t startId, size_t endId)
         {
            float phi, theta, v, r;
            for (size_t i = startId; i < endId; ++i)
            {
               phi = linear_rand(-M_PI, M_PI);
               theta = linear_rand(-M_PI, M_PI);
               v = linear_rand(m_minVel, m_maxVel);

               r = v * sinf(phi);
               p->m_vel[i].z = v * cosf(phi);
               p->m_vel[i].x = r * cosf(theta);
               p->m_vel[i].y = r * sinf(theta);
            }
         }

         void from_pos::generate(double dt, data *p, size_t startId, size_t endId)
         {
            for (size_t i = startId; i < endId; ++i)
            {
               float scale = static_cast<float>(linear_rand(m_minScale, m_maxScale));
               vec4 vel = (p->m_pos[i] - m_offset);
               p->m_vel[i] = scale * vel;
            }
         }

      } // namespace velocity


      namespace time
      {


         void time::basic::generate(double dt, data *p, size_t startId, size_t endId)
         {

            for (size_t i = startId; i < endId; ++i)
            {

               p->m_time[i].x = p->m_time[i].y = linear_rand(m_minTime, m_maxTime);
               p->m_time[i].z = (float)0.0;
               p->m_time[i].w = (float)1.0 / p->m_time[i].x;

            }

         }


      } // namespace time


   } // namespace generator


} // namespace particle