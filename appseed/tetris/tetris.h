#pragma once


#include "estamira/estamira.h"
#include "core/user/html/html/html.h"


#ifdef _GAME_TETRIS_LIBRARY
    #define CLASS_DECL_GAME_TETRIS  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_GAME_TETRIS  CLASS_DECL_IMPORT
#endif

namespace tetris
{

   class application;
   class view;


} // namespace flag

#undef App
#define App(papp) (*papp->cast < ::tetris::application > ())
#undef Gam
#define Gam(pbaseapp) (*App(pbaseapp).m_pgame.cast < ::tetris::game >())

#include "tetris_interface.h"
#include "tetris_game.h"
#include "tetris_preview.h"

#include "tetris_document.h"
#include "tetris_view.h"
#include "tetris_frame.h"
#include "tetris_pane_view_update_hint.h"
#include "tetris_pane_view.h"

#include "tetris_application.h"
