#include "framework.h"


namespace coincube
{

   cube::cube(::aura::application * papp):
      object(papp)
   {
      m_bGrow = false;
      m_iRefSize = -1;
      m_iCredit = 0;
   }

   cube::~cube()
   {

   }


   void cube::on_draw(::draw2d::graphics * pgraphics)
   {



      ::draw2d::brush_sp b1(allocer());


      b1->CreateRadialGradientBrush(pointd(m_pt.x, m_pt.y),sized(m_iSize * 8,m_iSize*8),ARGB(84,255,255,0),ARGB(0,255,255,255));

      rect r(m_pt.x - m_iSize * 4,m_pt.y - m_iSize * 4,m_pt.x + m_iSize * 4,m_pt.y + m_iSize * 4);

      pgraphics->SelectObject(b1);

      pgraphics->FillEllipse(r);


      ::draw2d::pen_sp pen(allocer());

      pen->create_solid(m_iSize / 2, ARGB(255, 100, 120, 200));

      pgraphics->SelectObject(pen);


      pgraphics->MoveTo(m_pt.x - m_iSize,m_pt.y - m_iSize);
      pgraphics->LineTo(m_pt.x - m_iSize,m_pt.y + m_iSize);
      pgraphics->LineTo(m_pt.x + m_iSize,m_pt.y + m_iSize);
      pgraphics->LineTo(m_pt.x + m_iSize,m_pt.y - m_iSize);

      rect rCred(m_pt.x - m_iSize, m_pt.y + m_iSize - m_iCredit, m_pt.x+m_iSize, m_pt.y+m_iSize);



      pgraphics->FillSolidRect(rCred,ARGB(255,250,240,10));

      r.deflate(m_iSize *2, m_iSize * 2);

      pgraphics->DrawEllipse(r);



      if(m_bGrow)
      {

         if(m_iRefSize < 0)
         {
          
            m_iRefSize = m_iSize;

         }


         double dSurprise = 300.0;

         double dSlow = 100000.0 / dSurprise;

         double dRate = (::get_tick_count() - m_dwLastGrow) / (dSlow * 2);

         int iS = m_iRefSize * 1.25;

         m_iSize = m_iRefSize + (iS - m_iRefSize) * dRate;

         m_pview->on_layout();


         if(::get_tick_count() - m_dwLastGrow < dSlow)
         {

            double dRate = (::get_tick_count() - m_dwLastGrow) / dSlow;
            
            int iSize = m_iSize * 2 * dRate;
            
            ::draw2d::brush_sp b2(allocer());

            b2->CreateRadialGradientBrush(pointd(m_pt.x,m_pt.y),sized(m_iSize * 8 + iSize,m_iSize * 8 + iSize),ARGB((byte)((255 - 220) * (1.0 - dRate) + 220),255,255,255),ARGB(84,255,255,255));

            rect r(m_pt.x - m_iSize * 4 - iSize,m_pt.y - m_iSize * 4 - iSize,m_pt.x + m_iSize * 4 + iSize,m_pt.y + m_iSize * 4 + iSize);

            pgraphics->SelectObject(b2);

            pgraphics->FillEllipse(r);



         }
         else if(::get_tick_count() - m_dwLastGrow < dSlow * 2.0)
         {

            double dRate = 2.0 - (::get_tick_count() - (m_dwLastGrow + dSlow))  / dSlow;


            int iSize = m_iSize * 2 * dRate;

            ::draw2d::brush_sp b2(allocer());

            b2->CreateRadialGradientBrush(pointd(m_pt.x,m_pt.y),sized(m_iSize * 9 + iSize,m_iSize * 9 + iSize),ARGB((byte)((220 - 184) * (dRate) + 184),255,255,255),ARGB((byte)(84 * dRate),255,255,255));

            rect r(m_pt.x - m_iSize * 4 - iSize,m_pt.y - m_iSize * 4 - iSize,m_pt.x + m_iSize * 4 + iSize,m_pt.y + m_iSize * 4 + iSize);

            pgraphics->SelectObject(b2);

            pgraphics->FillEllipse(r);

         }
         else
         {

            m_bGrow = false;

            m_iSize = iS;
            m_iRefSize = -1;
         }

      }




   }

   
} // namespace coincube