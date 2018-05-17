#pragma once


namespace matchmaking
{


   class CLASS_DECL_APP_CORE_MATCHMAKING main :
      virtual public ::user::split_view
   {
   public:


      lobby *                 m_plobby;
      view *                  m_pview;


      main(::aura::application * papp);
      virtual ~main();


      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      void on_create_views();

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint);

      virtual void on_control_event(::user::control_event * pevent);


   };


} // namespace matchmaking





