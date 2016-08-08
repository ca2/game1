#include "framework.h"

//#include "ft2build.h"
//#include FT_FREETYPE_H

//void draw_freetype_bitmap2(::draw2d::dib * m_p,int32_t dx,int32_t dy,void * pftbitmap,int x,int y);
//void draw_freetype_bitmap2(::draw2d::dib * m_p,int32_t dx,int32_t dy,void * pftbitmap,int x,int y,byte a,byte r,byte g,byte b);

int ColorGHOST(int iColor)
{
   switch(iColor)
   {
   case ::console::WHITE:
      return 4;
   case ::console::RED:
      return 3;
   case ::console::CYAN:
      return 1;
   case ::console::YELLOW:
      return 0;
   case ::console::MAGENTA:
      return 2;
   case ::console::BLUE:
      return 5;
   };

   return -1;
}



namespace pacman
{


   console::console(::aura::application * papp,size sizeTile):
      object(papp),
      dib_console(papp,sizeTile),
      m_dib0(allocer()),
      m_dib1(allocer()),
      m_dib2(allocer()),
      m_dib3(allocer()),
      m_dib4(allocer()),
      m_dib5(allocer()),
      m_dibChar(allocer())
   {

      // m_iFont = FT_New_Face((FT_Library)System.ftlibrary(), Application.dir().matter_file("crackman.ttf"), 0, (FT_Face *)&m_face);

      m_sizeDib = m_sizeTile;

      m_offset.cx = m_sizeTile.cy / 5;
      m_offset.cy = m_sizeTile.cy / 5;

      m_sizeDib.cx+=m_offset.cx * 2;
      m_sizeDib.cy+=m_offset.cy * 2;


      ::visual::dib_sp dib(allocer());

      dib.load_from_file("matter://pacman.png", false);

      int size = dib->m_size.cy / 2;

      m_dib0->create(m_sizeDib);

      m_dib0->FillByte(0);

      m_dib0->get_graphics()->StretchBlt(0,0,m_sizeDib.cx,m_sizeDib.cy,dib->get_graphics(),0,0,size,size,SRCCOPY);

      m_dib1->create(m_sizeDib.cx,m_sizeDib.cy);

      m_dib1->FillByte(0);

      m_dib1->get_graphics()->StretchBlt(0,0,m_sizeDib.cx,m_sizeDib.cy,dib->get_graphics(),size,0,size ,size,SRCCOPY);

      m_dib2->create(m_sizeDib.cx,m_sizeDib.cy);

      m_dib2->FillByte(0);

      m_dib2->get_graphics()->StretchBlt(0,0,m_sizeDib.cx,m_sizeDib.cy,dib->get_graphics(),size *2,0,size,size,SRCCOPY);

      m_dib3->create(m_sizeDib.cx,m_sizeDib.cy);

      m_dib3->FillByte(0);

      m_dib3->get_graphics()->StretchBlt(0,0,m_sizeDib.cx,m_sizeDib.cy,dib->get_graphics(),0,size,size,size,SRCCOPY);

      m_dib4->create(m_sizeDib.cx,m_sizeDib.cy);

      m_dib4->FillByte(0);

      m_dib4->get_graphics()->StretchBlt(0,0,m_sizeDib.cx,m_sizeDib.cy,dib->get_graphics(),size,size,size,size,SRCCOPY);

      m_dib5->create(m_sizeDib.cx,m_sizeDib.cy);

      m_dib5->FillByte(0);

      m_dib5->get_graphics()->StretchBlt(0,0,m_sizeDib.cx,m_sizeDib.cy,dib->get_graphics(),size * 2,size,size,size,SRCCOPY);





      m_ga.set_size(6);


      dib.load_from_file("matter://ghosts.png",false);

      size = dib->m_size.cy;

      int i = 0;

      for(auto & g : m_ga)
      {
         g.alloc(allocer());
         g->create(m_sizeDib.cx,m_sizeDib.cy);
         g->FillByte(0);
         g->get_graphics()->StretchBlt(0,0,m_sizeDib.cx,m_sizeDib.cy,dib->get_graphics(),size * i,0,size,size,SRCCOPY);
         i++;
      }



   }


