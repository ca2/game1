#include "framework.h"


namespace sokoban
{


   block::block(::aura::application * papp, const string & strImage) :
      m_dibSource(papp->allocer()),
      m_dib(papp->allocer())
   {

      m_strImage = strImage;

   }

   void block::update(asset * passet)
   {

      if(!m_dibSource.load_from_file(App(m_dibSource->get_app()).dir().matter(::file::path("theme") / passet->m_strMatter / m_strImage + ".png"), false))
         return;

      m_dib->create(passet->m_iSize,passet->m_iSize);

      m_dib->stretch_dib(m_dibSource);

   }




   void block::draw(::draw2d::graphics * pgraphics,asset * passet,int x,int y, byte bA)
   {

      pgraphics->alpha_blend(passet->m_iSize * x,passet->m_iSize *y,passet->m_iSize,passet->m_iSize,m_dib->get_graphics(),0,0,passet->m_iSize, passet->m_iSize, bA / 255.0);

   }




} // namespace sokoban