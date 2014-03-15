#pragma once
#include <ctime>
#include <climits>
#include "ProTk.h"

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

class TLog
{
public:
	static FILE		*TLog::fp_log;
	static wchar_t  TLog::w_file_path[MAX_PATH];
	static time_t   TLog::start_time;

private:
	static int		TLog::line_number;
	static wchar_t  TLog::w_str[MAX_PATH];
	static char     TLog::c_str[MAX_PATH];

private:
	const wchar_t  *TLog::w_message;

public:
	TLog::TLog(const wchar_t *w_message)
		:w_message(w_message)
	{
		TLog::Print(L"===> %s", w_message);
	}

	~TLog()
	{
		TLog::Print(L"<=== %s", w_message);
	}

public:
	static void TLog::Open(const wchar_t *w_directory, const wchar_t *w_file_name, bool append = false);
	static void TLog::Open(const wchar_t *w_file_path, bool append = false);
	static void TLog::Open();
	static void TLog::Close();

	static void TLog::Print(const wchar_t *w_format, ...);
	static void TLog::Print(const char *format, ...);

	static void TLog::Print2(const wchar_t *w_format, ...);
	static void TLog::Print2(const char *format, ...);

	static void TLog::CreateFolder(const wchar_t *w_path);
	static void TLog::PrintHeader();
	static bool TLog::IsOverSize(const wchar_t *w_file_path);
	static long TLog::GetFileSize(const wchar_t *w_file_path);

	static void TLog::StartTimer()
	{
		time(&TLog::start_time);
	}

	static double TLog::GetTimeSpan()
	{
		time_t now;
		time(&now);
		return difftime(now, TLog::start_time);
	}

	static wchar_t *TLog::GetTimeWstr();
	static char    *TLog::GetTimeCstr();
};

