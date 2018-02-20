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

      connect_command("new_game", &view::_001OnNewGame);


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

      ::user::impact::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE,psender,this,&view::_001OnCreate);
      IGUI_MSG_LINK(WM_LBUTTONDOWN,psender,this,&view::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP,psender,this,&view::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_KEYDOWN,psender,this,&view::_001OnKeyDown);
      IGUI_MSG_LINK(WM_KEYUP,psender,this,&view::_001OnKeyUp);

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

      pgraphics->FillSolidRect(rectClient, ARGB(0,0,0,0));

      if (m_parkanoid == NULL)
      {

         return;

      }

      m_parkanoid->draw(pgraphics);

   }



   ::user::document * view::get_document()
   {

      return ::user::impact::get_document();

   }



   void view::start()
   {

      m_parkanoid = new arkanoid(get_app());

      m_parkanoid->reset();

   }


   void view::on_layout()
   {

      m_bDibLayout = true;

      ::rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.is_empty())
      {

         return;

      }

      m_parkanoid->windowWidth = rectClient.width();

      m_parkanoid->windowHeight = rectClient.height();

      m_parkanoid->reset();

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
         
         m_parkanoid->m_paddle.key_left_up(m_parkanoid);

      }
      else if(pkey->m_ekey == ::user::key_right)
      {

         m_parkanoid->m_paddle.key_right_up(m_parkanoid);

      }

      pkey->m_bRet = true;

   }

   void view::_001OnKeyUp(::message::message * pobj)
   {

      SCAST_PTR(::message::key,pkey,pobj);
      if(pkey->m_ekey == ::user::key_left)
      {
         if(m_parkanoid->m_paddle.m_v.x <0)
         {
            m_parkanoid->m_paddle.key_down(m_parkanoid);
         }
      }
      else if(pkey->m_ekey == ::user::key_right)
      {
         if(m_parkanoid->m_paddle.m_v.x > 0)
         {
            m_parkanoid->m_paddle.key_down(m_parkanoid);
         }
      }
   }

   bool view::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && IsWindowVisible();

   }

   void view::_001OnNewGame(::message::message * pobj)
   {

      pobj->m_bRet = true;

      m_parkanoid->reset();

   }



} // namespace arkanoid



