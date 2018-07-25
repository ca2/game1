#pragma once


namespace game_of_life
{


   class CLASS_DECL_GAME_GAME_OF_LIFE application :
      virtual public ::estamira::application
   {
   public:


      sp(::user::single_document_template)  m_ptemplateHelloMultiverseMain;
      sp(::user::single_document_template)  m_ptemplateHelloMultiverseView;


      application();
      virtual ~application();


      virtual bool init_instance() override;
      virtual void term_instance() override;

      virtual void on_request(::create * pcreate);


   };


} // namespace game_of_life





