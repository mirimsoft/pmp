#include "MsExcel.h"
#include "StdAfx.h"

#pragma region Constructor

MsExcel::MsExcel(bool visible)
	:Visible(visible)
{
	try
	{
		this->IsStarted = false;

		AfxEnableControlContainer();
		if (!this->_application.CreateDispatch(L"Excel.Application"))
		{
			AfxMessageBox(L"ERROR in App.CreateDispatch(): Cannot start Microsoft Excel...");  
			return;  
		}

		this->_application.put_Visible(this->Visible);  
		LPDISPATCH lpdisp = this->_application.get_Workbooks();
		this->_workbooks.AttachDispatch(lpdisp);  

		// Now Excel started
		this->IsStarted = true;
	}
	catch(COleException *e)
	{
		wchar_t w_message[1024];    
		wsprintf(w_message, L"COleException. SCODE: %08lx.", (long)e->m_sc);
		::MessageBox(NULL, w_message, L"COleException", MB_TOPMOST | MB_OK);
	}
	catch(COleDispatchException *e)
	{
		wchar_t w_message[1024];     
		wsprintf(w_message, L"COleDispatchException. SCODE: %08lx, Description: \"%s\".", (long)e->m_wCode,(LPSTR)e->m_strDescription.GetBuffer(512));
		::MessageBox(NULL, w_message, L"COleDispatchException", MB_TOPMOST | MB_OK);
	}
	catch(...)
	{
		::MessageBox(NULL, L"General Exception caught.", L"Catch-All", MB_TOPMOST | MB_OK);
	}
}


MsExcel::~MsExcel(void)
{

}

#pragma endregion

#pragma region Common Methods

bool MsExcel::OpenWorkbook(const wchar_t *w_file_path)
{
	CFileFind file_find;
	if(!file_find.FindFile(w_file_path))
	{
		wchar_t w_message[512];
		wsprintf(w_message, L"File not found: %s", w_file_path);
		::MessageBox(NULL, w_message, L"ERROR", MB_TOPMOST | MB_OK);
		return false;
	}

	try
	{
		COleVariant vresult;  
		COleVariant covTrue((short)TRUE);
		COleVariant covFalse((short)FALSE);
		COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

        LPDISPATCH lpdispatch = this->_workbooks.Open(  
			w_file_path,  // Filename
			covOptional,  // UpdateLink
			covFalse,	  // Readonly
			covOptional,  // Format
			covOptional,  // Password
			covOptional,  // WriteResPassword
			covOptional,  // IgnoreReadOnlyRecommended
			covOptional,  // Origin
			covOptional,  // Delimeter
			covOptional,  // Editable
			covOptional,  // Notify
			covOptional,  // Converter
			covOptional,  // AddToMru
			covOptional,  // Local
			covOptional); // CorruptLoad 

		// get Workbook  
		this->_workbook.AttachDispatch(lpdispatch);
        return true;
	}
	catch(...)
	{
		wchar_t w_message[512];
		wsprintf(w_message, L"Could not open Excel file: %s", w_file_path);
		::MessageBox(NULL, w_message, L"ERROR", MB_TOPMOST | MB_OK);
		return false;
	}
}

bool MsExcel::GetWorksheet(const int sheet_number)
{
    try
    {
        LPDISPATCH lpdispatch = this->_workbook.get_Worksheets();
        this->_worksheets.AttachDispatch(lpdispatch);

        lpdispatch = this->_worksheets.get_Item(COleVariant((short) sheet_number));
        this->_worksheet.AttachDispatch(lpdispatch);
        CString name = this->_worksheet.get_Name();
        return true;
    }
    catch(...)
    {
        wchar_t w_message[512];
        wsprintf(w_message, L"Could not find Workheet #: %d", sheet_number);
        ::MessageBox(NULL, w_message, L"ERROR", MB_TOPMOST | MB_OK);
        return false;
    }
}

