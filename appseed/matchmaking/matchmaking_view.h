#pragma once


namespace matchmaking
{


   class CLASS_DECL_APP_CORE_MATCHMAKING view :
      virtual public ::user::impact
   {
   public:

      double m_dFps;
      DWORD m_dwRoll;

      string_map < ::draw2d::dib_sp >       m_map;

      sp(pcre_util) m_ppcreutil;


      enum e_effect
      {

         effect_none,
         effect_crt,

      };

      string m_strNewFont;
      string m_strFont;
      e_effect                m_eeffect;

      //main_view *             m_pmainview;
      ::visual::dib_sp        m_dibBk;
      ::visual::dib_sp        m_dibTime;


      string                  m_strServer;
      mutex                   m_mutexText;
      ::visual::dib_sp        m_dibAi1;
      ::visual::dib_sp        m_dibAi2;

      string                  m_strImage;
      ::draw2d::dib_sp        m_dibPost;
      ::draw2d::dib_sp        m_dibColor;
      ::visual::dib_sp        m_dibFast;

      string                  m_strNewHelloMultiverse;
      string                  m_strHelloMultiverse;
      bool                    m_bOkPending;
      DWORD                   m_dwLastOk;
      DWORD                   m_dwAnime;
      DWORD                   m_dwLastFast;
      DWORD                   m_dwFastAnime;
      bool                    m_bFast;
      bool                    m_bFastOnEmpty;


      bool                    m_bHelloLayoutOn001Layout;
      bool                    m_b001LayoutIgnoreEmpty;


      render *                m_prender;

      manual_reset_event *    m_pevRenderEnd;



      view(::aura::application * papp);
      virtual ~view();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual void install_message_handling(::message::dispatch * pdispatch);


      virtual void _001OnPostProcess(::draw2d::dib * pdib);

      virtual void _001OnHelloDraw(::draw2d::dib * pdib);
      virtual void _001OnDraw(::draw2d::dib * pdib);

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint);

      ::user::document * get_document();

      virtual void matchmaking_fast_render(const string & strHelloMultiverse);


      virtual void layout();

      DECL_GEN_SIGNAL(_001OnLayout);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);

      virtual string get_matchmaking();

      virtual string get_processed_matchmaking();

      virtual bool in_anime();

      virtual int64_t add_ref()
      {
         return ::object::add_ref();
      }
      virtual int64_t dec_ref()
      {
         return ::object::dec_ref();
      }

      ::draw2d::dib * get_map(string str);

   };


} // namespace matchmaking





















