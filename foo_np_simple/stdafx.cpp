#include "stdafx.h"
#if (_ATL_VER < 0x0300)
CAppModule _Module;

BOOL WINAPI DllMain(HMODULE hInst, ULONG ul_reason_for_call, LPVOID lpReserved)
{
	if(ul_reason_for_call == DLL_PROCESS_ATTACH){
		DisableThreadLibraryCalls(hInst);
		_Module.Init(0, hInst);
	}else if(ul_reason_for_call == DLL_PROCESS_DETACH){
		_Module.Term();
	}
	return TRUE;
}
#endif
