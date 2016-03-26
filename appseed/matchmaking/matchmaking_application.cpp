#include "framework.h"




namespace matchmaking
{


   application::application():
      m_mutexAiFont(this)
   {

      //m_ptopviewLast                          = NULL;
      //m_pviewLast                            = NULL;

      //m_ptopviewMain                          = NULL;
      //m_pviewMain                          = NULL;
      //m_ptoggleviewMain= NULL;
      //m_peditMain= NULL;

      //m_ptopviewSwitcher                          = NULL;
      //m_pviewSwitcher                          = NULL;
      //m_ptoggleviewSwitcher= NULL;
      //m_peditSwitcher= NULL;

      //m_ptopviewFont                          = NULL;
      //m_pfontlistview                          = NULL;
      //m_ptoggleviewFontSel= NULL;
      //m_peditFontSel = NULL;

      m_ptemplateHelloMultiverseMain = NULL;
      m_ptemplateHelloMultiverseView = NULL;
      m_ptemplateHelloMultiverseSwitcher = NULL;

      m_strAppName            = "matchmaking";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;

      m_etype                 = type_normal;

      m_strHelloMultiverseDefault             = "Hello Multiverse!!";
      m_strAlternateHelloMultiverseDefault    = "Hello!!";

      m_strHelloMultiverse             = m_strHelloMultiverseDefault;
      m_strAlternateHelloMultiverse    = m_strAlternateHelloMultiverseDefault;

      m_iErrorAiFont = -1;

      m_bLoadAiFont = false;

      m_faceAi = NULL; // FT_Face m_faceAi;

      m_bMultiverseChat = true;



   }


   application::~application()
   {
   }


   bool application::initialize_instance()
   {

      System.factory().creatable_small < ::matchmaking::document >();
      System.factory().creatable_small < ::matchmaking::frame >();
      System.factory().creatable_small < ::matchmaking::edit_view >();
//      System.factory().creatable_small < ::matchmaking::::user::button_view >();
      System.factory().creatable_small < ::user::button_view >();
//      System.factory().creatable_small < ::matchmaking::::user::split_view >();
//      System.factory().creatable_small < ::matchmaking::lite_view >();
//      System.factory().creatable_small < ::matchmaking::full_view >();
      System.factory().creatable_small < ::matchmaking::view >();
      System.factory().creatable_small < ::matchmaking::main_view >();
      System.factory().creatable_small < ::matchmaking::switcher_view >();
      System.factory().creatable_small < ::matchmaking::pane_view >();
      System.factory().creatable_small < ::user::font_list >();
      System.factory().creatable_small < ::user::font_list_view >();
      System.factory().creatable_small < ::matchmaking::font_view >();
      System.factory().creatable_small < ::matchmaking::top_view >();
      System.factory().creatable_small < ::matchmaking::toggle_view >();

      if(!::core::application::initialize_instance())
         return false;

//      if(directrix()->m_varTopicQuery.has_property("install"))
//      {
//         ::simple_message_box(NULL, "HelloMultiverse install", "HelloMultiverse install", 0);
//      }


      string str = directrix()->m_varTopicQuery["matchmaking"];

      if (str.has_char())
      {

         m_strHelloMultiverse = str;

      }

      m_dataid.m_id = m_dataid.m_id + ".local://";

      ::user::single_document_template* pDocTemplate;
      pDocTemplate = canew(::user::single_document_template(
                              this,
                              "main",
                              System.type_info < document >(),
                              System.type_info < frame > (),       // top level SDI frame::user::interaction_impl
                              System.type_info < pane_view > ()));
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseMain = pDocTemplate;
      pDocTemplate = canew(::user::single_document_template(
                              this,
                              "main",
                              System.type_info < document > (),
                              System.type_info < frame > (),       // top level SDI frame::user::interaction_impl
                              System.type_info < main_view > ()));
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseView = pDocTemplate;
      pDocTemplate = canew(::user::single_document_template(
                              this,
                              "main",
                              System.type_info < document >(),
                              System.type_info < frame >(),       // top level SDI frame::user::interaction_impl
                              System.type_info < switcher_view >()));
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseSwitcher = pDocTemplate;


      m_ptemplateHelloMultiverseFontSel = canew(::user::single_document_template(
                                             this,
                                             "main",
                                             System.type_info < ::user::document >(),
                                             System.type_info < ::simple_frame_window >(),       // top level SDI frame::user::interaction_impl
                                             System.type_info < font_view >()));

      add_document_template(m_ptemplateHelloMultiverseFontSel);

      return true;
   }

