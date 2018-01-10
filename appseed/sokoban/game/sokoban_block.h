#pragma once 


namespace sokoban
{


   class asset;

   class block
   {
   public:

      
      string            m_strImage;
      ::visual::dib_sp  m_dibSource;
      ::draw2d::dib_sp  m_dib;


      block(::aura::application * papp, const string & strImage);


      void update(asset * passet);
      void draw(::draw2d::graphics * pgraphics,asset * passet,int x,int y, byte bA);


   };



} // namespace sokoban




