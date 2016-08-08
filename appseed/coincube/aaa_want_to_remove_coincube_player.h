#pragma once



namespace tictactoe
{



   class CLASS_DECL_GAME_TICTACTOE player:
      virtual public object
   {
   public:

      
      e_check                 m_echeck;
      arbitrator *            m_parbitrator;
      point                   m_ptLast;


      player(::aura::application * papp);
      virtual ~player();


      virtual void play();
      virtual void set_ready();

      

   };


} // namespace tictactoe





