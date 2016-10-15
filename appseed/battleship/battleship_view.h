#pragma once




namespace tictactoe
{


   class document;


   class CLASS_DECL_GAME_TICTACTOE view :
      virtual public ::user::impact,
      virtual public player
   {
   public:


      string                  m_strServer;
      mutex                   m_mutexWork;
      mutex                   m_mutexDraw;
      mutex                   m_mutexSwap;

      ::draw2d::dib_sp        m_dibBk;
      ::draw2d::dib_sp        m_dib1;
      ::draw2d::dib_sp        m_dib2;
      bool                    m_bDib1;

      ::visual::fastblur      m_dib;
      ::draw2d::dib_sp        m_dibColor;
      ::visual::dib_sp        m_dibWork;

      ::draw2d::font_sp       m_font;
      string                  m_strHelloMultiverse;
      int32_t                 m_iErrorAiFont;
      void *                  m_faceAi; // FT_Face m_faceAi;


      ::rect                  m_rectSpace;
      ::rect                  m_rectCheckSpace;

      byte                    m_bBkAlpha;


      view(::aura::application * papp);
	   virtual ~view();

   #ifdef DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif


      void get_board_rect(LPRECT lprect);
      void get_check_rect(LPRECT lprect,int i,int j);
      bool hit_test_check(int & i, int & j, point pt);



      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);
      virtual void tictactoe_render(::draw2d::graphics * pgraphics);

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint);

      ::user::document * get_document();

      //void load_ai_font();
      void render();

      //static UINT thread_proc_load_ai_font(void * pparam);
      static UINT thread_proc_render(void * pparam);

      virtual void on_layout();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnNewGame);



      virtual void draw_x(::draw2d::graphics * pgraphics,const RECT & lpcrect);
      virtual void draw_o(::draw2d::graphics * pgraphics,const RECT & lpcrect);
      virtual void draw_board(::draw2d::graphics * pgraphics,const RECT & lpcrect);

      virtual void new_game();

   };


} // namespace tictactoe




