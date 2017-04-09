#pragma once


namespace multimedia
{


   class sound_track:
      virtual public ::multimedia::audio::wave_player_container,
      virtual public ::multimedia::audio_plugin::playground
   {
   public:

      sp(::multimedia::audio_decode::decoder_plugin) m_pdecoderplugin;


      manual_reset_event      m_eventEnd;
      string_map < array<::multimedia::audio_plugin::plugin *> > m_mapPlugin;
      string_map < ::file::file_sp > m_mapFile;

      sound_track(::aura::application * papp);
      virtual ~sound_track();

      ::multimedia::audio_plugin::plugin * sound_plugin(const char *);
      ::file::file_sp sound_file(const char *);
      string sound_path(const char *);
      void queue(const char *);


      virtual void audio_plugin_on_event(e_event eevent);

   };


} // namespace multimedia