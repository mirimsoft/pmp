#pragma once
#include "ProTk.h"


namespace Mirim
{
	class Option
	{
		// Static Data Memebr
	public:
		static ProPath ProductName;
		static ProPath ApplicationRoot;
		static ProPath FilePath;

	public:
		ProPath LicenseFile;
		ProPath SourceFolder;
		ProPath PrinterName;
		ProPath PaperSize;
		ProPath PrintFormat;

		bool ShowAsm1;
		bool ShowPrt1;
		bool ShowAsm2;
		bool ShowDrw2;

		bool ExportDxf;
		bool ExportDwg;
		bool ExportHpgl;
		bool ExportPdf;
		bool Print;

		int  TotalLength;
		int  PartNrStart;
		int  PartNrLength;

        wchar_t *ColumnWidths;
        int     n_folders;
	private:
		static Option *_uniqueInstance;

	private:
		Option(void);
		~Option(void);

	public:
		static Option *Option::GetUniqueInstance();
		static Option *Option::Read();
		static ProError Option::Save(Option &option);
        static ProError Option::GetRootDirectory(wchar_t *w_path);
	};

}