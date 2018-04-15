#include "framework.h"


namespace pacman
{


   sound_track::sound_track(::aura::application * papp):
      object(papp),
      ::multimedia::audio_plugin::playground(papp),
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

      c.Play(0.0, false);

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

   ::file::file_sp sound_track::sound_file(const char * psz)
   {

      ::file::file_sp & file = m_mapFile[psz];

      if(!file.is_set())
      {

         file = Application.file().get_file(sound_path(psz),::file::type_binary | ::file::mode_read | ::file::share_deny_none);

      }

      return file;

   }

   ::multimedia::audio_plugin::plugin * sound_track::sound_plugin(const char * psz)
   {

      ::multimedia::audio_plugin::plugin * & pplugin = m_mapPlugin[psz];

      if(pplugin == NULL)
      {

         if(m_pdecoderplugin == NULL)
            return NULL;

         sp(::multimedia::audio_decode::decoder) pdecoderFile = m_pdecoderplugin->NewDecoder();

         string str(psz);

         ::str::begins_eat_ci(str,"wait:");

         auto file = sound_file(str);

         if (file.is_null())
         {

            return NULL;

         }

         pdecoderFile->multimedia_open(file);

         ::multimedia::audio_plugin::resampler * presampler = new ::multimedia::audio_plugin::resampler(get_app());

         presampler->m_pplugin = pdecoderFile;

         pplugin = presampler;

         presampler->audio_plugin_initialize();

      }


      return pplugin;

   }

   void sound_track::queue(const char * psz)
   {

      synch_lock sl(m_pmutex);

      m_eventEnd.ResetEvent();

      string str(psz);

      if(str.is_empty())
      {

         m_str = "";

         return;

      }

      if (m_str == "intermission")
      {

         if (str == "end:intermission")
         {

            m_str = "";

            return;

         }
         else if (str == "chomp")
         {

            return;

         }

      }

      bool bWait = ::str::begins_ci(str,"wait:");

      ::multimedia::audio_plugin::plugin * pplugin = sound_plugin(str);

      if (pplugin == NULL)
      {

         return;

      }

      if(m_pluginptra.get_count() > 0 && !m_pluginptra[0]->audio_plugin_eof() && m_straMode.contains(str))
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

         pplugin->m_bKick = true;

      }


      m_bEof = false;

      init_child(pplugin);

      if(bWait)
      {

         pplugin->audio_plugin_seek_begin();

         pplugin->m_bLoop = false;

      }
      else
      {

         pplugin->m_bLoop = true;

         //if(m_straMode.contains(m_str))
         //{

         //   pdecoder->m_bKick = false;

         //}

      }

      ::output_debug_string(str + "\n");

      m_pluginptra.add(pplugin);



   }

   void sound_track::audio_plugin_on_event(e_event eevent)
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











