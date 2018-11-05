#include "framework.h"


namespace pacman
{


   pellet::pellet(pacman * ppacman):
      console_composite(ppacman),
      level(ppacman->level)
   {

   }


   void pellet::print()
   {

       _008SetCursorPos(y, x);
       cout << level[y][x];

   }


} // namespace pacman