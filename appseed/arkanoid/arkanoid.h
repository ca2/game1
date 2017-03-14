#pragma once


#include "estamira/estamira.h"
#include "core/user/html/html/html.h"


#ifdef _APP_CORE_ARKANOID_LIBRARY
    #define CLASS_DECL_APP_CORE_ARKANOID  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_APP_CORE_ARKANOID  CLASS_DECL_IMPORT
#endif


namespace arkanoid
{

   class application;
   class view;


} // namespace flag

#undef App
#define App(pbaseapp) (pbaseapp->m_pcoreapp->cast_app < ::arkanoid::application > ())

#include "arkanoid_interface.h"
#include "arkanoid_arkanoid.h"
#include "arkanoid_preview.h"

#include "arkanoid_document.h"
#include "arkanoid_view.h"
#include "arkanoid_frame.h"
#include "arkanoid_pane_view_update_hint.h"
#include "arkanoid_pane_view.h"

#include "arkanoid_application.h"
