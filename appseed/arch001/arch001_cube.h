#pragma once


namespace arch001
{

   class CLASS_DECL_GAME_ARCH001 cube :
      virtual public object
   {
   public:


      point          m_pt; // center
      double         m_dAngle; // school x-y
      int            m_iSize;
      bool           m_bGrow;
      DWORD          m_dwLastGrow;
      int            m_iRefSize;
      view *m_pview;
      int            m_iCredit;

      cube(::aura::application * papp);
      virtual ~cube();


      void on_draw(::draw2d::dib * pdib);

   };


} // namespace arch001