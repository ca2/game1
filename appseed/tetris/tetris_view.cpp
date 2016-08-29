#include "framework.h"
#include <math.h>


namespace tetris
{


   view::view(::aura::application * papp) :
      ::object(papp),
      m_font(allocer()),
      m_dib(allocer())
   {

      m_ppreview = NULL;

      m_bDibLayout = true;

      m_xDib   = -1;


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
      IGUI_WIN_MSG_LINK(WM_KEYDOWN,pdispatch,this,&view::_001OnKeyDown);

   }


   void view::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;


      start();

   }


   void view::_001OnLButtonDown(signal_details * pobj)
   {

      //pobj->m_bRet = true;

   }


   void view::_001OnLButtonUp(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      point pt(pmouse->m_pt);

      ScreenToClient(&pt);

      int i = -1;
      int j = -1;


   }


   void view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }



   void view::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      

      ::rect rectClient;

      GetClientRect(rectClient);

      //pgraphics->FillSolidRect(rectClient, ARGB(255,84,84,84));

      


      if( m_ppreview == NULL)
         return;

      int cx = Game.m_sizePage.cx;

      int cy = Game.m_sizePage.cy + m_ppreview->m_dib->m_size.cy +10;

      int x = (rectClient.width() - cx) / 2;

      int y = (rectClient.height() - cy) / 2;

      if(m_bDibLayout || m_xDib != x)
      {
         m_xDib = x;
         m_bDibLayout = false;

         int cxGame = Game.m_sizePage.cx;
         int cyGame = Game.m_sizePage.cy;

         m_dib.alloc(allocer());
         m_dib.initialize(rectClient.size(),5);
         m_dib->Fill(0,0,0,0);
         m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
         m_dib->get_graphics()->FillSolidRect(x,y,m_ppreview->m_dib->m_size.cx,m_ppreview->m_dib->m_size.cy,ARGB(255,23,23,23));
         m_dib->get_graphics()->FillSolidRect(x,y + m_ppreview->m_dib->m_size.cy + 10,cxGame, cyGame,ARGB(255,23,23,23));
         int r = 3;
         int h = 18;
         ::rect rect1;
         rect1.left = x + m_ppreview->m_dib->m_size.cx + 10 - r * 2;
         rect1.top = y - r;
         rect1.right = rect1.left + h + r * 2;
         rect1.bottom = rect1.top + h + r * 2;
         ::draw2d::brush_sp b(allocer());
         b->create_solid(ARGB(128,49,49,49));
         m_dib->get_graphics()->SelectObject(b);
         ::rect rect;

         ::rect rectx;

         rectx.left = x + m_ppreview->m_dib->m_size.cx + 10 - r * 2;
         rectx.top = y - r;
         rectx.right = x + cx ;
         rectx.bottom = rectx.top + h + r * 2;

         ::draw2d::path_sp path1(allocer());
         path1->begin_figure(true,::draw2d::fill_mode_winding);
         path1->add_arc_label(rectx);
         path1->end_figure(true);
         m_dib->get_graphics()->fill_path(path1);

         rectx.top = y + 30 - r;
         rectx.bottom = rectx.top + h + r * 2;

         ::draw2d::path_sp path2(allocer());
         path2->begin_figure(true,::draw2d::fill_mode_winding);
         path2->add_arc_label(rectx);
         path2->end_figure(true);
         m_dib->get_graphics()->fill_path(path2);
         //{
         //   path->add_arc(rect1,0,360);
         //   rect.left = x + m_ppreview->m_dib->m_size.cx + 10 + h / 2 - r;
         //   rect.top = y - r;
         //   rect.right = rect.left + cx - m_ppreview->m_dib->m_size.cx - h - 10 - r;
         //   rect.bottom = rect.top + h + r * 2;
         //   path->add_rect(rect);
         //   ::rect rect3(rect1);
         //   rect3.offset(cx - m_ppreview->m_dib->m_size.cx - h - 10,0);
         //   path->add_arc(rect3,0,360);
         //}

         //path->begin_figure(true,::draw2d::fill_mode_winding);
         //{

         //   ::rect rect2;
         //   rect2.left = x + m_ppreview->m_dib->m_size.cx + 10 - r * 2;
         //   rect2.top = y + 30 - r;


         //   rect2.right = rect2.left + h + r * 2;
         //   rect2.bottom = rect2.top + h + r * 2;
         //   path->add_arc(rect2,0,360);

         //   rect.left = x + m_ppreview->m_dib->m_size.cx + 10 + h / 2 - r;
         //   rect.top = y + 30 - r;
         //   rect.right = rect.left + cx - m_ppreview->m_dib->m_size.cx - h - 10 - r;
         //   rect.bottom = rect.top + h + r * 2;
         //   path->add_rect(rect);


         //   ::rect rect4(rect2);

         //   rect4.offset(cx - m_ppreview->m_dib->m_size.cx - h - 10,0);
         //   path->add_arc(rect4,0,360);


         //}

         //path->end_figure(true);

         

         m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
         //m_dib->get_graphics()->FillSolidRect(rect1,ARGB(255,23,23,23));
         //m_dib->get_graphics()->FillSolidRect(rect2,ARGB(255,23,23,23));

         m_dib.blur();
         m_dib.blur();
         m_dib.blur();
         m_dib.blur();
         m_dib.blur();
         m_dib->get_graphics()->fill_path(path1);
         m_dib->get_graphics()->fill_path(path2);
      }

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      

      pgraphics->from(rectClient.size(),m_dib->get_graphics(),SRCCOPY);

      pgraphics->set_text_color(ARGB(255,255,255,255));
      pgraphics->TextOut(x + m_ppreview->m_dib->m_size.cx + 10,y,"Score:");
      pgraphics->TextOut(x + m_ppreview->m_dib->m_size.cx + 10,y+30,"Level:");
      pgraphics->TextOut(x + m_ppreview->m_dib->m_size.cx + 50,y,m_strScore);
      pgraphics->TextOut(x + m_ppreview->m_dib->m_size.cx + 50,y+30,m_strLevel);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

      pgraphics->from(::point(x,y),m_ppreview->m_dib->m_size,m_ppreview->m_dib->get_graphics(),::null_point(),SRCCOPY);

      Game.m_ptOffset = ::point(x, y + m_ppreview->m_dib->m_size.cy + 10);
      Game._001OnDraw(pgraphics);
      // pgraphics->from(::point(x, y + m_ppreview->m_dib->m_size.cy + 10), Game.m_dib->m_size, Game.m_dib->get_graphics(), ::null_point(), SRCCOPY);

   }



   ::user::document * view::get_document()
   {

      return ::user::impact::get_document();

   }



   void view::start()
   {

      m_ppreview = new _TetrisPreview(this);
      
      int iCellSize = 24;
      
      if(Application.directrix()->m_varTopicQuery.has_property("cell_size"))
      {
         
         iCellSize = Application.directrix()->m_varTopicQuery["cell_size"];
         
         iCellSize = MIN(1024, MAX(2, iCellSize));
         
      }

      Application.m_pgame = new game(get_app(), 10,20,iCellSize,this);

      Game.start(this);

      sp(frame) pframe = GetTopLevelFrame();

      pframe->m_sizeView.cx = Game.widthInPixels+ 80;
      pframe->m_sizeView.cy = Game.heightInPixels + 80 + 10 + m_ppreview->m_dib->m_size.cy;

      sp(frame) pframe1 = GetParentFrame();

      pframe1->m_sizeView = pframe->m_sizeView;

   }


   void view::layout()
   {

      m_bDibLayout = true;

   }

   void view::_001OnKeyDown(signal_details * pobj)
   {

      SCAST_PTR(::message::key,pkey,pobj);
      
      auto ekey =  pkey->m_ekey;
      
      ::fork(get_app(), [=]()
      {

      if(ekey == ::user::key_down)
      {
         Game.drop();
      }
      else if(ekey == ::user::key_left)
      {
         Game.moveLeft(0);
      }
      else if(ekey == ::user::key_right)
      {
         Game.moveRight(0);
      }
      else if(ekey == ::user::key_z)
      {
         Game.rotate(false);
      }
      else if(ekey == ::user::key_x)
      {
         Game.rotate(true);
      }
         
      });

      pkey->m_bRet = true;

   }

   bool view::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && IsWindowVisible();

   }



} // namespace tetris



