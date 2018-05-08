#pragma once


namespace estamira
{


   class CLASS_DECL_ESTAMIRA application :
      virtual public ::multimedia::application
   {
   public:


      sp(::estamira::game)       m_pgame;


      application();
      virtual ~application();


      virtual bool init_instance() override;
      virtual void term_instance() override;

   };


} // namespace estamira





