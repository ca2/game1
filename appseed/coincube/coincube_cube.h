#pragma once


namespace coincube
{

   class CLASS_DECL_GAME_COINCUBE cube :
      virtual public object
   {
   public:


      point          m_pt;
      double         m_dAngle;
      int            m_iSize;
      bool           m_bGrow;
      DWORD          m_dwLastGrow;
      view *         m_pview;
      int            m_iCredit;
      int            m_iRefSize;


      cube(view * pview);
      virtual ~cube();


      void on_draw(::draw2d::graphics * pgraphics);

   };


} // namespace coincube