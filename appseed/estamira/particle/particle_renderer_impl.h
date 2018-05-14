#pragma once


namespace particle
{


   class system;


   class CLASS_DECL_ESTAMIRA renderer_impl : public renderer
   {
   public:


      class system * m_psystem { nullptr };

      unsigned int m_bufPos{ 0 };
      unsigned int m_bufCol{ 0 };


      renderer_impl(::aura::application * papp) : ::object(papp), renderer(papp) { }
      ~renderer_impl() { destroy(); }


      void generate(::draw2d::graphics * pgraphics, class system *sys, bool useQuads) override;
      void destroy() override;
      void update(::draw2d::graphics * pgraphics, class system *sys) override;
      void render(::draw2d::graphics * pgraphics, float cx, float cy, class system *sys) override;


   };


} // namespace particle




