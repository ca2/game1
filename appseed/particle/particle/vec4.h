#pragma once


template <typename T>
struct tvec4
{

   union
   {
      T m[4];

      struct
      {
         T x, y, z, w;
      };

      struct
      {
         T r, g, b, a;
      };
   };




   tvec4() = default;
   tvec4(float f) { x = y = z = f; };
   tvec4(const tvec4 & v) = default;
   tvec4(tvec4 && v) = default;
   tvec4(T a, T b) { x = a; y = b; z = 0.0f; w = 0.0f; }
   tvec4(T a, T b, T c) { x = a; y = b; z = c; w = 0.0f; }
   tvec4(T a, T b, T c, T d) { x = a; y = b; z = c; w = d; }
   ~tvec4() = default;

   tvec4 & operator =(const tvec4 & v) = default;

   inline void setAll(T f) { x = y = z = w = f; }

   // simple menthods: operates on x, y
   inline void add2(const tvec4 & a) { x += a.x; y += a.y; }
   inline void sub2(const tvec4 & a) { x -= a.x; y -= a.y; }
   inline void mul2(const T &v) { x *= v; y *= v; }
   inline void set2(T a, T b) { x = a; y = b; }

   static inline void mix2(const tvec4 &a, const tvec4 &b, T t, tvec4 &c)
   {
      c.x = a.x*((T)1.0 - t) + b.x*t;
      c.y = a.y*((T)1.0 - t) + b.y*t;
   }

   // simple menthods: operates on x, y, z
   inline void add3(const tvec4 & a) { x += a.x; y += a.y; z += a.z; }
   inline void sub3(const tvec4 & a) { x -= a.x; y -= a.y; z -= a.z; }
   inline void mul3(const T &v) { x *= v; y *= v; z *= v; }
   inline void set3(T a, T b, T c) { x = a; y = b; z = c; }

   static inline void mix3(const tvec4 &a, const tvec4 &b, T t, tvec4 &c)
   {
      c.x = a.x*((T)1.0 - t) + b.x*t;
      c.y = a.y*((T)1.0 - t) + b.y*t;
      c.z = a.z*((T)1.0 - t) + b.z*t;
   }

   // simple menthods: operates on x, y, z, w
   inline void add4(const tvec4 & a) { x += a.x; y += a.y; z += a.z; w += a.w; }
   inline void sub4(const tvec4 & a) { x -= a.x; y -= a.y; z -= a.z; w -= a.w; }
   inline void mul4(const T &v) { x *= v; y *= v; z *= v; w *= v; }
   inline void set4(T a, T b, T c, T d) { x = a; y = b; z = c; w = d; }

   static inline void mix4(const tvec4 &a, const tvec4 &b, T t, tvec4 &c)
   {
      c.x = a.x*((T)1.0 - t) + b.x*t;
      c.y = a.y*((T)1.0 - t) + b.y*t;
      c.z = a.z*((T)1.0 - t) + b.z*t;
      c.w = a.w*((T)1.0 - t) + b.w*t;
   }

   inline tvec4 operator *(const T & t) const
   {
      return tvec4(x * t, y * t, z * t, w * t);

   }

   inline tvec4 operator /(const T & t) const
   {
      return tvec4(x / t, y / t, z / t, w / t);

   }

   inline tvec4 operator +(const tvec4 & t) const
   {
      return tvec4(x + t.x, y + t.y, z + t.z, w + t.w);
   }

   inline tvec4 operator -(const tvec4 & t) const
   {
      return tvec4(x - t.x, y - t.y, z - t.z, w - t.w);
   }

   inline tvec4 & operator +=(const tvec4 & a)
   {
      add4(a);
      return *this;
   }
   inline tvec4 & operator -=(const tvec4 & a)
   {
      sub4(a);
      return *this;
   }

   inline T dot(const tvec4 & t) const
   {
      return x * t.x + y * t.y + z * t.z + w * t.w;
   }

};




using vec4 = tvec4 < float >;

inline vec4 operator * (float f, const vec4 & v)
{

   return vec4(f * v.x, f * v.y, f *v.z, f * v.w);
}


template < typename T >
inline T linear_rand(const T & t1, const T & t2)
{
   if (t2 == t1)
      return t1;
   return ((t2 - t1) * rand()/ RAND_MAX) + t1;

}

template < >
inline vec4 linear_rand(const vec4 & t1, const vec4 & t2)
{

   return vec4(
          linear_rand(t1.x, t2.x),
          linear_rand(t1.y, t2.y),
          linear_rand(t1.z, t2.z),
          linear_rand(t1.w, t2.w));

}