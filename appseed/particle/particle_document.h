#pragma once


namespace particle
{


   class CLASS_DECL_GAME_PARTICLE document :
      public ::user::document
   {
   public:


      document(::aura::application * papp);
      virtual ~document();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual bool on_new_document();
      virtual bool on_open_document(var varFile);

   };


} // namespace particle











