#pragma once


#include "core/core/core.h"
//#include "core/user/user/user.h"
//#include "core/user/simple/simple.h"
#include "core/user/userex/userex.h"
//#include "core/filesystem/filemanager/filemanager.h"


#ifdef _GAME_TICTACTOE_LIBRARY
    #define CLASS_DECL_GAME_TICTACTOE  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_GAME_TICTACTOE  CLASS_DECL_IMPORT
#endif

namespace tictactoe
{


   enum e_check
   {

      check_none,
      check_x,
      check_o,
      check_draw

   };


   class view;
   class document;
   class arbitrator;
   class player;


   class application;


   CLASS_DECL_GAME_TICTACTOE e_check toggle(e_check echeck);


} // namespace flag

#undef App
#define App(pbaseapp) (pbaseapp->m_pcoreapp->cast_app < ::tictactoe::application > ())


#include "tictactoe_board.h"
#include "tictactoe_arbitrator.h"
#include "tictactoe_player.h"



#include "tictactoe_document.h"
#include "tictactoe_view.h"
#include "tictactoe_frame.h"
#include "tictactoe_pane_view_update_hint.h"
#include "tictactoe_pane_view.h"

#include "tictactoe_application.h"
