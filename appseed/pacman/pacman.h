#pragma once


#include "estamira/estamira.h"
#include "core/user/html/html/html.h"


#ifdef WINDOWS
#ifdef _APP_CORE_PACMAN_LIBRARY
    #define CLASS_DECL_APP_CORE_PACMAN  _declspec(dllexport)
#else
    #define CLASS_DECL_APP_CORE_PACMAN  _declspec(dllimport)
#endif
#else
   #define CLASS_DECL_APP_CORE_PACMAN
#endif

namespace pacman
{

   class application;
   class view;


} // namespace flag

#undef App
#define App(papp) (*papp->cast < ::pacman::application > ())


#include "pacman_console.h"

#include "pacman_constants.h"


#include "pacman_sound_track.h"




typedef char LEVEL[LEVELHEIGHT][LEVELWIDTH];


#include "pacman_player.h"
#include "pacman_ghost.h"
#include "pacman_pellet.h"

#include "pacman_sound.h"

#include "pacman_pacman.h"


#include "pacman_interface.h"
#include "pacman_pacman.h"
#include "pacman_preview.h"

#include "pacman_document.h"
#include "pacman_view.h"
#include "pacman_frame.h"
#include "pacman_pane_view_update_hint.h"
#include "pacman_pane_view.h"

#include "pacman_application.h"
