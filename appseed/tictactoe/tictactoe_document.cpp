#include "framework.h"


namespace tictactoe
{


   document::document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::user::controller(papp),
      ::user::document(papp)
   {

   }


   document::~document()
   {

   }


   void document::assert_valid() const
   {

      ::user::document::assert_valid();

   }

   void document::dump(dump_context & dumpcontext) const
   {

      ::user::document::dump(dumpcontext);

   }



   bool document::on_new_document()
   {

      return ::user::document::on_new_document();

   }


   bool document::on_open_document(var varFile)
   {

      return true;

   }


} // namespace tictactoe












