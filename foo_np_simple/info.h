#pragma once

class info
{
public:
	void set_data(const string8 &data){
		string8 path(cfg_path), expath;
		if(path.length() == 0)
			return;
		uExpandEnvironmentStrings(path, expath);
		pfc::stringcvt::string_wide_from_utf8_t<> ws(expath);

		if (CFG_SAVE_TO.to_file != 0)
		{
			bool logmode = (cfg_logmode!=0);
			DWORD openmod = logmode?OPEN_ALWAYS:CREATE_ALWAYS;

			HANDLE hFile = CreateFileW(ws, GENERIC_WRITE, FILE_SHARE_DELETE|FILE_SHARE_READ|FILE_SHARE_WRITE, 0, openmod, FILE_ATTRIBUTE_NORMAL, 0);
			if(hFile == INVALID_HANDLE_VALUE){
				string8 msg("Can't write to the file ");
				msg += path;
				msg += ": ";
				msg += pfc::stringcvt::string_utf8_from_wide(_com_error(HRESULT_FROM_WIN32(GetLastError())).ErrorMessage()).get_ptr();
				console::error(msg);
				return;
			}
			if(logmode){
				LONG dist = 0;
				SetFilePointer(hFile, 0, &dist, FILE_END);
			}
			DWORD wrtn=0;
			if(cfg_encoding == ENC_UTF8 || cfg_encoding == ENC_UTF8_HEADER){
				if(cfg_encoding == ENC_UTF8_HEADER){
					if(!logmode || IsFileEmpty(hFile)){
						const unsigned char buf[] = { 0xEF, 0xBB, 0xBF };
						WriteFile(hFile, buf, sizeof(buf), &wrtn, 0);
					}
				}
				WriteFile(hFile, data.get_ptr(), data.length(), &wrtn, 0);
			}else if(cfg_encoding == ENC_UNICODE){
				const unsigned char buf[] = { 0xFF, 0xFE };
				WriteFile(hFile, buf, sizeof(buf), &wrtn, 0);
				pfc::stringcvt::string_wide_from_utf8 dtwd(data);
				WriteFile(hFile, dtwd.get_ptr(), dtwd.length()*2, &wrtn, 0);
			}else if(cfg_encoding == ENC_ANSI){
				pfc::stringcvt::string_ansi_from_utf8 dtans(data);
				WriteFile(hFile, dtans.get_ptr(), dtans.length(), &wrtn, 0);
			}
			CloseHandle(hFile);
		}
		if (CFG_SAVE_TO.to_clipboard != 0)
		{
			if (OpenClipboard(NULL))
			{
				if (EmptyClipboard())
				{
					pfc::stringcvt::string_wide_from_utf8 dtwd(data);
					HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (dtwd.length() + 1) * sizeof(wchar_t)); 

					if (hglbCopy != NULL) 
					{ 
						LPWSTR lptstrCopy = (LPWSTR)GlobalLock(hglbCopy);
						memcpy(lptstrCopy, dtwd.get_ptr(), dtwd.length() * sizeof(wchar_t)); 
						lptstrCopy[dtwd.length()] = (TCHAR) 0;    // null character 
						GlobalUnlock(hglbCopy); 
 
						// Place the handle on the clipboard. 
 
						SetClipboardData(CF_UNICODETEXT, hglbCopy); 
					} 
				}
				CloseClipboard();
			}
		}
	}
	bool IsFileEmpty(HANDLE hFile)
	{
		DWORD hsize;
		DWORD lsize = GetFileSize(hFile, &hsize);
		return !(hsize|lsize);
	}
};
static info g_info;
