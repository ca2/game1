#include "framework.h"


namespace pacman
{


   sound_track::sound_track(::aura::application * papp):
      object(papp),
      ::multimedia::audio_decode::track(papp),
      ::multimedia::decoder(papp),
      m_eventEnd(papp)
   {

      m_presampler = new ::multimedia::audio_decode::resampler(get_app());


      m_pwaveplayer = new ::multimedia::audio::wave_player(get_app());

      if(!m_pwaveplayer->begin_synch())
         return;

      m_pdecoderplugin = get_wave_player()->m_decoderset.LoadPlugin("audio_decode_wave");

      ::multimedia::audio::wave_player_command c;

      c.OpenDecoder(this);

      get_wave_player()->DecoderOpen(c);

      c.Play(imedia::position(0), false);

      get_wave_player()->ExecuteCommand(c);


   }

   sound_track::~sound_track()
   {
   }
   
   string sound_track::sound_path(const char * psz)
   {
   
      string strFileName = string("pacman_") + psz + string(".wav");
   
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

      ::multimedia::audio_decode::decoder * & pdecoder = m_mapDecoder[psz];

      if(pdecoder == NULL)
      {
         
         if(m_pdecoderplugin == NULL)
            return NULL;

         pdecoder = m_pdecoderplugin->NewDecoder();

         pdecoder->DecoderInitialize(sound_file(psz),false);


      }

      return pdecoder;

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


         m_presampler->m_pdecoder = sound_decoder(str);

         init_child(m_presampler);

         m_presampler->DecoderInitialize(NULL,false);

         m_decoderptra.remove_all();

         m_iDecoder = 0;

         if(bWait)
         {
            m_presampler->m_pdecoder->DecoderSeekBegin();

            m_presampler->m_bLoop = false;
         }
         else
         {
            
            m_presampler->m_bLoop = true;

         }

         m_decoderptra.add(m_presampler);

         m_bEof = false;

   
      }

   void sound_track::DecoderOnEvent(e_event eevent)
   {
      if(eevent == event_eof)
      {
         m_eventEnd.SetEvent();
      }
   }


} // namespace pacman











