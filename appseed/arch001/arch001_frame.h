#pragma once


namespace arch001
{


   class pane_view;


   class CLASS_DECL_GAME_ARCH001 frame :
      virtual public simple_frame_window
   {
   public:


      frame(::aura::application * papp);
      virtual ~frame();


      sp(::user::wndfrm::frame::frame) create_frame_schema();
	   
   
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   

      virtual bool get_translucency(::user::e_translucency & etranslucency);


      virtual bool on_create_bars();


   };


} // namespace arch001











