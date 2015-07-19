#pragma once




namespace tictactoe
{

   
   class document;

   
   class CLASS_DECL_GAME_TICTACTOE view :
      public ::user::impact
   {
   public:

      enum e_check
      {

         check_none,
         check_x,
         check_o

      };

      e_check                 m_echeck;
      string                  m_strServer;
      mutex                   m_mutexWork;
      mutex                   m_mutexDraw;
      mutex                   m_mutexSwap;
      
      ::visual::dib_sp        m_dibBk;
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

      array < array < e_check > > m_check2aBoard;


      view(::aura::application * papp);
	   virtual ~view();

   #ifdef DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif


      void reset_board();

      void get_board_rect(LPRECT lprect);
      void get_check_rect(LPRECT lprect,int i,int j);
      bool hit_test_check(int & i, int & j, point pt);
      bool match(int i,int j);
      bool match();



      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::graphics * pdc);
      virtual void tictactoe_render(::draw2d::graphics * pdc);

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint);

      ::user::document * get_document();
      
      //void load_ai_font();
      void render();
      
      //static UINT thread_proc_load_ai_font(void * pparam);
      static UINT thread_proc_render(void * pparam);

      virtual void layout();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);



      virtual void draw_x(::draw2d::graphics * pdc,const RECT & lpcrect);
      virtual void draw_o(::draw2d::graphics * pdc,const RECT & lpcrect);
      virtual void draw_board(::draw2d::graphics * pdc,const RECT & lpcrect);



   };

   
} // namespace tictactoe