bool MsExcel::GetWorksheet(const wchar_t *w_sheet_name)
{
	try
	{
		LPDISPATCH lpdispatch = this->_workbook.get_Worksheets();
		this->_worksheets.AttachDispatch(lpdispatch);

		this->_worksheet = this->_worksheets.get_Item(COleVariant(w_sheet_name));
		CString name = this->_worksheet.get_Name();
        return true;
	}
	catch(...)
	{
		wchar_t w_message[512];
		wsprintf(w_message, L"Could not find Workheet #: %s", w_sheet_name);
		::MessageBox(NULL, w_message, L"ERROR", MB_TOPMOST | MB_OK);
		return false;
	}
}

bool MsExcel::Save()
{
    try
    {
        this->_workbook.Save();
        return true;
    }
    catch(...)
    {
        wchar_t w_message[512];
        wsprintf(w_message, L"Could not save Workbook...");
        ::MessageBox(NULL, w_message, L"ERROR", MB_TOPMOST | MB_OK);
        return false;
    }
}

bool MsExcel::SaveAs(const wchar_t *w_file_path, bool save_as_2003)
{
	try
	{
		COleVariant vresult;  
		COleVariant covTrue((short)TRUE);
		COleVariant covFalse((short)FALSE);
		COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

		if (save_as_2003)
		{
			this->_workbook.SaveAs(
				COleVariant(w_file_path),	// Filename
				COleVariant((long) 56),  	// FileFormat xlExcel8 = 56,
				covOptional,	  			// Password
				covOptional,  				// WriteResPassword
				covOptional,  				// ReadOnlyRecommended
				covOptional,  				// CreateBackup
				1,  						// AccessMode = xlNoChange = 1, xlShared = 2, xlExclusive = 3
				covOptional,  				// ConflictResolution
                covOptional,  				// AddToMru
                covOptional,  				// TextCodepage
                covOptional,  				// TextVisualLayout
                covOptional); 				// Local
            return true;
        }
        else
        {
            this->_workbook.SaveAs(  
                COleVariant(w_file_path),	// Filename
                covOptional,  				// FileFormat xlExcel8 = 56,
                covOptional,	  			// Password
                covOptional,  				// WriteResPassword
                covOptional,  				// ReadOnlyRecommended
                covOptional,  				// CreateBackup
                1,  						// AccessMode = xlNoChange = 1, xlShared = 2, xlExclusive = 3
                covOptional,  				// ConflictResolution
                covOptional,  				// AddToMru
                covOptional,  				// TextCodepage
                covOptional,  				// TextVisualLayout
                covOptional); 				// Local
            return true;
        }
    }
    catch(...)
    {
		wchar_t w_message[512];
		wsprintf(w_message, L"Could not SaveAs Excel file: %s", w_file_path);
		::MessageBox(NULL, w_message, L"ERROR", MB_TOPMOST | MB_OK);
		return false;
	}

}

bool MsExcel::Quit()
{
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	this->_workbook.Close(covOptional, COleVariant(this->_workbook.get_FullName()), covOptional);  
	this->_workbooks.Close();  
	this->_application.Quit(); 
	return true;
}

bool MsExcel::GetCellValue(wchar_t *w_cell, wchar_t *w_value)
{
	try
	{
		LPDISPATCH lpdispatch = this->_worksheet.get_Range(COleVariant(w_cell), COleVariant(w_cell));

		CRange range;
		range.AttachDispatch(lpdispatch);

		VARIANT variant = range.get_Value2();
		wcscpy(w_value, variant.bstrVal);
		return true;
	}
	catch(...)
	{
		wchar_t w_message[512];
		wsprintf(w_message, L"Failed to read cell: %s", w_cell);
		::MessageBox(NULL, w_message, L"ERROR", MB_TOPMOST | MB_OK);

		return false;
	}

}

COleSafeArray MsExcel::ReadRange(const wchar_t *w_cell1, const wchar_t *w_cell2)
{
	try
	{
		LPDISPATCH lpdispatch;
		if (wcslen(w_cell2) < 1)
		{
			COleVariant covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
			lpdispatch = this->_worksheet.get_Range(COleVariant(w_cell1), COleVariant(w_cell1));
		}
		else
		{
			lpdispatch = this->_worksheet.get_Range(COleVariant(w_cell1), COleVariant(w_cell2));
		}

		CRange range;
		range.AttachDispatch(lpdispatch);
		VARIANT variant = range.get_Value2();
		COleSafeArray safe_array(variant);
		return safe_array;
	}
	catch(...)
	{
		wchar_t w_message[512];
		wsprintf(w_message, L"Failed to read range: %s, %s", w_cell1, w_cell2);
		::MessageBox(NULL, w_message, L"ERROR", MB_TOPMOST | MB_OK);
		return NULL;
	}
}

