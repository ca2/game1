#include "framework.h"
#include <math.h>


//extern CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;


namespace matchmaking
{



   view::view(::aura::application * papp):
      object(papp),
      m_dibColor(allocer()),
      m_dibFast(allocer()),
      m_mutexText(papp),
      m_dibAi1(allocer()),
      m_dibAi2(allocer()),
      m_dibPost(allocer()),
      m_dibBk(allocer()),
      m_dibTime(allocer())
   {

      m_pevRenderEnd = NULL;

      m_strNewFont = FONT_SANS;


      m_eeffect                  = effect_none;

      m_bOkPending               = false;
      m_dwLastOk                 = 0;
      m_dwAnime                  = 0;
      m_dwLastFast               = 0;
      m_dwFastAnime              = 0;
      m_bFast                    = false;
      m_bFastOnEmpty             = false;
      //m_dFps = 1.0 / 60.0;
      m_dFps = 0.0;


      m_bHelloLayoutOn001Layout  = false;
      m_b001LayoutIgnoreEmpty    = false;


      m_prender                  = NULL;


      m_prender = new render(get_app());

      m_prender->m_pview = this;

      m_prender->m_pmutexText = &m_mutexText;

      m_dwAnime = 1984;

      m_dwFastAnime = 584;

      m_bOkPending = true;

      m_bHelloLayoutOn001Layout = true;

      m_b001LayoutIgnoreEmpty = false;

      m_bFastOnEmpty = true;

      m_bFast = true;

      m_dibBk.load_from_file(Application.directrix()->m_varTopicQuery["hello_bk"]);


      m_ppcreutil = pcre_util::compile(get_app(), "\\:\\-\\)");

   }

   view::~view()
   {
   }

   void view::assert_valid() const
   {
      database::user::interaction::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      database::user::interaction::dump(dumpcontext);
   }

