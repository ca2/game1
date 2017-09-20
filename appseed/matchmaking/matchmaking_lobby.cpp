#include "framework.h"
#include <math.h>


//extern CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;


namespace matchmaking
{



   lobby::lobby(::aura::application * papp) :
      object(papp),
      m_font(allocer()),
      m_font2(allocer())
   {
      m_font->create_point_font("Arial Black", 48);
      m_font2->create_point_font("Arial", 20, 800);
      m_iHover = -1;
   }

   lobby::~lobby()
   {
   }

   void lobby::assert_valid() const
   {
      user::box::assert_valid();
   }

   void lobby::dump(dump_context & dumpcontext) const
   {
      user::box::dump(dumpcontext);
   }

   void lobby::install_message_routing(::message::sender * psender)
   {

      ::user::impact::install_message_routing(psender);

      IGUI_MSG_LINK(message_view_update, psender, this, &lobby::_001OnLayout);
      IGUI_MSG_LINK(WM_CREATE, psender, this, &lobby::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, psender, this, &lobby::_001OnDestroy);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &lobby::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, psender, this, &lobby::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MOUSEMOVE, psender, this, &lobby::_001OnMouseMove);

   }

   int lobby::hit_test(point pt)
   {
      if (m_rect1.contains(pt))
      {
         return 0;
      }
      if (m_rect2.contains(pt))
      {
         return 1;
      }
      if (m_rect3.contains(pt))
      {
         return 2;
      }
      if (m_rect4.contains(pt))
      {
         return 3;
      }
      if (m_rect5.contains(pt))
      {
         return 4;
      }
      return -1;
   }


   void lobby::_001OnCreate(::message::message * pobj)
   {

      SCAST_PTR(::message::create, pcreate, pobj);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;

      string strText;


   }

   void lobby::_001OnDestroy(::message::message * pobj)
   {


   }

   void lobby::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      int iHover = hit_test(pt);

      if (m_iHover != iHover)
      {

         if (iHover < 0)
         {

            ReleaseCapture();

         }
         else if (m_iHover < 0)
         {

            SetCapture();

         }

         m_iHover = iHover;


      }

   }


   void lobby::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pobj->m_bRet = true;

   }

   void lobby::_001OnLButtonUp(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pobj->m_bRet = true;


   }

   void lobby::_001OnLayout(::message::message * pobj)
   {

      synch_lock sl(m_pmutex);


   }


   void lobby::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {

      if (lHint == 0)
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

   bool lobby::in_anime()
   {
      return false;
   }




   void lobby::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      

      ::rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.area() <= 0)
         return;

      pgraphics->selectFont(m_font);

      uint64_t startTime = get_nanos();

      pgraphics->FillSolidRect(rectClient, ARGB(255, 23, 11, 33));

      draw_member(pgraphics, 0, m_rect1, "+", "Player 1", ARGB(255, 128, 184, 180), ARGB(255, 48, 204, 198));

      draw_member(pgraphics, 1, m_rect2, "+", "Player 2", ARGB(255, 204, 148, 128), ARGB(255, 238, 148, 48));

      draw_member(pgraphics, 2, m_rect3, "+", "Player 3", ARGB(255, 128, 184, 180), ARGB(255, 48, 204, 198));

      draw_member(pgraphics, 3, m_rect4, "+", "Player 4", ARGB(255, 204, 148, 128), ARGB(255, 238, 148, 48));

      draw_member(pgraphics, 4, m_rect5, "+", "Player 5", ARGB(255, 128, 184, 180), ARGB(255, 48, 204, 198));



   }





   document * lobby::get_document()
   {

      return  dynamic_cast < document * > (::user::impact::get_document());

   }




   void lobby::on_layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.area() <= 0)
         return;

      m_rect1 = rectClient;

      m_rect1.right = rectClient.left + rectClient.width() / 5;

      m_rect2 = rectClient;

      m_rect2.left = rectClient.left + rectClient.width() / 5;
      m_rect2.right = rectClient.left + rectClient.width() * 2 / 5;
      
      m_rect3 = rectClient;

      m_rect3.left = rectClient.left + rectClient.width() * 2/ 5;
      m_rect3.right = rectClient.left + rectClient.width() * 3 / 5;
      
      m_rect4 = rectClient;

      m_rect4.left = rectClient.left + rectClient.width() * 3/ 5;
      m_rect4.right = rectClient.left + rectClient.width() * 4 / 5;
      
      m_rect5 = rectClient;

      m_rect5.left = rectClient.left + rectClient.width() * 4 / 5;

   }



   void lobby::draw_member(::draw2d::graphics * pgraphics, int iButton, rect & rectButton, string str1, string str2, COLORREF cr1, COLORREF cr2)
   {

      if (m_iHover == iButton)
      {

         rect r = rectButton;
         r.deflate(5, 5);
         //for (index i = 0; i < 25; i++)
         {

            pgraphics->Draw3dRect(r, cr1, cr1);

         }

      }
      //else
      //{
      //   pgraphics->FillSolidRect(m_rectPlay, ARGB(255, 0, 0, 0));
      //}

      pgraphics->selectFont(m_font);



      pgraphics->set_text_color(cr2);
      //      pgraphics->set_text_color(ARGB(255, 128, 184, 184));

      rect rect;

      rect.left = 0;
      rect.top = 0;
      rect.right = pgraphics->GetTextExtent(str1).cx;
      rect.bottom = pgraphics->GetTextExtent(str1).cy;

      rect.Align(align_center, rectButton);

      pgraphics->text_out(rect.left, rect.top, str1);

      pgraphics->selectFont(m_font2);


      ::rect r2;

      r2.left = 0;
      r2.top = 0;
      r2.right = pgraphics->GetTextExtent(str2).cx;
      r2.bottom = pgraphics->GetTextExtent(str2).cy;

      r2.Align(align_center, rectButton);

      r2.offset(0, -r2.top + rect.bottom);

      pgraphics->set_text_color(ARGB(255, 128, 128, 128));
      pgraphics->text_out(r2.left, r2.top, str2);

   }



} // namespace matchmaking

















