#pragma once


namespace pacman
{


   class CLASS_DECL_APP_CORE_PACMAN dib_console:
      virtual public ::dib_console
   {
   public:


      dib_console(::aura::application * papp,size sizeTile);


      void SetCursorPosition(int y,int x);

   };


} // namespace windows




