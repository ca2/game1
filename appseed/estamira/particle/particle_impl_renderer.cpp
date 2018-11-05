#include "framework.h"


namespace particle
{

   void renderer_impl::generate(::draw2d::graphics * pgraphics, class system *sys, bool)
   {
      assert(sys != nullptr);

      m_psystem = sys;

      const size_t count = sys->numAllParticles();

   }

   void renderer_impl::destroy()
   {

   }

   void renderer_impl::update(::draw2d::graphics * pgraphics, class system *sys)
   {
   }

   void renderer_impl::render(::draw2d::graphics * pgraphics, float cx, float cy, class system *sys)
   {

      const size_t count = m_psystem->numActiveParticles();

      for(index i = 0; i < count; i++)
      {
         ::draw2d::brush_sp br(allocer());
         br->create_solid(
         ARGB((BYTE)(m_psystem->finalData()->m_col[i].a * 255.f),
              (BYTE)(m_psystem->finalData()->m_col[i].r * 255.f),
              (BYTE)(m_psystem->finalData()->m_col[i].g * 255.f),
              (BYTE)(m_psystem->finalData()->m_col[i].b * 255.f)));
         pgraphics->SelectObject(br);
         double x = (m_psystem->finalData()->m_pos[i].x + m_psystem->finalData()->m_pos[i].y);
         double y = (m_psystem->finalData()->m_pos[i].z + m_psystem->finalData()->m_pos[i].y);
         pgraphics->FillEllipse(
         x,
         y,
         x + 5,
         y + 5);

      }

   }

}

/*
First of all, I don't really understand why you use pos.x + 1.

Next, like Nathan said, you shouldn't use the clip-space point, but the eye-space point. This means you only use the modelview-transformed point (without projection) to compute the distance.

uniform mat4 MV;       //modelview matrix

vec3 eyePos = MV * vec4(pos.x, pos.y, 0.5, 1);
Furthermore I don't completely understand your attenuation computation. At the moment a higher constAtten value means less attenuation. Why don't you just use the model that OpenGL's deprecated point parameters used:

float dist = length(eyePos);   //since the distance to (0,0,0) is just the length
float attn = inversesqrt(constAtten + linearAtten*dist + quadAtten*dist*dist);
EDIT: But in general I think this attenuation model is not a good way, because often you just want the sprite to keep its object space size, which you have quite to fiddle with the attenuation factors to achieve that I think.

A better way is to input its object space size and just compute the screen space size in pixels (which is what gl_PointSize actually is) based on that using the current view and projection setup:

uniform mat4 MV;                //modelview matrix
uniform mat4 P;                 //projection matrix
uniform float spriteWidth;      //object space width of sprite (maybe an per-vertex in)
uniform float screenWidth;      //screen width in pixels

vec4 eyePos = MV * vec4(pos.x, pos.y, 0.5, 1);
vec4 projCorner = P * vec4(0.5*spriteWidth, 0.5*spriteWidth, eyePos.z, eyePos.w);
gl_PointSize = screenWidth * projCorner.x / projCorner.w;
gl_Position = P * eyePos;
This way the sprite always gets the size it would have when rendered as a textured quad with a width of spriteWidth.

EDIT: Of course you also should keep in mind the limitations of point sprites. A point sprite is clipped based of its center position. This means when its center moves out of the screen, the whole sprite disappears. With large sprites (like in your case, I think) this might really be a problem.

Therefore I would rather suggest you to use simple textured quads. This way you circumvent this whole attenuation problem, as the quads are just transformed like every other 3d object. You only need to implement the rotation toward the viewer, which can either be done on the CPU or in the vertex shader
*/

