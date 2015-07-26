#pragma once




//
//
//	_TetrisPreview
//	By Camilo Sasuke Tsumanuma 25/09/1998
//
//
//
//

namespace tetris
{



   class _TetrisPreview :
      virtual public _TetrisInterface
   {
   public:


      ::tetris::view * m_pparent;
      ::draw2d::dib_sp m_dib;
      int curType,curRotation;
      //COLORREF colors[9];
      mutex       m_mutex;


      _TetrisPreview(::tetris::view * pview);


      ::size preferredSize();





      void pickTypeAndRotation(int * ptype, int *protation);


      //int pickRotation();


      void drawBlock();



      void redraw();


      void drawCell(int x,int y,int color);



      void paint(::draw2d::graphics * pdc);

   };


} // namespace tetris









