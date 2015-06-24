#include "framework.h"

#ifdef WINDOWS
namespace pacman
{


   void system_console::SetCursorPosition(int y,int x)
   {

      ::windows::console::SetCursorPosition(y + 3, x);

   }


} // namespace pacman

#endif
