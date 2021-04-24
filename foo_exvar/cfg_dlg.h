#pragma once

class CEditVarDlg : public CDialogImpl<CEditVarDlg>
	, public CDialogResize<CEditVarDlg>
{
	typedef CDialogResize<CEditVarDlg> rszBase;
	CEdit m_edName;
	CEdit m_edValue;
	CButton m_btnOK;
public:
	enum { IDD = IDD_EDVAR };
	BEGIN_MSG_MAP(CEditVarDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(IDC_EDIT_NAME, EN_CHANGE, OnChangeName)
		CHAIN_MSG_MAP(rszBase)
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(CEditVarDlg)
		DLGRESIZE_CONTROL(IDC_EDIT_NAME, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_EDIT_VALUE, DLSZ_SIZE_X|DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDOK, DLSZ_MOVE_X|DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDCANCEL, DLSZ_MOVE_X|DLSZ_MOVE_Y)
	END_DLGRESIZE_MAP()
	
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CenterWindow();

		m_edName = GetDlgItem(IDC_EDIT_NAME);
		m_edValue = GetDlgItem(IDC_EDIT_VALUE);
		m_btnOK = GetDlgItem(IDOK);

		m_edName.SetWindowText(name);
		m_edValue.SetWindowText(value);
		UpdateButtons();
		DlgResize_Init();
		edit_var_dlg_pos.on_window_creation(m_hWnd);
		return TRUE;
	}
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		edit_var_dlg_pos.on_window_destruction(m_hWnd);
		return 0;
	}
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		m_edName.GetWindowText(name);
		m_edValue.GetWindowText(value);
		EndDialog(wID);
		return 0;
	}
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}
	LRESULT OnChangeName(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		UpdateButtons();
		return 0;
	}
	void UpdateButtons()
	{
		m_btnOK.EnableWindow(m_edName.GetWindowTextLength()>0);
	}
public:
	CString name;
	CString value;
};

///////////////////////////////////////////////////////////////////////
// config
///////////////////////////////////////////////////////////////////////
class config_exvars : public preferences_page,
	public CDialogImpl<config_exvars>
{
	CListViewCtrl m_list;
	CButton m_btnAdd, m_btnDel, m_btnEdit, m_btnUp, m_btnDown;
public:
	enum { IDD = IDD_CONFIG };
	BEGIN_MSG_MAP(config_exvars)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDC_ADD, OnAdd)
		COMMAND_ID_HANDLER(IDC_DELETE, OnDel)
		COMMAND_ID_HANDLER(IDC_EDIT, OnEdit)
		//COMMAND_ID_HANDLER(IDC_UP, OnUp)
		//COMMAND_ID_HANDLER(IDC_DOWN, OnDown)
		NOTIFY_HANDLER(IDC_LIST1, LVN_ITEMCHANGED, OnItemChanged)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		m_list = GetDlgItem(IDC_LIST1);
		m_btnAdd = GetDlgItem(IDC_ADD);
		m_btnDel = GetDlgItem(IDC_DELETE);
		m_btnEdit = GetDlgItem(IDC_EDIT);
		m_btnUp = GetDlgItem(IDC_UP);
		m_btnDown = GetDlgItem(IDC_DOWN);

		m_list.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		m_list.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100, 0);
		m_list.InsertColumn(1, _T("Value"), LVCFMT_LEFT, 300, 1);

		UpdateList();
		UpdateButtons();
		return TRUE;
	}

	LRESULT OnItemChanged(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
	{
		UpdateButtons();
		return 0;
	}

	LRESULT OnAdd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ItemAdd();
		return 0;
	}
	LRESULT OnDel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ItemDelete();
		return 0;
	}
	LRESULT OnEdit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ItemEdit();
		return 0;
	}
	LRESULT OnUp(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ItemUp();
		return 0;
	}
	LRESULT OnDown(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ItemDown();
		return 0;
	}

	void ItemEdit()
	{
		int i = m_list.GetSelectedIndex();
		if(i == -1)
			return;

		CEditVarDlg dlg;
		dlg.name = g_varvec[i].name;
		dlg.value = g_varvec[i].value;
		if(dlg.DoModal() == IDOK){
			g_varvec[i].name = pfc::stringcvt::string_utf8_from_wide(dlg.name);
			g_varvec[i].value = pfc::stringcvt::string_utf8_from_wide(dlg.value);
			UpdateList();
			m_list.SelectItem(i);
			UpdateButtons();
		}
	}

	void ItemAdd()
	{
		CEditVarDlg dlg;
		if(dlg.DoModal() == IDOK){
			ITEM it;
			it.name = pfc::stringcvt::string_utf8_from_wide(dlg.name);
			it.value = pfc::stringcvt::string_utf8_from_wide(dlg.value);
			g_varvec.push_back(it);
			UpdateList();
			UpdateButtons();
		}
	}
	void ItemDelete()
	{
		int i = m_list.GetSelectedIndex();
		if(i == -1)
			return;
		g_varvec.erase(g_varvec.begin()+i);
		UpdateList();
		UpdateButtons();
	}
	void ItemUp()
	{
	}
	void ItemDown()
	{
	}

	void UpdateList()
	{
		m_list.SetRedraw(FALSE);
		m_list.DeleteAllItems();
		VARVEC::iterator it;
		int i;
		for(it=g_varvec.begin(), i=0; it!=g_varvec.end(); ++it,++i){
			int index = m_list.InsertItem(i, pfc::stringcvt::string_wide_from_utf8(it->name));
			m_list.SetItemText(index, 1, pfc::stringcvt::string_wide_from_utf8(it->value));
		}
		m_list.SetRedraw(TRUE);
	}
	void UpdateButtons()
	{
		BOOL bEdit = false, bDel = false, bUp = false, bDown = false;
		int nCount = m_list.GetItemCount();
		int nSel = m_list.GetSelectedIndex();
		if(nSel != -1){
			bEdit = true;
			bDel = true;
			if(nSel > 0)
				bUp = true;
			if(nSel < (nCount-1))
				bDown = true;
		}
		m_btnAdd.EnableWindow(TRUE);
		m_btnDel.EnableWindow(bDel);
		m_btnEdit.EnableWindow(bEdit);
		//m_btnDown.EnableWindow(bDown);
		//m_btnUp.EnableWindow(bUp);
	}

	//
	virtual HWND create(HWND parent)
	{
		return __super::Create(parent);
	}
	virtual const char * get_name() {return "Extended Variables";}
	virtual GUID get_parent_guid(){
		return preferences_page::guid_tools;
	}
	virtual GUID get_guid(){
		// {B270CE55-3D39-4d2d-9B8D-46990F73D938}
		static const GUID guid = 
		{ 0xb270ce55, 0x3d39, 0x4d2d, { 0x9b, 0x8d, 0x46, 0x99, 0xf, 0x73, 0xd9, 0x38 } };
		return guid;
	}
	virtual bool reset_query(){
		return false;
	}
	virtual void reset(){
	}
};
static preferences_page_factory_t<config_exvars> iuqywe;
