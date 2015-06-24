#include "framework.h"


namespace pacman
{


   dib_console::dib_console(::aura::application * papp,size sizeTile) :
      object(papp),
      ::dib_console(papp, sizeTile)
   {

   }


   void dib_console::SetCursorPosition(int y,int x)
   {

      ::dib_console::SetCursorPosition(y + 3,x);

   }


} // namespace windows



