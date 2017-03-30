#include "framework.h"
#include <math.h>




namespace arch001
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
      m_mutexSwap(papp)
   {
      m_iCount = 0;
      m_iPhase = 0;


      m_bGame = false;

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
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pdispatch, this, &view::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pdispatch, this, &view::_001OnKeyUp);

   }


   void view::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      Application.m_pgame = new game(get_app());

      Game.start(this);


      m_psound = new ::multimedia::sound_track(get_app());
      m_psound->audio_plugin_initialize(NULL,false);

      m_dataid += ".local://";

      initialize_data_client(Application.simpledb().get_data_server());
      if(!m_bGame)
      {
         m_bGame = true;
//         new_game();

      }


      data_get("count",m_iCount);
      data_get("phase",m_iPhase);



      pcreate->previous();

      if(pcreate->m_bRet)
         return;

      GetMain()->Enable(true);

   }

   void view::_001OnKeyDown(signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj);

      pobj->m_bRet = true;

   }
   

   void view::_001OnKeyUp(signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj);
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



   }

   void view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }



   void view::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      Game._001OnDraw(pgraphics);

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





   void view::_001OnNewGame(signal_details * pobj)
   {

      pobj->m_bRet = true;


   }


   bool view::keyboard_focus_is_focusable()
   {

      return true;

   }
} // namespace arch001



