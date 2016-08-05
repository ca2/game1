#pragma once 


#include <math.h>


namespace sokoban
{



   class asset :
      virtual public object
   {
   public:
      
      
      int         m_iSize;
      int         m_iWidth;
      int         m_iHeight;
      string      m_strMatter;

      block       m_blockPlace;
      block       m_blockWall;
      block       m_blockBox;
      block       m_blockPlayer;

      int         m_iLevel;
      
      asset(::aura::application * papp);
      virtual ~asset();


      void update();

      void draw(::draw2d::graphics * pgraphics, char ch, int x, int y, byte bA);

   
   };


} // namespace sokoban




