#include "framework.h"


namespace particle
{

   renderer * renderer_factory::create(const char * pszName)
   {

      string strRendererName(pszName);

      if (strRendererName == "impl")
      {

         return canew(renderer_impl(get_app()));

      }

      return NULL;

   }
}

