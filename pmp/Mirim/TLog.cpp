#include "TLog.h"

FILE	*TLog::fp_log = NULL;
int		TLog::line_number = 0;
wchar_t TLog::w_file_path[MAX_PATH];
wchar_t TLog::w_str[MAX_PATH];
char	TLog::c_str[MAX_PATH];
time_t  TLog::start_time;


wchar_t *TLog::GetTimeWstr()
{
	time_t now(NULL);
	time(&now);

	struct tm current_time;
	localtime_s(&current_time, &now);

	swprintf_s(TLog::w_str, MAX_PATH, L"@[%04d/%02d/%02d %02d:%02d:%02d] # ", 
		current_time.tm_year+1900, 
		current_time.tm_mon+1, 
		current_time.tm_mday, 
		current_time.tm_hour, 
		current_time.tm_min, 
		current_time.tm_sec);

	return TLog::w_str;
}

char *TLog::GetTimeCstr()
{
	time_t now(NULL);
	time(&now);

	struct tm current_time;
	localtime_s(&current_time, &now);

	sprintf_s(TLog::c_str, MAX_PATH, "@[%04d/%02d/%02d %02d:%02d:%02d] # ", 
		current_time.tm_year+1900, 
		current_time.tm_mon+1, 
		current_time.tm_mday, 
		current_time.tm_hour, 
		current_time.tm_min, 
		current_time.tm_sec);

	return TLog::c_str;
}

void TLog::CreateFolder(const wchar_t *w_directory)
{
	wchar_t  w_path[MAX_PATH];
	wchar_t	 w_dir[MAX_PATH];

	wcscpy_s(w_path, MAX_PATH, w_directory);

	wchar_t  *p = w_path;      
	wchar_t	 *q = w_dir;  

	while(*p)
	{
		if ((L'\\' == *p) ||(L'/' == *p))    
		{
			if (L':' != *(p-1)) 
			{
				CreateDirectory(w_dir, NULL);
			}
		}

		*q++ = *p++;
		*q = '\0';
	}

	CreateDirectory(w_dir, NULL);  
}

long TLog::GetFileSize(const wchar_t *w_file_path)
{
	struct _stat64 stat;
	_wstat64(w_file_path, &stat);

	return(long) stat.st_size;
}

bool TLog::IsOverSize(const wchar_t *w_file_path)
{
	struct _stat64 stat;
	_wstat64(w_file_path, &stat);

	int size_in_megabyte = stat.st_size/1024/1024;
	return  size_in_megabyte > 10; 
}



void TLog::PrintHeader()
{
	fwprintf(TLog::fp_log, L"#===============================================================================\n");
	fwprintf(TLog::fp_log, L"#    Pro/TOOLKIT Application Log File\n");
	fwprintf(TLog::fp_log, L"#    By Mirim System Co., Ltd\n#\n");
	fwprintf(TLog::fp_log, L"#    File Path: %s\n", TLog::w_file_path);
	fwprintf(TLog::fp_log, L"#===============================================================================\n");

	return;
}


void TLog::Open(const wchar_t *w_file_path, const bool append)
{
	if (TLog::IsOverSize(w_file_path))
		_wremove(w_file_path);

	errno_t error;
	if (append)
		error = _wfopen_s(&TLog::fp_log, TLog::w_file_path, L"a");
	else
		error = _wfopen_s(&TLog::fp_log, TLog::w_file_path, L"w");

	if (error != 0 || fp_log == NULL)
	{
		ProPath w_message;
		wsprintf(w_message, L"Could not open log file: %s", TLog::w_file_path);
		MessageBox(NULL, w_message, L"Pro/TOOLKIT ERROR", MB_OK);
		return;
	}

	TLog::PrintHeader();

	fclose(TLog::fp_log);
}

void TLog::Open(const wchar_t *w_directory, const wchar_t *w_file_name , const bool append)
{
	TLog::CreateFolder(w_directory);
	wsprintf(TLog::w_file_path, L"%s\\%s", w_directory, w_file_name);
	TLog::Open(TLog::w_file_path, append);
}


void TLog::Open()
{
	ProPath w_path;
	ProToolkitApplTextPathGet(w_path);
	TLog::Open(w_path, L"pmp_log.txt");
}

void TLog::Close()
{
	if (TLog::fp_log != NULL)
	{
		fclose(TLog::fp_log);
	}
}


void TLog::Print(const wchar_t *w_format, ...)
{
	errno_t error = _wfopen_s(&TLog::fp_log, TLog::w_file_path, L"a");
	if (TLog::fp_log == NULL) return;

	wchar_t	w_log[MAX_PATH] = L"";
	va_list args;
	va_start(args, w_format);
	int count = vswprintf_s(w_log, MAX_PATH, w_format, args);
	va_end(args);
	fwprintf_s(TLog::fp_log, L"%s%s\n", TLog::GetTimeWstr(), w_log);
	fclose(TLog::fp_log);
}

void TLog::Print(const char *format, ...)
{
	errno_t error = _wfopen_s(&TLog::fp_log, TLog::w_file_path, L"a");
	if (TLog::fp_log == NULL) return;

	char log[MAX_PATH] = "";
	va_list args;
	va_start(args, format);
	int count = vsprintf_s(log, MAX_PATH, format, args);
	va_end(args);
	fprintf_s(TLog::fp_log, "%s%s\n", TLog::GetTimeCstr(), log);
	fclose(TLog::fp_log);
}

void TLog::Print2(const wchar_t *w_format, ...)
{
	errno_t error = _wfopen_s(&TLog::fp_log, TLog::w_file_path, L"a");
	if (TLog::fp_log == NULL) return;

	wchar_t	w_log[MAX_PATH] = L"";
	va_list args;
	va_start(args, w_format);
	int count = vswprintf_s(w_log, MAX_PATH, w_format, args);
	va_end(args);
	fwprintf_s(TLog::fp_log, L"%s%s\n", TLog::GetTimeWstr(), w_log);
	fclose(TLog::fp_log);

	char log[MAX_PATH];
	size_t n_converted;
	wcstombs_s(&n_converted, log, wcslen(w_log) + 1, w_log, _TRUNCATE);
	ProMessageClear();
	ProMessageDisplay(MSGFIL, "PMP_MSG %0s", log);
}

void TLog::Print2(const char *format, ...)
{
	if (TLog::fp_log == NULL) return;

	char log[MAX_PATH] = "";
	va_list args;
	va_start(args, format);
	int count = vsprintf_s(log, MAX_PATH, format, args);
	va_end(args);
	fprintf_s(TLog::fp_log, "%s%s\n", TLog::GetTimeCstr(), log);
	fclose(TLog::fp_log);

	ProMessageClear();
	ProMessageDisplay(MSGFIL, "PMP_MSG %0s", log);
}