COleSafeArray MsExcel::ReadRange(const wchar_t *w_cell1, int n_cols, int n_rows)
{
	if (n_cols == 0) return NULL;
	else if (n_cols == 1) n_cols++;
	
	try
	{
		LPDISPATCH lpdispatch = this->_worksheet.get_Range(COleVariant(w_cell1), COleVariant(w_cell1));

		CRange range;
		range.AttachDispatch(lpdispatch);
		lpdispatch = range.get_Resize(COleVariant((long) n_rows), COleVariant((long) n_cols));
		range.AttachDispatch(lpdispatch);
		VARIANT variant = range.get_Value2();

		COleSafeArray safe_array(variant);
		return safe_array;
	}
	catch(...)
	{
		wchar_t w_message[512];
		wsprintf(w_message, L"Failed to read range: %s, Columns = %d, Rows = %d", w_cell1, n_cols, n_rows);
		::MessageBox(NULL, w_message, L"ERROR", MB_TOPMOST | MB_OK);
		TLog::Print(w_message);

		return NULL;
	}
}

bool MsExcel::GetValidRange(const wchar_t *w_cell1, const int n_columns, int *n_rows)
{
	int col_count;
	int row_count;
	try
	{
		// Find Used Range
		COleVariant covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
		LPDISPATCH lpdispatch = this->_worksheet.get_UsedRange();
		CRange range;
		range.AttachDispatch(lpdispatch);

		CRange rows;
		rows.AttachDispatch(range.get_Rows());
		CRange columns;
		columns.AttachDispatch(range.get_Columns());

		row_count = rows.get_Count();
		col_count = columns.get_Count();

		// Set Range from First cell
		lpdispatch = this->_worksheet.get_Range(COleVariant(w_cell1), COleVariant(w_cell1));
		range.AttachDispatch(lpdispatch);

		// and resize to Used Range with specified column width
		lpdispatch = range.get_Resize(COleVariant((long) row_count), COleVariant((long) n_columns));
		range.AttachDispatch(lpdispatch);

		VARIANT variant = range.get_Value2();
		COleSafeArray safe_array(variant);

		long row_lower, col_lower;
		safe_array.GetLBound(1, &row_lower);
		safe_array.GetLBound(2, &col_lower);
		long row_upper, col_upper;
		safe_array.GetUBound(1, &row_upper);
		safe_array.GetUBound(2, &col_upper);

		// Find empty row
		*n_rows = 0;
		long index[2];
		VARIANT value;
		for (int i=row_lower; i<=row_upper; i++)
		{
			bool is_empty = true;
			for (int j=col_lower; j<=col_upper; j++)
			{
				index[0] = i;
				index[1] = j;
				safe_array.GetElement(index, &value);

				if (value.vt == VT_BSTR)
				{
					CString c_str(value.bstrVal);
					c_str = c_str.Trim();		
					if (c_str.GetLength() > 0)
					{
						is_empty = false;
						break;
					}
				}
				else if (value.vt != VT_EMPTY)
				{
					is_empty = false;
					break;
				}
			}

			if (is_empty) break;

			(*n_rows)++;
		}

        if (*n_rows == 0) return false;

		lpdispatch = this->_worksheet.get_Range(COleVariant(w_cell1), COleVariant(w_cell1));
		range.AttachDispatch(lpdispatch);
		lpdispatch = range.get_Resize(COleVariant((long) *n_rows), COleVariant((long) n_columns));
		range.AttachDispatch(lpdispatch);

		safe_array.Destroy();
		return true;
	}
	catch(...)
	{
		wchar_t w_message[512];
		wsprintf(w_message, L"Failed to GetValidRange: %s, %s", w_cell1);
		::MessageBox(NULL, w_message, L"ERROR", MB_TOPMOST | MB_OK);
		TLog::Print(w_message);

		return false;
	}
}

