#pragma once


namespace matchmaking
{


   class CLASS_DECL_APP_CORE_MATCHMAKING application :
      virtual public ::core::application
   //,virtual public ::html::application
   {
   public:


      enum e_type
      {

         type_normal,
         type_mili,

      };

      string                                 m_strSteamUserName;
      string                                 m_strSteamId;
      bool                                   m_bLoginSteam;

      e_type                                 m_etype;
      string                                 m_strHelloMultiverse;
      string                                 m_strHelloMultiverseDefault;
      string                                 m_strAlternateHelloMultiverse;
      string                                 m_strAlternateHelloMultiverseDefault;

      bool                                   m_bMultiverseChat;

      ::user::document *                     m_pdocMenu;
//      ::calculator::plain_edit_view *        m_prollfps;
      ::user::plain_edit_view *        m_prollfps;
      ::user::single_document_template *     m_ptemplateHelloMultiverseMain;
      ::user::single_document_template *     m_ptemplateHelloMultiverseView;
      ::user::single_document_template *     m_ptemplateHelloMultiverseSwitcher;
      ::user::single_document_template *     m_ptemplateHelloMultiverseFontSel;

      //::user::split_view *                             m_ptopviewLast;
      //view *                                 m_pviewLast;

      //::user::split_view *                             m_ptopviewMain;
      //view *                                 m_pviewMain;
      //::user::button_view *                          m_ptoggleviewMain;
      //::user::plain_edit_view *              m_peditMain;

      //::user::split_view *                             m_ptopviewSwitcher;
      //view *                                 m_pviewSwitcher;
      //::user::button_view *                          m_ptoggleviewSwitcher;
      //::user::plain_edit_view *              m_peditSwitcher;

      //::user::split_view *                             m_ptopviewFont;
      //::user::font_list_view *               m_pfontlistview;
      //::user::button_view *                          m_ptoggleviewFontSel;
      //::user::plain_edit_view *              m_peditFontSel;

      mutex                                  m_mutexAiFont;
      int32_t                                m_iErrorAiFont;
      bool                                   m_bLoadAiFont;
      void *                                 m_faceAi; // FT_Face m_faceAi;

      application();
      virtual ~application();


      virtual bool init_instance();
      virtual int32_t  exit_application() override;

      virtual void on_request(::create * pcreate);

      static UINT thread_proc_load_ai_font(void * pparam);
      virtual void load_ai_font();

      //virtual void on_create_split_view(::user::split_view * psplit) override;

      //virtual bool BaseOnControlEvent(::user::control_event * pevent) override;

      //virtual bool BaseOnControlEvent(::user::control_event * pevent) override;

      //virtual void on_create_view(::user::view_creator_data * pcreatordata) override;

      //virtual void on_show_view(::user::tab * ptab) override;

      virtual int64_t add_ref();
      virtual int64_t dec_ref();

      string get_steam_user_name();
      string get_steam_id();

      void defer_update_steam_info();

   };


} // namespace matchmaking



