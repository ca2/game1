#pragma once


#include "estamira/estamira.h"


#ifdef _GAME_PARTICLE_LIBRARY
#define CLASS_DECL_GAME_PARTICLE  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_GAME_PARTICLE  CLASS_DECL_IMPORT
#endif


namespace particle
{

   class application;
   class view;


} // namespace flag

#undef App
#define App(papp) (*papp->cast < ::particle::application > ())

#include "particle/particle.h"

#include "particle_interface.h"
#include "particle_particle.h"
#include "particle_preview.h"

#include "particle_document.h"
#include "particle_view.h"
#include "particle_frame.h"
#include "particle_pane_view_update_hint.h"
#include "particle_pane_view.h"

#include "particle_main_frame.h"

#include "particle_application.h"
