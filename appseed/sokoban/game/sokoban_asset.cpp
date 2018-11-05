#include "framework.h"


namespace sokoban
{


   asset::asset(::aura::application * papp):
      object(papp),
      m_blockPlace(papp,"place"),
      m_blockWall(papp,"wall"),
      m_blockBox(papp,"box"),
      m_blockPlayer(papp,"player")
   {

      m_iLevel = 0;


   }



   asset::~asset()
   {



   }



   void asset::update()
   {

      m_blockPlace.update(this);
      m_blockWall.update(this);
      m_blockBox.update(this);
      m_blockPlayer.update(this);

   }

   void asset::draw(::draw2d::graphics * pgraphics,char ch,int x,int y, byte bA)
   {

      if(ch == '.')
      {
         m_blockPlace.draw(pgraphics,this,x,y, bA);
      }
      else if(ch == '#')
      {
         m_blockWall.draw(pgraphics,this,x,y,bA);
      }
      else if(ch == '$')
      {
         m_blockBox.draw(pgraphics,this,x,y,bA);
      }
      else if(ch == '@')
      {
         m_blockPlayer.draw(pgraphics,this,x,y,bA);
      }
      else if(ch == '*')
      {
         m_blockPlace.draw(pgraphics,this,x,y,bA);
         m_blockBox.draw(pgraphics,this,x,y,bA);
      }
      else if(ch == '+')
      {
         m_blockPlace.draw(pgraphics,this,x,y,bA);
         m_blockPlayer.draw(pgraphics,this,x,y,bA);
      }

   }

} // namespace sokoban












