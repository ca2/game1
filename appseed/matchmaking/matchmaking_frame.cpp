#include "framework.h"
#include <math.h>


namespace matchmaking
{


   frame::frame(::aura::application * papp) :
      object(papp),
      simple_frame_window(papp)
   {

      WfiEnableFullScreen();

      m_bWindowFrame = !Application.handler()->m_varTopicQuery.has_property("client_only");



      if(Application.handler()->m_varTopicQuery.has_property("opaque"))
      {

         m_bExplicitTranslucency = true;

         m_etranslucency = ::user::translucency_none;

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

      //sp(::user::wndfrm::frame::frame) pschema = Application.wndfrm()->get_frame_schema("wndfrm_core", "001");

      sp(::user::wndfrm::frame::frame) pschema = Application.wndfrm()->get_frame_schema(NULL,"013");

      pschema->set_style("LightBlue");

//       // pschema->m_typeinfoControlBoxButton = System.type_info < MetaButton > ();

      return pschema;

   }


   bool frame::get_translucency(::user::e_translucency & etranslucency)
   {

      if(m_bExplicitTranslucency)
      {

         etranslucency = m_etranslucency;

         return true;

      }

      if(m_puserstyle != NULL)
      {

         if(m_puserstyle->_001GetMainFrameTranslucency(etranslucency))
            return true;

      }
      etranslucency = ::user::translucency_present;

//      etranslucency = ::user::translucency_none;

      return true;

   }


} // namespace matchmaking







