#pragma once


#include "estamira/estamira.h"
#include "core/user/userex/userex.h"
#include "app-core/appseed/gcom/gcom/gcom.h"


#ifdef _GAME_ARCH001_LIBRARY
    #define CLASS_DECL_GAME_ARCH001  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_GAME_ARCH001  CLASS_DECL_IMPORT
#endif

namespace arch001
{




   class view;
   class document;
   class arbitrator;
   class player;


   class main_frame;


   class application;



} // namespace flag

#undef App
#define App(papp) (*papp->cast < ::arch001::application > ())
#undef Gam
#define Gam(pbaseapp) (*App(pbaseapp).m_pgame.cast < ::arch001::game >())



//#include "multimedia_soundtrack.h"

#include "arch001_game.h"


#include "arch001_document.h"
#include "arch001_view.h"
#include "arch001_frame.h"
#include "arch001_main_frame.h"
#include "arch001_pane_view_update_hint.h"
#include "arch001_pane_view.h"


#include "arch001_application.h"