bool MsExcel::IndexToString(const int row, const int col, wchar_t *w_cell)
{
	if (col > 26)
		wsprintf(w_cell, L"%c%c%d", 'A' + (col -1)/26 -1, 'A' + (col -1) %26, row);
	else
		wsprintf(w_cell, L"%c%d", 'A' + (col -1) %26, row);

	return true;
}

bool MsExcel::StringToIndex(const wchar_t *w_cell, int *row, int *col)
{
	wchar_t w_name[16];
	wcscpy_s(w_name, w_cell);
	wchar_t *w_ptr = w_name;
	while(*w_ptr)
	{
		if(isdigit(*w_ptr))
		{
			*row = _wtoi(w_ptr);
			*w_ptr = 0;
			if (wcslen(w_name) == 1)
				*col = w_name[0] - 'A' + 1;
			else if (wcslen(w_name) == 2)
				*col = (w_name[0] - 'A' + 1) * 26 + w_name[1] - 'A' + 1;
			else 
				return false;
		}
		else
			w_ptr++;
	}

	return true;
}

bool MsExcel::GetStringValue(COleSafeArray &safe_array, int row, int col, wchar_t *w_value)
{
    *w_value = 0;

    long index[2] = { row, col };
    VARIANT value;

	safe_array.GetElement(index, &value);
	
    _bstr_t bs(value);
    if (value.vt == VT_BOOL)
    {
        if (value.iVal == 0)
            wcscpy(w_value, L"False");
        else
            wcscpy(w_value, L"True");
    }
    else
    {
        std::string str(static_cast<const char*>(bs));
        size_t converted;
        mbstowcs_s(&converted, w_value, strlen(str.c_str()) + 1, str.c_str(), _TRUNCATE);
    }

    return true;
}


void MsExcel::SetStringValue(COleSafeArray &safe_array, int row, int col, const wchar_t *w_value)
{
	VARIANT v;
	long index[] = {row, col};

	VariantInit(&v);
	v.vt = VT_BSTR;
	v.bstrVal = SysAllocString(w_value);
	safe_array.PutElement(index, v.bstrVal);
	SysFreeString(v.bstrVal);
	VariantClear(&v);
	return;
}


bool MsExcel::InsertRange(const wchar_t *w_cell1, const int n_rows, const int n_cols)
{
	LPDISPATCH lpdispatch = this->_worksheet.get_Range(COleVariant(w_cell1), COleVariant(w_cell1));
	CRange range;
	range.AttachDispatch(lpdispatch);
	range = range.get_Resize(COleVariant((long) n_rows), COleVariant((long) n_cols));

	// XlInsertShiftDirection: xlShiftToRight = -4161, xlShiftDown = -4121
	// XlInsertFormatOrigin: xlFormatFromLeftOrAbove = 0, xlFormatFromRightOrBelow = 1
	range.Insert(COleVariant((short) -4121), COleVariant((short) 0)); 
	return true;
}


bool MsExcel::WriteRange(const wchar_t *w_cell1, COleSafeArray &safe_array)
{
	long row_lower, col_lower;
	safe_array.GetLBound(1, &row_lower);
	safe_array.GetLBound(2, &col_lower);

	long row_upper, col_upper;
	safe_array.GetUBound(1, &row_upper);
	safe_array.GetUBound(2, &col_upper);

	long n_rows = row_upper - row_lower + 1;
	long n_cols = col_upper - col_lower + 1;
	if (n_rows > 2)
	{
		int row, col;
		this->StringToIndex(w_cell1, &row, &col);
		wchar_t w_format_cell[16];
		this->IndexToString(row + 1, col, w_format_cell);
		this->InsertRange(w_format_cell, n_rows -2, n_cols);
	}

	//COleVariant covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
	//CString address = range.get_Address(covOptional, covOptional, 1, covOptional, covOptional);
	// get_Address return value: $B$3 or $B$3:$F$10

	LPDISPATCH lpdispatch = this->_worksheet.get_Range(COleVariant(w_cell1), COleVariant(w_cell1));
	CRange range;
	range.AttachDispatch(lpdispatch);
	range = range.get_Resize(COleVariant((long)n_rows), COleVariant((long)n_cols)); 
	range.put_Value2(COleVariant(safe_array));
	return true;
}

