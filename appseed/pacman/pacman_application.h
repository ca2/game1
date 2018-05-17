#pragma once


namespace pacman
{

   class restart :
      virtual public ::exception::exception
   {
   public:

      restart() {}

   };

   class CLASS_DECL_APP_CORE_PACMAN application :
      virtual public ::estamira::application
   {
   public:

      sp(::user::single_document_template)  m_ptemplatePacManMain;
      sp(::user::single_document_template)  m_ptemplatePacManView;

      ::user::split_view *    m_psplit;
      view * m_pview;

      ::console::window *     m_pconsolewindow;

      int m_iConsole;

      pacman *                m_ppacman;


      application();
      virtual ~application();


      void start();
      ::console::window * create_console(int iIndex);
      void change_console(int iIndex);


      virtual bool init_instance() override;
      virtual void term_instance() override;

      virtual void on_request(::create * pcreate);

      virtual void on_control_event(::user::control_event * pevent);

      virtual void on_create_split_view(::user::split_view * psplit);

   };


} // namespace pacman





