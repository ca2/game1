#pragma once


namespace matchmaking
{


   class CLASS_DECL_APP_CORE_MATCHMAKING pane_view :
      virtual public ::userex::pane_tab_view,
      virtual public ::user::form_callback
   {
   public:


      ::user::split_view *                             m_ptopviewLast;
      view *                                 m_pviewLast;

      ::user::document *                            m_pdocMenu;
      ::calculator::plain_edit_view *                        m_prollfps;
//      ::user::plain_edit_view *                        m_prollfps;
      //::user::interaction *                        m_prollspf;

      pane_view(::aura::application * papp);
      virtual ~pane_view();


      void on_create_view(::user::view_creator_data * pcreatordata);

      virtual void install_message_routing(::message::sender * pinterface);

      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      DECL_GEN_SIGNAL(_001OnCreate);
      void on_control_event(::user::control_event * pevent);
      void on_show_view();
   };


} // namespace matchmaking













