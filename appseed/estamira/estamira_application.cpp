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



} // namespace estamira




