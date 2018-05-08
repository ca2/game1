#include "framework.h"
#include <math.h>


namespace particle
{


   view::view(::aura::application * papp) :
      ::object(papp),
      m_font(allocer()),
      m_dib(allocer())
   {

      //m_ppreview = NULL;

      m_pparticle = NULL;

      m_bDibLayout = true;

      m_xDib   = -1;

      connect_command("new_game", &view::_001OnNewGame);


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

      if (m_pparticle == NULL)
      {

         return;

      }

      m_pparticle->draw(pgraphics);

      for (int i = 0; i < m_pparticle->m_effecta.get_count(); i++)
      {


         m_pparticle->m_effecta[i]->cpuUpdate(0.05);

         m_pparticle->m_effecta[i]->render(pgraphics, width(), height());

      }

      for (int i = 0; i < m_pparticle->m_effecta.get_count();)
      {

         if (i < m_pparticle->m_effecta.get_upper_bound())
         {

            if (m_pparticle->m_effecta[i]->numActiveParticles() <= 0)
            {

               m_pparticle->m_effecta.remove_at(i);

            }
            else
            {
               i++;
            }


         }
         else
         {
            i++;

         }



      }

   }



   ::user::document * view::get_document()
   {

      return ::user::impact::get_document();

   }



   void view::start()
   {

      m_pparticle = new particle(get_app());

      m_pparticle->reset();

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

      m_pparticle->windowWidth = rectClient.width();

      m_pparticle->windowHeight = rectClient.height();

      m_pparticle->reset();

   }

   void view::_001OnKeyDown(::message::message * pobj)
   {

      SCAST_PTR(::message::key,pkey,pobj);

      //if(pkey->m_ekey == ::user::key_down)
      //{
      //   m_pparticle->drop();
      //}
      //else
      if(pkey->m_ekey == ::user::key_left)
      {

         m_pparticle->m_paddle.key_left_up(m_pparticle);

      }
      else if(pkey->m_ekey == ::user::key_right)
      {

         m_pparticle->m_paddle.key_right_up(m_pparticle);

      }

      pkey->m_bRet = true;

   }

   void view::_001OnKeyUp(::message::message * pobj)
   {

      SCAST_PTR(::message::key,pkey,pobj);
      if(pkey->m_ekey == ::user::key_left)
      {
         if(m_pparticle->m_paddle.m_v.x <0)
         {
            m_pparticle->m_paddle.key_down(m_pparticle);
         }
      }
      else if(pkey->m_ekey == ::user::key_right)
      {
         if(m_pparticle->m_paddle.m_v.x > 0)
         {
            m_pparticle->m_paddle.key_down(m_pparticle);
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

      m_pparticle->reset();

   }



} // namespace particle



