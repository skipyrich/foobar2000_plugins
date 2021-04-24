#pragma once

///////////////////////////////////////////////////////////////////////
// Play callback
///////////////////////////////////////////////////////////////////////

class main_thread_callback_apply_format : public main_thread_callback {
public:
	void callback_run() {
		string8 s;
		g_format_title(cfg_fmt, s);
		g_info.set_data(s);
		if(g_config)
			::PostMessage(g_config, VM_REFRESH, 0, 0);
	}
};

class play_cb : public play_callback_static
{
public:
	play_cb()
		: thread_()
		, threadId_()
	{
	}

	~play_cb()
	{
		if (thread_)
		{
			PostThreadMessage(threadId_, WM_QUIT, 0, 0);
			WaitForSingleObject(thread_, INFINITE);
			thread_ = 0;
			threadId_ = 0;
		}
	}

	void FB2KAPI on_playback_starting(play_control::t_track_command p_command,bool p_paused){
#ifdef _DEBUG
		console::info("on_playback_starting");
#endif
		format_title();
	}
	void FB2KAPI on_playback_new_track(metadb_handle_ptr p_track){
#ifdef _DEBUG
		console::info("on_playback_new_track");
#endif
		if(CFG_EVENTS.on_new_track)
			format_title();
	}
	void FB2KAPI on_playback_stop(play_control::t_stop_reason p_reason){
#ifdef _DEBUG
		console::info("on_playback_stop");
#endif
		if(p_reason != play_control::stop_reason_starting_another && CFG_EVENTS.on_stop){
			format_title();
		}
	}
	void FB2KAPI on_playback_seek(double p_time){}
	void FB2KAPI on_playback_pause(bool p_state){
#ifdef _DEBUG
		console::info("on_playback_pause");
#endif
		if(CFG_EVENTS.on_pause)
			format_title();
	}
	void FB2KAPI on_playback_edited(metadb_handle_ptr p_track){}
	void FB2KAPI on_playback_dynamic_info(const file_info & p_info){}
	void FB2KAPI on_playback_dynamic_info_track(const file_info & p_info){
#ifdef _DEBUG
		console::info("on_playback_dynamic_info_track");
#endif
		if(CFG_EVENTS.on_new_track)
			format_title();
	}
	void FB2KAPI on_playback_time(double p_time){
		if(CFG_EVENTS.on_every_second)
			format_title();
	}
	void FB2KAPI on_volume_change(float p_new_val){}

	unsigned get_flags(){
		return play_callback::flag_on_playback_dynamic_info_track | play_callback::flag_on_playback_new_track | play_callback::flag_on_playback_stop | play_callback::flag_on_playback_pause | play_callback::flag_on_playback_time;
	}

private:
	void format_title()
	{
		if (CFG_EVENTS.use_delay)
		{
			if (thread_ == 0)
			{
				HANDLE event = CreateEvent(0,0,0,0);
				thread_ = (HANDLE)_beginthreadex(0, 0, delay_thread, event, 0, &threadId_);

				if (thread_)
				{
					WaitForSingleObject(event, INFINITE);
				}
				
				CloseHandle(event);
			}

			if (thread_)
			{
				PostThreadMessage(threadId_, WM_USER + 0x4, 1, 2);
				return;
			}
		}

		string8 s;
		g_format_title(cfg_fmt, s);
		g_info.set_data(s);
		if(g_config)
			::PostMessage(g_config, VM_REFRESH, 0, 0);
	}

	static VOID CALLBACK timerproc(HWND, UINT, UINT_PTR, DWORD)
	{
		static_api_ptr_t<main_thread_callback_manager>()->add_callback(new service_impl_t<main_thread_callback_apply_format>());
	}

	static unsigned __stdcall delay_thread(void *d)
	{
		HANDLE event = (HANDLE)d;
		MSG msg;
		UINT timer = 0;
		BOOL ret = 0;

		PeekMessage(&msg, 0, 0, 0, 0);
		SetEvent(event);

		while (ret = GetMessage(&msg, 0, 0, 0))
		{
			if (ret != -1)
			{
				if (msg.message == WM_USER + 0x4 && msg.wParam == 1 && msg.lParam == 2)
				{
					if (timer)
					{
						KillTimer(0, timer);
						timer = 0;
					}

					timer = SetTimer(0, 0, CFG_EVENTS.delay_for_ms, timerproc);
				}
				
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		if (timer)
		{
			KillTimer(0, timer);
			timer = 0;
		}

		return 0;
	}

private:
	HANDLE thread_;
	unsigned int threadId_;
};
static play_callback_static_factory_t<play_cb> dqdqw;

