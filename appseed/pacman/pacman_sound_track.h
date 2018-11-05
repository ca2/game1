#pragma once


namespace pacman
{


   class sound_track :
      virtual public ::multimedia::audio::wave_player_container,
      virtual public ::multimedia::audio_plugin::playground,
      virtual public ::multimedia::audio::wave_player::listener
   {
   public:

      sp(::multimedia::audio_decode::decoder_plugin) m_pdecoderplugin;


      //::multimedia::audio_decode::resampler * m_presampler;
      manual_reset_event      m_eventEnd;
      string_map < ::multimedia::audio_plugin::plugin * > m_mapPlugin;
      string_map < ::file::file_sp > m_mapFile;
      stringa        m_straMode;
      
      sound_track(::aura::application * papp);
      virtual ~sound_track();

      ::multimedia::audio_plugin::plugin * sound_plugin(const char *);
      ::file::file_sp sound_file(const char *);
      string sound_path(const char *);
      void queue(const char *);


      virtual void audio_plugin_on_event(e_event eevent) override;

      virtual void OnWavePlayerEvent(::multimedia::audio::wave_player * pplayer,::multimedia::audio::wave_player::e_event event,::multimedia::audio::wave_player_command * pcommand = NULL) override;

   };


} // namespace pacman
