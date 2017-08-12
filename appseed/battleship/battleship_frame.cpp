#include "framework.h"
#include <math.h>


namespace tictactoe
{


   frame::frame(::aura::application * papp) :
      ::object(papp),
      simple_frame_window(papp)
   {

//      m_dataid = "::core::tictactoe::frame";

      WfiEnableFullScreen();

      m_bWindowFrame = !Application.handler()->m_varTopicQuery.has_property("client_only");

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

      sp(::user::wndfrm::frame::frame) pschema = Application.wndfrm()->get_frame_schema(NULL, "001");
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

   bool frame::on_create_bars()
   {

      if(!LoadToolBar(1,"frame/center_toolbar.xml",TBSTYLE_ALIGN_CENTER,WS_CHILD | WS_VISIBLE | CBRS_ALIGN_BOTTOM))
      {

         return false;

      }

      return true;

   }


} // namespace tictactoe



