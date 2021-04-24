// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define _STATIC_CPPLIB
#define _CRT_SECURE_NO_DEPRECATE

#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <atlstr.h>
#include <atlbase.h>
#include <atlapp.h>

#if (_ATL_VER < 0x0300)
extern CAppModule _Module;
#endif

#include <atlwin.h>
#include <atlctrls.h>

#include <commctrl.h>
#include <stdlib.h>
#include <shellapi.h>
#include <memory>
using namespace std;

#include <atlctrlx.h>

// TODO: reference additional headers your program requires here
#include "../SDK/foobar2000/SDK/foobar2000.h"
using namespace pfc;

#include <comdef.h>