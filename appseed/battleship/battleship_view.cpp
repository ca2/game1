#include "framework.h"
#include <math.h>




namespace tictactoe
{


   view::view(::aura::application * papp) :
      ::object(papp),
      m_dib1(allocer()),
      m_dib2(allocer()),
      m_dib(allocer()),
      m_dibColor(allocer()),
      m_dibWork(allocer()),
      m_font(allocer()),
      m_mutexDraw(papp),
      m_mutexWork(papp),
      m_mutexSwap(papp),
      player(papp)
   {

      m_strHelloMultiverse = "Hello Multiverse!!";

      connect_command("new_game",&view::_001OnNewGame);

      m_parbitrator = new arbitrator(get_app());

      m_parbitrator->m_board.reset();

      string str = THIS_FRIENDLY_NAME();

      if(Application.directrix()->m_varTopicQuery.has_property("bk_alpha") && Application.directrix()->m_varTopicQuery["bk_alpha"].has_property(str))
      {

         m_bBkAlpha= MAX(0,MIN(255,((int)(Application.directrix()->m_varTopicQuery["bk_alpha"][str].get_double() * 255.0))));

      }
      else
      {

         m_bBkAlpha = 255;

      }


   }


   view::~view()
   {

   }


#ifdef DEBUG

   void view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif

