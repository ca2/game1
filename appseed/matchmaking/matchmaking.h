#pragma once


#include "core/core/core.h"
#include "core/filesystem/filemanager/filemanager.h"
#include "core/user/user/user.h"
#include "core/user/html/html/html.h"
#include "pcre/pcre.h"


//#include "ft2build.h"
//#include FT_FREETYPE_H


#ifdef _APP_CORE_MATCHMAKING_LIBRARY
   #define CLASS_DECL_APP_CORE_MATCHMAKING  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_APP_CORE_MATCHMAKING  CLASS_DECL_IMPORT
#endif


namespace user
{

   //typedef ::user::show < ::user::plain_edit > plain_edit_view;

   typedef ::user::show < ::user::button > button_view;

} // namespace user


namespace matchmaking
{

   class application;
   class top_view;
   class main_view;
   class document;
   class view;
   class font_view;

} // namespace flag


#undef App
#define App(pbaseapp) (pbaseapp->m_pcoreapp->cast_app < ::matchmaking::application > ())


#include "user_font_list.h"

#include "matchmaking_render.h"

#include "matchmaking_document.h"
#include "matchmaking_font_view.h"
#include "matchmaking_edit_view.h"
#include "matchmaking_toggle_view.h"
#include "matchmaking_top_view.h"
#include "matchmaking_view.h"
//#include "matchmaking_lite_view.h"
//#include "matchmaking_full_view.h"
#include "matchmaking_main_view.h"
#include "matchmaking_switcher_view.h"
#include "matchmaking_frame.h"
#include "matchmaking_pane_view_update_hint.h"
#include "matchmaking_pane_view.h"

#include "matchmaking_application.h"

