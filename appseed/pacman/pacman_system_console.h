#pragma once


#ifdef WINDOWS


namespace pacman
{


   class CLASS_DECL_APP_CORE_PACMAN system_console:
      virtual public ::windows::console
   {
   public:


      void SetCursorPosition(int y,int x);


   };


} // namespace windows


#endif





