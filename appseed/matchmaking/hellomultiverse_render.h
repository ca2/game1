//
//  hellomultiverse_render.h
//  app_core_hellomultiverse
//
//  Created by Thomas Borregaard Sørensen on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Tsumanuma. All rights reserved.
//


#pragma once


namespace hellomultiverse
{
   
   
   class CLASS_DECL_APP_CORE_HELLOMULTIVERSE render :
      virtual public ::thread
   {
   public:
      
      bool                    m_bDib1;
      
      bool                    m_bAlternate;
      
      bool                    m_bLite;

      bool                    m_bImageEnable;
      
      mutex                   m_mutexWork;
      mutex                   m_mutexDraw;
      mutex                   m_mutexSwap;
      
      bool                    m_bNewLayout;
      bool                    m_bHelloRender;
      int                     m_cx;
      int                     m_cy;
      int                     m_cxCache1;
      int                     m_cyCache1;
      
      ::visual::fastblur      m_dibImage;
      ::draw2d::dib_sp        m_dib1;
      ::draw2d::dib_sp        m_dib2;
      ::visual::dib_sp        m_dibWork;
      ::visual::fastblur      m_dib;
      ::visual::dib_sp        m_dibTemplate;
      
      bool                    m_bVoidTransfer;
      bool                    m_bFirstDone;
      
      ::draw2d::font_sp       m_font;
      
      double                  m_dMinRadius;
      double                  m_dMaxRadius;
      
      string                  m_strHelloMultiverse;
      
      rect                    m_rectClient;


      mutex *                 m_pmutexText;

      view *                  m_pview;


      render(::aura::application * papp);
      virtual ~render();
      
      
      string get_hellomultiverse() { synch_lock slText(m_pmutexText);  string str(m_strHelloMultiverse.c_str()); return str; }
      
      
      virtual int32_t run();
      
      
      virtual void full_render();
      virtual void hellomultiverse_render();
      virtual void hellomultiverse_draw();
      virtual void hellomultiverse_render(::draw2d::dib * pdib);
      //virtual void hellomultiverse_render(::draw2d::dib * pdib);
      
      virtual void hellomultiverse_render_full_view(::draw2d::dib * pdib);
      virtual void hellomultiverse_render_lite_view(::draw2d::dib * pdib);
      
      
   };


} // namespace hellomultiverse


