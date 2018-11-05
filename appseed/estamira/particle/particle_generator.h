#pragma once


namespace particle
{


   namespace generator
   {


      namespace position
      {


         class CLASS_DECL_ESTAMIRA box : public generator
         {
         public:

            vec4 m_pos;
            vec4 m_maxStartPosOffset;

            box(::aura::application * papp) : ::object(papp), generator(papp), m_pos(0.0), m_maxStartPosOffset(0.0) { }

            virtual void generate(double dt, data *p, size_t startId, size_t endId) override;


         };


         class CLASS_DECL_ESTAMIRA round : public generator
         {
         public:


            vec4 m_center;
            float m_radX;
            float m_radY;


            round(::aura::application * papp) : ::object(papp), generator(papp), m_center(0.0), m_radX(0.0), m_radY(0.0) { }
            round(::aura::application * papp, const vec4 &center, double radX, double radY)
               :  ::object(papp), generator(papp),
                  m_center(center)
               , m_radX((float)radX)
               , m_radY((float)radY)
            { }

            virtual void generate(double dt, data *p, size_t startId, size_t endId) override;

         };


      } // namespace position


      namespace color
      {


         class CLASS_DECL_ESTAMIRA basic : public generator
         {
         public:
            vec4 m_minStartCol;
            vec4 m_maxStartCol;
            vec4 m_minEndCol;
            vec4 m_maxEndCol;
         public:
            basic(::aura::application * papp) : ::object(papp), generator(papp), m_minStartCol(0.0), m_maxStartCol(0.0), m_minEndCol(0.0), m_maxEndCol(0.0) { }

            virtual void generate(double dt, data *p, size_t startId, size_t endId) override;
         };

      } // namespace color


      namespace velocity
      {

         class CLASS_DECL_ESTAMIRA basic : public generator
         {
         public:
            vec4 m_minStartVel;
            vec4 m_maxStartVel;
         public:
            basic(::aura::application * papp) : ::object(papp), generator(papp), m_minStartVel(0.0), m_maxStartVel(0.0) { }

            virtual void generate(double dt, data *p, size_t startId, size_t endId) override;
         };

         class CLASS_DECL_ESTAMIRA sphere : public generator
         {
         public:
            float m_minVel;
            float m_maxVel;
         public:
            sphere(::aura::application * papp) : ::object(papp), generator(papp), m_minVel(0.0), m_maxVel(0.0) { }

            virtual void generate(double dt, data *p, size_t startId, size_t endId) override;
         };

         class CLASS_DECL_ESTAMIRA from_pos : public generator
         {
         public:
            vec4 m_offset;
            float m_minScale;
            float m_maxScale;
         public:
            from_pos(::aura::application * papp) : ::object(papp), generator(papp), m_offset(0.0), m_minScale(0.0), m_maxScale(0.0) { }
            from_pos(::aura::application * papp, const vec4 &off, double minS, double maxS)
               : ::object(papp), generator(papp),
                 m_offset(off)
               , m_minScale((float)minS)
               , m_maxScale((float)maxS)
            { }

            virtual void generate(double dt, data *p, size_t startId, size_t endId) override;
         };


      } // namespace velocity


      namespace time
      {

         class CLASS_DECL_ESTAMIRA basic : public generator
         {
         public:
            float m_minTime;
            float m_maxTime;
         public:
            basic(::aura::application * papp) : ::object(papp), generator(papp), m_minTime(0.0), m_maxTime(0.0) { }

            virtual void generate(double dt, data *p, size_t startId, size_t endId) override;
         };

      }


   } // namespace generator


} // namespace particle




