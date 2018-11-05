#include "framework.h"


namespace coincube
{

   coin::coin(view * pview):
      object(pview->get_app()),
      m_pview(pview)
   {

   }

   coin::~coin()
   {

   }

   void coin::reinvent_merit()
   {

      int iCount = System.math().RandRange(20, 40);

      sp(particle::effect::effect) peffect = canew(particle::effect::random_color_range_fountain(get_app(), m_pt.x, m_pt.y));
      peffect->initialize(200, iCount);
      peffect->initializeRenderer();
      m_pview->m_effecta.add(peffect);


      int iMaxPhase = 125;
      m_iSpin =System.math().RandRange(40,iMaxPhase);
      m_iPhase = System.math().RandRange(0,m_pview->m_dibCoin->m_size.cx / m_pview->m_dibCoin->m_size.cy - 1 * iMaxPhase);

      m_v.x  =   ((double)System.math().RandRange(5,40)) / 10.0;

      if(System.math().RandRange(0,1) == 1)
      {
         m_v.x = -m_v.x;
      }
      m_v.y  =   ((double)System.math().RandRange(5,40)) / 10.0;

      rect rectClient;

      m_pview->GetClientRect(rectClient);

      m_pt.x = System.math().RandRange(rectClient.left + 10,rectClient.right - 10);
      m_pt.y = System.math().RandRange(rectClient.top + 10,rectClient.bottom - m_pview->m_pot.m_iSize * 3);


   }


   void coin::on_draw(::draw2d::graphics * pgraphics)
   {

      point pt(m_pt.x - m_pview->m_dibCoin->m_size.cy / 2,m_pt.y - m_pview->m_dibCoin->m_size.cy / 2);
      size s(m_pview->m_dibCoin->m_size.cy,m_pview->m_dibCoin->m_size.cy);

      point pt2((((::get_tick_count() + m_iPhase) * m_iSpin / 1000) % (m_pview->m_dibCoin->m_size.cx / m_pview->m_dibCoin->m_size.cy)) *m_pview->m_dibCoin->m_size.cy,0);

      pgraphics->draw(pt,s,m_pview->m_dibCoin->get_graphics(),pt2,SRCCOPY);
      defer_check_credit();
      m_pt.x += m_v.x;
      m_pt.y += m_v.y;

      rect rectClient;

      m_pview->GetClientRect(rectClient);

      if(m_pt.x > (rectClient.right + m_pview->m_dibCoin->m_size.cy))
      {
         reinvent_merit();
      }
      else if(m_pt.x < (rectClient.left - m_pview->m_dibCoin->m_size.cy))
      {
         reinvent_merit();
      }
      else if(m_pt.y > (rectClient.bottom + m_pview->m_dibCoin->m_size.cy))
      {
         reinvent_merit();
      }



   }

   void coin::defer_check_credit()
   {

      int cs = m_pview->m_dibCoin->m_size.cy;

      if(m_pt.y >= m_pview->m_pot.m_pt.y - m_pview->m_pot.m_iSize - m_pview->m_pot.m_iSize / 2
            && m_pt.y <= m_pview->m_pot.m_pt.y + m_pview->m_pot.m_iSize + m_pview->m_pot.m_iSize / 2)
      {

         if(m_pt.x >= m_pview->m_pot.m_pt.x - m_pview->m_pot.m_iSize
               && m_pt.x <= m_pview->m_pot.m_pt.x + m_pview->m_pot.m_iSize
               && m_pt.y >= m_pview->m_pot.m_pt.y + m_pview->m_pot.m_iSize - m_pview->m_pot.m_iSize / 4 - m_pview->m_pot.m_iCredit)
         {

            m_pview->credit();
            reinvent_merit();

         }
         else if(m_v.x > 0.0)
         {

            if(m_pt.x >= m_pview->m_pot.m_pt.x - m_pview->m_pot.m_iSize - m_pview->m_pot.m_iSize / 4 && m_pt.x <= m_pview->m_pot.m_pt.x - m_pview->m_pot.m_iSize)
            {

               m_v.x = -m_v.x;

               m_pt.x = m_pview->m_pot.m_pt.x - m_pview->m_pot.m_iSize - m_pview->m_pot.m_iSize / 4;

            }
            else if(m_pt.x >= m_pview->m_pot.m_pt.x + m_pview->m_pot.m_iSize && m_pt.x <= m_pview->m_pot.m_pt.x + m_pview->m_pot.m_iSize + m_pview->m_pot.m_iSize / 4)
            {

               m_pt.x = m_pview->m_pot.m_pt.x + m_pview->m_pot.m_iSize + m_pview->m_pot.m_iSize / 4;

            }
            else if(m_pt.x >= m_pview->m_pot.m_pt.x - m_pview->m_pot.m_iSize  && m_pt.x <= m_pview->m_pot.m_pt.x - m_pview->m_pot.m_iSize + m_pview->m_pot.m_iSize / 4)
            {

               m_pview->credit();
               reinvent_merit();

            }
            else if(m_pt.x >= m_pview->m_pot.m_pt.x + m_pview->m_pot.m_iSize - m_pview->m_pot.m_iSize / 4 && m_pt.x <= m_pview->m_pot.m_pt.x + m_pview->m_pot.m_iSize)
            {

               m_pview->credit();
               reinvent_merit();

            }

         }
         else
         {

            if(m_pt.x >= m_pview->m_pot.m_pt.x - m_pview->m_pot.m_iSize - m_pview->m_pot.m_iSize / 4 && m_pt.x <= m_pview->m_pot.m_pt.x - m_pview->m_pot.m_iSize)
            {

               m_pt.x = m_pview->m_pot.m_pt.x - m_pview->m_pot.m_iSize - m_pview->m_pot.m_iSize / 4;

            }
            else if(m_pt.x >= m_pview->m_pot.m_pt.x + m_pview->m_pot.m_iSize && m_pt.x <= m_pview->m_pot.m_pt.x + m_pview->m_pot.m_iSize + m_pview->m_pot.m_iSize / 4)
            {

               m_v.x = -m_v.x;

               m_pt.x = m_pview->m_pot.m_pt.x + m_pview->m_pot.m_iSize + m_pview->m_pot.m_iSize / 4;

            }
            else if(m_pt.x >= m_pview->m_pot.m_pt.x - m_pview->m_pot.m_iSize  && m_pt.x <= m_pview->m_pot.m_pt.x - m_pview->m_pot.m_iSize + m_pview->m_pot.m_iSize / 4)
            {

               m_pview->credit();
               reinvent_merit();

            }
            else if(m_pt.x >= m_pview->m_pot.m_pt.x + m_pview->m_pot.m_iSize - m_pview->m_pot.m_iSize / 4 && m_pt.x <= m_pview->m_pot.m_pt.x + m_pview->m_pot.m_iSize)
            {

               m_pview->credit();
               reinvent_merit();

            }

         }

      }

   }


} // namespace coincoin