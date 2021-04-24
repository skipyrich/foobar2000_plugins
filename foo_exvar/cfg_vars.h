#pragma once
#include <time.h>

#define VERSION 1

// {E4DC1796-8CE4-407d-9832-C380C054FC7D}
static const GUID edit_var_dlg_pos_GUID = 
{ 0xe4dc1796, 0x8ce4, 0x407d, { 0x98, 0x32, 0xc3, 0x80, 0xc0, 0x54, 0xfc, 0x7d } };
cfg_window_placement edit_var_dlg_pos(edit_var_dlg_pos_GUID);

struct ITEM
{
	pfc::string8 name;
	pfc::string8 value;
	t_size len;
};

typedef vector<ITEM> VARVEC;
VARVEC g_varvec;

class cfg_varvec;

class VarHolder
{
	VARVEC m_vars;

	void AddColor(DWORD color, const char *name, char *buf)
	{
		DWORD clr = GetSysColor(color);
		sprintf(buf, "%X", clr);
		ITEM it = { name, buf, strlen(buf) };
		m_vars.push_back(it);
	}
	void AddSystemMetric(int nIndex, const char *name, char *buf)
	{
		int sm = GetSystemMetrics(nIndex);
		sprintf(buf, "%d", sm);
		ITEM it = { name, buf, strlen(buf) };
		m_vars.push_back(it);
	}
	inline void add_var(const char *name, const char *value)
	{
		ITEM it = { name, value, strlen(value) };
		m_vars.push_back(it);
	}
public:
	VarHolder()
	{
		WCHAR *buf = new WCHAR[65536];
		DWORD len = GetModuleFileName(0, buf, 65535);
		while(len){
			if(buf[len] == '/' || buf[len] == ':' || buf[len] == '\\'){
				++len;
				break;
			}
			--len;
		}
		buf[len] = 0;
		add_var("FOOBAR_PATH", pfc::stringcvt::string_utf8_from_wide(buf));

		char* cbuf = (char*)buf;
		AddColor(COLOR_SCROLLBAR,				"COLOR_SCROLLBAR", cbuf);
		AddColor(COLOR_BACKGROUND,				"COLOR_BACKGROUND", cbuf);
		AddColor(COLOR_ACTIVECAPTION,			"COLOR_ACTIVECAPTION", cbuf);
		AddColor(COLOR_INACTIVECAPTION,			"COLOR_INACTIVECAPTION", cbuf);
		AddColor(COLOR_MENU,					"COLOR_MENU", cbuf);
		AddColor(COLOR_WINDOW,					"COLOR_WINDOW", cbuf);
		AddColor(COLOR_WINDOWFRAME,				"COLOR_WINDOWFRAME", cbuf);
		AddColor(COLOR_MENUTEXT,				"COLOR_MENUTEXT", cbuf);
		AddColor(COLOR_WINDOWTEXT,				"COLOR_WINDOWTEXT", cbuf);
		AddColor(COLOR_CAPTIONTEXT,				"COLOR_CAPTIONTEXT", cbuf);
		AddColor(COLOR_ACTIVEBORDER,			"COLOR_ACTIVEBORDER", cbuf);
		AddColor(COLOR_INACTIVEBORDER,			"COLOR_INACTIVEBORDER", cbuf);
		AddColor(COLOR_APPWORKSPACE,			"COLOR_APPWORKSPACE", cbuf);
		AddColor(COLOR_HIGHLIGHT,				"COLOR_HIGHLIGHT", cbuf);
		AddColor(COLOR_HIGHLIGHTTEXT,			"COLOR_HIGHLIGHTTEXT", cbuf);
		AddColor(COLOR_BTNFACE,					"COLOR_BTNFACE", cbuf);
		AddColor(COLOR_BTNSHADOW,				"COLOR_BTNSHADOW", cbuf);
		AddColor(COLOR_GRAYTEXT,				"COLOR_GRAYTEXT", cbuf);
		AddColor(COLOR_BTNTEXT,					"COLOR_BTNTEXT", cbuf);
		AddColor(COLOR_INACTIVECAPTIONTEXT,		"COLOR_INACTIVECAPTIONTEXT", cbuf);
		AddColor(COLOR_BTNHIGHLIGHT,			"COLOR_BTNHIGHLIGHT", cbuf);
		AddColor(COLOR_3DDKSHADOW,				"COLOR_3DDKSHADOW", cbuf);
		AddColor(COLOR_3DLIGHT,					"COLOR_3DLIGHT", cbuf);
		AddColor(COLOR_INFOTEXT,				"COLOR_INFOTEXT", cbuf);
		AddColor(COLOR_INFOBK,					"COLOR_INFOBK", cbuf);
		AddColor(COLOR_HOTLIGHT,				"COLOR_HOTLIGHT", cbuf);
		AddColor(COLOR_GRADIENTACTIVECAPTION,	"COLOR_GRADIENTACTIVECAPTION", cbuf);
		AddColor(COLOR_GRADIENTINACTIVECAPTION,	"COLOR_GRADIENTINACTIVECAPTION", cbuf);
		AddColor(COLOR_MENUHILIGHT,				"COLOR_MENUHILIGHT", cbuf);
		AddColor(COLOR_MENUBAR,					"COLOR_MENUBAR", cbuf);
		AddColor(COLOR_DESKTOP,					"COLOR_DESKTOP", cbuf);
		AddColor(COLOR_3DFACE,					"COLOR_3DFACE", cbuf);
		AddColor(COLOR_3DSHADOW,				"COLOR_3DSHADOW", cbuf);
		AddColor(COLOR_3DHIGHLIGHT,				"COLOR_3DHIGHLIGHT", cbuf);
		AddColor(COLOR_3DHILIGHT,				"COLOR_3DHILIGHT", cbuf);
		AddColor(COLOR_BTNHILIGHT,				"COLOR_BTNHILIGHT", cbuf);

		AddSystemMetric(SM_ARRANGE,				"SM_ARRANGE", cbuf);
		AddSystemMetric(SM_CMONITORS,			"SM_CMONITORS", cbuf);
		AddSystemMetric(SM_CMOUSEBUTTONS,		"SM_CMOUSEBUTTONS", cbuf);
		AddSystemMetric(SM_CXBORDER,			"SM_CXBORDER", cbuf);
		AddSystemMetric(SM_CXCURSOR,			"SM_CXCURSOR", cbuf);
		AddSystemMetric(SM_CXDLGFRAME,			"SM_CXDLGFRAME", cbuf);
		AddSystemMetric(SM_CXDOUBLECLK,			"SM_CXDOUBLECLK", cbuf);
		AddSystemMetric(SM_CXDRAG,				"SM_CXDRAG", cbuf);
		AddSystemMetric(SM_CXEDGE,				"SM_CXEDGE", cbuf);
		AddSystemMetric(SM_CXFIXEDFRAME,		"SM_CXFIXEDFRAME", cbuf);
		AddSystemMetric(SM_CXFOCUSBORDER,		"SM_CXFOCUSBORDER", cbuf);
		AddSystemMetric(SM_CXFRAME,				"SM_CXFRAME", cbuf);
		AddSystemMetric(SM_CXFULLSCREEN,		"SM_CXFULLSCREEN", cbuf);
		AddSystemMetric(SM_CXHSCROLL,			"SM_CXHSCROLL", cbuf);
		AddSystemMetric(SM_CXHTHUMB,			"SM_CXHTHUMB", cbuf);
		AddSystemMetric(SM_CXICON,				"SM_CXICON", cbuf);
		AddSystemMetric(SM_CXICONSPACING,		"SM_CXICONSPACING", cbuf);
		AddSystemMetric(SM_CXMAXIMIZED,			"SM_CXMAXIMIZED", cbuf);
		AddSystemMetric(SM_CXMAXTRACK,			"SM_CXMAXTRACK", cbuf);
		AddSystemMetric(SM_CXMENUCHECK,			"SM_CXMENUCHECK", cbuf);
		AddSystemMetric(SM_CXMENUSIZE,			"SM_CXMENUSIZE", cbuf);
		AddSystemMetric(SM_CXMIN,				"SM_CXMIN", cbuf);
		AddSystemMetric(SM_CXMINIMIZED,			"SM_CXMINIMIZED", cbuf);
		AddSystemMetric(SM_CXMINSPACING,		"SM_CXMINSPACING", cbuf);
		AddSystemMetric(SM_CXMINTRACK,			"SM_CXMINTRACK", cbuf);
		AddSystemMetric(SM_CXSCREEN,			"SM_CXSCREEN", cbuf);
		AddSystemMetric(SM_CXSIZE,				"SM_CXSIZE", cbuf);
		AddSystemMetric(SM_CXSIZEFRAME,			"SM_CXSIZEFRAME", cbuf);
		AddSystemMetric(SM_CXSMICON,			"SM_CXSMICON", cbuf);
		AddSystemMetric(SM_CXSMSIZE,			"SM_CXSMSIZE", cbuf);
		AddSystemMetric(SM_CXVIRTUALSCREEN,		"SM_CXVIRTUALSCREEN", cbuf);
		AddSystemMetric(SM_CXVSCROLL,			"SM_CXVSCROLL", cbuf);
		AddSystemMetric(SM_CYBORDER,			"SM_CYBORDER", cbuf);
		AddSystemMetric(SM_CYCAPTION,			"SM_CYCAPTION", cbuf);
		AddSystemMetric(SM_CYCURSOR,			"SM_CYCURSOR", cbuf);
		AddSystemMetric(SM_CYDLGFRAME,			"SM_CYDLGFRAME", cbuf);
		AddSystemMetric(SM_CYDOUBLECLK,			"SM_CYDOUBLECLK", cbuf);
		AddSystemMetric(SM_CYDRAG,				"SM_CYDRAG", cbuf);
		AddSystemMetric(SM_CYEDGE,				"SM_CYEDGE", cbuf);
		AddSystemMetric(SM_CYFIXEDFRAME,		"SM_CYFIXEDFRAME", cbuf);
		AddSystemMetric(SM_CYFOCUSBORDER,		"SM_CYFOCUSBORDER", cbuf);
		AddSystemMetric(SM_CYFRAME,				"SM_CYFRAME", cbuf);
		AddSystemMetric(SM_CYFULLSCREEN,		"SM_CYFULLSCREEN", cbuf);
		AddSystemMetric(SM_CYHSCROLL,			"SM_CYHSCROLL", cbuf);
		AddSystemMetric(SM_CYICON,				"SM_CYICON", cbuf);
		AddSystemMetric(SM_CYICONSPACING,		"SM_CYICONSPACING", cbuf);
		AddSystemMetric(SM_CYKANJIWINDOW,		"SM_CYKANJIWINDOW", cbuf);
		AddSystemMetric(SM_CYMAXIMIZED,			"SM_CYMAXIMIZED", cbuf);
		AddSystemMetric(SM_CYMAXTRACK,			"SM_CYMAXTRACK", cbuf);
		AddSystemMetric(SM_CYMENU,				"SM_CYMENU", cbuf);
		AddSystemMetric(SM_CYMENUCHECK,			"SM_CYMENUCHECK", cbuf);
		AddSystemMetric(SM_CYMENUSIZE,			"SM_CYMENUSIZE", cbuf);
		AddSystemMetric(SM_CYMIN,				"SM_CYMIN", cbuf);
		AddSystemMetric(SM_CYMINIMIZED,			"SM_CYMINIMIZED", cbuf);
		AddSystemMetric(SM_CYMINSPACING,		"SM_CYMINSPACING", cbuf);
		AddSystemMetric(SM_CYMINTRACK,			"SM_CYMINTRACK", cbuf);
		AddSystemMetric(SM_CYSCREEN,			"SM_CYSCREEN", cbuf);
		AddSystemMetric(SM_CYSIZE,				"SM_CYSIZE", cbuf);
		AddSystemMetric(SM_CYSIZEFRAME,			"SM_CYSIZEFRAME", cbuf);
		AddSystemMetric(SM_CYSMCAPTION,			"SM_CYSMCAPTION", cbuf);
		AddSystemMetric(SM_CYSMICON,			"SM_CYSMICON", cbuf);
		AddSystemMetric(SM_CYSMSIZE,			"SM_CYSMSIZE", cbuf);
		AddSystemMetric(SM_CYVIRTUALSCREEN,		"SM_CYVIRTUALSCREEN", cbuf);
		AddSystemMetric(SM_CYVSCROLL,			"SM_CYVSCROLL", cbuf);
		AddSystemMetric(SM_CYVTHUMB,			"SM_CYVTHUMB", cbuf);
		AddSystemMetric(SM_MEDIACENTER,			"SM_MEDIACENTER", cbuf);
		AddSystemMetric(SM_MENUDROPALIGNMENT,	"SM_MENUDROPALIGNMENT", cbuf);
		AddSystemMetric(SM_MIDEASTENABLED,		"SM_MIDEASTENABLED", cbuf);
		AddSystemMetric(SM_MOUSEPRESENT,		"SM_MOUSEPRESENT", cbuf);
		AddSystemMetric(SM_MOUSEWHEELPRESENT,	"SM_MOUSEWHEELPRESENT", cbuf);
		AddSystemMetric(SM_PENWINDOWS,			"SM_PENWINDOWS", cbuf);
		AddSystemMetric(SM_REMOTECONTROL,		"SM_REMOTECONTROL", cbuf);
		AddSystemMetric(SM_REMOTESESSION,		"SM_REMOTESESSION", cbuf);
		AddSystemMetric(SM_SAMEDISPLAYFORMAT,	"SM_SAMEDISPLAYFORMAT", cbuf);
		AddSystemMetric(SM_SHOWSOUNDS,			"SM_SHOWSOUNDS", cbuf);
		AddSystemMetric(SM_SWAPBUTTON,			"SM_SWAPBUTTON", cbuf);
		AddSystemMetric(SM_XVIRTUALSCREEN,		"SM_XVIRTUALSCREEN", cbuf);
		AddSystemMetric(SM_YVIRTUALSCREEN,		"SM_YVIRTUALSCREEN", cbuf);
		delete [] buf;
	}
	inline bool get_val(t_uint32 index, titleformat_text_out * out)
	{
		if (index == m_vars.size())
		{
			__time32_t ts;
			_time32(&ts);
			struct tm stm;
			_localtime32_s(&stm, &ts);
			wchar_t stime[64];
			_wasctime_s(stime, &stm);
			wchar_t *p = stime;
			while(*p && *p >= 0x20) ++p;
			*p = 0;
			pfc::string8 str = pfc::stringcvt::string_utf8_from_wide(stime).get_ptr();
			out->write(titleformat_inputtypes::unknown, str, str.length());
			return true;
		}

		if(index >= m_vars.size())
			return false;

		const ITEM &it = m_vars[index];

		if (it.value.length() > 7 && strncmp(it.value, "$eval(", 6) == 0 && it.value[it.value.length() - 1] == ')')
		{
			pfc::string8 s;
			s.add_string_nc((const char*)it.value + 6, it.value.length() - 7);
			service_ptr_t<titleformat_object> script;
			static_api_ptr_t<play_control> pc;

			if(static_api_ptr_t<titleformat_compiler>()->compile(script, s))
			{
				metadb_handle_ptr h;

				if(!pc->get_now_playing(h) || h.is_empty())
				{
					playable_location_impl l;
					static_api_ptr_t<metadb>()->handle_create(h, l);
				}
				
				pfc::string8 ss;

				if (pc->playback_format_title_ex(h, 0, ss, script, 0, play_control::display_level_all))
				{
					out->write(titleformat_inputtypes::unknown, ss, ss.length());
					return true;
				}
			}

			return false;
		}
		else
		{
			out->write(titleformat_inputtypes::unknown, it.value, it.len);
		}

		return true;
	}
	inline t_size count(){
		return m_vars.size() + 1;
	}
	inline void get_field_name(t_uint32 index, pfc::string_base & out){
		if (index == m_vars.size())
		{
			out = "datetime";
		}
		else
		{
			out = m_vars[index].name;
		}
	}
	void update_with_refresh(){
	}
protected:
	friend class cfg_varvec;
	inline void append()
	{
		//m_vars.insert(m_vars.end(), g_varvec.begin(), g_varvec.end());
		VARVEC::iterator it;
		size_t buflen = 65536;
		WCHAR *buf = new WCHAR[buflen];
		for(it=g_varvec.begin(); it!=g_varvec.end(); ++it){
			ITEM &item = *it;
			ITEM ittt;
			ittt.name = item.name;
			pfc::stringcvt::string_wide_from_utf8 wide(item.value);
			DWORD err = 0;
			while( (err = ExpandEnvironmentStringsW(wide.get_ptr(), buf, buflen)) > buflen){
				delete [] buf;
				buf = new WCHAR[buflen];
			}
			pfc::stringcvt::string_utf8_from_wide utf8(buf, err);
			ittt.value = utf8.get_ptr();
			ittt.len = strlen(ittt.value);
			m_vars.push_back(ittt);
		}
		delete [] buf;
	}
} g_vars;

