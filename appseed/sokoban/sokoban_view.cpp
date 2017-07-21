#include "framework.h"
#include <math.h>


namespace sokoban
{


   view::view(::aura::application * papp) :
      ::object(papp),
      m_font(allocer()),
      m_dib(allocer()),
      m_asset(papp),
      m_font1(allocer())
   {

      m_asset.m_strMatter = "ca2";
      m_bDibLayout = true;
      m_xDib   = -1;
      m_iSideBarWidth = 284;
      m_font1->create_pixel_font(FONT_SANS_FX,36.0, 900);

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
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE,pdispatch,this,&view::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN,pdispatch,this,&view::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP,pdispatch,this,&view::_001OnKeyUp);
      //IGUI_WIN_MSG_LINK(WM_TIMER,pdispatch,this,&view::_001OnTimer);

   }


   void view::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;


      //m_asset.update();

   }


   void view::_001OnTimer(::timer * ptimer)
   {

      ::user::impact::_001OnTimer(ptimer);

      if(ptimer->m_nIDEvent == 1923)
      {
         if(m_dGotoLevel > 0.2)
            m_dGotoLevel-= m_dGotoLevel /4.0;
         else
         {
            KillTimer(1923);
            m_bDisableInput = false;
            m_dGotoLevel = 0.0;
         }
         set_viewport_offset_y(m_iScrollStart - (int) m_dGotoLevel);
      }

   }



   void view::_001OnLButtonDown(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      point pt(pmouse->m_pt);

      ScreenToClient(&pt);

      int iLevel = hit_test_level(pt);

      if(iLevel >= 0)
      {

         go_to_level(iLevel);

      }

   }

   void view::_001OnLButtonUp(signal_details * pobj)
   {

      //pobj->m_bRet = true;

   }

   void view::_001OnMouseMove(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      point pt(pmouse->m_pt);

      ScreenToClient(&pt);

      int iLevel = hit_test_level(pt);

      m_iHoverLevel = iLevel;

   }


   void view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);

      if(lHint == 123)
      {
         on_layout();

      }
   }



   void view::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      

      point ptViewport = pgraphics->GetViewportOrg();

      point ptOffset = get_viewport_offset();

      //pgraphics->OffsetViewportOrg(-ptOffset.x + m_iSideBarWidth,-ptOffset.y);
      pgraphics->OffsetViewportOrg(m_iSideBarWidth, 0);






      ::rect rectClient;

      GetClientRect(rectClient);

      pgraphics->FillSolidRect(rectClient, ARGB(0,255,255,255));

      int yOffset = 0;
      int yNextOffset;

      bool bEntered = false;

      for(index iLevel = 0; iLevel < get_document()->m_levela.get_count(); iLevel++)
      {

         yNextOffset = yOffset + get_document()->m_levela[iLevel]->m_stra.get_count() + 1;

         if(yNextOffset * m_asset.m_iSize - ptOffset.y >= 0)
         {


            if(iLevel == m_iHoverLevel)
            {
               if(iLevel != m_asset.m_iLevel)
               {
                  pgraphics->FillSolidRect(0 - m_iSideBarWidth,yOffset * m_asset.m_iSize,rectClient.width() + m_iSideBarWidth,get_document()->m_levela[iLevel]->m_stra.get_count()* m_asset.m_iSize,ARGB(84,177,255,184));
               }
            }



            string str;

            str = "Level " + ::str::from(iLevel + 1);

            pgraphics->selectFont(m_font1);

            pgraphics->set_text_color(ARGB(184, 49, 49, 49));

            pgraphics->text_out(- m_iSideBarWidth + 10,yOffset * m_asset.m_iSize,str);

            get_document()->m_levela[iLevel]->draw(pgraphics,&m_asset,yOffset);

            bEntered = true;

         }

         yOffset = yNextOffset;

         if (bEntered)
         {

            if (yOffset  * m_asset.m_iSize - ptOffset.y > rectClient.height())
               break;

         }

      }
      pgraphics->SetViewportOrg(ptViewport);

   }



   document * view::get_document()
   {

      return dynamic_cast < document * > (::user::impact::get_document());

   }



   void view::start()
   {

//      m_ppreview = new _SokobanPreview(this);


   }


   void view::on_layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      if(rectClient.area() <= 0)
         return;

      int yOffset = 0;

      int xMax = 0;

      int yMax = 0;

      for(index iLevel = 0; iLevel < get_document()->m_levela.get_count(); iLevel++)
      {

         yOffset += get_document()->m_levela[iLevel]->m_stra.get_count() + 1;

         yMax = MAX(yMax,get_document()->m_levela[iLevel]->m_stra.get_count());

         xMax = MAX(xMax, get_document()->m_levela[iLevel]->m_iWidth);

      }

      yMax += 2;

      xMax += m_iSideBarWidth;

      m_asset.m_iSize = rectClient.height() / yMax;

      m_asset.update();

      m_sizeTotal.cy = yOffset * m_asset.m_iSize;
      m_sizeTotal.cx = xMax * m_asset.m_iSize;

      //m_scrollinfo.m_sizePage = rectClient.size();

      on_change_view_size();

   }

   void view::_001OnKeyDown(signal_details * pobj)
   {

      SCAST_PTR(::message::key,pkey,pobj);

      if(m_bDisableInput)
      {
         pkey->m_bRet = true;
         return;
      }

      if(pkey->m_ekey == ::user::key_z)
      {
         if(Session.is_key_pressed(::user::key_shift))
         {
            get_document()->m_levela[m_asset.m_iLevel]->redo();
         }
         else
         {
            get_document()->m_levela[m_asset.m_iLevel]->undo();
         }
      }
      else if(pkey->m_ekey == ::user::key_y)
      {
         get_document()->m_levela[m_asset.m_iLevel]->redo();
      }
      else if(pkey->m_ekey == ::user::key_left)
      {
         get_document()->m_levela[m_asset.m_iLevel]->move_left(false);
      }
      else if(pkey->m_ekey == ::user::key_right)
      {
         get_document()->m_levela[m_asset.m_iLevel]->move_right(false);
      }
      else if(pkey->m_ekey == ::user::key_down)
      {
         get_document()->m_levela[m_asset.m_iLevel]->move_down(false);
      }
      else if(pkey->m_ekey == ::user::key_up)
      {
         get_document()->m_levela[m_asset.m_iLevel]->move_up(false);
      }

      if(get_document()->m_levela[m_asset.m_iLevel]->is_solved())
      {

         go_to_next_level();

      }

      pkey->m_bRet = true;

   }

   void view::_001OnKeyUp(signal_details * pobj)
   {

      SCAST_PTR(::message::key,pkey,pobj);
   }

   bool view::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && IsWindowVisible();

   }

   void view::go_to_next_level()
   {

      go_to_level(m_asset.m_iLevel + 1);

   }

   void view::go_to_level(int iLevel)
   {

      if(iLevel < 0)
         return;

      if(iLevel >= get_document()->m_levela.get_count())
         return;

      int yOffset = 0;

      for(index i = 0; i < iLevel; i++)
      {

         yOffset += (get_document()->m_levela[i]->m_stra.get_count() + 1);

      }

      m_iScrollStart = yOffset * m_asset.m_iSize;

      point ptOffset = get_viewport_offset();

      m_dGotoLevel = m_iScrollStart - ptOffset.y;

      SetTimer(1923,23, NULL);

      m_asset.m_iLevel = iLevel;

      on_change_view_size();

   }


   int view::hit_test_level(point pt)
   {


      ::rect rectClient;

      GetClientRect(rectClient);

      int yHit = pt.y;

      point ptOffset = get_viewport_offset();

      int yOffset = -ptOffset.y;

      for(index iLevel = 0; iLevel < get_document()->m_levela.get_count(); iLevel++)
      {



         if(yHit >= yOffset && yHit < yOffset + get_document()->m_levela[iLevel]->m_stra.get_count() * m_asset.m_iSize)
            return iLevel;

         yOffset += (get_document()->m_levela[iLevel]->m_stra.get_count() + 1) * m_asset.m_iSize;

      }


      return -1;


   }

} // namespace sokoban



