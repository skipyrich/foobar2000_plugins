#include "stdafx.h"
#include <time.h>

#include "resource.h"
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

#define SITE "http://www.skipyrich.com/"
#define EMAIL "skipyrich@skipyrich.com"
#define TSITE _T(SITE)
#define TEMAIL _T(EMAIL)

static const char *PLUGIN_NAME = "Now Playing Simple";

DECLARE_COMPONENT_VERSION(PLUGIN_NAME, "1.9.2", "(C) Skipy Rich <" EMAIL ">\n" SITE)

void g_format_datetime(string8 &form)
{
	t_size index = form.find_first("%datetime%");
	if(index != -1){
		__time32_t ts;
		_time32(&ts);
		struct tm stm;
		_localtime32_s(&stm, &ts);
		wchar_t stime[64];
		_wasctime_s(stime, &stm);
		wchar_t *p = stime;
		while(*p && *p >= 0x20) ++p;
		*p = 0;
		string8 str = pfc::stringcvt::string_utf8_from_wide(stime).get_ptr();
		do{
			form.remove_chars(index, 10);
			form.insert_chars(index, str, str.length());
			index = form.find_first("%datetime%", index);
		}while(index != -1);
	}
}

void g_format_datetime_param(string8& form)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	
	std::wstring s(pfc::stringcvt::string_wide_from_utf8_fast(form).get_ptr());
	boost::wregex rx(L"\\$datetime\\s*\\(\\s*'(.*?)'\\s*\\)");
	boost::wsmatch res;

	while (boost::regex_search(s, res, rx, boost::regex_constants::match_default))
	{
		std::wstring match = res.str(0);
		std::wstring fmt = res.str(1);

		wchar_t buf[256] = { 0 };
		GetDateFormat(LOCALE_CUSTOM_UI_DEFAULT, 0, &st, fmt.c_str(), buf, _countof(buf));
		wchar_t buf1[256] = { 0 };
		GetTimeFormat(LOCALE_CUSTOM_UI_DEFAULT, 0, &st, buf, buf1, _countof(buf1));

		boost::replace_all(s, match, buf1);
	}

	form = pfc::stringcvt::string_utf8_from_wide(s.c_str()).get_ptr();
}

#include "cfg_vars.h"

HANDLE g_hEvent = 0;
HWND g_config;

#define VM_REFRESH (WM_USER+0x111)

void g_format_volume(static_api_ptr_t<play_control> &pc, string8 &form)
{
	t_size index = form.find_first("%volume%");
	if(index != -1){
		float volume = pc->get_volume();
		string8 vol;
		vol += pfc::format_float(volume, 0, 2);
		do{
			form.remove_chars(index, 8);
			form.insert_chars(index, vol, vol.length());
			index = form.find_first("%volume%", index);
		}while(index != -1);
	}
}


bool g_format_title(const char *fmt, string8 &p_out)
{
	service_ptr_t<titleformat_object> script;
	static_api_ptr_t<play_control> pc;
	string8 form(fmt);
	g_format_volume(pc, form);
	g_format_datetime(form);
	g_format_datetime_param(form);

	if(static_api_ptr_t<titleformat_compiler>()->compile(script,form)){
		metadb_handle_ptr h;
		if(!pc->get_now_playing(h) || h.is_empty()){
			playable_location_impl l;
			static_api_ptr_t<metadb>()->handle_create(h, l);
		}
		return pc->playback_format_title_ex(h, 0, p_out, script, 0, play_control::display_level_all);
	}
	return false;
}

#include "config_dlg.h"
#include "info.h"
#include "play_cb.h"
#include "iq.h"
