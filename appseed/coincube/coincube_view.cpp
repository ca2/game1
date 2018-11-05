#include "framework.h"
#include <math.h>




namespace coincube
{


   view::view(::aura::application * papp) :
      ::object(papp),
      m_dib1(allocer()),
      m_dib2(allocer()),
      m_dib(allocer()),
      m_dibColor(allocer()),
      m_dibWork(allocer()),
      m_mutexDraw(papp),
      m_mutexWork(papp),
      m_mutexSwap(papp),
      m_pot(this),
      m_dibCoin(allocer()),
      m_dibMony(allocer()),
      m_dibMon2(allocer()),
      m_effecta(papp)
   {

      m_dGrow = 1.15;

      m_iCount = 0;
      m_iPhase = 0;

      int iCount = 0;
      if(!m_dibCoin.load_from_file("matter://coin.png"))
      {

         iCount++;

      }

      if(!m_dibMony.load_from_file("matter://mony.png"))
      {

         iCount++;

      }

      if(!m_dibMon2.load_from_file("matter://mon2.png"))
      {

         iCount++;

      }

      if(iCount > 0)
      {

         Application.simple_message_box(NULL, "Could not load "+::str::from(iCount)+" image(s).");

      }

      m_bGame = false;

      m_pot.m_pview =this;

      connect_command("new_game",&view::_001OnNewGame);

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

      //::backview::Interface::install_message_routing(psender);

      ::user::impact::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE,psender,this,&view::_001OnCreate);
      IGUI_MSG_LINK(WM_LBUTTONDOWN,psender,this,&view::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP,psender,this,&view::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MOUSEMOVE,psender,this,&view::_001OnMouseMove);

   }


   void view::_001OnCreate(::message::message * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      pcreate->previous();

      m_psound = new ::multimedia::sound_track(get_app());

      m_psound->audio_plugin_initialize();

      new_game();

      data_get("credit",m_pot.m_iCredit);
      data_get("count",m_iCount);
      data_get("phase",m_iPhase);


      for(index i = 0; i < m_iCount; i++)
      {

         m_pot.m_iSize = m_pot.m_iSize * m_dGrow;

      }

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      GetMain()->Enable(true);

   }


   void view::_001OnLButtonDown(::message::message * pobj)
   {

      pobj->m_bRet = true;



   }


   void view::_001OnLButtonUp(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      point pt(pmouse->m_pt);

      ScreenToClient(&pt);

      int i = -1;
      int j = -1;


   }


   void view::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      point pt(pmouse->m_pt);

      ScreenToClient(&pt);

      rect rectClient;

      GetClientRect(rectClient);

      m_ptFinal.x = MAX(rectClient.left + m_pot.m_iSize * 2,MIN(pt.x, rectClient.right - m_pot.m_iSize * 2));


   }

   void view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }



   void view::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);



      rect rectClient;
      GetClientRect(rectClient);


//      ::backview::user::interaction::_001OnDraw(pgraphics);

      int x = 0;
      int y = 0;

      int iPhaseY = 0;

      for(index i = 0; i < m_iPhase; i++)
      {

         if(x > 0)
         {

            if(x + m_dibMon2->m_size.cx > rectClient.width())
            {
               x = 0;
               y += m_dibMon2->m_size.cy;

            }

         }

         pgraphics->draw(point(x,y),m_dibMon2->m_size,m_dibMon2->get_graphics());

         x+=m_dibMon2->m_size.cx;

         iPhaseY = m_dibMon2->m_size.cy;

      }




      for(index i = 0; i < m_iCount; i++)
      {

         if(x > 0)
         {

            if(x + m_dibMony->m_size.cx > rectClient.width())
            {
               x = 0;
               y += MAX(m_dibMony->m_size.cy, iPhaseY);
               iPhaseY = 0;
            }

         }

         pgraphics->draw(point(x,y),m_dibMony->m_size,m_dibMony->get_graphics());

         x+=m_dibMony->m_size.cx;

      }


      rect r(rectClient);

      r.top = r.bottom - m_pot.m_iSize * 6;

      pgraphics->fill_solid_rect(r,ARGB(84,255,255,255));

      m_pot.m_pt.x = m_pot.m_pt.x + (m_ptFinal.x - m_pot.m_pt.x)  * 0.1;

      m_pot.on_draw(pgraphics);

      for(auto & pc : m_money)
      {
         pc->on_draw(pgraphics);
      }

      m_effecta.draw(pgraphics, rectClient.width(), rectClient.height());

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

      m_pot.m_pt.y = rectClient.bottom - m_pot.m_iSize * 3;

      m_ptFinal.y = m_pot.m_pt.y;

   }





   void view::_001OnNewGame(::message::message * pobj)
   {

      pobj->m_bRet = true;

      new_game();

   }


   void view::credit()
   {

      m_psound->queue("wait:coin");

      m_pot.m_iCredit++;

      if(m_pot.m_iCredit >= m_pot.m_iSize)
      {

         m_iCount++;

         if(m_iCount > 7)
         {
            m_iCount = 0;

            int x = m_dibMon2->m_size.cx / 2;
            int y = m_dibMon2->m_size.cy / 2;
            for (int i = 0; i < m_iPhase; i++)
            {

               x += m_dibMon2->m_size.cx;

            }
            m_iPhase++;
            sp(particle::effect::effect) peffect = canew(particle::effect::gold_color_fountain(get_app(), x, y));
            peffect->initialize(200, 160);
            peffect->initializeRenderer();
            m_effecta.add(peffect);
            for (int i = 0; i < 8; i++)
            {
               int y = m_dibMony->m_size.cy / 2;
               x += m_dibMony->m_size.cx;
               sp(particle::effect::effect) peffect = canew(particle::effect::gold_color_fountain(get_app(), x, y));
               peffect->initialize(200, 80);
               peffect->initializeRenderer();
               m_effecta.add(peffect);

            }

            m_psound->queue("wait:velo2");

         }
         else
         {

            m_pot.m_iCredit=0;
            m_pot.m_bGrow = true;
            m_pot.m_dwLastGrow = ::get_tick_count();

            m_psound->queue("wait:velo");
            int x = m_dibMon2->m_size.cx / 2;
            int y = m_dibMon2->m_size.cy / 2;
            for (int i = 0; i < m_iPhase; i++)
            {

               x += m_dibMon2->m_size.cx;

            }
            for (int i = 0; i < m_iCount-1; i++)
            {
               y = m_dibMony->m_size.cy / 2;
               x += m_dibMony->m_size.cx;

            }
            sp(particle::effect::effect) peffect = canew(particle::effect::gold_color_fountain(get_app(), x, y));
            peffect->initialize(200, 80);
            peffect->initializeRenderer();
            m_effecta.add(peffect);

         }


      }

      data_set("credit",m_pot.m_iCredit);
      data_set("count",m_iCount);
      data_set("phase",m_iPhase);

   }


   void view::new_game()
   {

      rect rectClient;

      GetClientRect(rectClient);

      m_pot.m_iSize = 16;

      m_pot.m_pt.x = (rectClient.right + rectClient.left) / 2;

      m_pot.m_pt.y = rectClient.bottom - m_pot.m_iSize * 3;

      m_ptFinal = m_pot.m_pt;

      while(m_money.get_size() < 23)
      {

         m_money.add(canew(coin(this)));

      }

      for(auto & pc : m_money)
      {

         pc->reinvent_merit();

      }

   }


} // namespace coincube



