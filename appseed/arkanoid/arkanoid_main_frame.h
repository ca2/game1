#pragma once


namespace arkanoid
{


   class CLASS_DECL_GAME_ARKANOID main_frame :
      virtual public ::estamira::main_frame
   {
   public:


      main_frame(::aura::application * papp);
      virtual ~main_frame();


      sp(::user::wndfrm::frame::frame) create_frame_schema();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual bool get_translucency(::user::e_translucency & etranslucency);


      virtual bool on_create_bars();


   };


} // namespace arkanoid











