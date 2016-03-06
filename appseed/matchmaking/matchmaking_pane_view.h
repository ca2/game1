#pragma once


namespace hellomultiverse
{


   class CLASS_DECL_APP_CORE_HELLOMULTIVERSE pane_view :
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

      virtual void install_message_handling(::message::dispatch * pinterface);

	   virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

	   DECL_GEN_SIGNAL(_001OnCreate);
      bool BaseOnControlEvent(::user::form_window * pview,::user::control_event * pevent);
      void on_show_view();
   };


} // namespace hellomultiverse













