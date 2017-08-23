#pragma once


namespace arch001
{

   class view;

   class CLASS_DECL_GAME_ARCH001 pane_view : 
      public ::userex::pane_tab_view
   {
   public:


      sp(::arch001::view)                     m_pflagview;


      pane_view(::aura::application * papp);
	   virtual ~pane_view();

      
      void on_create_view(::user::view_creator_data * pcreatordata);

      virtual void install_message_routing(::message::sender * pinterface);

   #ifdef DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

	   DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace arch001


