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

   class application;


} // namespace flag

#undef App
#define App(pbaseapp) (pbaseapp->m_pcoreapp->cast_app < ::tictactoe::application > ())

#include "tictactoe_document.h"
#include "tictactoe_view.h"
#include "tictactoe_frame.h"
#include "tictactoe_pane_view_update_hint.h"
#include "tictactoe_pane_view.h"

#include "tictactoe_application.h"
