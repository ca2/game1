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
      m_dibTime(allocer()),
      m_lines(papp),
      m_dibCheck(allocer())
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

      m_dwAnime = 2000;

      m_dwFastAnime = 584;

      m_bOkPending = true;

      m_bHelloLayoutOn001Layout = true;

      m_b001LayoutIgnoreEmpty = false;

      m_bFastOnEmpty = true;

      m_bFast = true;

      m_dibBk.load_from_file(Application.handler()->m_varTopicQuery["hello_bk"]);


      m_ppcreutil = pcre_util::compile(get_app(), "\\:\\-\\)");

   }

   view::~view()
   {
   }

   void view::assert_valid() const
   {
      user::box::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      user::box::dump(dumpcontext);
   }

   void view::install_message_routing(::message::sender * psender)
   {

      ::user::impact::install_message_routing(psender);

      IGUI_MSG_LINK(WM_VIEW_UPDATE,psender,this,&view::_001OnLayout);
      IGUI_MSG_LINK(WM_CREATE,psender,this,&view::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, psender, this, &view::_001OnDestroy);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &view::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, psender, this, &view::_001OnLButtonUp);

   }


   void view::_001OnCreate(::message::message * pobj)
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

      ::file::patha patha;

      Application.dir().matter_ls("map", patha);

      for (auto & path : patha)
      {



         if (path.m_iDir == 0 && path.extension().compare_ci("png") == 0)
         {

            ::draw2d::dib * pdib = get_map(path.title());




         }


      }

      m_font.alloc(allocer());

      m_font->create_pixel_font("Verdana", 16);

      visual::dib_sp d(allocer());

      d.load_from_matter("check.png", false);

      m_dibCheck->create(16, 16);
      m_dibCheck->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
      m_dibCheck->get_graphics()->alpha_blend(0, 0, m_dibCheck->size().cx, m_dibCheck->size().cy, d->get_graphics(), 0, 0, d->size().cx, d->size().cy, 1.0);

   }

   void view::_001OnDestroy(::message::message * pobj)
   {

      m_pevRenderEnd = new manual_reset_event(get_app());

      m_prender->post_quit();

      m_pevRenderEnd->wait(seconds(15));

      delete m_pevRenderEnd;

   }

   void view::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pobj->m_bRet = true;

   }

   void view::_001OnLButtonUp(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pobj->m_bRet = true;

      for (auto & r : m_rectmap)
      {

         rect rs(r.m_element2);

         ClientToScreen(rs);

         if (rs.contains(pmouse->m_pt))
         {

            m_vote[r.m_element1]++;

         }



      }

   }

   void view::_001OnLayout(::message::message * pobj)
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

         on_layout();

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


   void view::_001OnHelloDraw(::draw2d::graphics * pgraphics)
   {

      ::draw2d::graphics * pgraphics = pdibParam->get_graphics();

      rect rectClient;

      GetClientRect(rectClient);

      pgraphics->FillSolidRect(rectClient, ARGB(255, 23, 11, 33));

      point ptCursor;

      Session.get_cursor_pos(&ptCursor);

      pgraphics->selectFont(m_font);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);

      pgraphics->set_text_color(ARGB(255, 255, 255, 255));

      string str = "User: " + Application.get_steam_user_name();



      if (str.get_length() < 20)
      {
         TRACE("x");
      }

      pgraphics->text_out(100, 50, str);

      int starty = 100;
      int startx = 100;
      int x = 100;
      int y = starty;
      int maxx = 0;
      int maxy = 0;
      pgraphics->set_text_color(ARGB(255, 255, 255, 255));
      for (auto & pair : m_map)
      {

         ::draw2d::dib * pdib1 = get_map(pair.m_element1);

         if (x > startx)
         {

            if (x + pdib1->m_size.cx > rectClient.right - startx)
            {

               x = startx;

               y += maxy + 8;

               maxy = 0;

            }

         }

         string str(pair.m_element1);

         rect & r = m_rectmap[str];

         r.left = x;
         r.top = y;
         r.right = r.left + pdib1->size().cx;
         r.bottom = r.top + pdib1->size().cy;

         rect rS(r);

         ClientToScreen(rS);


         pgraphics->BitBlt(r, pdib1->get_graphics(), null_point(), SRCCOPY);

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
         if (rS.contains(ptCursor))
         {
            pgraphics->FillSolidRect(r, ARGB(70, 0, 0, 0));
         }
         else
         {

         }



         xfplayer_view_line * & pline = m_linemap[str];

         if (pline == NULL)
         {

            pline = canew(xfplayer_view_line(&m_lines));

            //pgraphics->text_out(x + 2, y + 2, str);


            m_lines.add(pline);

            m_linemap[str] = pline;

            pline->SetBlend(1.0);
            pline->m_bColonPrefix = false;
            pline->SetFont(m_font);
            pline->PrepareLine(
               pgraphics,
               str,
               0,
               rectClient);
            pline->Show(true);
            pline->SetColors(ARGB(255, 255, 255, 255), ARGB(255, 127, 127, 120));

         }

         pline->SetPlacement(r);

         pline->to(pdibParam, true, rectClient, NULL_REF(rect_array), false);

         maxx = MAX(maxx, pdib1->size().cx);

         maxy = MAX(maxy, pdib1->size().cy);

         if (m_vote[str] > 0)
         {

            int startx2 = x + 2;

            int x2 = startx2;

            int y2 = y + pdib1->size().cy - m_dibCheck->size().cy - 2;

            for (index i = 0; i < m_vote[str]; i++)
            {


               pgraphics->BitBlt(x2, y2, m_dibCheck->size().cx, m_dibCheck->size().cy, m_dibCheck->get_graphics(), 0, 0, 1.0);

               x2 += 18;

               if (x2 + 18 > r.right)
               {

                  x2 = startx2;
                  y2 -= m_dibCheck->size().cy + 2;

               }

            }

         }

         x += pdib1->size().cx + 8;



      }


      return;

      pgraphics = pdibParam->get_graphics();



      if(Application.m_etype == application::type_mili)
      {

         {

            synch_lock slText(&m_mutexText);

            string strHelloMultiverse = get_processed_matchmaking();

            if(m_prender->m_bNewLayout)
            {

               float fHeight = 100.0;

               m_prender->m_font->create_pixel_font(FONT_SANS,fHeight,FW_BOLD);

               pgraphics->set_font(m_prender->m_font);

               pgraphics->set_text_rendering(::draw2d::text_rendering_anti_alias);

               class size size = pgraphics->GetTextExtent(strHelloMultiverse);

               double ratey = fHeight * 0.84 / size.cy;

               m_prender->m_font->create_pixel_font(FONT_SANS,MIN(m_prender->m_cy * ratey,m_prender->m_cx * size.cy * ratey / size.cx),FW_BOLD);

               //m_dMinRadius = MAX(1.0,m_font->m_dFontSize / 23.0);

               //m_dMaxRadius = m_dMinRadius * 2.3;

               //m_dibFast->Fill(0,0,0,0);

               //pgraphics->set_font(m_font);

               //size = pgraphics->GetTextExtent(strHelloMultiverse);

               //::draw2d::path_sp path(allocer());

               //path->add_string((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse,m_font);

               //::draw2d::pen_sp pen(allocer());

               //pen->create_solid(1.0,ARGB(255,84 / 2,84 / 2,77 / 2));

               //pgraphics->FillSolidRect(0,0,m_cx,m_cy,ARGB(0,0,0,0));

               //pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               //pgraphics->draw_path(path,pen);

               m_prender->m_bNewLayout = false;

            }


            ::color ca;

            double dPeriod = (500) * 11;

            ca.set_hls(fmod(::get_tick_count(),dPeriod) / dPeriod,0.49,0.84);

            ::draw2d::brush_sp brush(allocer());

            brush->create_solid(ARGB(255,ca.m_uchR,ca.m_uchG,ca.m_uchB));

            pgraphics->SelectObject(brush);

            pgraphics->set_font(m_prender->m_font);

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            pgraphics->set_text_rendering(::draw2d::text_rendering_anti_alias);

            ::size size = pgraphics->GetTextExtent(strHelloMultiverse);

            pgraphics->text_out((m_prender->m_cx - size.cx) / 2,(m_prender->m_cy - size.cy) / 2,strHelloMultiverse);

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

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         pgraphics->BitBlt(null_point(),size(m_prender->m_cx,m_prender->m_cy),m_dibFast->get_graphics());

         //pgraphics->FillSolidRect(400,400,100,100,ARGB(128,0,0,128));

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

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      if(::get_tick_count() - m_dwLastOk < m_dwAnime)
      {

         byte uchAlpha = MAX(0,MIN(255,(::get_tick_count() - m_dwLastOk) * 255 / m_dwAnime));

         rect rectClient;

         GetClientRect(rectClient);

         //pgraphics->FillSolidRect(rectClient,0);

         System.visual().imaging().bitmap_blend(pgraphics,null_point(),pdib->get_size(),pdib->get_graphics(),null_point(),uchAlpha);

         System.visual().imaging().bitmap_blend(pgraphics,null_point(),pdibFast->get_size(),pdibFast->get_graphics(),null_point(),255 - uchAlpha);

      }
      else
      {
         //pdibParam->map();
         //pdib->map();
         pgraphics->from(null_point(),pdib->get_size(),pdib->get_graphics(),null_point(), SRCCOPY);

      }

      //System.visual().imaging().bitmap_blend(pgraphics,null_point(),pdibFast->get_size(),pdibFast->get_graphics(),null_point(),255);


      //pgraphics->FillSolidRect(100,100,100,100,ARGB(128,0,128,0));

   }


   void view::_001OnDraw(::draw2d::graphics * pgraphics)
   {
      
      uint64_t startTime = get_nanos();




      //if (m_prender != NULL)
      //{

      //   synch_lock sl(&m_mutexText);

      //   if (get_processed_hellomultiverse() != m_prender->m_strHelloMultiverse)
      //   {

      //      m_prender->m_strHelloMultiverse = get_processed_hellomultiverse().c_str(); // rationale : string allocation fork *for multithreading*

      //      sl.unlock();

      //      _001OnLayout(NULL);

      //   }

      //}

      ::rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.area() <= 0)
         return;

      m_dibPost->create(rectClient.size());

      m_dibPost->Fill(00, 00, 00, 00);

      if (m_dibBk.is_set() && m_dibBk->area() > 0)
      {
         m_dibPost->get_graphics()->BitBlt(
            0, 0, MIN(rectClient.width(), m_dibBk->m_size.cx),
            MIN(rectClient.height(), m_dibBk->m_size.cy),
            m_dibBk->get_graphics());
      }

      if (m_prender->m_bImageEnable && m_prender->m_dibImage.is_set() && m_prender->m_dibImage->area() > 0)
         //if(m_prender->m_dibImage.is_set() && m_prender->m_dibImage->area() > 0)
      {

         //m_bFirstDone = true;

         ::rect rectWork(0, 0, m_prender->m_dibWork->get_size().cx, m_prender->m_dibWork->get_size().cy);
         ::rect rectImage(0, 0, m_prender->m_dibImage->get_size().cx, m_prender->m_dibImage->get_size().cy);

         rectImage.FitOnCenterOf(rectWork);

         m_dibPost->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         m_dibPost->get_graphics()->StretchBlt(rectImage.left, rectImage.top, rectImage.width(), rectImage.height(),
                                               m_prender->m_dibImage->get_graphics(), 0, 0,
                                               m_prender->m_dibImage->get_size().cx,
                                               m_prender->m_dibImage->get_size().cy, SRCCOPY);


      }

      ::draw2d::graphics * pgraphics = m_dibPost->get_graphics();



      _001OnHelloDraw(m_dibPost);

      m_dibTime->create(m_dibPost->get_size());

      m_dibTime->Fill(0, 0, 0, 0);


      DWORD xOffset;

      xOffset = m_dibTime->m_size.cx * m_dFps * (double)(::get_tick_count() - m_dwRoll) / 1000.0; // x = v.t; f=fps  1920 * 1FPS * t

      xOffset %= m_dibTime->m_size.cx;

      m_dibTime->from(point(xOffset, 0), m_dibPost, ::null_point(), ::size(m_dibPost->m_size.cx - xOffset, m_dibPost->m_size.cy));
      m_dibTime->from(null_point(), m_dibPost, point(m_dibPost->m_size.cx - xOffset, 0), size(xOffset, m_dibPost->m_size.cy));

      //m_dibPost->from(m_dibTime);
      _001OnPostProcess(m_dibTime);

      ::draw2d::graphics * pdcParam = pdib->get_graphics();

      pdcParam->set_alpha_mode(::draw2d::alpha_mode_blend);

      //      m_dibPost->get_graphics()->FillSolidRect(110,110,100,100,ARGB(184,177,184,60));

      pdcParam->from(m_dibTime->get_size(), m_dibTime->get_graphics(), SRCCOPY);

      //pdcScreen->FillSolidRect(10,10,100,100,ARGB(184,49,184,60));

      //pdcScreen->Draw3dRect(200,200,100,100,ARGB(255,0,255,0),ARGB(255,0,0,255));
      uint64_t endTime = get_nanos();

      uint64_t micros = (endTime - startTime) / 1000;

      //char sz[512];

      //::output_debug_string("view:");
      //::ultoa_dup(sz, micros, 10);
      //::output_debug_string(sz);
      //::output_debug_string(", ");



   }

   ::draw2d::dib * view::get_map(string str)
   {

      if (m_map[str].is_null())
      {

         m_map[str].alloc(allocer());

         visual::dib_sp d(allocer());

         d.load_from_matter("map/" + str + ".png", false);

         m_map[str]->from(d);

      }

      return m_map[str];

   }


   void view::matchmaking_fast_render(const string & strHelloMultiverse)
   {

      if(m_prender->m_cx <= 0 || m_prender->m_cy <= 0)
         return;

      synch_lock slDraw(&m_prender->m_mutexDraw);

      ::size sizeNew = ::size(m_prender->m_cx,m_prender->m_cy);

      m_dibFast->create(sizeNew);

      m_dibFast->Fill(0,0,0,0);

      ::draw2d::graphics * pgraphics = m_dibFast->get_graphics();

      float fHeight = 100.0;

      m_prender->m_font->create_pixel_font(m_strFont,fHeight,FW_BOLD);

      pgraphics->set_font(m_prender->m_font);

      pgraphics->set_text_rendering(::draw2d::text_rendering_anti_alias);

      class size size = pgraphics->GetTextExtent(strHelloMultiverse);

      double ratey = fHeight * 0.84 / size.cy;

      m_prender->m_font->create_pixel_font(m_strFont,MIN(m_prender->m_cy * ratey,m_prender->m_cx * size.cy * ratey / size.cx),FW_BOLD);

      m_prender->m_dMinRadius = MAX(1.0,MIN(m_prender->m_cy * ratey,m_prender->m_cx * size.cy * ratey / size.cx) / 46.0);

      m_prender->m_dMaxRadius = m_prender->m_dMinRadius * 2.3;



      pgraphics->set_font(m_prender->m_font);

      size = pgraphics->GetTextExtent(strHelloMultiverse);

      ::draw2d::path_sp path(allocer());

      path->m_bFill = false;

      path->add_string((m_prender->m_cx - size.cx) / 2,(m_prender->m_cy - size.cy) / 2,strHelloMultiverse,m_prender->m_font);

      ::draw2d::pen_sp pen(allocer());

      pen->create_solid(1.0,ARGB(255,84,84,77));

      ::draw2d::pen_sp penW(allocer());

      penW->create_solid(3.0,ARGB(84,255,255,255));

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

//      pgraphics->FillSolidRect((m_prender->m_cx - size.cx) / 2,(m_prender->m_cy - size.cy) / 2, 100, 100, ARGB(255,255,200,240));

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->draw_path(path,penW);
      pgraphics->draw_path(path,pen);
      //pgraphics->FillSolidRect(00,00,100,100,ARGB(128,128,0,0));

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






   void view::on_layout()
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
                  Sleep(900);
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

