class cfg_varvec : public cfg_var
{
	static void stream_write_string(stream_writer * p_stream, const pfc::string8 &s, abort_callback &p_abort) {
		t_int32 size = s.length();
		p_stream->write_lendian_t(size, p_abort);
		p_stream->write((const char*)s, size, p_abort);
	}

	static void stream_read_string(stream_reader * p_stream, pfc::string8 &s, abort_callback &p_abort) {
		s.reset();
		t_int32 size;
		p_stream->read_lendian_t(size, p_abort);
		if(size){
			char *ptr = s.lock_buffer(size + 1);
			p_stream->read(ptr, size, p_abort);
			ptr[size] = 0;
			s.unlock_buffer();
		}
	}
public:
	cfg_varvec(const GUID & p_guid) : cfg_var(p_guid) {}

	virtual void get_data_raw(stream_writer *p_stream, abort_callback &p_abort) {
		p_stream->write_lendian_t(VERSION, p_abort);
		VARVEC::iterator it;
		p_stream->write_lendian_t(g_varvec.size(), p_abort);
		for(it=g_varvec.begin(); it!=g_varvec.end(); ++it){
			stream_write_string(p_stream, it->name, p_abort);
			stream_write_string(p_stream, it->value, p_abort);
		}
	}

	virtual void set_data_raw(stream_reader * p_stream,t_size p_sizehint,abort_callback & p_abort) {
		t_int32 version = 0;
		p_stream->read_lendian_t(version, p_abort);

		g_varvec.clear();
		t_int32 size;
		p_stream->read_lendian_t(size, p_abort);
		ITEM item;

		for(t_int32 j=0; j<size; ++j){
			stream_read_string(p_stream, item.name, p_abort);
			stream_read_string(p_stream, item.value, p_abort);
			item.len = strlen(item.value);
			g_varvec.push_back(item);
		}
		g_vars.append();
	}
};

// {2A4987C0-FC20-44d0-9A70-DE7FD47EE654}
static const GUID cfg_vv_guid = 
{ 0x2a4987c0, 0xfc20, 0x44d0, { 0x9a, 0x70, 0xde, 0x7f, 0xd4, 0x7e, 0xe6, 0x54 } };
cfg_varvec cfg_vv(cfg_vv_guid);