   void view::install_message_handling(::message::dispatch * pdispatch)
   {

      ::user::impact::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_USER + 1984 + 77 + 2,pdispatch,this,&view::_001OnLayout);
      IGUI_WIN_MSG_LINK(WM_CREATE,pdispatch,this,&view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_DESTROY, pdispatch, this, &view::_001OnDestroy);

   }


   void view::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

      string strText;

      data_get("cur_font",m_strNewFont);

      {

         var v;

         data_get("cur_fps",v);

         m_dFps = v.get_double();

         m_dwRoll = ::get_tick_count();

      }


      //    data_get("cur_text",strText);

      if(GetTypedParent<::user::split_view>() != NULL)
      {

         if(GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view") != NULL)
         {

            GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view")->_001SetText(strText,::action::source_initialize);

         }

      }




      if(Application.m_etype == application::type_normal)
      {

         if(!m_prender->m_bLite)
         {

            Application.load_ai_font();

         }

         m_prender->begin();

      }



   }

   void view::_001OnDestroy(signal_details * pobj)
   {

      m_pevRenderEnd = new manual_reset_event(get_app());

      m_prender->set_run_thread(false);

      m_pevRenderEnd->wait(seconds(15));

      delete m_pevRenderEnd;

   }

   void view::_001OnLayout(signal_details * pobj)
   {

      synch_lock sl(m_pmutex);

      {

         synch_lock slText(&m_mutexText);

         if(m_strNewHelloMultiverse.is_empty())
         {

            if(m_bFastOnEmpty)
            {

               m_bFast = true;

            }

            return;

         }

      }

      m_prender->m_bHelloRender = true;

      if(m_bHelloLayoutOn001Layout)
      {

         m_prender->m_bNewLayout = true;

         m_bOkPending = true;

         m_bFast = true;

      }
      else
      {

         layout();

      }

   }


   void view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {

      if(lHint == 0)
      {
         sp(::userex::pane_tab_view) ppaneview = GetTypedParent < ::userex::pane_tab_view >();
         //if(ppaneview.is_set())
         //{
         //   ppaneview->m_pflagview = this;
         //}

      }
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }

   bool view::in_anime()
   {
      if(m_bFast || ::get_tick_count() - m_dwLastFast < m_dwFastAnime)
         return true;
      if(::get_tick_count() - m_dwLastOk < m_dwAnime)
         return true;
      return false;
   }


   void view::_001OnHelloDraw(::draw2d::dib * pdibParam)
   {

      ::draw2d::graphics * pdc = pdibParam->get_graphics();



      if(Application.m_etype == application::type_mili)
      {

         {

            synch_lock slText(&m_mutexText);

            string strHelloMultiverse = get_processed_matchmaking();

            if(m_prender->m_bNewLayout)
            {

               float fHeight = 100.0;

               m_prender->m_font->create_pixel_font(FONT_SANS,fHeight,FW_BOLD);

               pdc->set_font(m_prender->m_font);

               pdc->set_text_rendering(::draw2d::text_rendering_anti_alias);

               class size size = pdc->GetTextExtent(strHelloMultiverse);

               double ratey = fHeight * 0.84 / size.cy;

               m_prender->m_font->create_pixel_font(FONT_SANS,MIN(m_prender->m_cy * ratey,m_prender->m_cx * size.cy * ratey / size.cx),FW_BOLD);

               //m_dMinRadius = MAX(1.0,m_font->m_dFontSize / 23.0);

               //m_dMaxRadius = m_dMinRadius * 2.3;

               //m_dibFast->Fill(0,0,0,0);

               //pdc->set_font(m_font);

               //size = pdc->GetTextExtent(strHelloMultiverse);

               //::draw2d::path_sp path(allocer());

               //path->add_string((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse,m_font);

               //::draw2d::pen_sp pen(allocer());

               //pen->create_solid(1.0,ARGB(255,84 / 2,84 / 2,77 / 2));

               //pdc->FillSolidRect(0,0,m_cx,m_cy,ARGB(0,0,0,0));

               //pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

               //pdc->draw_path(path,pen);

               m_prender->m_bNewLayout = false;

            }


            ::color ca;

            double dPeriod = (500) * 11;

            ca.set_hls(fmod(::get_tick_count(),dPeriod) / dPeriod,0.49,0.84);

            ::draw2d::brush_sp brush(allocer());

            brush->create_solid(ARGB(255,ca.m_uchR,ca.m_uchG,ca.m_uchB));

            pdc->SelectObject(brush);

            pdc->set_font(m_prender->m_font);

            pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

            pdc->set_text_rendering(::draw2d::text_rendering_anti_alias);

            ::size size = pdc->GetTextExtent(strHelloMultiverse);

            pdc->TextOut((m_prender->m_cx - size.cx) / 2,(m_prender->m_cy - size.cy) / 2,strHelloMultiverse);

            return;

         }

      }

      if(m_bFast || !m_prender->m_bFirstDone || ::get_tick_count() - m_dwLastFast < m_dwFastAnime)
      {

         synch_lock sl1(get_wnd()->m_pmutex);

         synch_lock slDraw(&m_prender->m_mutexDraw);

         if(m_bFast || m_dibFast.is_null())
         {

            m_bFast = false;

            {

               synch_lock slText(&m_mutexText);

               matchmaking_fast_render(get_processed_matchmaking());

            }

            m_prender->m_bFirstDone = false;

         }

         if(m_bFast || !m_prender->m_bFirstDone)
         {

            m_dwLastFast = ::get_tick_count();

         }

         pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

         pdc->BitBlt(null_point(),size(m_prender->m_cx,m_prender->m_cy),m_dibFast->get_graphics());

         //pdc->FillSolidRect(400,400,100,100,ARGB(128,0,0,128));

         m_bOkPending = true;

         return;

      }

      if(m_bOkPending)
      {

         m_bOkPending = false;

         m_dwLastOk = ::get_tick_count();

      }

      ::draw2d::dib * pdib = NULL;

      ::draw2d::dib * pdibFast = m_dibFast;

      synch_lock sl(&m_prender->m_mutexDraw);

      synch_lock slSwap(&m_prender->m_mutexSwap);

      if(m_prender->m_bDib1)
      {

         pdib = m_prender->m_dib1;

         //         pdibFast = m_dibFast1;

      }
      else
      {

         pdib = m_prender->m_dib2;

         //         pdibFast = m_dibFast2;

      }

      if(pdib->area() <= 0)
         return;

      pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

      if(::get_tick_count() - m_dwLastOk < m_dwAnime)
      {

         byte uchAlpha = MAX(0,MIN(255,(::get_tick_count() - m_dwLastOk) * 255 / m_dwAnime));

         rect rectClient;

         GetClientRect(rectClient);

         //pdc->FillSolidRect(rectClient,0);

         System.visual().imaging().bitmap_blend(pdc,null_point(),pdib->get_size(),pdib->get_graphics(),null_point(),uchAlpha);

         System.visual().imaging().bitmap_blend(pdc,null_point(),pdibFast->get_size(),pdibFast->get_graphics(),null_point(),255 - uchAlpha);

      }
      else
      {
         //pdibParam->map();
         //pdib->map();
         pdc->from(null_point(),pdib->get_size(),pdib->get_graphics(),null_point(), SRCCOPY);

      }

      //System.visual().imaging().bitmap_blend(pdc,null_point(),pdibFast->get_size(),pdibFast->get_graphics(),null_point(),255);


      //pdc->FillSolidRect(100,100,100,100,ARGB(128,0,128,0));

   }


   void view::_001OnDraw(::draw2d::dib * pdib)
   {

      ::draw2d::graphics * pdc = pdib->get_graphics();

      rect rectClient;

      GetClientRect(rectClient);

      pdc->FillSolidRect(rectClient, ARGB(255, 23, 11, 33));

      ::draw2d::dib * pdib1 = get_map("de_dust2");

      pdc->BitBlt(100, 100, pdib1->size().cx, pdib1->size().cy,
                  pdib1->get_graphics(),
                  0, 0, SRCCOPY);

   }

   ::draw2d::dib * view::get_map(string str)
   {

      if (m_map[str].is_null())
      {

         m_map[str].alloc(allocer());

         visual::dib_sp d(allocer());

         d.load_from_matter("map/" + str + ".png");

         m_map[str]->from(d);

      }

      return m_map[str];

   }


   void view::matchmaking_fast_render(const string & strHelloMultiverse)
   {

      if(m_prender->m_cx <= 0 || m_prender->m_cy <= 0)
         return;

      synch_lock slDraw(&m_prender->m_mutexDraw);

      ::size sizeNew = ::size(m_prender->m_cx,m_prender->m_cy) + ::size(100,100);

      bool bNewSize = m_dibFast->m_size.cx < sizeNew.cx || m_dibFast->m_size.cy < sizeNew.cy;

      if(bNewSize)
      {

         m_dibFast->create(sizeNew);

      }

      m_dibFast->m_iHeight = m_prender->m_cy;

      m_dibFast->Fill(0,0,0,0);

      ::draw2d::graphics * pdc = m_dibFast->get_graphics();

      float fHeight = 100.0;

      m_prender->m_font->create_pixel_font(m_strFont,fHeight,FW_BOLD);

      pdc->set_font(m_prender->m_font);

      pdc->set_text_rendering(::draw2d::text_rendering_anti_alias);

      class size size = pdc->GetTextExtent(strHelloMultiverse);

      double ratey = fHeight * 0.84 / size.cy;

      m_prender->m_font->create_pixel_font(m_strFont,MIN(m_prender->m_cy * ratey,m_prender->m_cx * size.cy * ratey / size.cx),FW_BOLD);

      m_prender->m_dMinRadius = MAX(1.0,MIN(m_prender->m_cy * ratey,m_prender->m_cx * size.cy * ratey / size.cx) / 46.0);

      m_prender->m_dMaxRadius = m_prender->m_dMinRadius * 2.3;



      pdc->set_font(m_prender->m_font);

      size = pdc->GetTextExtent(strHelloMultiverse);

      ::draw2d::path_sp path(allocer());

      path->m_bFill = false;

      path->add_string((m_prender->m_cx - size.cx) / 2,(m_prender->m_cy - size.cy) / 2,strHelloMultiverse,m_prender->m_font);

      ::draw2d::pen_sp pen(allocer());

      pen->create_solid(1.0,ARGB(255,84,84,77));

      ::draw2d::pen_sp penW(allocer());

      penW->create_solid(3.0,ARGB(84,255,255,255));

      pdc->set_alpha_mode(::draw2d::alpha_mode_set);

//      pdc->FillSolidRect((m_prender->m_cx - size.cx) / 2,(m_prender->m_cy - size.cy) / 2, 100, 100, ARGB(255,255,200,240));

      pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

      pdc->draw_path(path,penW);
      pdc->draw_path(path,pen);
      //pdc->FillSolidRect(00,00,100,100,ARGB(128,128,0,0));

   }




   ::user::document * view::get_document()
   {

      return  (::user::impact::get_document());

   }



   void view::_001OnPostProcess(::draw2d::dib * pdib)
   {

      if(m_eeffect == effect_crt)
      {

         int iFactor = 3;
         int iMult = 1 << iFactor;

         pdib->get_graphics()->StretchBlt(0,0,pdib->get_size().cx / iMult,pdib->get_size().cy / iMult,pdib->get_graphics(),0,0,pdib->get_size().cx,pdib->get_size().cy,SRCCOPY);
         pdib->get_graphics()->StretchBlt(0,0,pdib->get_size().cx,pdib->get_size().cy,pdib->get_graphics(),0,0,pdib->get_size().cx / iMult,pdib->get_size().cy / iMult,SRCCOPY);

         COLORREF cr;

         byte a,r,g,b,rm,gm,bm;

         size s = pdib->m_size;

         pdib->map();

         int h = (s.cy / 3) * 3;

         int w = (s.cx / 3) * 3;

         int rstride = pdib->m_iScan / sizeof(COLORREF);

         for(int i = 0; i < h; i+=3)
         {
            for(int j = 0; j < w; j+=3)
            {
               cr = pdib->m_pcolorref[i * rstride + j];
               a = argb_get_a_value(cr);
               r = argb_get_r_value(cr);
               g = argb_get_g_value(cr);
               b = argb_get_b_value(cr);
               rm = (g + b) / 4;
               gm = (r + b) / 4;
               bm = (r + g) / 4;
               pdib->m_pcolorref[i * rstride + j] = ARGB(a,r,rm,rm);
               pdib->m_pcolorref[i * rstride + j + 1] = ARGB(a,gm,g,gm);
               pdib->m_pcolorref[i * rstride + j + 2] = ARGB(a,bm,bm,b);
               pdib->m_pcolorref[(i + 1) * rstride + j] = ARGB(a,r,rm,rm);
               pdib->m_pcolorref[(i + 1) * rstride + j + 1] = ARGB(a,gm,g,gm);
               pdib->m_pcolorref[(i + 1) * rstride + j + 2] = ARGB(a,bm,bm,b);
               pdib->m_pcolorref[(i + 2) * rstride + j] = ARGB(a,r,rm,rm);
               pdib->m_pcolorref[(i + 2) * rstride + j + 1] = ARGB(a,gm,g,gm);
               pdib->m_pcolorref[(i + 2) * rstride + j + 2] = ARGB(a,bm,bm,b);
            }
         }

         ::draw2d::pen_sp pen(allocer());

         pen->create_solid(0.5,ARGB(84,0,0,0));

         pdib->get_graphics()->SelectObject(pen);

         for(int i = 0; i < pdib->get_size().cy; i+=3)
         {

            pdib->get_graphics()->draw_line(0,i,pdib->get_size().cx,i);

         }


      }

   }






   void view::layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      if(rectClient.area() <= 0)
         return;

      if(m_prender->m_cx == rectClient.width()
            && m_prender->m_cy == rectClient.height()
            && m_strNewFont == m_strFont)
         return;


      if(m_strNewFont != m_strFont)
      {
         m_strFont = m_strNewFont;

         data_set("cur_font",m_strFont);

      }

      m_prender->m_cx = rectClient.width();

      m_prender->m_cy = rectClient.height();

      m_prender->m_rectClient = rectClient;

      m_prender->m_bNewLayout = true;

      m_bOkPending = true;

      m_bFast = true;

   }


   string view::get_processed_matchmaking()
   {

      synch_lock slText(&m_mutexText);

      string str = get_matchmaking();

      int c = m_ppcreutil->matches(str);

//      int c = pcre2_get_ovector_count(m_pmd);

      if(c > 0)
      {
         str += "Smile for you too (pcremade |-) !!";
      }


      if(::str::begins_eat_ci(str,"image:"))
      {

         string strImage = str;

         strsize iFind = strImage.find(",");

         if(iFind >= 0)
         {

            strImage = strImage.Mid(0,iFind);

         }

         if(m_strImage != strImage)
         {

            m_strImage = strImage;


            ::fork(get_app(),[=]() {


               if(::str::ends_ci(strImage,".png"))
               {
               }
               else if(::str::ends_ci(strImage,".jpg"))
               {
               }
               else
               {
                  Sleep(884);
               }

               if(m_strImage != strImage)
                  return;


               get_document()->on_open_document(m_strImage);
               //   var varFile;
               //
               //   varFile["url"] = strImage;
               //
               //   varFile["http_set"]["raw_http"] = System.url().get_server(m_strImage).find_wci("ca2") < 0;
               //
               //   ::visual::dib_sp dib(allocer());
               //
               //   if(dib.load_from_file(varFile))
               //   {
               //
               //      if(strImage == m_strImage)
               //      {

               //         *m_prender->m_dibImage = *dib;
               //      }

               //   }

            });

         }


         if(m_prender->m_dibImage.is_set() && m_prender->m_dibImage->area() > 0)
         {

            if(::str::begins_eat_ci(str,m_strImage))
            {
               ::str::begins_eat_ci(str,",");
            }

         }

      }

      if(::str::begins_eat_ci(str, "crt:"))
      {

         m_eeffect = effect_crt;

      }
      else
      {

         m_eeffect = effect_none;

      }

      return str;

   }


   string view::get_matchmaking()
   {

      synch_lock sl(&m_mutexText);

      if(m_strHelloMultiverse != m_strNewHelloMultiverse)
      {

         m_strHelloMultiverse = m_strNewHelloMultiverse;

      }

      if(m_strHelloMultiverse.is_empty())
      {

         if(m_prender->m_bAlternate)
         {

            if(m_dFps != 0.0)
            {
               return "Rolling " + Application.m_strAlternateHelloMultiverse;
            }
            else
            {
               return Application.m_strAlternateHelloMultiverse;
            }


         }
         else
         {

            if(m_dFps != 0.0)
            {
               return "Rolling " + Application.m_strHelloMultiverse;
            }
            else
            {
               return Application.m_strHelloMultiverse;
            }


         }

      }
      else
      {

         return m_strHelloMultiverse;

      }

   }




} // namespace matchmaking

















