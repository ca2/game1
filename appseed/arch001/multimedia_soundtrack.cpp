#include "framework.h"


namespace multimedia
{


   sound_track::sound_track(::aura::application * papp):
      object(papp),
      ::multimedia::audio_decode::playground(papp),
      ::multimedia::decoder(papp),
      m_eventEnd(papp)
   {



      if (!initialize_wave_player(::multimedia::audio::purpose_default))
      {

         throw resource_exception(get_app());

      }

      m_pdecoderplugin = get_wave_player()->m_decoderset.LoadPlugin("audio_decode_wave");

      ::multimedia::audio::wave_player_command c;

      c.OpenDecoder(this);

      get_wave_player()->DecoderOpen(c);

      c.Play(0, imedia::position(0),false);

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

   ::file::buffer_sp sound_track::sound_file(const char * psz)
   {

      ::file::buffer_sp & file = m_mapFile[psz];

      if(!file.is_set())
      {

         file = Application.file().get_file(sound_path(psz),::file::type_binary | ::file::mode_read);

      }

      return file;

   }

   ::multimedia::audio_decode::decoder * sound_track::sound_decoder(const char * psz)
   {

      array<::multimedia::audio_decode::resampler *> & decodera = m_mapDecoder[psz];

      int i = decodera.pred_find_first([](::multimedia::audio_decode::decoder *p) {return p->DecoderEOF();});

      if(i >= 0)
      {
         decodera[i]->DecoderInitialize(NULL, false);
         decodera[i]->DecoderSeekBegin();
         return decodera[i];

      }


      if(m_pdecoderplugin == NULL)
         return NULL;

      ::multimedia::audio_decode::decoder * pdecoder = dynamic_cast <::multimedia::audio_decode::decoder *>( m_pdecoderplugin->NewDecoder());

      pdecoder->DecoderInitialize(sound_file(psz),false);

      ::multimedia::audio_decode::resampler * presampler = new ::multimedia::audio_decode::resampler(get_app());

      presampler->m_pdecoder = pdecoder;

      pdecoder->m_bLoop = false;

      presampler->DecoderInitialize(NULL, false);

      presampler->m_pdecoder->DecoderSeekBegin();


      decodera.add(presampler);




      return presampler;

   }

   void sound_track::queue(const char * psz)
   {
      synch_lock sl(&m_mutex);

      m_eventEnd.ResetEvent();

      if(string(psz) == string(""))
      {
         m_str = "";
      }
      else if(m_str != "intermission")
      {

         if(!::str::begins_ci(m_str,"wait:"))
         {

            m_str = psz;

         }

      }

      string str(psz);

      bool bWait = ::str::begins_eat_ci(str,"wait:");

      bool bNoLoop = ::str::begins_eat_ci(str,"noloop:");


      auto pdecoder = sound_decoder(str);

      

      init_child(pdecoder);

      m_decoderptra.add(pdecoder);

      m_bEof = false;


   }

   void sound_track::DecoderOnEvent(e_event eevent)
   {
      if(eevent == event_eof)
      {
         m_eventEnd.SetEvent();
      }
   }


} // namespace multimedia











