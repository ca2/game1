#pragma once


namespace pacman
{

   class restart
   {
   public:

      restart(){}

   };

   class CLASS_DECL_APP_CORE_PACMAN application :
      virtual public ::hellomultiverse::application,
      virtual public ::html::application,
      virtual public ::multimedia::application,
      virtual public ::multimedia::audio::wave_player_container
   {
   public:


      sp(::user::single_document_template)  m_ptemplatePacManMain;
      sp(::user::single_document_template)  m_ptemplatePacManView;

      ::user::split_view *    m_psplit;
      view * m_pview;

      ::console::window *     m_pconsolewindow;

      int m_iConsole;

      ::multimedia::audio_decode::decoder_plugin * m_pdecoderplugin;


      pacman *                m_ppacman;


      application();
      virtual ~application();

      
      void start();
      ::console::window * create_console(int iIndex);
      void change_console(int iIndex);


      virtual bool initialize_instance();
      virtual int32_t  exit_instance();

      virtual void on_request(sp(::create) pcreatecontext);

      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      virtual void on_create_split_view(::user::split_view * psplit);

   };


} // namespace pacman





