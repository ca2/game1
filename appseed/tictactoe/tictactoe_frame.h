#pragma once


namespace tictactoe
{


   class pane_view;


   class CLASS_DECL_APP_CORE_TICTACTOE frame :
      public simple_frame_window
   {
   public:


      frame(::aura::application * papp);
      virtual ~frame();


      sp(::user::wndfrm::frame::frame) create_frame_schema();
	   
   
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   

      virtual bool get_translucency(::user::ETranslucency & etranslucency);


   };


} // namespace tictactoe











