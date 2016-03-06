#pragma once


namespace hellomultiverse
{


   class CLASS_DECL_APP_CORE_HELLOMULTIVERSE top_view:
      virtual public ::user::split_view
   {
   public:


      edit_view *                   m_peditview;
      toggle_view *                 m_ptoggleview;


      top_view(::aura::application * papp);
      virtual ~top_view();


      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      void on_create_views();

      virtual void on_update(::user::impact * pSender,LPARAM lHint,object* pHint);

      virtual bool IsWindowVisible() override;


   };


} // namespace hellomultiverse







