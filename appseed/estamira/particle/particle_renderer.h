#pragma once


namespace particle
{


   class system;


   class CLASS_DECL_ESTAMIRA renderer :
      virtual public ::object
   {
   public:
      renderer(::aura::application * papp) : ::object(papp) { }
      virtual ~renderer() { }

      virtual void generate(::draw2d::graphics * pgraphics, class system *sys, bool useQuads) = 0;
      virtual void destroy() = 0;
      virtual void update(::draw2d::graphics * pgraphics, class system *sys) = 0;
      virtual void render(::draw2d::graphics * pgraphics, float cx, float cy, class system *sys) = 0;
   };


   class CLASS_DECL_ESTAMIRA renderer_factory :
      virtual public ::object
   {
   public:

      renderer_factory(::aura::application * papp) : ::object(papp) {}

      renderer * create(const char *name);

   };


}  // namespace particle



