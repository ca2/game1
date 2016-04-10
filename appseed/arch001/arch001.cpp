#include "framework.h"


#ifdef METROWIN
[MTAThread]
#endif
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   UNREFERENCED_PARAMETER(hInstance);
   UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {
      ::OutputDebugStringW(L"::core:: arch001.dll :: initializing!\n");
      

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
      ::OutputDebugStringW(L"::core:: arch001.dll :: terminating!\n");
   }
   return 1;   // ok
}


