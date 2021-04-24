#pragma once

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NON_CONFORMING_SWPRINTFS
#define _STATIC_CPPLIB

#define _WTL_NEW_PAGE_NOTIFY_HANDLERS

#define _WIN32_WINNT 0x0501
#define WINVER 0x0501

#define _ATL_NO_COM
#define _ATL_NO_SERVICE
#define _ATL_NO_COM_SUPPORT
#define _ATL_NO_PERF_SUPPORT

#include <atlstr.h>
#include <atlbase.h>
#include <atlapp.h>

#if (_ATL_VER < 0x0300)
extern CAppModule _Module;
#else
#define _Module _AtlBaseModule
#endif

#define _WTL_NO_CSTRING
#include <atlmisc.h>
#include <atlwin.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlframe.h>

#include "../SDK/foobar2000/SDK/foobar2000.h"
#include "../SDK/foobar2000/helpers/window_placement_helper.h"

#include <string>
#include <vector>
#include <map>
using namespace std;
