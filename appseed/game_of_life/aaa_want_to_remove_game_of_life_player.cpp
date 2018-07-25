#include "framework.h"



namespace tictactoe
{



   player::player(::aura::application * papp):
      object(papp)
   {


   }


   player::~player()
   {


   }


   void player::play()
   {


   }


   void player::set_ready()
   {

      m_parbitrator->m_evReady.SetEvent();

   }


} // namespace tictactoe