   bool console::defer_write(char ch,int x,int y,int cx,int cy, int iColor)
   {
      if(ch == char(250))
      {
         //m_dib->get_graphics()->FillSolidRect(x - m_offset.cx,y - m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,ARGB(255,0,0,0));
         ::draw2d::brush_sp brush(allocer());
         brush->create_solid(ARGB(255,255,255,0));
         m_dib->get_graphics()->SelectObject(brush);
         rect r2(x - m_offset.cx,y - m_offset.cy,x - m_offset.cx + m_sizeDib.cx,y - m_offset.cy + m_sizeDib.cy);
         rect r(0,0,m_sizeDib.cx / 7,m_sizeDib.cy / 7);
         r.Align(::align_center,r2);
         m_dib->get_graphics()->FillEllipse(r);
         return true;
      }
      else if(ch == 'o')
      {
         //m_dib->get_graphics()->FillSolidRect(x - m_offset.cx,y - m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,ARGB(255,0,0,0));
         ::draw2d::brush_sp brush(allocer());
         brush->create_solid(ARGB(255,255,255,0));
         m_dib->get_graphics()->SelectObject(brush);
         rect r2(x - m_offset.cx,y - m_offset.cy,x - m_offset.cx + m_sizeDib.cx,y - m_offset.cy + m_sizeDib.cy);
         rect r(0,0,m_sizeDib.cx / 2,m_sizeDib.cy / 2);
         r.Align(::align_center,r2);
         m_dib->get_graphics()->FillEllipse(r);
         return true;
      }
      else if(ch == '\'')
      {
         //m_dib->get_graphics()->FillSolidRect(x - m_offset.cx,y - m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,ARGB(255,0,0,0));
         m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
         m_dib->get_graphics()->BitBlt(x-m_offset.cx,y-m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,m_dib5->get_graphics(),0,0,SRCCOPY);
         return true;
      }
      else if(ch == '*')
      {
         //m_dib->get_graphics()->FillSolidRect(x - m_offset.cx,y - m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,ARGB(255,0,0,0));
         m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
         m_dib->get_graphics()->BitBlt(x-m_offset.cx,y-m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,m_dib0->get_graphics(),0,0,SRCCOPY);
         return true;
      }
      else if(ch == '>')
      {
         //m_dib->get_graphics()->FillSolidRect(x - m_offset.cx,y - m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,ARGB(255,0,0,0));
         m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
         m_dib->get_graphics()->BitBlt(x-m_offset.cx,y-m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,m_dib1->get_graphics(),0,0,SRCCOPY);
         return true;
      }
      else if(ch == '<')
      {
         //m_dib->get_graphics()->FillSolidRect(x - m_offset.cx,y - m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,ARGB(255,0,0,0));
         m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
         m_dib->get_graphics()->BitBlt(x-m_offset.cx,y-m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,m_dib2->get_graphics(),0,0,SRCCOPY);
         return true;
      }
      else if(ch == 'v')
      {
         //m_dib->get_graphics()->FillSolidRect(x - m_offset.cx,y - m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,ARGB(255,0,0,0));
         m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
         m_dib->get_graphics()->BitBlt(x-m_offset.cx,y-m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,m_dib3->get_graphics(),0,0,SRCCOPY);
         return true;
      }
      else if(ch == '^')
      {
         //m_dib->get_graphics()->FillSolidRect(x - m_offset.cx,y - m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,ARGB(255,0,0,0));
         m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
         m_dib->get_graphics()->BitBlt(x-m_offset.cx,y-m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,m_dib4->get_graphics(),0,0,SRCCOPY);
         return true;
      }
      else if(ch == char(150) && ColorGHOST(iColor) >= 0)
      {
         //m_dib->get_graphics()->FillSolidRect(x - m_offset.cx,y - m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,ARGB(255,0,0,0));
         m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
         m_dib->get_graphics()->BitBlt(x-m_offset.cx,y-m_offset.cy,m_sizeDib.cx,m_sizeDib.cy,m_ga[ColorGHOST(iColor)]->get_graphics(),0,0,SRCCOPY);
         return true;
      }
      else if(isalnum_dup(ch) || ch=='!')
      {

         string str = ch;
         m_dib->get_graphics()->set_text_color(console_COLORREF(iColor));
         m_dib->get_graphics()->TextOut(x - m_offset.cx, y - m_offset.cy, str);
         //FT_Face & face = (FT_Face &)m_face;

         //int32_t error;

         //error = FT_Set_Char_Size(face,        /* handle to face object */
         //   0,          /* char_width in 1/64th of points */
         //   m_sizeTile.cy * 72,          /* char_height in 1/64th of points */
         //   72,         /* horizontal device resolution */
         //   72);         /* vertical device resolution */

         //if(error == 0)
         //{

         //   error = FT_Select_Charmap(face, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

         //   if(error == 0)
         //   {

         //      string strUtf8;
         //
         //      ::str::international::multibyte_to_utf8(437,strUtf8,string(ch));

         //      int64_t iChar =  ::str::ch::uni_index(strUtf8);

         //      int32_t glyph_index = FT_Get_Char_Index(face,(int32_t)iChar);

         //      error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */

         //      if(error == 0)
         //      {

         //         error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */

         //         if(error == 0)
         //         {

         //            ::visual::dib_sp &  dib = m_dib;

         //            //dib->create(face->glyph->bitmap.width,face->glyph->bitmap.rows);

         //            //dib->realize(pgraphics);
         //            COLORREF cr = console_COLORREF(iColor);

         //            byte a = argb_get_a_value(cr);
         //            byte r = argb_get_r_value(cr);
         //            byte g = argb_get_g_value(cr);
         //            byte b = argb_get_b_value(cr);

         //            m_dibChar->create(m_sizeTile.cx * 3,m_sizeTile.cy * 3);

         //            m_dibChar->Fill(0);

         //            draw_freetype_bitmap2(m_dibChar.m_p,0,0,&face->glyph->bitmap,0,0,a,r,g,b);

         //            m_dib->get_graphics()->BitBlt(x - m_offset.cx,y - m_offset.cy,m_dibChar->m_size.cx,m_dibChar->m_size.cy,m_dibChar->get_graphics(),0,0,SRCCOPY);

         //            //pgraphics->SetStretchBltMode(HALFTONE);

         //            //pgraphics->StretchBlt(0,0,dib->m_size.cx / 40,dib->m_size.cy / 40,dib->get_graphics(),0,0,dib->m_size.cx,dib->m_size.cy,SRCCOPY);

         //            //pgraphics->StretchBlt(0,m_cy - dib->m_size.cy / 40,dib->m_size.cx / 40,dib->m_size.cy / 40,dib->get_graphics(),0,0,dib->m_size.cx,dib->m_size.cy,SRCCOPY);

         //         }

         //      }

         //   }

         //}

         return true;

      }

      return false;

   }



}

