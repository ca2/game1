#include "framework.h"
#include <math.h>


namespace arkanoid
{


   view::view(::aura::application * papp) :
      ::object(papp),
      m_font(allocer()),
      m_dib(allocer())
   {

      //m_ppreview = NULL;

      m_parkanoid = NULL;

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

   void view::install_message_routing(::message::sender * psender)
   {

      ::user::impact::install_message_routing(pdispatch);

      IGUI_WIN_MSG_LINK(WM_CREATE,pdispatch,this,&view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,pdispatch,this,&view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,pdispatch,this,&view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN,pdispatch,this,&view::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP,pdispatch,this,&view::_001OnKeyUp);

   }


   void view::_001OnCreate(::message::message * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;


      start();

   }


   void view::_001OnLButtonDown(::message::message * pobj)
   {

      //pobj->m_bRet = true;

   }


   void view::_001OnLButtonUp(::message::message * pobj)
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

      pgraphics->FillSolidRect(rectClient, ARGB(0,255,255,255));

      //pgraphics->set_text_color(ARGB(255,255,255,255));


      if(m_parkanoid == NULL)
         return;


      m_parkanoid->draw(pgraphics);

      /*int cx = m_parkanoid->m_dib->m_size.cx;

      int cy = m_parkanoid->m_dib->m_size.cy + m_ppreview->m_dib->m_size.cy +10;

      int x = (rectClient.width() - cx) / 2;

      int y = (rectClient.height() - cy) / 2;

      if(m_bDibLayout || m_xDib != x)
      {
         m_xDib = x;
         m_bDibLayout = false;

         m_dib.alloc(allocer());
         m_dib.initialize(rectClient.size(),5);
         m_dib->Fill(0,0,0,0);
         m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
         m_dib->get_graphics()->FillSolidRect(x,y,m_ppreview->m_dib->m_size.cx,m_ppreview->m_dib->m_size.cy,ARGB(255,23,23,23));
         m_dib->get_graphics()->FillSolidRect(x,y + m_ppreview->m_dib->m_size.cy + 10,m_parkanoid->m_dib->m_size.cx,m_parkanoid->m_dib->m_size.cy,ARGB(255,23,23,23));
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

      pgraphics->text_out(x + m_ppreview->m_dib->m_size.cx + 10,y,"Score:");
      pgraphics->text_out(x + m_ppreview->m_dib->m_size.cx + 10,y+30,"Level:");
      pgraphics->text_out(x + m_ppreview->m_dib->m_size.cx + 50,y,m_strScore);
      pgraphics->text_out(x + m_ppreview->m_dib->m_size.cx + 50,y+30,m_strLevel);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

      pgraphics->from(::point(x,y),m_ppreview->m_dib->m_size,m_ppreview->m_dib->get_graphics(),::null_point(),SRCCOPY);

      pgraphics->from(::point(x,y + m_ppreview->m_dib->m_size.cy + 10),m_parkanoid->m_dib->m_size,m_parkanoid->m_dib->get_graphics(),::null_point(),SRCCOPY);*/

   }



   ::user::document * view::get_document()
   {

      return ::user::impact::get_document();

   }



   void view::start()
   {

//      m_ppreview = new _TetrisPreview(this);

      m_parkanoid = new _Arkanoid(get_app());

      m_parkanoid->reset();

      sp(frame) pframe = GetTopLevelFrame();

      //pframe->m_sizeView.cx = m_parkanoid->widthInPixels+ 80;
      //pframe->m_sizeView.cy = m_parkanoid->heightInPixels + 80 + 10 + m_ppreview->m_dib->m_size.cy;

      sp(frame) pframe1 = GetParentFrame();

      //pframe1->m_sizeView = pframe->m_sizeView;

   }


   void view::on_layout()
   {

      m_bDibLayout = true;

   }

   void view::_001OnKeyDown(::message::message * pobj)
   {

      SCAST_PTR(::message::key,pkey,pobj);

      //if(pkey->m_ekey == ::user::key_down)
      //{
      //   m_parkanoid->drop();
      //}
      //else 
      if(pkey->m_ekey == ::user::key_left)
      {
         m_parkanoid->paddle.key_left_up(m_parkanoid);
      }
      else if(pkey->m_ekey == ::user::key_right)
      {
         m_parkanoid->paddle.key_right_up(m_parkanoid);
      }

      pkey->m_bRet = true;

   }

   void view::_001OnKeyUp(::message::message * pobj)
   {

      SCAST_PTR(::message::key,pkey,pobj);
      if(pkey->m_ekey == ::user::key_left)
      {
         if(m_parkanoid->paddle.m_v.x <0)
         {
            m_parkanoid->paddle.key_down(m_parkanoid);
         }
      }
      else if(pkey->m_ekey == ::user::key_right)
      {
         if(m_parkanoid->paddle.m_v.x > 0)
         {
            m_parkanoid->paddle.key_down(m_parkanoid);
         }
      }
   }

   bool view::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && IsWindowVisible();

   }



} // namespace arkanoid



