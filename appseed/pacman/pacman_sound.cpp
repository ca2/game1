#include "framework.h"
//#include <mmsystem.h>
//#include <mmsystem.h>



//namespace pacman
//{
//
//
//   sound::sound(::aura::application * papp):
//      //object(p->get_app()),
//      object(papp),
//      wave_player(papp),
//      m_mutex(papp)
//   {
//
//
//
//      begin();
//   }
//
//   int sound::run()
//   {
//
//      prepare_sound();
//      WCHAR sz[2058];
//
//      single_lock sl(&m_mutex);
//      string str;
//      string strX;
//      bool bWait;
//
//      string strPlaying;
//      while(m_bRun)
//      {
//         if(!pump_message())
//            break;
//         sl.lock();
//         str = m_str;
//         strX = str;
//
//         bWait = ::str::begins_eat_ci(strX,"wait:");
//
//         if(!bWait)
//         {
//
//            sl.unlock();
//
//         }
//         if(str.is_empty())
//         {
//            if(bWait)
//            {
//
//               sl.unlock();
//
//            }
//            Sleep(5);
//            continue;
//         }
//
//         if(strPlaying.has_char())
//         {
//
//            if(strPlaying != m_str)
//            {
//
//               ExecuteStop();
//
///*               DWORD dw = LIBCALL(winmm,mciSendStringW)(L"stop " + wstring(strPlaying) + L"",NULL,0,NULL);
//               WCHAR sz[2048];
//
//               mciGetErrorStringW(
//                  dw,
//                  sz,
//                  2048
//                  );*/
//
//            }
//
//            //LIBCALL(winmm,mciSendStringW)(L"status " + wstring(strPlaying) + L" mode",sz,2048,NULL);
//
//            if(IsPlaying())
//            {
//               if(bWait)
//               {
//
//                  sl.unlock();
//
//               }
//               Sleep(5);
//               continue;
//            }
//
//         }
//
////         if(bWait)
//         if(strX.has_char())
//         {
//
//            ::multimedia::audio::wave_player_command command;
//
//            cres cr;
//            //command.m_ecommand = ::multimedia::audio::command_open_file_mp3;
//            command.OpenWavFile(Application.file().get_file(string(sound_path(strX)), ::file::type_binary | ::file::mode_read, &cr));
//
//            ExecuteCommand(command);
//
//            command.Play(imedia::position(0));
//
//            ExecuteCommand(command);
//
//
////            DWORD dw = LIBCALL(winmm,mciSendStringW)(L"play " + wstring(strX) + L" from 0 wait",NULL,0,NULL);
////            WCHAR sz[2048];
////
////            mciGetErrorStringW(
////               dw,
////               sz,
////               2048
////               );
////
//            m_str = "";
//            sl.unlock();
//
//         }
////         else
////         {
////            DWORD dw = LIBCALL(winmm,mciSendStringW)(L"play " + wstring(str) + L" from 0",NULL,0,NULL);
////            WCHAR sz[2048];
////
////            mciGetErrorStringW(
////               dw,
////               sz,
////               2048
////               );
////
////            if(dw == 0)
////            {
////               strPlaying = str;
////            }
////         }
//
//      }
//      return 0;
//   }
//
//   wstring sound::sound_path(const char * psz)
//   {
//
//      string strFileName = string("pacman_") + psz + string(".wav");
//
//      string strFilePath = Application.dir().matter(strFileName);
//
//      return wstring(strFilePath);
//
//   }
//
//   void sound::queue(const char * psz)
//   {
//      synch_lock sl(&m_mutex);
//
//
//      if(string(psz) == string(""))
//      {
//         m_str = "";
//      }
//      else if(m_str != "intermission")
//      {
//
//         if(!::str::begins_ci(m_str,"wait:"))
//         {
//
//            m_str = psz;
//
//         }
//
//      }
//
//
//
//
//
//   }
//   void sound::prepare_sound()
//   {
//
//      prepare_sound("beginning");
//      prepare_sound("death");
//      prepare_sound("chomp");
//      prepare_sound("eatfruit");
//      prepare_sound("eatghost");
//      prepare_sound("intermission");
//
//   }
//
//   void sound::prepare_sound(const char * psz)
//   {
//
////      m_map
////
////      DWORD dw= LIBCALL(winmm,mciSendStringW)(L"open \"" + sound_path(psz) + L"\" type waveaudio  alias " + wstring(psz),NULL,0,NULL);
////
////      WCHAR sz[2048];
////
////      mciGetErrorStringW(
////         dw,
////         sz,
////         2048
////         );
//
//   }
//
//
//
//} // namespace pacman