   int32_t application::exit_instance()
   {

      return ::core::application::exit_instance();
   }

   void application::on_request(sp(::create) pcreatecontext)
   {

      /*

      {
         id lowvalue;
         {
            string str = "ABC";
            lowvalue = str.lower();
         }
      }

      property_set set;

      set["c"] = 0;
      set["ABC"] = 0;
      set["abc"] = 0;
      set["ebc"] = 0;

      ::MessageBox(NULL,"stop oh yes!!","stop oh yes!!",MB_ICONINFORMATION);

      */

      //pcreatecontext->m_bMakeVisible = false;

      m_bMultiverseChat = !directrix()->m_varTopicQuery["no_hello_edit"].is_set();

      if(m_ptemplateHelloMultiverseMain->get_document_count() == 0)
      {

         m_ptemplateHelloMultiverseMain->open_document_file(pcreatecontext);

      }

      if(pcreatecontext->m_spCommandLine->m_varFile.has_char())
      {

         m_ptemplateHelloMultiverseView->open_document_file(pcreatecontext);

      }

      //rect r(20, 20, 20, 20);

      //ClipCursor(r);

      if (directrix()->m_varTopicQuery["wfi_maximize"].is_set())
      {

         pcreatecontext->m_spCommandLine->m_varQuery["document"].cast < document >()->get_typed_view < ::userex::pane_tab_view >()->GetTopLevelFrame()->_001WindowMaximize();

      }

      //pcreatecontext->m_spCommandLine->m_varQuery["document"].cast < document >()->get_typed_view < pane_view >()->GetParentFrame()->WfiRestore(true);

   }



   void application::load_ai_font()
   {

      if(m_bLoadAiFont)
         return ;

      m_bLoadAiFont = true;

      m_iErrorAiFont = -1;

      __begin_thread(get_app(),&thread_proc_load_ai_font,this,::multithreading::priority_normal,0,0,NULL);

   }


   UINT application::thread_proc_load_ai_font(void * pparam)
   {

      application * pview = (application *)pparam;

      pview->m_iErrorAiFont = -1;

      //pview->m_iErrorAiFont = FT_New_Face((FT_Library)Sys(pview->get_app()).ftlibrary(),Sess(pview->get_app()).dir().matter_file("font/truetype/arialuni.ttf"),0,(FT_Face *)&pview->m_faceAi);

      return pview->m_iErrorAiFont;

   }
   //void application::on_create_view(::user::view_creator_data * pcreatordata)
   //{

   //   switch(pcreatordata->m_id)
   //   {
   //   case PaneViewMenu:
   //   {
   //      m_pdocMenu = Session.userex()->create_child_form(this,pcreatordata->m_pholder);

   //      m_pdocMenu->open_document("matter://menu.html");

   //      sp(::user::impact) pview = m_pdocMenu->get_view();

   //      m_prollfps = dynamic_cast < ::calculator::plain_edit_view * > (pview->get_child_by_id("roll_fps"));
   //      //         m_prollspf = pview->get_child_by_id("roll_spf");
   //      //try
   //      //{
   //      //   pform->get_child_by_id("clockverse_auto")->_001SetCheck(Application.should_auto_launch_clockverse_on_hover(),::action::source_initialize);
   //      //}
   //      //catch(...)
   //      //{
   //      //}

   //      //try
   //      //{
   //      //   pform->get_child_by_id("flag")->_001SetCheck(Application.should_bind_flag_country_ca2_domain_image_on_hover(),::action::source_initialize);
   //      //}
   //      //catch(...)
   //      //{
   //      //}

