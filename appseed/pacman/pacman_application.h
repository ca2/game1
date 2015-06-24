#pragma once


namespace pacman
{


   class CLASS_DECL_APP_CORE_PACMAN application :
      virtual public ::hellomultiverse::application,
      virtual public ::html::application,
      virtual public ::multimedia::application
   {
   public:


      sp(::user::single_document_template)  m_ptemplatePacManMain;
      sp(::user::single_document_template)  m_ptemplatePacManView;

      ::user::split_view *    m_psplit;
      view * m_pview;

      int m_i;


      application();
      virtual ~application();


      virtual bool initialize_instance();
      virtual int32_t  exit_instance();

      virtual void on_request(sp(::create) pcreatecontext);

      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      virtual void on_create_split_view(::user::split_view * psplit);

   };


} // namespace pacman