   void view::install_message_handling(::message::dispatch * pdispatch)
   {

      ::user::impact::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_CREATE,pdispatch,this,&view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,pdispatch,this,&view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,pdispatch,this,&view::_001OnLButtonUp);

   }


   void view::_001OnCreate(signal_details * pobj)
   {

      new_game();

      SCAST_PTR(::message::create,pcreate,pobj);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

      //load_ai_font();

      __begin_thread(get_app(),&thread_proc_render,this,::multithreading::priority_normal,0,0,NULL);


   }


   void view::_001OnLButtonDown(signal_details * pobj)
   {

      pobj->m_bRet = true;

   }


   void view::_001OnLButtonUp(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      point pt(pmouse->m_pt);

      ScreenToClient(&pt);

      int i = -1;
      int j = -1;

      if(hit_test_check(i,j,pt))
      {

         if(i >= 0 && j >= 0)
         {

            m_ptLast.x = i;

            m_ptLast.y = j;

            set_ready();

         }

      }

   }


   void view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }



   void view::_001OnDraw(::draw2d::graphics * pgraphicsParam)
   {

      //::draw2d::graphics * pgraphics = pdibParam->get_graphics();

      ::draw2d::dib * pdib = NULL;

      synch_lock sl(&m_mutexDraw);

      synch_lock slSwap(&m_mutexSwap);

      if(m_bDib1)
      {

         pdib = m_dib1;

      }
      else
      {
         pdib = m_dib2;
      }

      if(pdib->area() <= 0)
         return;

      rect rectClient;

      GetClientRect(rectClient);

      pgraphicsParam->set_alpha_mode(::draw2d::alpha_mode_set);

      //pgraphics->FillSolidRect(rectClient, ARGB(255,184,184,184));

      pgraphicsParam->set_alpha_mode(::draw2d::alpha_mode_blend);
      if(m_dibBk.is_set() && m_dibBk->area() > 0)
      {
        // pgraphics->FillSolidRect(rectClient,ARGB(0,0,0,0));
         if(m_bBkAlpha == 255)
         {
            pgraphicsParam->BitBlt(
               0,0,MIN(rectClient.width(),m_dibBk->m_size.cx),
               MIN(rectClient.height(),m_dibBk->m_size.cy),
               m_dibBk->get_graphics());

         }
         else
         {
            System.visual().imaging().bitmap_blend(pgraphicsParam,null_point(),size(MIN(rectClient.width(),m_dibBk->m_size.cx),
               MIN(rectClient.height(),m_dibBk->m_size.cy)),m_dibBk->get_graphics(),null_point(),m_bBkAlpha);
         }
      }
      else
      {
         pgraphicsParam->FillSolidRect(rectClient,ARGB(49,0xff,0xff,0xff));
      }
      pgraphicsParam->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphicsParam->from(pdib->m_size,pdib->get_graphics(),SRCCOPY);

   }


   void view::tictactoe_render(::draw2d::graphics * pgraphics)
   {

      

      if(m_dib->area() <= 0)
         return;

      if(m_dibWork->area() <= 0)
         return;

      m_dib->defer_realize(pgraphics);

      m_dib->Fill(0,0,0,0);

      rect rectClient;

      ::rect rectCheck;

      e_check echeck;

      rectClient.left = 0;
      rectClient.top = 0;
      rectClient.right = m_dib->m_size.cx;
      rectClient.bottom = m_dib->m_size.cy;

      int32_t iCount = 20;

      ::draw2d::brush_sp brushText(allocer());
      ::draw2d::brush_sp brushToe(allocer());

      ::draw2d::pen_sp penText(allocer());
      ::draw2d::pen_sp penToe(allocer());

      int32_t i = ::get_tick_count()  / 100 % iCount;

      int32_t iBlur;

      if(i <= (iCount / 2))
         iBlur = i;
      else
         iBlur = iCount - i;

      m_dib->get_graphics()->set_font(m_font);

      m_font->m_bUpdated = false;


      board & board = m_parbitrator->m_board;

      ::size size = m_dib->get_graphics()->GetTextExtent(m_strHelloMultiverse);

      if(!Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
      {

         m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

         brushText->create_solid(ARGB(255, 255, 255, 255));

         penText->create_solid(m_rectSpace.width() / 16,ARGB(255,255,255,255));

         m_dib->get_graphics()->SelectObject(brushText);
         m_dib->get_graphics()->SelectObject(penText);

         draw_board(m_dib->get_graphics(),m_rectSpace);

         for(index i = 0; i < board.get_size(); i++)
         {

            for(index j = 0; j < board.get_size(); j++)
            {

               echeck = board[i][j];

               if(echeck != check_none)
               {

                  get_check_rect(rectCheck,i,j);

                  if(echeck == check_x)
                  {

                     draw_x(m_dib->get_graphics(),rectCheck);

                  }
                  else
                  {
                     draw_o(m_dib->get_graphics(),rectCheck);
                  }

               }



            }

         }

         m_dib.blur();

         m_dib.blur();

//////         m_dib.blur();

      //   m_dib.blur();

         for(int32_t i = 0; i < iBlur; i++)
         {

            //if((i % 2) == 0)

            m_dib.blur();

         }


      }

      ::color ca;


      double dPeriod = (5000) * 11;

      ca.set_hls(fmod(::get_tick_count(), dPeriod) / dPeriod, 0.49, 0.84);

      if(!Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
      {

         m_dib->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_green);

         m_dib->set_rgb(ca.m_uchR, ca.m_uchG, ca.m_uchB);

         //m_dib->Fill(255, ca.m_uchR, ca.m_uchG, ca.m_uchB);


         //m_dib->channel_multiply(visual::rgba::channel_alpha, 2.84);

      }

      //pgraphics->FillSolidRect(50, 50, 100, 100, ARGB(255, 255, 255, 0));

      //m_dib->get_graphics()->FillSolidRect(10, 10, 100, 100, ARGB(255, 0, 255, 0));

      pgraphics->SetStretchBltMode(HALFTONE);
      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
      pgraphics->BitBlt(rectClient, m_dib->get_graphics());
//      System.visual().imaging().true_blend(pgraphics, null_point(), rectClient.size(), m_dib->get_graphics(), null_point());
  //    System.visual().imaging().true_blend(pgraphics, null_point(), rectClient.size(), m_dib->get_graphics(), null_point());
    //  System.visual().imaging().true_blend(pgraphics, null_point(), rectClient.size(), m_dib->get_graphics(), null_point());
      /*for(int32_t i = 0; i < iBlur + 1; i++)
      {
      if((i % 2) == 1)
      System.visual().imaging().true_blend(pgraphics, null_point(), rectClient.size(), m_dib->get_graphics(), null_point());
      }
      */

      m_font->m_bUpdated = false;

      pgraphics->set_font(m_font);

      bool bHasMatch = m_parbitrator->check_winner() != check_none;

      if(Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
      {
         brushToe->create_solid(ARGB(255,ca.m_uchR,ca.m_uchG,ca.m_uchB));
         penToe->create_solid(m_rectSpace.width() / 16,ARGB(255,ca.m_uchR,ca.m_uchG,ca.m_uchB));
         if(bHasMatch)
         {
            brushText->create_solid(ARGB(177,ca.m_uchR,ca.m_uchG,ca.m_uchB));
            penText->create_solid(m_rectSpace.width() / 16,ARGB(184,ca.m_uchR,ca.m_uchG,ca.m_uchB));
         }

      }
      else
      {

         brushToe->create_solid(ARGB(255,255,255,255));
         penToe->create_solid(m_rectSpace.width() / 16,ARGB(255,255,255,255));
         if(bHasMatch)
         {
            brushText->create_solid(ARGB(184,184 + 49,184 + 49,177 + 49));
            penText->create_solid(m_rectSpace.width() / 16,ARGB(177,184 + 49,184 + 49,177 + 49));
         }
      }
      if(!bHasMatch)
      {
         brushText = brushToe;
         penText = penToe;
      }


      pgraphics->SelectObject(brushText);
      pgraphics->SelectObject(penText);

      draw_board(pgraphics,m_rectSpace);


      for(index i = 0; i < board.get_size(); i++)
      {

         for(index j = 0; j < board.get_size(); j++)
         {

            echeck = board[i][j];

            if(echeck != check_none)
            {

               if(m_parbitrator->m_board.match(i,j) != check_none)
               {
                  pgraphics->SelectObject(brushToe);
                  pgraphics->SelectObject(penToe);

               }
               else
               {
                  pgraphics->SelectObject(brushText);
                  pgraphics->SelectObject(penText);

               }

               get_check_rect(rectCheck,i,j);

               if(echeck == check_x)
               {

                  draw_x(pgraphics,rectCheck);

               }
               else
               {
                  draw_o(pgraphics,rectCheck);
               }

            }



         }

      }


      //pgraphics->SelectObject(brushText);

      //pgraphics->text_out((rectClient.width() - size.cx) / 2, (rectClient.height() - size.cy) / 2,  m_strHelloMultiverse);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      for(index i = 0; i < board.get_size(); i++)
      {

         for(index j = 0; j < board.get_size(); j++)
         {

            echeck = board[i][j];

            if(echeck != check_none)
            {

               get_check_rect(rectCheck,i,j);

               pgraphics->FillSolidRect(rectCheck,ARGB(1,255,255,255));

            }



         }
      }

      //if(m_iErrorAiFont == 0)
      //{

      //   FT_Face & face = (FT_Face &) m_faceAi;

      //   int32_t error;

      //   error = FT_Set_Char_Size( face,        /* handle to face object */
      //      0,          /* char_width in 1/64th of points */
      //      800*64,          /* char_height in 1/64th of points */
      //      72,         /* horizontal device resolution */
      //      72 );         /* vertical device resolution */

      //   if(error == 0)
      //   {

      //      error = FT_Select_Charmap( face, /* target face object */ FT_ENCODING_UNICODE ); /* encoding */

      //      if(error == 0)
      //      {

      //         int64_t iChar =  ::str::ch::uni_index(::str::international::unicode_to_utf8(L"愛"));

      //         int32_t glyph_index = FT_Get_Char_Index( face, (int32_t) iChar );

      //         error = FT_Load_Glyph( face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT ); /* load flags, see below */

      //         if(error == 0)
      //         {

      //            error = FT_Render_Glyph( face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL ); /* render mode */

      //            if(error == 0)
      //            {

      //               ::visual::dib_sp dib(allocer());

      //               dib->create(face->glyph->bitmap.width, face->glyph->bitmap.rows);

      //               dib->realize(pgraphics);

      //               draw_freetype_bitmap(dib.m_p, 0,0,&face->glyph->bitmap,0,0, 184, 77, 77, 184);

      //               pgraphics->SetStretchBltMode(HALFTONE);

      //               pgraphics->StretchBlt(0, 0, dib->m_size.cx / 40, dib->m_size.cy / 40, dib->get_graphics(), 0, 0, dib->m_size.cx, dib->m_size.cy,  SRCCOPY);

      //               pgraphics->StretchBlt(0, rectClient.height() - dib->m_size.cy / 40, dib->m_size.cx / 40, dib->m_size.cy / 40, dib->get_graphics(), 0, 0, dib->m_size.cx, dib->m_size.cy,  SRCCOPY);

      //            }

      //         }

      //      }

      //   }


      //   error = FT_Set_Char_Size( face,        /* handle to face object */
      //      0,          /* char_width in 1/64th of points */
      //      640*64,          /* char_height in 1/64th of points */
      //      72,         /* horizontal device resolution */
      //      72 );         /* vertical device resolution */

      //   if(error == 0)
      //   {

      //      error = FT_Select_Charmap( face, /* target face object */ FT_ENCODING_UNICODE ); /* encoding */

      //      if(error == 0)
      //      {

      //         int64_t iChar =  ::str::ch::uni_index(::str::international::unicode_to_utf8(L"愛"));

      //         int32_t glyph_index = FT_Get_Char_Index( face, (int32_t) iChar );

      //         error = FT_Load_Glyph( face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT ); /* load flags, see below */

      //         if(error == 0)
      //         {

      //            error = FT_Render_Glyph( face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL ); /* render mode */

      //            if(error == 0)
      //            {

      //               ::visual::dib_sp dib(allocer());

      //               dib->create(face->glyph->bitmap.width, face->glyph->bitmap.rows);

      //               dib->realize(pgraphics);

      //               draw_freetype_bitmap(dib.m_p,0,0,&face->glyph->bitmap,0,0, 184, 84, 184, 77);

      //               pgraphics->SetStretchBltMode(HALFTONE);

      //               pgraphics->StretchBlt(rectClient.width() - dib->m_size.cx / 32, 0, dib->m_size.cx / 32, dib->m_size.cy / 32, dib->get_graphics(), 0, 0, dib->m_size.cx, dib->m_size.cy,  SRCCOPY);

      //               pgraphics->StretchBlt(rectClient.width() - dib->m_size.cx / 32, rectClient.height() - dib->m_size.cy / 32, dib->m_size.cx / 32, dib->m_size.cy / 32, dib->get_graphics(), 0, 0, dib->m_size.cx, dib->m_size.cy,  SRCCOPY);

      //            }

      //         }

      //      }

      //   }

      //}


   }


   ::user::document * view::get_document()
   {

      return ::user::impact::get_document();

   }


   void view::render()
   {

      {

         synch_lock sl(&m_mutexWork);

         ::draw2d::dib * pdib = m_dibWork;

         pdib->Fill(1,255,255,255);

         tictactoe_render(pdib->get_graphics());

      }

      synch_lock slUser(m_pmutex);

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


   //void view::load_ai_font()
   //{

   //   m_iErrorAiFont = -1;

   //   __begin_thread(get_app(), &thread_proc_load_ai_font, this, ::multithreading::priority_normal, 0, 0, NULL);

   //}


   //UINT view::thread_proc_load_ai_font(void * pparam)
   //{

   //   view * pview = (view *) pparam;

   //   pview->m_iErrorAiFont = -1;

   //   pview->m_iErrorAiFont = FT_New_Face((FT_Library) Sys(pview->get_app()).ftlibrary(), App(pview->get_app()).dir().matter_file("font/truetype/arialuni.ttf"), 0, (FT_Face *) &pview->m_faceAi);

   //   return pview->m_iErrorAiFont;

   //}

   UINT view::thread_proc_render(void * pparam)
   {

      view * pview = (view *)pparam;

      while(::get_thread_run())
      {

         try
         {

            pview->render();

            Sleep(25);

         }
         catch(...)
         {
            break;
         }

      }

      return 0;

   }

   void view::on_layout()
   {

      rect rectClient;
      GetClientRect(rectClient);

      if(rectClient.area() <= 0)
         return;

      string str = THIS_FRIENDLY_NAME();

      string strPath = Application.directrix()->m_varTopicQuery["bk"][str];

      ::visual::dib_sp dibBk(allocer());

      if(dibBk.load_from_file(strPath) && dibBk->area() > 0)
      {

         m_dibBk.alloc(allocer());

         m_dibBk->create(rectClient.size());

         m_dibBk->Fill(0, 0, 0, 0);

         double dRate = MAX((double)rectClient.width()/(double)dibBk->m_size.cx, (double)rectClient.height()/(double)dibBk->m_size.cy);

         double dx = MIN(dibBk->m_size.cx * dRate, rectClient.width());

         double dy = MIN(dibBk->m_size.cy * dRate, rectClient.height());

         double sdx = dx  / dRate;

         double sdy = dy  / dRate;

         m_dibBk->get_graphics()->SetStretchBltMode(HALFTONE);

         m_dibBk->get_graphics()->StretchBlt(0,0,dx,dy,dibBk->get_graphics(),0,0,sdx,sdy,SRCCOPY);

      }


      int iMinDim = MIN(rectClient.width(),rectClient.height());

      iMinDim = 84 * iMinDim / 100;

      m_rectSpace.CenterOf(rectClient,size(iMinDim,iMinDim));

      m_rectCheckSpace = m_rectSpace;

      {

         synch_lock slWork(&m_mutexWork);

         m_dib.alloc(allocer());

         if(!m_dib.initialize(rectClient.width(),rectClient.height(),5))
            return;

         //m_dib->m_iHeight = rectClient.height(); // 1 x 1 and not 0 x 0 : good!!

         m_dib->Fill(0,0,0,0);

         float fHeight = 100.0;

#ifdef LINUX
         m_font->create_pixel_font(FONT_SANS,fHeight,FW_BOLD);
#else
         m_font->create_pixel_font(FONT_SANS,fHeight,FW_BOLD);
#endif

         m_dib->get_graphics()->set_font(m_font);

         class size size = m_dib->get_graphics()->GetTextExtent(m_strHelloMultiverse);

         double ratey = fHeight * 0.84 / size.cy;

#ifdef LINUX
         m_font->create_pixel_font(FONT_SANS,MIN(rectClient.height() * ratey,rectClient.width() * size.cy * ratey / size.cx),FW_BOLD);
#else
         m_font->create_pixel_font(FONT_SANS,MIN(rectClient.height() * ratey,rectClient.width() * size.cy * ratey / size.cx),FW_BOLD);
#endif
         m_dibWork->create(rectClient.width(),rectClient.height());

         m_dibWork->Fill(0,0,0,0);

      }


      {

         synch_lock slDraw(&m_mutexDraw);

         m_dib1->create(rectClient.width(),rectClient.height());

         m_dib1->Fill(0,0,0,0);

         m_dib2->create(rectClient.width(),rectClient.height());

         m_dib2->Fill(0,0,0,0);

      }

      render();

   }


   void view::get_board_rect(LPRECT lprect)
   {

      *lprect = m_rectSpace;

   }


   void view::draw_board(::draw2d::graphics * pgraphics,const RECT & rect)
   {

      ::draw2d::path_sp path(allocer());

      path->begin_figure(false,::draw2d::fill_mode_winding);
      path->add_move(rect.left + width(rect) / 3,rect.top);
      path->add_line(rect.left + width(rect) / 3,rect.bottom);
      path->end_figure(false);

      path->begin_figure(false,::draw2d::fill_mode_winding);
      path->add_move(rect.left + width(rect) * 2 / 3,rect.top);
      path->add_line(rect.left + width(rect) * 2 / 3,rect.bottom);
      path->end_figure(false);

      path->begin_figure(false,::draw2d::fill_mode_winding);
      path->add_move(rect.left,rect.top + height(rect) / 3);
      path->add_line(rect.right,rect.top + height(rect) / 3);
      path->end_figure(false);

      path->begin_figure(false,::draw2d::fill_mode_winding);
      path->add_move(rect.left,rect.top + height(rect) * 2 / 3);
      path->add_line(rect.right,rect.top + height(rect) * 2 / 3);
      path->end_figure(false);

      pgraphics->draw_path(path);

   }

   void view::draw_x(::draw2d::graphics * pgraphics,const RECT & rect)
   {

      /*::draw2d::dib_sp dib(allocer());

      dib->create(width(rect),height(rect));

      dib->Fill(0,0,0,0);

      dib->get_graphics()->SelectObject(pgraphics->get_current_pen());

      dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      dib->get_graphics()->SetViewportOrg(-rect.left,-rect.top);

      dib->get_graphics()->MoveTo(rect.left,rect.top);
      dib->get_graphics()->LineTo(rect.right,rect.bottom);
      dib->get_graphics()->MoveTo(rect.right,rect.top);
      dib->get_graphics()->LineTo(rect.left,rect.bottom);

      dib->get_graphics()->SetViewportOrg(0,0);*/


      ::draw2d::path_sp path(allocer());

      path->begin_figure(false, ::draw2d::fill_mode_winding);
      path->add_line(rect.left,rect.top,rect.right,rect.bottom);
      path->end_figure(false);
      path->begin_figure(false,::draw2d::fill_mode_winding);
      path->add_line(rect.right,rect.top,rect.left,rect.bottom);
      path->end_figure(false);

      pgraphics->draw_path(path);

      //pgraphics->BitBlt(rect,dib->get_graphics());

   }

   void view::draw_o(::draw2d::graphics * pgraphics,const RECT & rect)
   {

      pgraphics->DrawEllipse(rect);

   }

   void view::get_check_rect(LPRECT lprect,int i,int j)
   {

      int iBorder = m_rectSpace.width() / 6;

      ::rect rect;
      rect.left = m_rectCheckSpace.left + i * m_rectCheckSpace.width() / 3;
      rect.right = m_rectCheckSpace.left + (i + 1) * m_rectCheckSpace.width() / 3;
      rect.top = m_rectCheckSpace.top + j * m_rectCheckSpace.width() / 3;
      rect.bottom = m_rectCheckSpace.top + (j + 1) * m_rectCheckSpace.width() / 3;

      rect.deflate(iBorder / 2, iBorder /2 );

      *lprect = rect;

   }

   bool view::hit_test_check(int & i,int & j, point pt)
   {

      rect rectCheck;

      board & board = m_parbitrator->m_board;

      for(i = 0; i < board.get_size(); i++)
      {

         for( j = 0; j < board[i].get_size(); j++)
         {

            get_check_rect(rectCheck,i,j);

            if(rectCheck.contains(pt))
               return true;

         }

      }

      i = -1;
      j = -1;

      return false;

   }


   void view::_001OnNewGame(signal_details * pobj)
   {

      pobj->m_bRet = true;

      new_game();

   }


   void view::new_game()
   {

      m_parbitrator->post_stop();

      m_parbitrator->launch(this,this,true);


   }


} // namespace tictactoe



