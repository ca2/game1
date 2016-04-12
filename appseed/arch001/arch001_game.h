#pragma once


namespace arch001
{


   class CLASS_DECL_GAME_ARCH001 game :
      virtual public ::estamira::game
   {
   public:

      game(::aura::application * papp);
      virtual ~game();

      virtual void install_message_handling(::message::dispatch * pdispatch);

      /// virtual void _001OnDraw(::draw2d::dib * pdib);

      virtual bool start(::user::interaction * pui);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      //virtual void update_movex();


   };


} // namespace arch001



