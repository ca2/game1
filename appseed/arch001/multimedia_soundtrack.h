#pragma once


namespace multimedia
{


   class sound_track:
      virtual public ::multimedia::audio::wave_player_container,
      virtual public ::multimedia::audio_decode::playground
   {
   public:

      sp(::multimedia::audio_decode::decoder_plugin) m_pdecoderplugin;


      manual_reset_event      m_eventEnd;
      string_map < array<::multimedia::audio_decode::resampler *> > m_mapDecoder;
      string_map < ::file::file_sp > m_mapFile;

      sound_track(::aura::application * papp);
      virtual ~sound_track();

      ::multimedia::audio_decode::decoder * sound_decoder(const char *);
      ::file::file_sp sound_file(const char *);
      string sound_path(const char *);
      void queue(const char *);


      virtual void DecoderOnEvent(e_event eevent);

   };


} // namespace multimedia