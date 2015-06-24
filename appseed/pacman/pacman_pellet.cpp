#include "framework.h"


namespace pacman
{


   pellet::pellet(pacman * ppacman): ::console::window_composite(ppacman),level(ppacman->level)
   {

   }


   void pellet::print()
   {

       SetCursorPosition(y, x);
       cout << level[y][x];

   }


} // namespace pacman