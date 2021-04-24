#pragma once

///////////////////////////////////////////////////////////////////////
// Init/Quit
///////////////////////////////////////////////////////////////////////
class initquit_np_simple : public initquit
{
	virtual void on_init(){
		string8 s;
		g_format_title(cfg_fmt, s);
		g_info.set_data(s);
	}
	virtual void on_quit() {
		string8 s(cfg_silence);
		g_format_datetime(s);
		if(cfg_logmode){
			if(s.length())
				s += "\r\n";
			else
				return;
		}
		g_info.set_data(s);
	}
};

static initquit_factory_t<initquit_np_simple> iujmf98yjw9yniufhskduyf;
