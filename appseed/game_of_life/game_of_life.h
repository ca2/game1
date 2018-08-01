#pragma once


#include "estamira/estamira.h"
#include "core/user/userex/userex.h"
#include "app-core/appseed/gcom/gcom/gcom.h"


#ifdef _GAME_GAME_OF_LIFE_LIBRARY
    #define CLASS_DECL_GAME_GAME_OF_LIFE  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_GAME_GAME_OF_LIFE  CLASS_DECL_IMPORT
#endif

namespace game_of_life
{




   class view;
   class document;
   class arbitrator;
   class player;


   class main_frame;


   class application;



} // namespace flag

#undef App
#define App(papp) (*papp->cast < ::game_of_life::application > ())
#undef Gam
#define Gam(pbaseapp) (*App(pbaseapp).m_pgame.cast < ::game_of_life::game >())



//#include "multimedia_soundtrack.h"

#include "game_of_life_game.h"


#include "game_of_life_document.h"
#include "game_of_life_view.h"
#include "game_of_life_frame.h"
#include "game_of_life_main_frame.h"
#include "game_of_life_pane_view_update_hint.h"
#include "game_of_life_pane_view.h"


#include "game_of_life_application.h"
