#pragma once


namespace arch001
{


   class CLASS_DECL_GAME_ARCH001 game :
      virtual public ::estamira::game
   {
   public:

      game(::aura::application * papp);
      virtual ~game();

//      virtual void install_message_routing(::message::sender * psender);

      /// virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual bool start(::user::impact * pview);
      //DECL_GEN_SIGNAL(_001OnKeyDown);
      //DECL_GEN_SIGNAL(_001OnKeyUp);
      //virtual void update_movex();


   };


} // namespace arch001



