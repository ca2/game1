#include "framework.h"


namespace pacman
{


   sound_track::sound_track(::aura::application * papp):
      object(papp),
      ::multimedia::audio_decode::playground(papp),
      ::multimedia::decoder(papp),
      m_eventEnd(papp)
   {

      m_straMode.add("intermission");
      m_straMode.add("chomp");

      m_bNonStopOnEof =true;

      
      if (!initialize_wave_player(::multimedia::audio::purpose_playground))
      {

         return;

      }

      get_wave_player()->add_listener(this);

      m_pdecoderplugin = get_wave_player()->m_decoderset.LoadPlugin("audio_decode_wave");

      ::multimedia::audio::wave_player_command c;

      c.OpenDecoder(this);

      get_wave_player()->DecoderOpen(c);

      c.Play(0, 0, false);

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

         file = Application.file().get_file(sound_path(psz),::file::type_binary | ::file::mode_read | ::file::share_deny_none);

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

         sp(::multimedia::audio_decode::decoder) pdecoderFile = m_pdecoderplugin->NewDecoder();

         string str(psz);

         ::str::begins_eat_ci(str,"wait:");

         pdecoderFile->DecoderInitialize(sound_file(str),false);

         ::multimedia::audio_decode::resampler * presampler = new ::multimedia::audio_decode::resampler(get_app());

         presampler->m_pdecoder = pdecoderFile;

         pdecoder = presampler;

         presampler->DecoderInitialize(NULL,false);

      }
      

      return pdecoder;

   }

   void sound_track::queue(const char * psz)
      {

         synch_lock sl(&m_mutex);
   
         m_eventEnd.ResetEvent();

         string str(psz);
         
         if(str.is_empty())
         {

            m_str = "";

            return;

         }

         bool bWait = ::str::begins_ci(str,"wait:");

         ::multimedia::audio_decode::decoder * pdecoder = sound_decoder(str);

         if(m_decoderptra.get_count() > 0 && !m_decoderptra[0]->DecoderEOF() && m_straMode.contains(str))
         {

            if(::str::begins_ci(m_str,"wait:"))
            {

               return;

            }

         }


         if(m_str == str)
         {

            return;

         }
         else
         {

            m_str = str;

            pdecoder->m_bKick = true;

         }
         

         m_bEof = false;

         init_child(pdecoder);

         if(bWait)
         {
            
            pdecoder->DecoderSeekBegin();

            pdecoder->m_bLoop = false;
            
         }
         else
         {
            
            pdecoder->m_bLoop = true;

            //if(m_straMode.contains(m_str))
            //{

            //   pdecoder->m_bKick = false;

            //}

         }

         ::output_debug_string(str + "\n");

         m_decoderptra.add(pdecoder);


   
      }

   void sound_track::DecoderOnEvent(e_event eevent)
   {
      if(eevent == event_eof)
      {
         m_eventEnd.SetEvent();
//         m_eventEnd.SetEvent();
      }
   }

   void sound_track::OnWavePlayerEvent(::multimedia::audio::wave_player * pplayer,::multimedia::audio::wave_player::e_event eevent,::multimedia::audio::wave_player_command * pcommand)
   {

      if(eevent == ::multimedia::audio::wave_player::EventPlaybackEnd)
      {

         

      }

   }

} // namespace pacman











