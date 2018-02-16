#pragma once


namespace arkanoid
{


   class CLASS_DECL_GAME_ARKANOID application :
      virtual public ::estamira::application
   {
   public:


      sp(::user::single_document_template)  m_ptemplateArkanoidMain;
      sp(::user::single_document_template)  m_ptemplateArkanoidView;


      application();
      virtual ~application();


      virtual bool init_instance() override;
      virtual void term_instance() override;

      virtual void on_request(::create * pcreate);


   };


} // namespace arkanoid





