#include "framework.h"


namespace estamira
{


   application::application()
   {

   }


   application::~application()
   {
   }


   bool application::init_instance()
   {


      m_prendererfactory = canew(class particle::renderer_factory(this));
      m_peffectfactory = canew(particle::effect::factory(this));


//      if (!::hellomultiverse::application::init_instance())
//         return false;

      if (!::multimedia::application::init_instance())
         return false;

      return true;

   }


   void application::term_instance()
   {

      ::multimedia::application::term_instance();

   }


   particle::renderer_factory & application::renderer_factory()
   {

      return *m_prendererfactory;

   }


} // namespace estamira




