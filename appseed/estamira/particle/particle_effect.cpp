#include "framework.h"


namespace particle
{


   namespace effect
   {

      effect * factory::create(const char * pszName)
      {

         string strEffectName(pszName);

         if (strEffectName == "tunnel")
            return canew(tunnel(get_app()));
         else if (strEffectName == "attractors")
            return canew(attractor(get_app()));
         else if (strEffectName == "fountain")
            return canew(fountain(get_app(), 0, 0));

         return NULL;

      }


   } // namespace effect


} // namespace particle




