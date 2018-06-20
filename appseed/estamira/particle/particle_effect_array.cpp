#include "framework.h"


namespace particle
{


   namespace effect
   {


      array::array(::aura::application * papp) :
         ::object(papp)
      {

      }

      array::~array()
      {


      }

      void array::draw(::draw2d::graphics * pgraphics, int cx, int cy)
      {

         for (index i = 0; i < get_count(); i++)
         {

            element_at(i)->cpuUpdate(0.05);

            element_at(i)->render(pgraphics, cx, cy);

         }

         for (index i = 0; i < get_count();)
         {

            if (i < get_upper_bound())
            {

               if (element_at(i)->numActiveParticles() <= 0)
               {

                  remove_at(i);

               }
               else
               {

                  i++;

               }


            }
            else
            {

               i++;

            }

         }

      }


   } // namespace effect


} // namespace particle



