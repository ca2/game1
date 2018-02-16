#pragma once


namespace arkanoid
{

   class view;

   class CLASS_DECL_GAME_ARKANOID pane_view :
      public ::userex::pane_tab_view
   {
   public:


      sp(::arkanoid::view)                     m_pflagview;


      pane_view(::aura::application * papp);
      virtual ~pane_view();


      void on_create_view(::user::view_creator_data * pcreatordata);

      virtual void install_message_routing(::message::sender * pinterface);


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace arkanoid


