#pragma once


#include "core/core/core.h"
#include "core/user/userex/userex.h"
#include "app/appseed/html/html/html.h"
#include "app-core/appseed/multimedia/multimedia/multimedia.h"


#ifdef _GAME_COINCUBE_LIBRARY
    #define CLASS_DECL_GAME_COINCUBE  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_GAME_COINCUBE  CLASS_DECL_IMPORT
#endif

namespace coincube
{




   class view;
   class document;
   class arbitrator;
   class player;


   class main_frame;


   class application;



} // namespace flag

#undef App
#define App(pbaseapp) (pbaseapp->m_pcoreapp->cast_app < ::coincube::application > ())


#include "coincube_coin.h"
#include "coincube_cube.h"


#include "multimedia_soundtrack.h"

#include "coincube_document.h"
#include "coincube_view.h"
#include "coincube_frame.h"
#include "coincube_main_frame.h"
#include "coincube_pane_view_update_hint.h"
#include "coincube_pane_view.h"

#include "coincube_application.h"
