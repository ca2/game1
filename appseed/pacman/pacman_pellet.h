

namespace pacman
{

   

   class pellet :
      virtual public console_composite
   {
   public:
      
      int y,x;

      LEVEL & level;


      pellet(pacman * ppacman);


      void print();

   };


} // namespace pacman



