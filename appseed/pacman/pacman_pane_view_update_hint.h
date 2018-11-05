#pragma once


namespace pacman
{

   enum EPaneView
   {
      PaneViewNone,
      PaneViewPacMan,
      PaneViewFileManager,
      PaneViewHelp
   };


   class CLASS_DECL_APP_CORE_PACMAN pane_view_update_hint :
      public object
   {
   public:
      enum e_type
      {
         TypeGetView,
         TypeSetView,
         TypeOnShowKaraoke,
         TypeOnShowView,
      };
   public:
      void set_type(e_type e_type);
      bool is_type_of(e_type e_type);

      pane_view_update_hint();
      virtual ~pane_view_update_hint();

      EPaneView m_eview;
   protected:
      e_type m_etype;

   };

} // namespace pacman
