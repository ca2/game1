#pragma once


namespace coincube
{

   class CLASS_DECL_GAME_COINCUBE coin:
      virtual public object
   {
   public:

      
      pointd          m_pt; // center
      double         m_dAngle; // school x-y
      int            m_iPhase;
      int            m_iSpin;
      view *m_pview;




      pointd        m_v;

      coin(view * pview);
      virtual ~coin();


      void on_draw(::draw2d::dib * pdib);

      void reinvent_merit();

      void defer_check_credit();

   };


} // namespace coincube