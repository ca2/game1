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
      m_font(allocer()),
      m_mutexDraw(papp),
      m_mutexWork(papp),
      m_mutexSwap(papp),
      m_pot(papp),
      m_dibCoin(allocer()),
      m_dibMony(allocer()),
      m_dibMon2(allocer())
   {

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
      m_strHelloMultiverse = "Hello Multiverse!!";

      connect_command("new_game",&view::_001OnNewGame);

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

      //::backview::Interface::install_message_handling(pdispatch);

      ::user::impact::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_CREATE,pdispatch,this,&view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,pdispatch,this,&view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,pdispatch,this,&view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE,pdispatch,this,&view::_001OnMouseMove);

   }


   void view::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      m_psound = new ::multimedia::sound_track(get_app());
      m_psound->DecoderInitialize(NULL,false);

      m_dataid += ".local://";

      initialize_data_client(Application.simpledb().get_data_server());
      if(!m_bGame)
      {
         m_bGame = true;
         new_game();

      }


      data_get("credit",m_pot.m_iCredit);
      data_get("count",m_iCount);
      data_get("phase",m_iPhase);



      for(index i = 0; i < m_iCount; i++)
      {
         m_pot.m_iSize = m_pot.m_iSize * 1.25;
      }
      pcreate->previous();

      if(pcreate->m_bRet)
         return;

      GetMain()->Enable(true);

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


   }


   void view::_001OnMouseMove(signal_details * pobj)
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

         pgraphics->BitBlt(point(x,y),m_dibMon2->m_size,m_dibMon2->get_graphics());

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

         pgraphics->BitBlt(point(x,y),m_dibMony->m_size,m_dibMony->get_graphics());

         x+=m_dibMony->m_size.cx;

      }


      rect r(rectClient);

      r.top = r.bottom - m_pot.m_iSize * 6;

      pgraphics->FillSolidRect(r,ARGB(84,255,255,255));

      m_pot.m_pt.x = m_pot.m_pt.x + (m_ptFinal.x - m_pot.m_pt.x)  * 0.1;

      m_pot.on_draw(pgraphics);

      for(auto & pc : m_money)
      {
         pc->on_draw(pgraphics);
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

      m_pot.m_pt.y = rectClient.bottom - m_pot.m_iSize * 3;

      m_ptFinal.y = m_pot.m_pt.y;

   }





   void view::_001OnNewGame(signal_details * pobj)
   {

      pobj->m_bRet = true;

      new_game();

   }

   void view::credit()
   {

      m_psound->queue("wait:coin");

      m_pot.m_iCredit++;

      if(m_pot.m_iCredit >= m_pot.m_iSize * 2 - 7)
      {

         m_iCount++;

         if(m_iCount > 7)
         {
            m_iCount = 0;
            m_iPhase++;
         }
         else
         {

            m_pot.m_iCredit=0;
            m_pot.m_bGrow = true;
            m_pot.m_dwLastGrow = ::get_tick_count();

            m_psound->queue("wait:velo");

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

      m_pot.m_iSize = 24;

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



