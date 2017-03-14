#pragma once


namespace sokoban
{


   class pane_view;


   class CLASS_DECL_APP_CORE_SOKOBAN frame :
      virtual public ::estamira::main_frame
   {
   public:


      ::size            m_sizeView;


      frame(::aura::application * papp);
      virtual ~frame();


      sp(::user::wndfrm::frame::frame) create_frame_schema();
	   
   
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   

      virtual bool get_translucency(::user::ETranslucency & etranslucency);

      virtual bool get_window_minimum_size(::size & sizeMin);

   };


} // namespace sokoban











