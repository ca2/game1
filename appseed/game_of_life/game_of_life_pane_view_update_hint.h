#pragma once


namespace game_of_life
{

   enum EPaneView
   {
      PaneViewNone,
      PaneViewHelloMultiverse,
      PaneViewFileManager,
   };


   class CLASS_DECL_GAME_GAME_OF_LIFE pane_view_update_hint :
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

} // namespace game_of_life
