#pragma once


namespace arkanoid
{


   class pane_view;

   class view;


   class CLASS_DECL_GAME_ARKANOID frame :
      virtual public ::estamira::main_frame
   {
   public:


      view * m_pview;

      ::size            m_sizeView;


      frame(::aura::application * papp);
      virtual ~frame();


      sp(::user::wndfrm::frame::frame) create_frame_schema();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual bool get_translucency(::user::e_translucency & etranslucency);

      virtual bool get_window_minimum_size(::size & sizeMin);

      virtual bool has_pending_graphical_update();

      virtual bool on_create_bars() override;


   };


} // namespace arkanoid











