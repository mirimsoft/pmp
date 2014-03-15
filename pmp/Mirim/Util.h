#pragma once
#include "ProTk.h"
#include "WinSpool.h"
#include <iptypes.h>
#include "Iphlpapi.h"

namespace Mirim
{
	class Util
	{
	public:
        static ProError Util::TrimString(const wchar_t *w_input, wchar_t *w_output);
        static ProError Util::TrimString(const char *input, char *output);
		static ProError Util::ReplaceString(const wchar_t *w_input, const wchar_t *w_what, const wchar_t *w_with, wchar_t *w_output);
		static ProError Util::RemoveWhiteSpace(const wchar_t *w_input, wchar_t *w_output);
		static ProError Util::ExecuteCommand(bool wait, wchar_t *w_command, wchar_t *w_option);
		static ProError Util::GetFilesList(wchar_t *w_path, std::vector<std::wstring> &list);
		static ProError Util::DeleteFiles(wchar_t *w_path);
		static ProError Util::GetMacAddresses(std::vector<std::wstring> &list);
		static bool Util::MacAddressExists(const wchar_t *w_address);
		static bool Util::DirectoryExists(const wchar_t *w_path);
		static bool Util::FileExists(const wchar_t *w_file_path);
	};

}