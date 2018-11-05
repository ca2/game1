#pragma once


namespace game_of_life
{

   class view;

   class CLASS_DECL_GAME_GAME_OF_LIFE pane_view :
      public ::userex::pane_tab_view
   {
   public:


      sp(::game_of_life::view)                     m_pview;
      ::user::document *                           m_pdocOptions;

      pane_view(::aura::application * papp);
      virtual ~pane_view();


      void on_create_view(::user::view_creator_data * pcreatordata);

      virtual void install_message_routing(::message::sender * pinterface);


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual void on_show_view() override;

      virtual void on_control_event(::user::control_event * pevent) override;

      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace game_of_life


