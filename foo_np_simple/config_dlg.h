#pragma once

///////////////////////////////////////////////////////////////////////
// config
///////////////////////////////////////////////////////////////////////
class config_snp : public preferences_page,
	public CDialogImpl<config_snp>
{
	std::auto_ptr<CHyperLink> m_link;
	service_ptr_t<titleformat_object> m_script;
	CComboBox m_box;
public:
	config_snp()
		: initialized_()
	{
	}

	enum { IDD = IDD_CONFIG };

	BEGIN_MSG_MAP(config_snp)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_HANDLER(IDC_PATH, EN_KILLFOCUS, OnChangePath)
		COMMAND_HANDLER(IDC_SILENCE, EN_KILLFOCUS, OnChangeSilence)

		COMMAND_HANDLER(IDC_FORMAT, EN_KILLFOCUS, OnChangeFormat)
		COMMAND_HANDLER(IDC_FORMAT, EN_CHANGE, OnChange)
		COMMAND_ID_HANDLER(IDC_BROWSE, OnBrowse)
		COMMAND_HANDLER(IDC_ENCODING, CBN_SELENDOK, OnChangeEncoding);
		COMMAND_ID_HANDLER(IDC_SAVE2FILE, OnSave2File);
		COMMAND_ID_HANDLER(IDC_COPY2CLIPBOARD, OnCopy2Clipboard);

		COMMAND_ID_HANDLER(IDC_LOGMODE, OnLogmode)
		COMMAND_ID_HANDLER(IDC_LOG_OPTIONS, OnLogOptions)

		COMMAND_ID_HANDLER(IDC_CHECK_DELAY, OnCheckDelay)
		COMMAND_HANDLER(IDC_EDIT_DELAY, EN_KILLFOCUS, OnChangeDelay)

		MESSAGE_HANDLER(VM_REFRESH, OnRefresh)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		g_config = m_hWnd;
		m_link.reset(new CHyperLink);
		m_link->SubclassWindow(GetDlgItem(IDC_LINK));
		m_link->SetHyperLink(TSITE);

		uSetDlgItemText(m_hWnd, IDC_FORMAT, cfg_fmt);
		uSetDlgItemText(m_hWnd, IDC_URL, cfg_path);
		uSetDlgItemText(m_hWnd, IDC_SILENCE, cfg_silence);
		m_box = GetDlgItem(IDC_ENCODING);
		m_box.AddString(_T("UTF-8"));
		m_box.AddString(_T("UTF-8 with header"));
		m_box.AddString(_T("Unicode"));
		m_box.AddString(_T("ANSI"));
		m_box.SetCurSel(cfg_encoding);
		CheckDlgButton(IDC_LOGMODE, cfg_logmode?BST_CHECKED:BST_UNCHECKED);
		CheckDlgButton(IDC_CHECK_DELAY, CFG_EVENTS.use_delay?BST_CHECKED:BST_UNCHECKED);
		CheckDlgButton(IDC_SAVE2FILE, CFG_SAVE_TO.to_file?BST_CHECKED:BST_UNCHECKED);
		CheckDlgButton(IDC_COPY2CLIPBOARD, CFG_SAVE_TO.to_clipboard?BST_CHECKED:BST_UNCHECKED);
		int val = CFG_EVENTS.delay_for_ms;
		CUpDownCtrl sp(GetDlgItem(IDC_SPIN_DELAY));
		sp.SetRange32(0, INT_MAX);
		sp.SetPos32(val);
		SetPreview();
		EnableControls();
		initialized_ = true;
		return TRUE;
	}
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		g_config = 0;
		m_link->UnsubclassWindow();
		m_link.reset();
		bHandled = false;
		return 0;
	}
	LRESULT OnChangeFormat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		pfc::string8 temp;
		uGetDlgItemText(m_hWnd, IDC_FORMAT, temp);
		cfg_fmt = temp;
		return 0;
	}
	LRESULT OnChangeEncoding(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		cfg_encoding = m_box.GetCurSel();
		return 0;
	}
	LRESULT OnChangePath(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		pfc::string8 temp;
		uGetDlgItemText(m_hWnd, IDC_PATH, temp);
		cfg_path = temp;
		return 0;
	}
	LRESULT OnChangeSilence(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		pfc::string8 temp;
		uGetDlgItemText(m_hWnd, IDC_SILENCE, temp);
		cfg_silence = temp;
		return 0;
	}
	LRESULT OnBrowse(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		pfc::string8 temp;
		uGetDlgItemText(m_hWnd, IDC_PATH, temp);
		if(uGetOpenFileName(m_hWnd, "Text Files (*.txt)|*.txt|All Files (*.*)|*.*|", 0, "txt", "Save file...", temp, temp, true)){
			uSetDlgItemText(m_hWnd, IDC_PATH, temp);
			cfg_path = temp;
		}
		return 0;
	}
	LRESULT OnSave2File(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CFG_SAVE_TO.to_file = IsDlgButtonChecked(IDC_SAVE2FILE) == BST_CHECKED;
		EnableControls();
		return 0;
	}
	LRESULT OnCopy2Clipboard(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CFG_SAVE_TO.to_clipboard = IsDlgButtonChecked(IDC_COPY2CLIPBOARD) == BST_CHECKED;
		EnableControls();
		return 0;
	}
	LRESULT OnCheckDelay(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CFG_EVENTS.use_delay = IsDlgButtonChecked(IDC_CHECK_DELAY) == BST_CHECKED;
		EnableControls();
		return 0;
	}
	LRESULT OnChangeDelay(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if (initialized_)
		{
			int val = GetDlgItemInt(IDC_EDIT_DELAY, 0, TRUE);
			CFG_EVENTS_ &ev = CFG_EVENTS;
			ev.delay_for_ms = val;
		}
		return 0;
	}
	LRESULT OnLogmode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		cfg_logmode = (IsDlgButtonChecked(IDC_LOGMODE)==BST_CHECKED)?1:0;
		EnableControls();
		return 0;
	}
	LRESULT OnLogOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		enum {
			CMD_ONNEWTRACK=1,
			CMD_ONPAUSE,
			CMD_ONSTOP,
			CMD_EVERY_SECOND,
		};
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING|(!CFG_EVENTS.on_new_track?MF_UNCHECKED:MF_CHECKED), CMD_ONNEWTRACK, _T("On new track"));
		menu.AppendMenu(MF_STRING|(!CFG_EVENTS.on_pause?MF_UNCHECKED:MF_CHECKED), CMD_ONPAUSE, _T("On pause"));
		menu.AppendMenu(MF_STRING|(!CFG_EVENTS.on_stop?MF_UNCHECKED:MF_CHECKED), CMD_ONSTOP, _T("On stop"));
		menu.AppendMenu(MF_STRING|(!CFG_EVENTS.on_every_second?MF_UNCHECKED:MF_CHECKED), CMD_EVERY_SECOND, _T("On every second"));
		RECT rect;
		GetDlgItem(IDC_OPTIONS).GetWindowRect(&rect);
		int nID = menu.TrackPopupMenu(TPM_NONOTIFY|TPM_RETURNCMD, rect.left, rect.bottom, m_hWnd);
		switch(nID){
			case CMD_ONNEWTRACK:	CFG_EVENTS.on_new_track = !CFG_EVENTS.on_new_track; break;
			case CMD_ONPAUSE:		CFG_EVENTS.on_pause = !CFG_EVENTS.on_pause; break;
			case CMD_ONSTOP:		CFG_EVENTS.on_stop = !CFG_EVENTS.on_stop; break;
			case CMD_EVERY_SECOND:	CFG_EVENTS.on_every_second = !CFG_EVENTS.on_every_second; break;
		}
		return 0;
	}
	LRESULT OnChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		SetPreview();
		return 0;
	}
	void SetPreview()
	{
		if(m_hWnd && IsWindow()){
			pfc::string8 fmt, s;
			uGetDlgItemText(m_hWnd, IDC_FORMAT, fmt);
			if(!g_format_title(fmt, s))
				s = "COMPILE ERROR";
			uSetWindowText(GetDlgItem(IDC_PREVIEW), s);
		}
	}
	LRESULT OnRefresh(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		SetPreview();
		return 0;
	}
	void EnableControls()
	{
		BOOL en = IsDlgButtonChecked(IDC_SAVE2FILE) == BST_CHECKED;
		GetDlgItem(IDC_PATH).EnableWindow(en);
		GetDlgItem(IDC_BROWSE).EnableWindow(en);
		GetDlgItem(IDC_ENCODING).EnableWindow(en);
		GetDlgItem(IDC_LOGMODE).EnableWindow(en);
		en = IsDlgButtonChecked(IDC_CHECK_DELAY) == BST_CHECKED;
		GetDlgItem(IDC_EDIT_DELAY).EnableWindow(en);
		GetDlgItem(IDC_SPIN_DELAY).EnableWindow(en);
	}
	virtual HWND create(HWND parent)
	{
		return __super::Create(parent);
	}
	virtual const char * get_name() {return PLUGIN_NAME;}
	virtual GUID get_parent_guid(){
		return preferences_page::guid_tools;
	}
	virtual GUID get_guid(){
		// {A39E4A9D-132C-44df-8639-E3D8B4CCBC73}
		static const GUID guid = 
		{ 0xa39e4a9d, 0x132c, 0x44df, { 0x86, 0x39, 0xe3, 0xd8, 0xb4, 0xcc, 0xbc, 0x73 } };
		return guid;
	}
	virtual bool reset_query(){
		return true;
	}
	virtual void reset(){
		cfg_fmt = CFG_FORMAT_DEFAULT;
		cfg_silence = CFG_SILENCE_DEFAULT;
		cfg_encoding = ENC_UTF8_HEADER;
	}

private:
	bool initialized_;
};
static preferences_page_factory_t<config_snp> iuqywe;