#pragma endregion


bool MsExcel::ReadStdParams(std::vector<Gui::StdParam> &list)
{
	wchar_t w_cell1[] = L"B4";
	int n_rows = 0;
	int n_columns = 6;
	list = std::vector<Gui::StdParam>();
	if (!this->GetValidRange(w_cell1, n_columns, &n_rows)) return false;

	COleSafeArray safe_array = this->ReadRange(w_cell1, n_columns, n_rows);
	
    long row_lower, col_lower;
	safe_array.GetLBound(1, &row_lower);
	safe_array.GetLBound(2, &col_lower);
	long row_upper;
	safe_array.GetUBound(1, &row_upper);
	for (int i=row_lower; i<=row_upper; i++)
	{
		Gui::StdParam param;
		this->GetStringValue(safe_array, i, col_lower, param.Name);
		this->GetStringValue(safe_array, i, col_lower + 1, param.Type);
		this->GetStringValue(safe_array, i, col_lower + 2, param.ReadOnly);
		this->GetStringValue(safe_array, i, col_lower + 3, param.Default);
		this->GetStringValue(safe_array, i, col_lower + 4, param.Names);
		this->GetStringValue(safe_array, i, col_lower + 5, param.Remark);
		list.push_back(param);
	}

	safe_array.Destroy();
	return true;
}


bool MsExcel::SaveStdParams(std::vector<Gui::StdParam> &list)
{
	const wchar_t w_cell1[] = L"B4";
	int n_rows = static_cast<int>(list.size());
	int n_cols = 6;

	COleSafeArray safe_array;
	DWORD n_elements[] = { n_rows, n_cols};
	safe_array.Create(VT_BSTR, 2, n_elements);

	for (int i=0; i<n_rows; i++)
	{
		this->SetStringValue(safe_array, i, 0, list[i].Name);
		this->SetStringValue(safe_array, i, 1, list[i].Type);
		this->SetStringValue(safe_array, i, 2, list[i].ReadOnly);
		this->SetStringValue(safe_array, i, 3, list[i].Default);
		this->SetStringValue(safe_array, i, 4, list[i].Names);
		this->SetStringValue(safe_array, i, 5, list[i].Remark);
	}

	this->WriteRange(w_cell1, safe_array);
	safe_array.Destroy();
	return true;
}



bool MsExcel::ReadParamNames(std::vector<std::pair<bool, wstring>> &list)
{
	wchar_t w_cell1[] = L"I4";
	int n_rows = 0;
	int n_columns = 1;
	list = std::vector<std::pair<bool, wstring>>();

	if (!this->GetValidRange(w_cell1, n_columns, &n_rows)) return false;
    
	COleSafeArray safe_array = this->ReadRange(w_cell1, n_columns, n_rows);
	if (safe_array)
	{
		long row_lower, col_lower;
		safe_array.GetLBound(1, &row_lower);
		safe_array.GetLBound(2, &col_lower);
		long row_upper;
		safe_array.GetUBound(1, &row_upper);

		wchar_t w_value[256];
		for (int i=row_lower; i<=row_upper; i++)
		{
			this->GetStringValue(safe_array, i, col_lower, w_value);
			list.push_back(std::make_pair(true, wstring(w_value)));
		}

		safe_array.Destroy();
	}
	else
	{
		::MessageBox(NULL, L"Failed to read parameters to delelte...", L"ERROR", MB_OK);
	}

	return true;
}


bool MsExcel::SaveParamNames(std::vector<std::pair<bool, wstring>> &list)
{
	const wchar_t w_cell1[] = L"I4";
	int n_rows = static_cast<int>(list.size());
    if (n_rows < 1) return false;

	int n_cols = 1;

	COleSafeArray safe_array;
	DWORD n_elements[] = { n_rows, n_cols};
	safe_array.Create(VT_BSTR, 2, n_elements);

	for (int i=0; i<n_rows; i++)
	{
		this->SetStringValue(safe_array, i, 0, list[i].second.c_str());
	}

	this->WriteRange(w_cell1, safe_array);
	safe_array.Destroy();
	return true;
}