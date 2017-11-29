//
//  matchmaking_render.cpp
//  app_core_matchmaking
//
//  Created by Camilo Sasuke Tsumanuma on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Tsumanuma. All rights reserved.
//


#include "framework.h"
#include <math.h>


namespace matchmaking
{


   render::render(::aura::application * papp):
      object(papp),
      thread(papp),
      m_font(allocer()),
      m_dibTemplate(allocer()),
      m_dibImage(allocer()),
      m_mutexDraw(papp),
      m_mutexWork(papp),
      m_mutexSwap(papp),
      m_dib1(allocer()),
      m_dib2(allocer()),
      m_dibWork(allocer()),
      m_dib(allocer())
   {

      m_pview                    = NULL;

      m_bImageEnable             = true;

      m_bDib1                    = false;

      m_bAlternate               = false;

      m_bLite                    = true;

      m_bNewLayout               = false;
      m_bHelloRender             = false;
      m_cx                       = 0;
      m_cy                       = 0;
      m_cxCache1                 = 0;
      m_cyCache1                 = 0;

      m_bVoidTransfer            = false;
      m_bFirstDone               = false;

      m_dMinRadius               = 0.0;
      m_dMaxRadius               = 0.0;

      m_rectClient.null();


      m_bVoidTransfer =  false;

      m_bFirstDone = true;

      m_cx = 0;

      m_cy = 0;

      m_dMinRadius = 1.0;

      m_dMaxRadius = 2.0;

      m_bNewLayout = false;

      m_bHelloRender = true;

      m_cxCache1 = 0;

      m_cyCache1 = 0;


   }


   render::~render()
   {

   }


   void render::full_render()
   {

      size sizeNew = size(m_cx,m_cy) + size(100,100);

      if(m_bNewLayout)
      {

         synch_lock sl2(&m_mutexWork);
         synch_lock sl3(&m_mutexDraw);
         synch_lock sl4(&m_mutexSwap);

         bool bNewSize = m_dib.m_size.cx < sizeNew.cx || m_dib.m_size.cy < sizeNew.cy;

         m_bNewLayout = false;


         {


            //          DWORD dwTime2 = ::get_tick_count();

            //TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
            //            TRACE("hello_view::lyot call timeA= %d ms",(uint64_t) (dwTime2 - t_time1.operator DWORD_PTR()));

         }


         {

            if(bNewSize)
            {

               //if(!m_dib.initialize(sizeNew.cx,sizeNew.cy,5))
               //   return;

               //m_dib->Fill(0,0,0,0);

            }


            if(bNewSize)
            {

               m_dibWork->create(sizeNew);


            }

         }

         if(bNewSize)
         {


            m_dib1->create(sizeNew);

            m_dib2->create(sizeNew);

         }

      }


      matchmaking_render();

      if(m_bFirstDone)
      {

         matchmaking_draw();

      }
      else
      {
         //TRACE("XXX123546");
      }

   }

   int32_t render::run()
   {

      while(m_bRun)
      {

         try
         {

            if(m_bHelloRender)
            {

               full_render();

            }

            Sleep(100);

         }
         catch(...)
         {

            break;

         }

      }

      if (m_pview != NULL && m_pview->m_pevRenderEnd != NULL)
      {

         m_pview->m_pevRenderEnd->SetEvent();

      }

      return 0;

   }

   void render::matchmaking_render()
   {

      {

         synch_lock sl(&m_mutexWork);

         ::draw2d::dib * pdib = m_dibWork;

         pdib->Fill(0,0,0,0);

         matchmaking_render(pdib);


      }

   }

   void render::matchmaking_render(::draw2d::dib * pdib)
   {



      //   if(m_bLite)
      {

         matchmaking_render_lite_view(pdib);

      }
      //   else
      //   {
      //
      //      matchmaking_render_full_view(pdib->get_graphics());
      //
      //   }

   }


   void render::matchmaking_draw()
   {

      if(m_bVoidTransfer)
         return;

      //_001OnPostProcess(m_dibWork);

      synch_lock slDraw(&m_mutexDraw);

      if(m_bDib1)
      {

         *m_dib2 = *m_dibWork;

      }
      else
      {

         *m_dib1 = *m_dibWork;

      }

      synch_lock slSwap(&m_mutexSwap);

      if(m_bDib1)
      {

         m_bDib1 = false;

      }
      else
      {

         m_bDib1 = true;

      }

   }

