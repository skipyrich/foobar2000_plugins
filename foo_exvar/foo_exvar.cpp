#include "stdafx.h"
#include "resource.h"

#define EMAIL "<skipyrich@skipyrich.com>"
#define SITE "http://www.skipyrich.com/"

#define TEMAIL _T(EMAIL)
#define TSITE _T(TSITE)

DECLARE_COMPONENT_VERSION("Extended Variables", "0.4.0", "(C) Skipyrich " EMAIL "\n" SITE)

#include "cfg_vars.h"
#include "cfg_dlg.h"

class blah : public metadb_display_field_provider
{
public:
	virtual t_uint32 get_field_count(){
		return g_vars.count();
	}
	virtual void get_field_name(t_uint32 index, pfc::string_base & out){
		g_vars.get_field_name(index, out);
	}
	virtual bool process_field(t_uint32 index, metadb_handle * handle, titleformat_text_out * out){
		return g_vars.get_val(index, out);
	}
};

static service_factory_single_t<blah> g_blah;
