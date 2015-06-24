#include "ft2build.h"
#include FT_FREETYPE_H


namespace pacman
{


   class CLASS_DECL_APP_CORE_PACMAN console:
      virtual public ::dib_console
   {
   public:

      int m_iFont;
      FT_Face m_face;
      size m_offset;

      size m_sizeDib;
      ::visual::dib_sp m_dibChar;

      ::visual::dib_sp m_dib0;
      ::visual::dib_sp m_dib1;
      ::visual::dib_sp m_dib2;
      ::visual::dib_sp m_dib3;
      ::visual::dib_sp m_dib4;
      ::visual::dib_sp m_dib5;
/*

http://undeadgaming.wikia.com/wiki/Ghost_%28Pacman%29

      Blinky Edit

         Blinky simply chases Pacman,ignoring the other Ghosts.
         Pinky Edit

         Pinky acknowledges Blinky's movements and takes advantage of them to corner Pacman.
         Inky Edit

         Inky acts similar to Blinky,but Retreats if Pacman Faces him head - on.
         Clyde Edit

         Clyde chases Pacman,though he tends to make wrong turns.

         Clockwise from top left: Clyde,Inky,Blinky and Pinky
         matter://ghosts-orig.png

         */
      array < ::visual::dib_sp > m_ga;

      console(::aura::application * papp,size sizeTile);


      virtual bool defer_write(char ch, int x, int y, int cx, int cy, int iColor);

      virtual void SetCursorPosition(int y,int x);

   };


} // namespace pacman