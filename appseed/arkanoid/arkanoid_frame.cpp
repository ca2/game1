#include "framework.h"
#include <math.h>


namespace arkanoid
{


   frame::frame(::aura::application * papp) :
      ::object(papp),
      simple_frame_window(papp),
      ::estamira::main_frame(papp)
   {

      m_pview = NULL;

      m_dataid = "::core::arkanoid::frame";

      WfiEnableFullScreen();

      m_bWindowFrame = !Application.command()->m_varTopicQuery.has_property("client_only");

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

      sp(::user::wndfrm::frame::frame) pschema = Application.wndfrm().get_frame_schema(NULL, "001");
      pschema->set_style("StyleLightBlue");
      //pschema->m_typeinfoControlBoxButton = System.type_info < MetaButton > ();
      return pschema;

/*      frame::FrameSchemaHardCoded005 * pschema = new frame::FrameSchemaHardCoded005(get_app());
      pschema->m_typeinfoControlBoxButton = System.type_info < MetaButton > ();
      pschema->SetStyle(frame::FrameSchemaHardCoded005::StyleTranslucidWarmGray);
      return pschema;*/
   }


   bool frame::get_translucency(::user::ETranslucency & etranslucency)
   {

      etranslucency      = ::user::TranslucencyPresent;

      return true;


   }

   bool frame::get_window_minimum_size(::size & sizeMin)
   {

      sizeMin.cx = m_sizeView.cx;
      sizeMin.cy = m_sizeView.cy + 50;

      return true;

   }



} // namespace arkanoid



