#pragma once

//
//
//	_TetrisInterface
//	By Camilo Sasuke Tsumanuma 25/09/1998
//
//
//
//

namespace tetris
{

   class _TetrisInterface:
      virtual public ::object
   {
   public:

      static int TOTALBLOCKS;

      static const char * blocks[7][4];

      static int shiftsPositions[8][2];

      COLORREF colors[9];


      int typesDistribution[7];




      _TetrisInterface(::aura::application * papp);


   };



} // namespace tetris




