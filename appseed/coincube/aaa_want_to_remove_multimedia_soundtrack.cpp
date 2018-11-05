#include "framework.h"


namespace multimedia
{


   sound_track::sound_track(::aura::application * papp):
      object(papp),
      ::multimedia::audio_decode::decoder(papp),
      ::multimedia::audio_decode::mixer(papp),
      ::multimedia::decoder(papp)
   {
      
      defer_create_mutex();

      m_bNonStopOnEof = true;
      m_bRemoveOnChildEof = true;


      if (!initialize_wave_player(::multimedia::audio::purpose_playground))
      {

         throw resource_exception(papp);

      }

      m_pdecoderplugin = get_wave_player()->m_decoderset.LoadPlugin("audio_decode_wave");

      ::multimedia::audio::wave_player_command c;

      c.OpenDecoder(this);

      get_wave_player()->DecoderOpen(c);

      c.Play(0, imedia_position(0),false);

      get_wave_player()->ExecuteCommand(c);


   }

   
   sound_track::~sound_track()
   {
      
   }
   

   string sound_track::sound_path(const char * psz)
   {

      string strFileName = string(psz) + string(".wav");

      string strFilePath = Application.dir().matter(strFileName);

      return strFilePath;

   }

   
   ::file::file_sp sound_track::sound_file(const char * psz)
   {

      //::file::file_sp & file = m_mapFile[psz];
      ::file::file_sp file;

      //if(!file.is_set())
      {

         file = Application.file().get_file(sound_path(psz),::file::type_binary | ::file::mode_read | ::file::share_deny_write);

      }

      return file;

   }

   ::multimedia::audio_decode::resampler * sound_track::sound_decoder(const char * psz)
   {

      synch_lock sl(m_pmutex);
      
      spa(::multimedia::audio_decode::resampler) & decodera = m_mapDecoder[psz];

      int i = decodera.pred_find_first([](::multimedia::audio_decode::resampler *p) {return p->audio_plugin_eof();});

      if(i >= 0)
      {
         decodera[i]->audio_plugin_initialize(NULL, false);

         return decodera[i];

      }

      if(m_pdecoderplugin == NULL)
         return NULL;

      auto presampler = new ::multimedia::audio_decode::resampler(get_app());
      
      presampler->m_pdecoder = m_pdecoderplugin->NewDecoder();

      presampler->m_pdecoder->audio_plugin_initialize(sound_file(psz),false);

      presampler->m_pdecoder->m_bLoop = false;

      presampler->audio_plugin_initialize(NULL, false);

      decodera.add(presampler);

      return presampler;

   }

   void sound_track::queue(const char * psz)
   {
      
      synch_lock sl(m_pmutex);

      string str(psz);
      
      ::str::begins_eat_ci(str, "wait:");

      auto pdecoder = sound_decoder(str);

      pdecoder->audio_plugin_seek_begin();

      pdecoder->m_pdecoder->audio_plugin_seek_begin();

      init_child(pdecoder);
      
      m_decoderptra.add(pdecoder);

      m_bEof = false;


   }


} // namespace multimedia











