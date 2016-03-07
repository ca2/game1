#include "framework.h"
#include <math.h>


namespace matchmaking
{


   frame::frame(::aura::application * papp) :
      object(papp),
      simple_frame_window(papp)
   {

      WfiEnableFullScreen();

      m_bWindowFrame = !Application.command()->m_varTopicQuery.has_property("client_only");



      if(Application.command()->m_varTopicQuery.has_property("opaque"))
      {

         m_bExplicitTranslucency = true;

         m_etranslucency = ::user::TranslucencyNone;

      }
      else
      {

         m_bExplicitTranslucency = false;

      }



   }


   frame::~frame()
   {

   }


   void frame::assert_valid() const
   {

      simple_frame_window::assert_valid();

   }


   void frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


   sp(::user::wndfrm::frame::frame) frame::create_frame_schema()
   {

      //sp(::user::wndfrm::frame::frame) pschema = Application.wndfrm().get_frame_schema("wndfrm_core", "001");

      sp(::user::wndfrm::frame::frame) pschema = Application.wndfrm().get_frame_schema(NULL,"013");

      pschema->set_style("LightBlue");

//       // pschema->m_typeinfoControlBoxButton = System.type_info < MetaButton > ();

      return pschema;

   }


   bool frame::get_translucency(::user::ETranslucency & etranslucency)
   {

      if(m_bExplicitTranslucency)
      {

         etranslucency = m_etranslucency;

         return true;

      }

      if(m_puserschema != NULL)
      {

         if(m_puserschema->_001GetMainFrameTranslucency(etranslucency))
            return true;

      }
      etranslucency = ::user::TranslucencyPresent;

//      etranslucency = ::user::TranslucencyNone;

      return true;

   }


} // namespace matchmaking







