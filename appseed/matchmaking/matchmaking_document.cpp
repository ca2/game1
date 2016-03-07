#include "framework.h"


namespace matchmaking
{


   document::document(::aura::application * papp) :
      object(papp),
      ::data::data_container_base(papp),
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

      view * pview = get_typed_view < view >();

      string strPath = varFile.get_string();

      varFile["url"] = strPath;

      varFile["http_set"]["raw_http"] = System.url().get_server(varFile["url"]).find_wci("ca2") < 0 || System.url().query_get_param( System.url().get_query(varFile["url"]), "sessid") == "noauth";
      varFile["http_set"]["disable_common_name_cert_check"] = true;

      string str;

      if(pview->m_prender->m_dibImage.load_from_file(varFile))
      {

         get_typed_view < view >()->m_strImage = varFile["url"];

         {

            synch_lock slText(get_typed_view < view >() != NULL  ? &get_typed_view < view >()->m_mutexText : NULL);

            get_typed_view < view >()->m_strHelloMultiverse = "image:" + get_typed_view < view >()->m_strImage + "," + get_typed_view < view >()->m_strHelloMultiverse;

         }

      }
      else if(get_typed_view < ::user::plain_edit_view >() != NULL
              && Application.file().exists(varFile)
              && (str = Application.file().as_string(varFile)).has_char())
      {

         get_typed_view < ::user::plain_edit_view >()->_001SetText(str.Left(84),::action::source_user);

      }
      else if(get_typed_view < ::userex::pane_tab_view >() != NULL)
      {

         get_typed_view < ::userex::pane_tab_view >()->set_cur_tab_by_id(::matchmaking::PaneViewHelloMultiverse);

      }

      return true;

   }


   int64_t document::add_ref()
   {

      return  ::user::document::add_ref();

   }

   int64_t document::dec_ref()
   {

      return  ::user::document::dec_ref();

   }



} // namespace matchmaking

















