//#pragma once
//
//
//
//
////
////
////	_PacManPreview
////	By Camilo Sasuke Tsumanuma 25/09/1998
////
////
////
////
//
//namespace pacman
//{
//
//
//
//   class _PacManPreview :
//      virtual public _PacManInterface
//   {
//   public:
//
//
//      ::pacman::view * m_pparent;
//      ::draw2d::dib_sp m_dib;
//      int curType,curRotation;
//      //COLORREF colors[9];
//      mutex       m_mutex;
//
//
//      _PacManPreview(::pacman::view * pview);
//
//
//      ::size preferredSize();
//
//
//
//
//
//      void pickTypeAndRotation(int * ptype, int *protation);
//
//
//      //int pickRotation();
//
//
//      void drawBlock();
//
//
//
//      void redraw();
//
//
//      void drawCell(int x,int y,int color);
//
//
//
//      void paint(::draw2d::dib * pdib);
//
//   };
//
//
//} // namespace pacman
//
//
//
//
//
//
//
//
//
