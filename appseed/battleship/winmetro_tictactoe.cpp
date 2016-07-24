#include "core/core/core.h"



[MTAThread]
int main(Array<String^>^)
{

   /*return app_core_main("m_app.exe : app=app/sphere/userstack app=app-cidadedecuritiba/alphaclock app=app-core/projection app-core/projection.countries=br,ru,us,se,jp \
   app-core/projection.br.link=\"http://ca2.etc.br\" app-core/projection.ru.link=\"http://ca2.ru\" app-core/projection.us.link=\"http://ca2.us\" app-core/projection.se.link=\"http://ca2.se\" app-core/projection.jp.link=\"http://ca2.jp\" \
   app=app-core/flag app-core/flag.file=\"http://ca2.se/image/_std/domain/symbol/se.png\" app=app-core/hellomultiverse build_number=\"basis\"");*/

   return app_core_main("m_app.exe : app=game/tictactoe client_only \"bk.tictactoe::view\"=\"https://ca2.cc/image/_std/cc/ca2core/bkimageoftheday/common/02209_stratosphere_1920x1080_o.JPG?sessid=noauth\"");

}


