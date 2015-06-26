#include "framework.h"
#include <math.h>


namespace pacman
{


   view::view(::aura::application * papp) :
      ::object(papp),
      m_font(allocer()),
      m_dib(allocer())
   {

      //m_ppreview = NULL;

      m_bDibLayout = true;

      m_xDib   = -1;

      m_bHarderControl = false;

      Application.m_pview = this;

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
      IGUI_WIN_MSG_LINK(WM_DESTROY,pdispatch,this,&view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,pdispatch,this,&view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,pdispatch,this,&view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN,pdispatch,this,&view::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP,pdispatch,this,&view::_001OnKeyUp);

   }


   void view::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

      m_font->create_pixel_font("Arial",16, 900);

      attach();

   }

   void view::_001OnDestroy(signal_details * pobj)
   {

      pobj->previous();


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



   void view::_001OnDraw(::draw2d::graphics * pdc)
   {

      ::rect rectClient;

      GetClientRect(rectClient);

      pdc->FillSolidRect(rectClient, ARGB(184,0,0,0));

      //pdc->set_text_color(ARGB(255,255,255,255));

      pacman * ppacman = Application.m_ppacman;

      if(ppacman == NULL)
         return;

      sp(::dib_console) pdib = Application.m_pconsolewindow;

      if(pdib.is_null())
         return;

      synch_lock sl(&pdib->m_mutex);

      pdib->m_dib->get_graphics()->SelectFont(m_font);

      pdib->update_dib();

      rect rectPacman;

      rectPacman.null();

      rectPacman.SetBottomRightSize(pdib->m_dib->m_size);

      rectPacman.Align(align_center,rectClient);

      pdc->BitBlt(rectPacman,pdib->m_dib->get_graphics());

   }



   ::user::document * view::get_document()
   {

      return ::user::impact::get_document();

   }



   void view::attach()
   {

//      m_ppreview = new _PacManPreview(this);

      //m_pconsolewindow = new console(get_app(),size(16,16));

      //m_pconsolewindow = new dib_console_window(get_app(),size(16,16));

      //m_pconsolewindow = new ::windows::console_window(get_app(),size(24,24));

/*      m_pconsolewindow = create_console();

      m_pconsolewindow->set_app(get_app());

      //Application.m_ppacman->::console::window_composite::m_p = m_pconsolewindow;
      //Application.m_ppacman->m_player.::console::window_composite::m_p = m_pconsolewindow;
      //for(auto ghost : Application.m_ppacman->ghosts)
      //{
      //   ghost->::console::window_composite::m_p = m_pconsolewindow;
      //}
      
      if(Application.m_ppacman->m_pthreadimpl.is_null())
      {
         Application.m_ppacman->begin();
      }

      */
   }


   void view::layout()
   {

      m_bDibLayout = true;

   }

   void view::_001OnKeyDown(signal_details * pobj)
   {

      SCAST_PTR(::message::key,pkey,pobj);

      //if(pkey->m_ekey == ::user::key_down)
      //{
      //   m_ppacman->drop();
      //}
      //else
      if(pkey->m_ekey == ::user::key_up)
      {
         Application.m_ppacman->up();
      }
      else if(pkey->m_ekey == ::user::key_down)
      {
         Application.m_ppacman->down();
      }
      else if(pkey->m_ekey == ::user::key_left)
      {
         Application.m_ppacman->left();
      }
      else if(pkey->m_ekey == ::user::key_right)
      {
         Application.m_ppacman->right();
      }

      pkey->m_bRet = true;

   }

   void view::_001OnKeyUp(signal_details * pobj)
   {

      SCAST_PTR(::message::key,pkey,pobj);
      if(m_bHarderControl)
      {
         if(pkey->m_ekey == ::user::key_up)
         {
            Application.m_ppacman->up(false);
         }
         else if(pkey->m_ekey == ::user::key_down)
         {
            Application.m_ppacman->down(false);
         }
         else if(pkey->m_ekey == ::user::key_left)
         {
            Application.m_ppacman->left(false);
         }
         else if(pkey->m_ekey == ::user::key_right)
         {
            Application.m_ppacman->right(false);
         }
      }

      pkey->m_bRet = true;


   }

   bool view::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && IsWindowVisible();

   }



} // namespace pacman



