#include "Util.h"

namespace Mirim
{
	ProError Util::TrimString(const wchar_t *w_input, wchar_t *w_output)
	{
		wcscpy(w_output, w_input);
		wchar_t *p = w_output;
		int length = static_cast<int>(wcslen(p));

		while(iswspace(p[length - 1]))
			p[--length] = 0;

		while(*p && iswspace(*p))
			++p, --length;

		memmove(w_output, p, sizeof(wchar_t) * length + 1);

		return PRO_TK_NO_ERROR;
	}

	ProError Util::TrimString(const char *input, char *output)
	{
		strcpy(output, input);
		char *p = output;
		int length = static_cast<int>(strlen(p));

		while(isspace(p[length - 1]))
			p[--length] = 0;

		while(*p && isspace(*p))
			++p, --length;

		memmove(output, p, sizeof(char) * length + 1);

		return PRO_TK_NO_ERROR;
	}

	ProError Util::ReplaceString(const wchar_t *w_input, const wchar_t *w_what, const wchar_t *w_with, wchar_t *w_output)
	{
		wchar_t *w_input1 = new wchar_t[wcslen(w_input) + 1];
		wcscpy(w_input1, w_input);
		w_input1 = wcsupr(w_input1);

		wchar_t *w_what1 = new wchar_t[wcslen(w_what) + 1];
		wcscpy(w_what1, w_what);
		w_what1 = wcsupr(w_what1);

		wchar_t *w_pointer = wcsstr(w_input1, w_what1);
		if (w_pointer == NULL)
		{
			return PRO_TK_BAD_INPUTS;
		}

		wcscpy(w_output, w_input);
		w_output[w_pointer - w_input1] = 0;

		wcscat(w_output, w_with);

		w_pointer += wcslen(w_what);
		wcscpy(w_input1, w_input);
		wcscat(w_output, w_pointer);

		delete[] w_input1;
		delete[] w_what1;

		return PRO_TK_NO_ERROR;
	}

	ProError Util::RemoveWhiteSpace(const wchar_t *w_input, wchar_t *w_output)
	{
		wchar_t *w_line = new wchar_t[wcslen(w_input) + 1];
		wcscpy(w_line, w_input);
		wchar_t *w_from = w_line;
		wchar_t *w_to = w_output;
		while(*w_from)
		{
			*w_to = *w_from++;
			if (!isspace(*w_to)) w_to++;
		}

		*w_to = NULL;

		delete[] w_line;
		return PRO_TK_NO_ERROR;
	}



	ProError Util::ExecuteCommand(bool wait, wchar_t *w_command, wchar_t *w_options)
	{
		DWORD ExitCode;
		int iExitCode;
		BOOL success;
		SHELLEXECUTEINFO SEInfo;

		memset( &SEInfo, 0, sizeof(SEInfo));
		SEInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		SEInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		SEInfo.hwnd = NULL;
		SEInfo.lpFile = w_command;         // execution file
		SEInfo.lpParameters = w_options;    // Parameter data file
		SEInfo.lpDirectory = NULL;
		SEInfo.nShow = SW_SHOWNORMAL;
		SEInfo.nShow = SW_HIDE;

		success = ShellExecuteEx(&SEInfo);
		if (success)
		{
			if (wait)
			{
				WaitForSingleObject(SEInfo.hProcess, INFINITE);
				GetExitCodeProcess(SEInfo.hProcess, &ExitCode);
				iExitCode = (int)ExitCode;

				if (iExitCode == 0)
					return(PRO_TK_NO_ERROR);
				else
					return(PRO_TK_GENERAL_ERROR);
				//#define STATUS_PENDING                  ((DWORD   )0x00000103L)    
				//#define STILL_ACTIVE                     STATUS_PENDING
			}
			else
			{
				return PRO_TK_NO_ERROR;
			}
		}
		else
		{
			return PRO_TK_GENERAL_ERROR;
		}
	}

	ProError Util::GetFilesList(wchar_t *w_path, std::vector<wstring> &list)
	{
		ProPath	w_filter;
		wcscpy(w_filter, w_path);
		wcscat(w_filter, L"\\*");

		list.clear();
		HANDLE handle;
		WIN32_FIND_DATA find_data;
		handle = FindFirstFile(w_filter, &find_data);
		while(handle != INVALID_HANDLE_VALUE)
		{
			const wstring file_name = find_data.cFileName;
			const bool is_directory = (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

			if (!(file_name[0] == '.') && !is_directory) 
			{
				const wstring full_file_name = wstring(w_path) + L"\\" + file_name;
				list.push_back(full_file_name);
			}

			if (!FindNextFile(handle, &find_data))
			{
				FindClose(handle);
				handle = INVALID_HANDLE_VALUE;
			}
		} 

		return PRO_TK_NO_ERROR;
	}

	ProError Util::DeleteFiles(wchar_t *w_path)
	{
		ProError status;
		std::vector<wstring> list;

		status = Util::GetFilesList(w_path, list);
		for(std::vector<std::wstring>::iterator it = list.begin(); it != list.end(); it++)
		{
			try
			{
				DeleteFile(it->c_str());
			}
			catch(...)
			{
				continue;
			}
		}

		return PRO_TK_NO_ERROR;
	}

	ProError Util::GetMacAddresses(std::vector<wstring> &list)
	{
		// Get the buffer length required for IP_ADAPTER_INFO.
		ULONG BufferLength = 0;
		BYTE* pBuffer = 0;
		if (ERROR_BUFFER_OVERFLOW == GetAdaptersInfo( 0, &BufferLength))
		{
			// Now the BufferLength contain the required buffer length.
			// Allocate necessary buffer.
			pBuffer = new BYTE[ BufferLength ];
		}
		else
		{
			return PRO_TK_GENERAL_ERROR;
		}

		// Get the Adapter Information.
		PIP_ADAPTER_INFO pAdapterInfo = reinterpret_cast<PIP_ADAPTER_INFO>(pBuffer);
		GetAdaptersInfo( pAdapterInfo, &BufferLength );

		// Iterate the network adapters and print their MAC address.
		while( pAdapterInfo )
		{
			// Assuming pAdapterInfo->AddressLength is 6.
			wchar_t w_address[32];
			wsprintf(w_address, L"%02X-%02X-%02X-%02X-%02X-%02X",
				pAdapterInfo->Address[0],
				pAdapterInfo->Address[1],
				pAdapterInfo->Address[2],
				pAdapterInfo->Address[3],
				pAdapterInfo->Address[4],
				pAdapterInfo->Address[5]);

			list.push_back(w_address);

			// Get next adapter info.
			pAdapterInfo = pAdapterInfo->Next;
		}

		// deallocate the buffer.
		delete[] pBuffer;

		return PRO_TK_NO_ERROR;
	}

	bool Util::MacAddressExists(const wchar_t *w_address)
	{
		ProError	status;

		std::vector<std::wstring> list;
		status = Util::GetMacAddresses(list);

		std::vector<std::wstring>::iterator it = find(list.begin(), list.end(), w_address);
		return it != list.end();
	}


	bool Util::DirectoryExists(const wchar_t *w_path)
	{
		return _waccess(w_path, 00) != -1;
	}

	bool Util::FileExists(const wchar_t *w_file_path)
	{
		return _waccess(w_file_path, 00) != -1;
	}

}