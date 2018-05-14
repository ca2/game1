#include "framework.h"

#define WIDTHINCELLS 9
#define HEIGHTINCELLS 9
#define CELLSIZEINPIXELS 6


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


   _TetrisPreview::_TetrisPreview(::tetris::view * pview) :
      ::object(pview->get_app()),
      _TetrisInterface(pview->get_app()),
      m_pparent(pview),
      m_mutex(pview->get_app()),
      m_dib(allocer())
   {


      //setBackground(colors[0]);

      //image = null;
      m_dib->create(preferredSize());

      pickTypeAndRotation(NULL, NULL);
      //pickRotation();



   }


   ::size _TetrisPreview::preferredSize()
   {
      return ::size(WIDTHINCELLS * CELLSIZEINPIXELS,HEIGHTINCELLS * CELLSIZEINPIXELS);
   }





   void _TetrisPreview::pickTypeAndRotation(int * ptype,int *protation)
   {

      synch_lock sl(&m_mutex);

      // pickType

      int retType = curType;
      int random = (int)System.math().RandRange(0, 100);
      int type = 0;
      int limite_inferior = 0,limite_superior;

      while(true)
      {
         limite_superior =  limite_inferior + typesDistribution[type];
         if((limite_inferior <= random) && (random <= limite_superior))
         {
            break;
         }
         limite_inferior = limite_superior;
         type++;
         if(type > TOTALBLOCKS)
         {
            type = 1;
            break;
         }
      }

      curType = type;

      if(ptype != NULL)
      {
         *ptype = retType;
      }

      // pickRotation

      //return retType;
      int retRotation = curRotation;
      curRotation = (int)System.math().RandRange(0,3);
//         return retRotation;

      if(protation != NULL)
      {
         *protation = retRotation;
      }

      redraw();

   }


   //int _TetrisPreview::pickRotation()
   //{

   //   //synch_lock sl(&m_mutex);
   //   int retRotation = curRotation;
   //   curRotation = (int)System.math().RandRange(0,3);
   //   return retRotation;
   //}



   void _TetrisPreview::drawBlock()
   {

      //::draw2d::graphics & imageGraph = *m_dib->get_graphics();

      int testX,testY,shiftX,shiftY;
      string strShift = blocks[curType][curRotation];
      int i = 0;

      testX = WIDTHINCELLS / 2;
      testY = HEIGHTINCELLS / 2;

      //imageGraph.set_text_color(colors[curType + 1]);

      while(true)
      {
         drawCell(testX,testY,curType + 1);
         if(i >= strShift.length()) return;
         shiftX = shiftsPositions[strShift[i] - '0'][0];
         shiftY = shiftsPositions[strShift[i] - '0'][1];
         testX += shiftX;
         testY += shiftY;
         i++;
      }
   }



   void _TetrisPreview::redraw()
   {
      ::draw2d::graphics & imageGraph = *m_dib->get_graphics();
      //imageGraph.setColor(colors[0]);
      m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
      imageGraph.fill_solid_rect_dim(0,0,WIDTHINCELLS * CELLSIZEINPIXELS,HEIGHTINCELLS * CELLSIZEINPIXELS, colors[0]);
      drawBlock();
      //repaint();
   }



   void _TetrisPreview::drawCell(int x,int y,int color)
   {

      ::draw2d::graphics & imageGraph = *m_dib->get_graphics();
      imageGraph.fill_solid_rect_dim((x * CELLSIZEINPIXELS) + 1,(y * CELLSIZEINPIXELS) + 1, CELLSIZEINPIXELS - 2,CELLSIZEINPIXELS - 2, colors[color]);
   }



   //void _TetrisPreview::paint(int x, int y::draw2d::graphics * pgraphics)
   //{
   //   pgraphics->BitBlt(0,
   //   while(!g.drawImage(image,0,0,this)) {};
   //}


} // namespace tetris













