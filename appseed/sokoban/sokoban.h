#pragma once


#include "estamira/estamira.h"
#include "core/user/html/html/html.h"


#ifdef _APP_CORE_SOKOBAN_LIBRARY
    #define CLASS_DECL_APP_CORE_SOKOBAN  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_APP_CORE_SOKOBAN  CLASS_DECL_IMPORT
#endif

namespace sokoban
{

   class application;
   class view;


} // namespace flag

#undef App
#define App(papp) (*papp->cast < ::sokoban::application > ())

#include "sokoban_interface.h"
#include "game/sokoban_block.h"
#include "game/sokoban_asset.h"
#include "game/sokoban_level.h"

#include "sokoban_document.h"
#include "sokoban_view.h"
#include "sokoban_frame.h"
#include "sokoban_pane_view_update_hint.h"
#include "sokoban_pane_view.h"

#include "sokoban_application.h"
