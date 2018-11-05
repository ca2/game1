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


   void pane_view::install_message_routing(::message::sender * pinterface)
   {

      ::userex::pane_tab_view::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);

   }


   void pane_view::_001OnCreate(::message::message * pobj)
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

      set_cur_tab_by_id(::matchmaking::PaneViewStart);

      //set_cur_tab_by_id(::matchmaking::PaneViewHelloMultiverseSwitcher);
      //set_cur_tab_by_id(::matchmaking::PaneViewHelloMultiverse);

   }

   void pane_view::on_show_view()
   {
      ::userex::pane_tab_view::on_show_view();
   }


   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {

      switch(pcreatordata->m_id)
      {
      case PaneViewStart:
      {
         create_view<start>(pcreatordata);
      }
      break;
      case PaneViewMenu:
      {
         m_pdocMenu = Application.create_child_form(this,pcreatordata->m_pholder);

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
         sp(::user::document) pdoc =  Application.m_ptemplateHelloMultiverseView->open_document_file(get_app(), NULL,true,pcreatordata->m_pholder);

         pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);

      }

      break;

      case PaneViewHelloMultiverseSwitcher:
      {

         Application.m_ptemplateHelloMultiverseSwitcher->open_document_file(get_app(), NULL,true,pcreatordata->m_pholder);



      }

      break;
      case PaneViewFontSel:
      {
         Application.m_ptemplateHelloMultiverseFontSel->open_document_file(get_app(), NULL,true,pcreatordata->m_pholder);


      }

      break;



      }

      ::userex::pane_tab_view::on_create_view(pcreatordata);

   }


   void pane_view::on_control_event(::user::control_event * pevent)
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