   //      //try
   //      //{
   //      //   pform->get_child_by_id("flag_auto")->_001SetCheck(Application.should_auto_launch_flag_on_hover(),::action::source_initialize);
   //      //}
   //      //catch(...)
   //      //{
   //      //}



   //   }
   //   break;
   //   case PaneViewHelloMultiverse:
   //   {
   //      sp(::user::document) pdoc =  Application.m_ptemplateHelloMultiverseView->open_document_file(NULL,true,pcreatordata->m_pholder);


   //   }

   //   break;

   //   case PaneViewHelloMultiverseSwitcher:
   //   {

   //      Application.m_ptemplateHelloMultiverseSwitcher->open_document_file(NULL,true,pcreatordata->m_pholder);



   //   }

   //   break;
   //   case PaneViewFontSel:
   //   {
   //      Application.m_ptemplateHelloMultiverseFontSel->open_document_file(NULL,true,pcreatordata->m_pholder);


   //   }

   //   break;



   //   }

   //   //::userex::pane_tab_view::on_create_view(pcreatordata);

   //}



//   void application::on_create_split_view(::user::split_view * psplit)
//   {
//
//      if(::str::ends(psplit->m_id.m_psz,"_top"))
//      {
//
//         psplit->m_bHideOnTransparentFrame = true;
//
//         if(psplit->get_pane_count() > 0)
//            return;
//
//         psplit->SetPaneCount(2);
//
//         psplit->SetSplitOrientation(orientation_vertical);
//
//         psplit->set_position_rate(0,0.84);
//
//         psplit->initialize_split_layout();
//
//         if(psplit->m_id == "matchmaking_top")
//         {
//
//            m_peditMain = psplit->create_view < ::user::plain_edit_view >(NULL,::null_rect(),psplit->get_pane_holder(0),"matchmaking_edit");
//
//            if(m_peditMain == NULL)
//            {
//
//               System.simple_message_box(NULL,"Could not create folder edit view");
//
//            }
//
//            m_ptoggleviewMain = psplit->create_view < ::user::button_view >(NULL,::null_rect(),psplit->get_pane_holder(1),"matchmaking_toggle");
//
//            if(m_ptoggleviewMain == NULL)
//            {
//
//               System.simple_message_box(NULL,"Could not create file list ::user::impact");
//
//            }
//
//
//         }
//         else if(psplit->m_id == "switcher_top")
//         {
//
//            m_peditSwitcher = psplit->create_view < ::user::plain_edit_view >(NULL,::null_rect(),psplit->get_pane_holder(0),"switcher_edit");
//
//            if(m_peditSwitcher == NULL)
//            {
//
//               System.simple_message_box(NULL,"Could not create folder edit view");
//
//            }
//
//            m_ptoggleviewSwitcher = psplit->create_view < ::user::button_view >(NULL,::null_rect(),psplit->get_pane_holder(1),"switcher_toggle");
//
//            if(m_ptoggleviewSwitcher == NULL)
//            {
//
//               System.simple_message_box(NULL,"Could not create file list ::user::impact");
//
//            }
//
//
//         }
//         else if(psplit->m_id == "fontsel_top")
//         {
//
//            m_peditFontSel =psplit-> create_view < ::user::plain_edit_view >(NULL,::null_rect(),psplit->get_pane_holder(0),"fontsel_edit");
//
//            if(m_peditFontSel == NULL)
//            {
//
//               System.simple_message_box(NULL,"Could not create folder edit view");
//
//            }
//
//            m_ptoggleviewFontSel = psplit->create_view < ::user::button_view >(NULL,::null_rect(),psplit->get_pane_holder(1),"fontsel_toggle");
//
//            if(m_ptoggleviewFontSel == NULL)
//            {
//
//               System.simple_message_box(NULL,"Could not create file list ::user::impact");
//
//            }
//
//
//         }
//
//
//
//
//      }
//      else if(psplit->get_document()->get_document_template() == m_ptemplateHelloMultiverseFontSel)
//      {
//
//
//         if(psplit->get_pane_count() > 0)
//            return;
//
//         psplit->SetPaneCount(2);
//
//         psplit->SetSplitOrientation(orientation_horizontal);
//
//         psplit->set_position(0,24);
//
//         psplit->initialize_split_layout();
//
//         m_ptopviewFont = psplit->create_view < ::user::split_view >(NULL,::null_rect(),psplit->get_pane_holder(0),"fontsel_top");
//
//         if(m_ptopviewFont == NULL)
//         {
//
//            System.simple_message_box(NULL,"Could not create folder edit view");
//
//         }
//
//         //SetPane(0,m_ptopview,false);
//
//         m_pfontlistview = psplit->create_view < ::user::font_list_view >(NULL,::null_rect(),psplit->get_pane_holder(1),"fontsel_view");
//
//         if(m_pfontlistview == NULL)
//         {
//
//            System.simple_message_box(NULL,"Could not create file list ::user::impact");
//
//         }
//
//         //SetPane(1,m_pview,false);
//
//      }
//      else if(psplit->get_document()->get_document_template() == m_ptemplateHelloMultiverseSwitcher)
//      {
//
//
//         if(psplit->get_pane_count() > 0)
//            return;
//
//         psplit->SetPaneCount(2);
//
//         psplit->SetSplitOrientation(orientation_horizontal);
//
//         psplit->set_position(0,24);
//
//         psplit->initialize_split_layout();
//
//         m_ptopviewSwitcher = psplit->create_view < ::user::split_view >(NULL,::null_rect(),psplit->get_pane_holder(0),"switcher_top");
//
//         if(m_ptopviewSwitcher == NULL)
//         {
//
//            System.simple_message_box(NULL,"Could not create folder edit view");
//
//         }
//
//         //SetPane(0,m_ptopview,false);
//
//         m_pviewSwitcher = psplit->create_view < view >(NULL,::null_rect(),psplit->get_pane_holder(1),"switcher_view");
//
//         m_pviewSwitcher->m_prender->m_bAlternate = true;
//
//         if(m_pviewSwitcher == NULL)
//         {
//
//            System.simple_message_box(NULL,"Could not create file list ::user::impact");
//
//         }
//
//         if(m_pviewSwitcher != NULL)
//         {
//
//            string strText;
//
//            m_pviewSwitcher->data_get("cur_text",strText);
//
//            m_peditSwitcher->_001SetText(strText, ::action::source_initialize);
//
//         }
//
//
//         //m_ptopviewSwitcher->m_pview = m_pview;
//
//
//         //SetPane(1,m_pview,false);
//
//      }
//      else if(psplit->get_document()->get_document_template() == m_ptemplateHelloMultiverseView)
//      {
//         if(psplit->get_pane_count() > 0)
//            return;
//
//         int iPane;
//
//         if(m_bMultiverseChat)
//         {
//
//            psplit->SetPaneCount(2);
//
//            psplit->SetSplitOrientation(orientation_horizontal);
//
//            psplit->set_position(0,31);
//
//            psplit->initialize_split_layout();
//
//            m_ptopviewMain = psplit->create_view < ::user::split_view >(NULL,::null_rect(),psplit->get_pane_holder(0),"matchmaking_top");
//
//            if(m_ptopviewMain == NULL)
//            {
//
//               System.simple_message_box(NULL,"Could not create folder edit view");
//
//            }
//
//            //SetPane(0,m_ptopview,false);
//
//            iPane = 1;
//
//         }
//         else
//         {
//
//            psplit->SetPaneCount(1);
//
//            psplit->initialize_split_layout();
//
//            iPane = 0;
//
//         }
//
//         //m_pview = create_view < lite_view >();
//
//         m_pviewMain = psplit->create_view < view >(NULL,::null_rect(),psplit->get_pane_holder(iPane),"matchmaking_view");
//
//         if(m_pviewMain == NULL)
//         {
//
//            System.simple_message_box(NULL,"Could not create file list ::user::impact");
//
//         }
//
//
//         if(m_peditMain != NULL)
//         {
//
//            string strText;
//
//            m_pviewMain->data_get("cur_text",strText);
//
//            m_peditMain->_001SetText(strText,::action::source_initialize);
//
//         }
//
//
//
//         if(m_ptopviewMain != NULL)
//         {
//
//            //m_ptopviewMain->m_pview = m_pviewMain;
//
//         }
//
//         //SetPane(iPane,m_pview,false);
//
//      }
//
//
//
//   }
//
//
//   bool application::BaseOnControlEvent(::user::control_event * pevent)
//   {
//
//      if(pevent->m_eevent == ::user::event_on_create_tab)
//      {
//
//         if(pevent->m_ptab != NULL && pevent->get_impact_matter() == "main")
//         {
//
//
//            pevent->m_ptab->set_tab("Menu",::matchmaking::PaneViewMenu);
//            pevent->m_ptab->set_tab("matchmaking",::matchmaking::PaneViewHelloMultiverse);
//            pevent->m_ptab->set_tab("switcher",::matchmaking::PaneViewHelloMultiverseSwitcher);
//            pevent->m_ptab->set_tab("Font",::matchmaking::PaneViewFontSel);
//#if 1
//            pevent->m_ptab->set_tab("Open","file_manager");
//#endif
//
//            //set_cur_tab_by_id(::matchmaking::PaneViewHelloMultiverseSwitcher);
//            pevent->m_ptab->set_cur_tab_by_id(::matchmaking::PaneViewHelloMultiverse);
//
//         }
//
//
//      }
//
//      else if(pevent->m_eevent == ::user::event_button_clicked)
//      {
//
//         if(pevent->m_puie->m_id == "switcher_toggle")
//         {
//
//            sp(view) pview = m_pviewSwitcher;
//
//            pview->m_prender->m_bLite = !pview->m_prender->m_bLite;
//
//         }
//         else if(pevent->m_puie->m_id == "matchmaking_toggle")
//         {
//
//            if(m_pviewMain->m_prender->m_bLite && !Application.m_bLoadAiFont)
//            {
//
//               Application.load_ai_font();
//
//            }
//
//            m_pviewMain->m_prender->m_bLite = !m_pviewMain->m_prender->m_bLite;
//
//
//            m_pviewMain->layout();
//
//         }
//
//
//      }
//      else if(pevent->m_eevent == ::user::event_after_change_text)
//      {
//
//         if(pevent->m_puie->m_id.is_text() && ::str::ends(pevent->m_puie->m_id.m_psz,"_edit"))
//         {
//
//            string strText;
//
//            pevent->m_puie->_001GetText(strText);
//
//            if(pevent->m_puie->m_id == "matchmaking_edit")
//            {
//
//               if(m_pviewMain != NULL)
//               {
//
//                  {
//
//                     synch_lock sl(&m_pviewMain->m_mutexText);
//
//                     m_pviewMain->data_set("cur_text",strText);
//
//                     m_pviewMain->m_strNewHelloMultiverse = strText;
//
//                  }
//
//                  m_pviewMain->post_message(WM_USER + 1984 + 77 + 2);
//
//               }
//
//               pevent->m_bRet = true;
//
//               pevent->m_bProcessed = true;
//
//               return true;
//
//            }
//            else if(pevent->m_puie->m_id == "switcher_edit")
//            {
//
//               if(m_pviewSwitcher != NULL)
//               {
//
//                  {
//
//                     synch_lock sl(&m_pviewSwitcher->m_mutexText);
//
//                     m_pviewSwitcher->data_set("cur_text",strText);
//
//                     m_pviewSwitcher->m_strNewHelloMultiverse = strText;
//
//                  }
//
//                  m_pviewSwitcher->post_message(WM_USER + 1984 + 77 + 2);
//
//               }
//
//               pevent->m_bRet = true;
//
//               pevent->m_bProcessed = true;
//
//               return true;
//            }
//            else if(pevent->m_puie->m_id == "fontsel_edit")
//            {
//
//               if(m_pfontlistview != NULL)
//               {
//
//                  {
//
//                     synch_lock sl(m_pfontlistview->m_pmutex);
//
//                     m_pfontlistview->m_strText = strText;
//
//                  }
//
//
//               }
//
//            }
//
//
//         }
//
//      }
//      else if(pevent->m_eevent == ::user::event_after_change_cur_sel)
//      {
//
//         if(m_pfontlistview == pevent->m_puie)
//         {
//
//            if(m_pviewLast != NULL)
//            {
//
//               string strFont = m_pfontlistview->get_cur_sel_face_name();
//
//               if(strFont.has_char())
//               {
//
//                  m_pviewLast->m_strNewFont = strFont;
//
//                  m_pviewLast->layout();
//
//               }
//
//            }
//
//         }
//
//      }
//
//      return true;
//
//   }
//
//   bool application::BaseOnControlEvent(::user::form_window * pview,::user::control_event * pevent)
//   {
//
//      if(m_pdocMenu != NULL && pview == m_pdocMenu->get_view(0))
//      {
//
//         if(pevent->m_eevent == ::user::event_after_change_text && pevent->m_puie != NULL)
//         {
//
//            if(m_prollfps != NULL && pevent->m_puie->m_id == "roll_fps" && !pevent->m_actioncontext.is_source(::action::source_initialize)
//               && !pevent->m_actioncontext.is_source(::action::source_database))
//            {
//
//               try
//               {
//                  string str;
//                  double d = m_prollfps->m_val.m_dR;
//
//                  {
//
//                     string str;
//
//                     m_prollfps->_001GetText(str);
//
//                     m_pviewLast->data_set("cur_fps_text",str);
//
//                  }
//
//                  {
//
//                     var v;
//
//                     v = d;
//
//                     m_pviewLast->data_set("cur_fps",v);
//
//                  }
//
//                  m_pviewLast->m_dFps = d;
//                  m_pviewLast->m_dwRoll = ::get_tick_count();
//                  //if(fabs(d) < 0.0000000001)
//                  //{
//                  //   m_prollspf->_001SetText("",::action::source_initialize);
//                  //}
//                  //else
//                  //{
//                  //   m_prollspf->_001SetText(::str::from(1.0/d),::action::source_initialize);
//                  //}
//               }
//               catch(...)
//               {
//               }
//
//            }
//            //else if(pevent->m_puie->m_id == "roll_spf" && !pevent->m_actioncontext.is_source(::action::source_initialize))
//            //{
//
//            //   try
//            //   {
//            //      string str;
//            //      m_prollspf->_001GetText(str);
//            //      double d = atof(str);
//            //      if(fabs(d) < 0.0000000001)
//            //      {
//            //         m_prollfps->_001SetText("",::action::source_initialize);
//            //      }
//            //      else
//            //      {
//            //         m_pflagview->m_dFps = 1.0/ d;
//            //         m_pflagview->m_dwRoll = ::get_tick_count();
//            //         m_prollfps->_001SetText(::str::from(1.0 / d),::action::source_initialize);
//            //      }
//            //   }
//            //   catch(...)
//            //   {
//            //   }
//
//            //}
//
//
//         }
//
//         //   if(pevent->m_puie->m_id == "clockverse")
//         //   {
//         //      Application.set_binding_clockverse_country_time_zone_set_on_hover(pevent->m_puie->_001GetCheck() == ::check::checked);
//         //      return true;
//         //   }
//         //   else if(pevent->m_puie->m_id == "clockverse_auto")
//         //   {
//         //      Application.set_auto_launch_clockverse_on_hover(pevent->m_puie->_001GetCheck() == ::check::checked);
//         //      return true;
//         //   }
//         //   else if(pevent->m_puie->m_id == "flag")
//         //   {
//         //      Application.set_binding_flag_country_ca2_domain_image_on_hover(pevent->m_puie->_001GetCheck() == ::check::checked);
//         //      return true;
//         //   }
//         //   else if(pevent->m_puie->m_id == "flag_auto")
//         //   {
//         //      Application.set_auto_launch_flag_on_hover(pevent->m_puie->_001GetCheck() == ::check::checked);
//         //      return true;
//         //   }
//         //}
//      }
//
//      return false;
//   }
//
//
//
//   void application::on_show_view(::user::tab * ptab)
//   {
//
//      sp(::userex::pane_tab_view) ptabview = ptab;
//
//      if(ptabview.is_set() && (ptabview->get_document()->get_document_template()->m_strMatter == "main"
//         || ::str::ends(ptabview->get_document()->get_document_template()->m_strMatter, "_main")))
//      {
//
//
////         ptabview->::userex::pane_tab_view::on_show_view();
//
//         string strId = ptabview->get_view_id();
//         stringa stra;
//         stra.explode("->:<-",strId);
//         if(ptabview->get_view_id() == ::matchmaking::PaneViewHelloMultiverse
//            || ptabview->get_view_id() == ::matchmaking::PaneViewHelloMultiverseSwitcher
//            || stra.contains(::str::from((int)::matchmaking::PaneViewHelloMultiverse))
//            || stra.contains(::str::from((int)::matchmaking::PaneViewHelloMultiverseSwitcher)))
//         {
//            if(ptabview->get_pane_by_id(::matchmaking::PaneViewMenu) != NULL && ptabview->get_pane_by_id(::matchmaking::PaneViewMenu)->m_pholder != NULL)
//            {
//               ptabview->get_pane_by_id(::matchmaking::PaneViewMenu)->m_pholder->ShowWindow(SW_HIDE);
//            }
//            if(ptabview->get_pane_by_id("file_manager") != NULL && ptabview->get_pane_by_id("file_manager")->m_pholder != NULL)
//            {
//               ptabview->get_pane_by_id("file_manager")->m_pholder->ShowWindow(SW_HIDE);
//            }
//            if(ptabview->get_pane_by_id(::matchmaking::PaneViewFontSel) != NULL && ptabview->get_pane_by_id(::matchmaking::PaneViewFontSel)->m_pholder != NULL)
//            {
//               ptabview->get_pane_by_id(::matchmaking::PaneViewFontSel)->m_pholder->ShowWindow(SW_HIDE);
//            }
//         }
//         else if(ptabview->get_view_id() == ::matchmaking::PaneViewMenu)
//         {
//
//            if(m_pviewLast != NULL)
//            {
//
//               string str;
//
//               m_pviewLast->data_get("cur_fps_text",str);
//
//               m_prollfps->_001SetText(str, ::action::source_database);
//
//            }
//
//         }
//
//         if(ptabview->get_view_id() == ::matchmaking::PaneViewHelloMultiverse)
//         {
//
//            m_pviewLast = m_pviewMain;
//
//         }
//         else if(ptabview->get_view_id() == ::matchmaking::PaneViewHelloMultiverseSwitcher)
//         {
//
//            m_pviewLast = m_pviewSwitcher;
//
//         }
//         //else if(ptabview->get_view_id() != ::matchmaking::PaneViewFontSel)
//         //{
//         //
//         //   m_pviewLast = NULL;
//
//         //}
//
//         if(m_pviewLast != NULL && m_pfontlistview != NULL)
//         {
//
//            m_pfontlistview->set_sel_by_name(m_pviewLast->m_strFont);
//
//         }
//
//      }
//
//   }

   int64_t application::add_ref()
   {

      return ::object::add_ref();

   }

   int64_t application::dec_ref()
   {

      return ::object::dec_ref();

   }


   string application::get_steam_user_name()
   {
      
      if (m_strSteamUserName.is_empty())
      {

         defer_update_steam_info();

      }

      return m_strSteamUserName;

   }

   string application::get_steam_id()
   {

      if (m_strSteamUserName.is_empty())
      {

         defer_update_steam_info();

      }

      return m_strSteamUserName;

   }


   void application::defer_update_steam_info()
   {

      if (m_bLoginSteam)
         return;

      m_bLoginSteam = true;
      ::fork(this, [=]()
      {
         
         string str = Application.http().api_get("/steam/get_user_name_and_id");

         stringa stra;

         stra.add_lines(str, false);

         if (stra.get_size() == 4 && stra[0] == "OK" && stra[3] == "OK")
         {

            m_strSteamUserName = stra[1];

            m_strSteamId = stra[2];

         }

         m_bLoginSteam = false;

      });

   }

} // namespace matchmaking




extern "C"
::aura::library * game_matchmaking_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::matchmaking::application >(papp, "game");

}




