#pragma once


#include "core/core/core.h"
#include "core/filesystem/filemanager/filemanager.h"
#include "core/user/user/user.h"
#include "core/user/html/html/html.h"
#include "pcre/pcre.h"


//#include "ft2build.h"
//#include FT_FREETYPE_H


#ifdef _APP_CORE_HELLOMULTIVERSE_LIBRARY
    #define CLASS_DECL_APP_CORE_HELLOMULTIVERSE  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_APP_CORE_HELLOMULTIVERSE  CLASS_DECL_IMPORT
#endif


namespace user
{

   //typedef ::user::show < ::user::plain_edit > plain_edit_view;

   typedef ::user::show < ::user::button > button_view;

} // namespace user


namespace hellomultiverse
{

   class application;
   class top_view;
   class main_view;
   class document;
   class view;
   class font_view;

} // namespace flag


#undef App
#define App(pbaseapp) (pbaseapp->m_pcoreapp->cast_app < ::hellomultiverse::application > ())


#include "user_font_list.h"

#include "hellomultiverse_render.h"

#include "hellomultiverse_document.h"
#include "hellomultiverse_font_view.h"
#include "hellomultiverse_edit_view.h"
#include "hellomultiverse_toggle_view.h"
#include "hellomultiverse_top_view.h"
#include "hellomultiverse_view.h"
//#include "hellomultiverse_lite_view.h"
//#include "hellomultiverse_full_view.h"
#include "hellomultiverse_main_view.h"
#include "hellomultiverse_switcher_view.h"
#include "hellomultiverse_frame.h"
#include "hellomultiverse_pane_view_update_hint.h"
#include "hellomultiverse_pane_view.h"

#include "hellomultiverse_application.h"

