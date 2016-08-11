#pragma once


namespace sokoban
{


   class CLASS_DECL_APP_CORE_SOKOBAN document :
      public ::user::document
   {
   public:


      spa(level)       m_levela;


      document(::aura::application * papp);
	   virtual ~document();

      
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;

      virtual bool on_new_document();
      virtual bool on_open_document(var varFile);


   };


} // namespace sokoban











