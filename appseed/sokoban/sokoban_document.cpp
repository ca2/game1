#include "framework.h"


namespace sokoban
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
      
      synch_lock sl(m_pmutex);

      ::file::listing listing(get_app());

      Application.dir().matter_ls("sok", listing);

      if(listing.get_count() > 0)
      {

         return on_open_document(listing[0]);

      }

      return true;

   }


   bool document::on_open_document(var varFile)
   {

      string str = Application.file().as_string(varFile);

      stringa stra;

      stra.add_lines(str);

      bool bLevel = false;

      stringa straLevel;

      for(index i = 0; i < stra.get_size(); i++)
      {

         string & strLine = stra[i];

         if(strLine.find("#")>= 0)
         {
            bLevel = true;

            if(strLine.find_ci("<L>")>=0)
            {
               strLine.trim_left();
               strLine.replace_ci("<L>", "");
            }
            strLine.replace_ci("</L>","");

            straLevel.add(strLine);
         }
         else
         {
            if(bLevel)
            {
               sp(level) spl = canew(level(get_app()));
               spl->m_stra = straLevel;
               spl->m_iLevel = m_levela.get_count();
               spl->initialize();
               m_levela.add(spl);
               straLevel.remove_all();
               bLevel = false;
            }
         }

      }

      update_all_views(NULL,123);

      return true;

   }


} // namespace sokoban