   void render::matchmaking_render_lite_view(::draw2d::dib * pdib)
   {

      //if(m_dib->area() <= 0)
      //   return;

      if(m_dibWork->area() <= 0)
         return;

      rect rectClient;

      rectClient.left = 0;

      rectClient.top = 0;

      rectClient.right = m_cx;

      rectClient.bottom = m_cy;

      //pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

      //pgraphics->FillSolidRect(rectClient,ARGB(0, 0, 0, 0));

      //      int32_t iCount = 30;

      ::draw2d::brush_sp brushText(allocer());

      double T = 2.3;

      if(false)
      {

         T = 2.3;

      }
      else if(m_bAlternate)
      {

         T = 1.2;

      }
      else
      {

         T = 2.3;

      }

      double t = ::get_tick_count() / 1000.0;

      double w = 2.0 * 3.1415 / T;

      double r = (tri(w * t) + 1.0) / 2.0;

      //      double dBlur = m_dMinRadius + (m_dMaxRadius - m_dMinRadius) * r;

      //int32_t i = ::get_tick_count()  / 100 % iCount;

      //int32_t iBlur;

      //if(i <= (iCount / 2))
      //   iBlur = i;
      //else
      //   iBlur = iCount - i;

      ::size size;

      

      synch_lock slText(m_pmutexText);

      string strHelloMultiverse(get_matchmaking().c_str()); // rationale : string allocation fork *for multithreading*

      slText.unlock();

      pgraphics->set_font(m_font);

      size = pgraphics->GetTextExtent(strHelloMultiverse);

      if(!m_bFirstDone)
      {

         if(Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
         {

            Sleep(47);
         }
         else
         {

            m_cxCache1 = m_cx;

            m_cyCache1 = m_cy;

            m_dib.initialize(m_cxCache1,m_cyCache1,m_dMaxRadius);

            //m_dib->defer_realize(pgraphics);

            m_dib->Fill(0,0,0,0);

            m_dib->get_graphics()->set_font(m_font);

            m_dib->get_graphics()->set_text_rendering(::draw2d::text_rendering_anti_alias);

            m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

            brushText->create_solid(ARGB(255,255,255,255));

            m_dib->get_graphics()->SelectObject(brushText);

            m_dib->get_graphics()->text_out((m_cxCache1 - size.cx) / 2,(m_cyCache1 - size.cy) / 2,strHelloMultiverse);

            //          m_dib->get_graphics()->FillSolidRect(400,100,100,100,ARGB(128,0,0,255));

            //          m_dib->get_graphics()->FillSolidRect(400,300,100,100,ARGB(255,0,0,255));

            m_dib->map();

            //          memset(m_dib->m_pcolorref, 128, m_dib->m_iScan * 100);

            Application.imaging().spread(m_dib->get_graphics(), point(-m_dMaxRadius, -m_dMaxRadius), m_dib->get_size(), m_dib->get_graphics(), null_point(), m_dMaxRadius * 2);

            m_dib.blur();

//            m_dib.blur();

//            m_dib.blur();

//            m_dib.blur();

            //          m_dib->get_graphics()->FillSolidRect(300,300,100,100,ARGB(128,128,255,255));

            m_dibTemplate->create(m_dib->m_size);

            m_dibTemplate->Fill(0,0,0,0);

            m_dibTemplate->channel_copy(visual::rgba::channel_alpha,visual::rgba::channel_green,m_dib);

         }

      }

      slText.lock();

      if(strHelloMultiverse != get_matchmaking() || m_cxCache1 != m_cx || m_cyCache1 != m_cy || m_dibTemplate->area() <= 0)
         return;

      slText.unlock();

      ::color ca;


      if(false)
      {

         double dPeriod = (5000) * 11;

         ca.set_hls(fmod(::get_tick_count(),dPeriod) / dPeriod,0.49,0.84);

      }
      else if(m_bAlternate)
      {

         double dPeriod = (5100) * 8;

         ca.set_hls(fmod(::get_tick_count(),dPeriod) / dPeriod,0.49,0.84);

      }
      else
      {

         double dPeriod = (4900) * 11;

         ca.set_hls(fmod(::get_tick_count(),dPeriod) / dPeriod,0.23,0.84);

      }

      if(!Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
      {

         //m_dibTemplate->set_rgb_pre_alpha(ca.m_uchR,ca.m_uchG,ca.m_uchB, 84 + 49 + (255 - 84 - 49) * r);
         m_dibTemplate->set_rgb_pre_alpha(ca.m_uchR, ca.m_uchG, ca.m_uchB);

      }

      pgraphics->SetStretchBltMode(HALFTONE);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      Application.imaging().bitmap_blend(pgraphics,null_point(),rectClient.size(),m_dibTemplate->get_graphics(),null_point(),84 + 49 + (255 - 84 - 49) * r);

      //pgraphics->from(rectClient.top_left(),m_dibTemplate, null_point(), rectClient>si);

      pgraphics->set_font(m_font);

      pgraphics->set_text_rendering(::draw2d::text_rendering_anti_alias);

      if(Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
      {

         brushText->create_solid(ARGB(255,ca.m_uchR,ca.m_uchG,ca.m_uchB));

      }
      else
      {

         if(m_bAlternate)
         {

            brushText->create_solid(ARGB(255,184,184,177));

         }
         else
         {

            brushText->create_solid(ARGB(255,255,255,255));

         }

      }

      pgraphics->SelectObject(brushText);

      //if(!m_bAlternate)
      {

         pgraphics->text_out((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse);

      }
      //      pgraphics->FillSolidRect(200,00,100,100,ARGB(128,128,128,255));

      //    pgraphics->FillSolidRect(200,200,100,100,ARGB(128,128,128,0));

      slText.lock();

      if(strHelloMultiverse == get_matchmaking() && m_cxCache1 == m_cx && m_cyCache1 == m_cy)
      {

         m_bFirstDone = true;

      }

   }


   void render::matchmaking_render_full_view(::draw2d::dib * pdib)
   {

      if(m_dibWork->area() <= 0)
         return;

      rect rectClient;

      rectClient.left = 0;

      rectClient.top = 0;

      rectClient.right = m_cx;

      rectClient.bottom = m_cy;

      if(rectClient.area() <= 0)
         return;

      //      int32_t iCount = 30;

      ::draw2d::brush_sp brushText(allocer());

      double T = 2.3;

      if(false)
      {

         T = 2.3;

      }
      else if(m_bAlternate)
      {

         T = 1.2;

      }
      else
      {

         T = 2.3;

      }

      double t = ::get_tick_count() / 1000.0;

      double w = 2.0 * 3.1415 / T;

      double r = (tri(w * t) + 1.0) / 2.0;

      double dBlur = m_dMinRadius + (m_dMaxRadius - m_dMinRadius) * r;

      ::color ca;

      if(false)
      {

         double dPeriod = (5000) * 11;

         ca.set_hls(fmod(::get_tick_count(),dPeriod) / dPeriod,0.49,0.84);

      }
      else if(m_bAlternate)
      {

         double dPeriod = (5100) * 8;

         ca.set_hls(fmod(::get_tick_count(),dPeriod) / dPeriod,0.49,0.84);

      }
      else
      {

         double dPeriod = (4900) * 11;

         ca.set_hls(fmod(::get_tick_count(),dPeriod) / dPeriod,0.23,0.84);

      }

      

      pgraphics->set_font(m_font);

      string strHelloMultiverse = get_matchmaking();

      ::size size = pgraphics->GetTextExtent(strHelloMultiverse);

      if(!Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
      {

         if(m_dMinRadius > 3.0)
         {

            m_dib.initialize(m_cx,m_cy,dBlur);

         }
         else
         {

            m_dib.initialize(m_cx,m_cy,5);

         }

         m_dib->defer_realize(pgraphics);

         m_dib->Fill(0,0,0,0);

         m_dib->get_graphics()->set_text_rendering(::draw2d::text_rendering_anti_alias);

         m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

         brushText->create_solid(ARGB(255,255,255,255));

         m_dib->get_graphics()->SelectObject(brushText);

         m_dib->get_graphics()->set_font(m_font);

         m_dib->get_graphics()->text_out((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse);

         if(m_dMinRadius > 3.0)
         {

            m_dib.blur(m_cx,m_cy);

         }
         else
         {

            for(int32_t i = 0; i < dBlur * 2; i++)
            {

               m_dib.blur(m_cx,m_cy);

            }

         }

         if(!Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
         {

            m_dib->channel_copy(visual::rgba::channel_alpha,visual::rgba::channel_green);

            m_dib->set_rgb_pre_alpha(ca.m_uchR,ca.m_uchG,ca.m_uchB);

         }

         pgraphics->SetStretchBltMode(HALFTONE);

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         pgraphics->BitBlt(rectClient,m_dib->get_graphics());

      }

      pgraphics->set_text_rendering(::draw2d::text_rendering_anti_alias);

      if(Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
      {

         brushText->create_solid(ARGB(255,ca.m_uchR,ca.m_uchG,ca.m_uchB));

      }
      else
      {

         if(m_bAlternate)
         {

            brushText->create_solid(ARGB(255,184,184,177));

         }
         else
         {

            brushText->create_solid(ARGB(255,255,255,255));

         }

      }

      pgraphics->SelectObject(brushText);

      pgraphics->text_out((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse);

      byte a,R,g,b;

      if(m_bAlternate)
      {
         a = 184;
         R = 177;
         g = 77;
         b = 184;
      }
      else
      {
         a = 184;
         R = 77;
         g = 184;
         b = 84;
      }

#if 0
      if(Application.m_iErrorAiFont == 0)
      {

         synch_lock slAiFont(&Application.m_mutexAiFont);

         FT_Face & face = (FT_Face &)Application.m_faceAi;

         int32_t error;

         error = FT_Set_Char_Size(face,        /* handle to face object */
                                  0,          /* char_width in 1/64th of points */
                                  800 * 64,          /* char_height in 1/64th of points */
                                  72,         /* horizontal device resolution */
                                  72);         /* vertical device resolution */

         if(error == 0)
         {

            error = FT_Select_Charmap(face, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

            if(error == 0)
            {

               int64_t iChar =  ::str::ch::uni_index(::str::international::unicode_to_utf8(L"愛"));

               int32_t glyph_index = FT_Get_Char_Index(face,(int32_t)iChar);

               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */

               if(error == 0)
               {

                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */

                  if(error == 0)
                  {

                     ::visual::dib_sp &  dib = m_dibAi1;

                     dib->create(face->glyph->bitmap.width,face->glyph->bitmap.rows);

                     dib->realize(pgraphics);

                     draw_freetype_bitmap(dib.m_p,0,0,&face->glyph->bitmap,0,0,a,R,g,b);

                     pgraphics->SetStretchBltMode(HALFTONE);

                     pgraphics->StretchBlt(0,0,dib->get_size().cx / 40,dib->get_size().cy / 40,dib->get_graphics(),0,0,dib->get_size().cx,dib->get_size().cy,SRCCOPY);

                     pgraphics->StretchBlt(0,m_cy - dib->get_size().cy / 40,dib->get_size().cx / 40,dib->get_size().cy / 40,dib->get_graphics(),0,0,dib->get_size().cx,dib->get_size().cy,SRCCOPY);

                  }

               }

            }

         }


         error = FT_Set_Char_Size(face,        /* handle to face object */
                                  0,          /* char_width in 1/64th of points */
                                  640 * 64,          /* char_height in 1/64th of points */
                                  72,         /* horizontal device resolution */
                                  72);         /* vertical device resolution */

         if(error == 0)
         {

            error = FT_Select_Charmap(face, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

            if(error == 0)
            {

               int64_t iChar =  ::str::ch::uni_index(::str::international::unicode_to_utf8(L"愛"));

               int32_t glyph_index = FT_Get_Char_Index(face,(int32_t)iChar);

               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */

               if(error == 0)
               {

                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */

                  if(error == 0)
                  {

                     ::visual::dib_sp &  dib = m_dibAi2;

                     dib->create(face->glyph->bitmap.width,face->glyph->bitmap.rows);

                     dib->realize(pgraphics);

                     draw_freetype_bitmap(dib.m_p,0,0,&face->glyph->bitmap,0,0,a,R,g,b);

                     pgraphics->SetStretchBltMode(HALFTONE);

                     pgraphics->StretchBlt(m_cx - dib->get_size().cx / 32,0,dib->get_size().cx / 32,dib->get_size().cy / 32,dib->get_graphics(),0,0,dib->get_size().cx,dib->get_size().cy,SRCCOPY);

                     pgraphics->StretchBlt(m_cx - dib->get_size().cx / 32,m_cy - dib->get_size().cy / 32,dib->get_size().cx / 32,dib->get_size().cy / 32,dib->get_graphics(),0,0,dib->get_size().cx,dib->get_size().cy,SRCCOPY);

                  }

               }

            }

         }

      }

#endif

      if(strHelloMultiverse == get_matchmaking() && m_cx == m_rectClient.width() && m_cy == m_rectClient.height())
      {

         m_bFirstDone = true;

      }

   }



} // namespace matchmaking



