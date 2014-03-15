#pragma once
#include "ProTk.h"
#include "CApplication.h"
#include "CRange.h"
#include "CRanges.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheets.h"
#include "CWorksheet.h"
#include "StdParam.h"

class MsExcel
{
public:
	bool Visible;
	bool IsStarted;

private:
	CApplication	_application;
	CWorkbooks		_workbooks;
	CWorkbook		_workbook;
	CWorksheets		_worksheets;
	CWorksheet		_worksheet;

public:
	MsExcel(bool visible);
	~MsExcel(void);

public:
	bool MsExcel::OpenWorkbook(const wchar_t *w_file_path);
	bool MsExcel::GetWorksheet(const int sheet_number);
	bool MsExcel::GetWorksheet(const wchar_t *w_sheet_name);
	bool MsExcel::Save();
	bool MsExcel::SaveAs(const wchar_t *w_file_path, bool save_as_2003 = false);
	bool MsExcel::Quit();



	COleSafeArray MsExcel::ReadRange(const wchar_t *w_cell1, const wchar_t *w_cell2);
	COleSafeArray MsExcel::ReadRange(const wchar_t *w_cell1, int n_cols, int n_rows);

	bool MsExcel::GetValidRange(const wchar_t *w_cell1, int n_columns, int *n_rows);
	bool MsExcel::WriteRange(const wchar_t *w_cell1, COleSafeArray &safe_array);
	bool MsExcel::InsertRange(const wchar_t *w_cell1, int n_rows, int n_cols); 

	bool MsExcel::GetStringValue(COleSafeArray &safe_array, int row, wchar_t *w_value);
	bool MsExcel::GetStringValue(COleSafeArray &safe_array, int row, int col, wchar_t *w_value);
	void MsExcel::SetStringValue(COleSafeArray &safe_array, int row, int col, const wchar_t *w_value);
	bool MsExcel::IndexToString(int row, int col, wchar_t *w_cell);
	bool MsExcel::StringToIndex(const wchar_t *w_cell, int *row, int *col);
	bool MsExcel::GetCellValue(wchar_t *w_cell, wchar_t *w_value);

public:
	
	bool MsExcel::ReadStdParams(std::vector<Gui::StdParam> &list);
	bool MsExcel::SaveStdParams(std::vector<Gui::StdParam> &list);
    bool MsExcel::ReadParamNames(std::vector<std::pair<bool, wstring>> &list1);
    bool MsExcel::SaveParamNames(std::vector<std::pair<bool, wstring>> &list1);

};

