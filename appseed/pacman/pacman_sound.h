#pragma once



namespace pacman
{


   class sound:
      virtual public ::multimedia::audio::wave_player
   {
   public:

      mutex          m_mutex;
      string         m_str;
      string_to_string m_map;

      sound(::aura::application * papp);



      // Main
      int run();





      void assert_valid() const{}
      void dump(dump_context &) const{}

      wstring sound_path(const char *);
      void queue(const char *);
      void prepare_sound();
      void prepare_sound(const char *);

   };

} // namespace pacman

