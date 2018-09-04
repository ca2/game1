#pragma once


namespace estamira
{


   class CLASS_DECL_ESTAMIRA main_frame :
      virtual public simple_frame_window
   {
   public:


      main_frame(::aura::application * papp);
      virtual ~main_frame();


      virtual void install_message_routing(::message::sender * psender) override;


      sp(::user::wndfrm::frame::frame) create_frame_schema() override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual bool get_translucency(::user::e_translucency & etranslucency);


      virtual bool on_create_bars() override;

      virtual bool has_pending_graphical_update() override;


   };


} // namespace estamira











