#pragma once


#include <math.h>


// PAC++MAN
// A C++ Console Application
// This is a C++ console application video game that I have written by myself,modeled after the classic arcade game,PAC - MAN.
// A demo can be found here: https://www.youtube.com/watch?v=nAFCtZF92UY
// No copyright infringement intended.
// https://github.com/dannye/pacplusplusman

// sprites form Pacman Code in C

namespace pacman
{

   class sound;

   class pacman :
      virtual public ::thread,
      virtual public ::console::window_composite
   {
   public:

      //mutex          m_mutex;
      sound    * m_psound;
      char level[LEVELHEIGHT][LEVELWIDTH];
      int oneuptimer = ONEUPMAX;
      int oneupcolor = ::console::WHITE;
      int pellettimer = PELLETMAX;
      int pelletcolor = ::console::WHITE;
      int ghostmode = MODEMAX;
      char m_ch;

      player m_player;
      spa2(ghost) ghosts;
      spa2(pellet) pellets;


      pacman(::console::window * p) :
         //object(p->get_app()),
         thread(p->get_app()),
         ::console::window_composite(p),
         m_player(this)
      {

         ghosts.add(canew(ghost(this)));
         ghosts.add(canew(ghost(this)));
         ghosts.add(canew(ghost(this)));
         ghosts.add(canew(ghost(this)));

         pellets.add(canew(pellet(this)));
         pellets.add(canew(pellet(this)));
         pellets.add(canew(pellet(this)));
         pellets.add(canew(pellet(this)));


         begin();
      }

      // Main
      int run();
      void mainloop();

      // Objects Manipulation
      void moveghosts();
      void updatetimers();
      void checkfordeath();
      void showall();
      void hideall();
      void initall();

      // Level Manipulation
      void loadlevel();
      void nextlevel();
      void printready();
      void gameover();


      void up(bool bPress = true);
      void down(bool bPress = true);
      void left(bool bPress = true);
      void right(bool bPress = true);


      char get_char();

      void assert_valid() const{}
      void dump(dump_context &) const{}
      void play_sound(const char *);
   };

} // namespace pacman

