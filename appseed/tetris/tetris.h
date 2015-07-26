#pragma once


#include "app-core/appseed/hellomultiverse/hellomultiverse.h"
#include "app/appseed/html/html/html.h"


#ifdef WINDOWS
#ifdef _GAME_TETRIS_LIBRARY
    #define CLASS_DECL_GAME_TETRIS  _declspec(dllexport)
#else
    #define CLASS_DECL_GAME_TETRIS  _declspec(dllimport)
#endif
#else
   #define CLASS_DECL_GAME_TETRIS
#endif

namespace tetris
{

   class application;
   class view;


} // namespace flag

#undef App
#define App(pbaseapp) (pbaseapp->m_pcoreapp->cast_app < ::tetris::application > ())

#include "tetris_interface.h"
#include "tetris_tetris.h"
#include "tetris_preview.h"

#include "tetris_document.h"
#include "tetris_view.h"
#include "tetris_frame.h"
#include "tetris_pane_view_update_hint.h"
#include "tetris_pane_view.h"

#include "tetris_application.h"
