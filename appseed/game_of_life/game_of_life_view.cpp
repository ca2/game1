#include "framework.h"
#include <math.h>


namespace game_of_life
{


   view::view(::aura::application * papp) :
      ::object(papp),
      ::estamira::view(papp),
      m_dib1(allocer()),
      m_dib2(allocer()),
      m_dib(allocer()),
      m_dibColor(allocer()),
      m_dibWork(allocer()),
      m_font(allocer()),
      m_mutexDraw(papp),
      m_mutexWork(papp),
      m_mutexSwap(papp)
   {

      m_iCount = 0;

      m_iPhase = 0;

      m_bGame = false;

      m_strHelloMultiverse = "Hello Multiverse!!";

      string str = THIS_FRIENDLY_NAME();

      if(Application.handler()->m_varTopicQuery.has_property("bk_alpha") && Application.handler()->m_varTopicQuery["bk_alpha"].has_property(str))
      {

         m_bBkAlpha= MAX(0,MIN(255,((int)(Application.handler()->m_varTopicQuery["bk_alpha"][str].get_double() * 255.0))));

      }
      else
      {

         m_bBkAlpha = 255;

      }

   }


   view::~view()
   {

   }


   void view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void view::install_message_routing(::message::sender * psender)
   {

      ::estamira::view::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE,psender,this,&view::_001OnCreate);
      IGUI_MSG_LINK(WM_LBUTTONDOWN,psender,this,&view::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP,psender,this,&view::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MOUSEMOVE,psender,this,&view::_001OnMouseMove);
      IGUI_MSG_LINK(WM_KEYDOWN, psender, this, &view::_001OnKeyDown);
      IGUI_MSG_LINK(WM_KEYUP, psender, this, &view::_001OnKeyUp);

   }


   void view::_001OnCreate(::message::message * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;

      GetMain()->Enable(true);

   }


   void view::_001OnKeyDown(::message::message * pobj)
   {

      SCAST_PTR(::message::key, pkey, pobj);

      pobj->m_bRet = true;

   }


   void view::_001OnKeyUp(::message::message * pobj)
   {

      SCAST_PTR(::message::key, pkey, pobj);

   }


   void view::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pobj->m_bRet = true;

      point pt(pmouse->m_pt);

      ScreenToClient(&pt);

   }


   void view::_001OnLButtonUp(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      point pt(pmouse->m_pt);

      ScreenToClient(&pt);

   }


   void view::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      point pt(pmouse->m_pt);

      ScreenToClient(&pt);

      rect rectClient;

      GetClientRect(rectClient);

   }


   void view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {

      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);

   }



   void view::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      if (Application.m_pgame != NULL)
      {

         synch_lock sl(Application.m_pgame->m_pmutex);

         Application.m_pgame->_001OnDraw(pgraphics);

      }

   }




   ::user::document * view::get_document()
   {

      return ::user::impact::get_document();

   }




   void view::on_layout()
   {

      rect rectClient;
      GetClientRect(rectClient);

      if(rectClient.area() <= 0)
         return;

      Game.on_layout();

   }


   bool view::keyboard_focus_is_focusable()
   {

      return true;

   }


} // namespace game_of_life



