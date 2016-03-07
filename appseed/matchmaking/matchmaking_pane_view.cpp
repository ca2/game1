#include "framework.h"
#include <math.h>

namespace matchmaking
{

   pane_view::pane_view(::aura::application * papp) :
      object(papp),
      ::user::tab(papp),

      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {
      m_pviewLast = NULL;
      m_prollfps = NULL;
   }


   pane_view::~pane_view()
   {

   }


   void pane_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void pane_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void pane_view::install_message_handling(::message::dispatch * pinterface)
   {

      ::userex::pane_tab_view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);

   }


   void pane_view::_001OnCreate(signal_details * pobj)
   {
      if(pobj->previous())
         return;

      set_tab("Login",::matchmaking::PaneViewMenu);
      set_tab("matchmaking", ::matchmaking::PaneViewHelloMultiverse);
      set_tab("switcher",::matchmaking::PaneViewHelloMultiverseSwitcher);
      set_tab("Font",::matchmaking::PaneViewFontSel);
#if 1
      set_tab("Open", "file_manager");
#endif

      //set_cur_tab_by_id(::matchmaking::PaneViewHelloMultiverseSwitcher);
      set_cur_tab_by_id(::matchmaking::PaneViewHelloMultiverse);

   }

   void pane_view::on_show_view()
   {
      ::userex::pane_tab_view::on_show_view();
      string strId = get_view_id();
      stringa stra;
      stra.explode("->:<-",strId);
      if(get_view_id() == ::matchmaking::PaneViewHelloMultiverse
            || get_view_id() == ::matchmaking::PaneViewHelloMultiverseSwitcher
            || stra.contains(::str::from((int)::matchmaking::PaneViewHelloMultiverse))
            || stra.contains(::str::from((int)::matchmaking::PaneViewHelloMultiverseSwitcher)))
      {

         if(get_pane_by_id(::matchmaking::PaneViewMenu) != NULL && get_pane_by_id(::matchmaking::PaneViewMenu)->m_pholder != NULL)
         {

            get_pane_by_id(::matchmaking::PaneViewMenu)->m_pholder->ShowWindow(SW_HIDE);

         }

         if(get_pane_by_id("file_manager") != NULL && get_pane_by_id("file_manager")->m_pholder != NULL)
         {

            get_pane_by_id("file_manager")->m_pholder->ShowWindow(SW_HIDE);

         }

         if(get_pane_by_id(::matchmaking::PaneViewFontSel) != NULL && get_pane_by_id(::matchmaking::PaneViewFontSel)->m_pholder != NULL)
         {

            get_pane_by_id(::matchmaking::PaneViewFontSel)->m_pholder->ShowWindow(SW_HIDE);

         }

         if(get_view_id() == ::matchmaking::PaneViewHelloMultiverse)
         {

            //::property_set set;

            //Application.http().get("https://api.ca2.cc/account/get_string?key=test", set);

            m_pviewLast = dynamic_cast < view * > (get_pane_by_id(::matchmaking::PaneViewHelloMultiverse)->m_pholder->get_child_by_id("matchmaking_view"));

         }
         else if (get_view_id() == ::matchmaking::PaneViewHelloMultiverseSwitcher)
         {

            m_pviewLast = dynamic_cast < view * > (get_pane_by_id(::matchmaking::PaneViewHelloMultiverseSwitcher)->m_pholder->get_child_by_id("matchmaking_view"));

         }


      }
      else if(get_view_id() == ::matchmaking::PaneViewMenu)
      {

         string str;

         //m_pviewLast->data_get("cur_fps_text",str);

         //m_prollfps->_001SetText(str, ::action::source_database);

      }
      else if(get_view_id() == ::matchmaking::PaneViewFontSel)
      {

         sp(::user::font_list_view) pfontview = get_pane_by_id(::matchmaking::PaneViewFontSel)->m_pholder->get_child_by_id("font_list_view");

         if(m_pviewLast != NULL && pfontview.is_set())
         {

            pfontview->set_sel_by_name(m_pviewLast->m_strFont);

         }

      }

   }


   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {

      switch(pcreatordata->m_id)
      {
      case PaneViewMenu:
         {
            m_pdocMenu = Session.userex()->create_child_form(this,pcreatordata->m_pholder);

            m_pdocMenu->open_document("matter://login.html");

            sp(::user::impact) pview = m_pdocMenu->get_view();

            m_prollfps = dynamic_cast < ::calculator::plain_edit_view * > (pview->get_child_by_id("roll_fps"));
//         m_prollspf = pview->get_child_by_id("roll_spf");
            //try
            //{
            //   pform->get_child_by_id("clockverse_auto")->_001SetCheck(Application.should_auto_launch_clockverse_on_hover(),::action::source_initialize);
            //}
            //catch(...)
            //{
            //}

            //try
            //{
            //   pform->get_child_by_id("flag")->_001SetCheck(Application.should_bind_flag_country_ca2_domain_image_on_hover(),::action::source_initialize);
            //}
            //catch(...)
            //{
            //}

            //try
            //{
            //   pform->get_child_by_id("flag_auto")->_001SetCheck(Application.should_auto_launch_flag_on_hover(),::action::source_initialize);
            //}
            //catch(...)
            //{
            //}



         }
         break;
      case PaneViewHelloMultiverse:
         {
            sp(::user::document) pdoc =  Application.m_ptemplateHelloMultiverseView->open_document_file(NULL,true,pcreatordata->m_pholder);


         }

         break;

      case PaneViewHelloMultiverseSwitcher:
         {

            Application.m_ptemplateHelloMultiverseSwitcher->open_document_file(NULL,true,pcreatordata->m_pholder);



         }

         break;
      case PaneViewFontSel:
         {
            Application.m_ptemplateHelloMultiverseFontSel->open_document_file(NULL,true,pcreatordata->m_pholder);


         }

         break;



      }

      ::userex::pane_tab_view::on_create_view(pcreatordata);

   }


   bool pane_view::BaseOnControlEvent(::user::form_window * pview,::user::control_event * pevent)
   {

      if(m_pdocMenu != NULL && dynamic_cast < ::user::impact * > (pview) == m_pdocMenu->get_view(0))
      {

         if(pevent->m_eevent == ::user::event_after_change_text && pevent->m_puie != NULL)
         {

            if(m_prollfps != NULL && pevent->m_puie->m_id == "roll_fps" && !pevent->m_actioncontext.is_source(::action::source_initialize)
                  && !pevent->m_actioncontext.is_source(::action::source_database))
            {

               try
               {
                  string str;
                  double d = m_prollfps->get_ex_value()["real"];
                  if(m_pviewLast != NULL)
                  {


                     {

                        string str;

                        m_prollfps->_001GetText(str);

                        m_pviewLast->data_set("cur_fps_text",str);

                     }

                     {

                        var v;

                        v = d;

                        m_pviewLast->data_set("cur_fps",v);

                     }
                     m_pviewLast->m_dFps = d;
                     m_pviewLast->m_dwRoll = ::get_tick_count();
                  }
                  //if(fabs(d) < 0.0000000001)
                  //{
                  //   m_prollspf->_001SetText("",::action::source_initialize);
                  //}
                  //else
                  //{
                  //   m_prollspf->_001SetText(::str::from(1.0/d),::action::source_initialize);
                  //}
               }
               catch(...)
               {
               }

            }
            //else if(pevent->m_puie->m_id == "roll_spf" && !pevent->m_actioncontext.is_source(::action::source_initialize))
            //{

            //   try
            //   {
            //      string str;
            //      m_prollspf->_001GetText(str);
            //      double d = atof(str);
            //      if(fabs(d) < 0.0000000001)
            //      {
            //         m_prollfps->_001SetText("",::action::source_initialize);
            //      }
            //      else
            //      {
            //         m_pflagview->m_dFps = 1.0/ d;
            //         m_pflagview->m_dwRoll = ::get_tick_count();
            //         m_prollfps->_001SetText(::str::from(1.0 / d),::action::source_initialize);
            //      }
            //   }
            //   catch(...)
            //   {
            //   }

            //}


         }

         //   if(pevent->m_puie->m_id == "clockverse")
         //   {
         //      Application.set_binding_clockverse_country_time_zone_set_on_hover(pevent->m_puie->_001GetCheck() == ::check::checked);
         //      return true;
         //   }
         //   else if(pevent->m_puie->m_id == "clockverse_auto")
         //   {
         //      Application.set_auto_launch_clockverse_on_hover(pevent->m_puie->_001GetCheck() == ::check::checked);
         //      return true;
         //   }
         //   else if(pevent->m_puie->m_id == "flag")
         //   {
         //      Application.set_binding_flag_country_ca2_domain_image_on_hover(pevent->m_puie->_001GetCheck() == ::check::checked);
         //      return true;
         //   }
         //   else if(pevent->m_puie->m_id == "flag_auto")
         //   {
         //      Application.set_auto_launch_flag_on_hover(pevent->m_puie->_001GetCheck() == ::check::checked);
         //      return true;
         //   }
         //}
      }

      return false;
   }





} // namespace matchmaking
