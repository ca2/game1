#pragma once


#include "core/core/core.h"
//#include "core/user/user/user.h"
//#include "core/user/simple/simple.h"
#include "core/user/userex/userex.h"
//#include "core/filesystem/filemanager/filemanager.h"


#ifdef WINDOWS
#ifdef _APP_CORE_TICTACTOE_LIBRARY
    #define CLASS_DECL_APP_CORE_TICTACTOE  _declspec(dllexport)
#else
    #define CLASS_DECL_APP_CORE_TICTACTOE  _declspec(dllimport)
#endif
#else
   #define CLASS_DECL_APP_CORE_TICTACTOE
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
