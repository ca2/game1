#include "framework.h"


namespace arch001
{

   game::game(::aura::application * papp) :
      object(papp),
      ::estamira::game(papp)
   {
   }

   game::~game()
   {

   }

   //void game::install_message_routing(::message::sender * psender)
   //{
   //   IGUI_MSG_LINK(WM_KEYDOWN, psender, this, &game::_001OnKeyDown);
   //   IGUI_MSG_LINK(WM_KEYUP, psender, this, &game::_001OnKeyUp);

   //}


   bool game::start(::user::interaction * pui)
   {

      if (!::estamira::game::start(pui))
      {
         
         return false;

      }

      remove_all_characters();

      add_new_character("male");

      auto * p = add_new_character("male");

      p->m_ekeyLeft = ::user::key_z;
      p->m_ekeyRight = ::user::key_x;
      p->m_ekeyUp = ::user::key_s;


      return true;

   }

   //void game::_001OnKeyDown(::message::message * pobj)
   //{
   //   SCAST_PTR(::message::key, pkey, pobj);

   //}

   //void game::_001OnKeyUp(::message::message * pobj)
   //{
   //   SCAST_PTR(::message::key, pkey, pobj);


   //}
} // namespace arch001