//void draw_freetype_bitmap2(::draw2d::dib * m_p,int32_t dx,int32_t dy,void * pftbitmap,int xParam,int yParam)
//{
//
//   FT_Bitmap * bitmap = (FT_Bitmap *)pftbitmap;
//   FT_Int x = (FT_Int)xParam;
//   FT_Int y = (FT_Int)yParam;
//
//   FT_Int  i,j,p,q;
//   FT_Int  x_max = x + bitmap->width;
//   FT_Int  y_max = y + bitmap->rows;
//
//   m_p->map();
//
//   for(i = x,p = 0; i < x_max; i++,p++)
//   {
//      for(j = y,q = 0; j < y_max; j++,q++)
//      {
//         if(i < 0 || j < 0 || i >= m_p->m_size.cx || j >= m_p->m_size.cy)
//            continue;
//
//         int32_t a = bitmap->buffer[q * bitmap->width + p];
//
//         *((COLORREF *)&((byte *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = ARGB(a,0,0,0);
//
//      }
//   }
//
//}
//
//
//void draw_freetype_bitmap2(::draw2d::dib * m_p,int32_t dx,int32_t dy,void * pftbitmap,int xParam,int yParam,byte aParam,byte r,byte g,byte b)
//{
//
//   FT_Bitmap * bitmap = (FT_Bitmap *)pftbitmap;
//   FT_Int x = (FT_Int)xParam;
//   FT_Int y = (FT_Int)yParam;
//
//   FT_Int  i,j,p,q;
//   FT_Int  x_max = x + bitmap->width;
//   FT_Int  y_max = y + bitmap->rows;
//
//   m_p->map();
//
//   for(i = x,p = 0; i < x_max; i++,p++)
//   {
//      for(j = y,q = 0; j < y_max; j++,q++)
//      {
//         if(i < 0 || j < 0 || i >= m_p->m_size.cx || j >= m_p->m_size.cy)
//            continue;
//
//         int32_t a = bitmap->buffer[q * bitmap->width + p];
//
//         if(a > 0)
//         {
//
//            *((COLORREF *)&((byte *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = ARGB(a * aParam / 255,b,g,r);
//
//         }
//         else
//         {
//
//            *((COLORREF *)&((byte *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = 0;
//
//         }
//
//      }
//   }
//
//}
