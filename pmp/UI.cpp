#include "stdafx.h"
#include "UI.h"

namespace Mirim
{
#pragma region Pro/TOOLKIT UI Operation

	bool UI::CopyToClipboard(const wchar_t *w_text)
	{
		HGLOBAL hGlobalCopy;

		if (OpenClipboard(NULL))
		{
			EmptyClipboard();
			wchar_t *wcBuffer = 0;
			hGlobalCopy = GlobalAlloc(GMEM_MOVEABLE, (wcslen(w_text) + 1) * sizeof(wchar_t));

			wcBuffer = (wchar_t*)GlobalLock(hGlobalCopy);
			wcscpy(wcBuffer, w_text);

			GlobalUnlock(hGlobalCopy);
			SetClipboardData(CF_UNICODETEXT, hGlobalCopy);
			CloseClipboard();
			return true;
		}
		else
		{
			return false;
		}
	}


	bool UI::PasteFromClipBoard(wchar_t **w_text)
	{
		// Test to see if we can open the clipboard first.
		if (OpenClipboard(NULL))
		{
			// Retrieve the Clipboard data (specifying that 
			// we want ANSI text (via the CF_TEXT value).
			HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);

			// Call GlobalLock so that to retrieve a pointer
			// to the data associated with the handle returned
			// from GetClipboardData.
			*w_text = (wchar_t *)GlobalLock(hClipboardData); // Pointer to clipboard data

			// Unlock the global memory.
			GlobalUnlock(hClipboardData);

			// Finally, when finished I simply close the Clipboard
			// which has the effect of unlocking it so that other
			// applications can examine or modify its contents.
			CloseClipboard();

			if (*w_text == NULL) return false;
			else return true;
		}
		else
		{
			return false;
		}
	}

	
	ProError UI::GetInputpanelValue(char *dialog, char *component, wchar_t *w_value)
	{
		ProError	status;
		wchar_t		*w_str;
		*w_value = NULL;
		status = ProUIInputpanelWidestringGet(dialog, component, &w_str);
		if (status != PRO_TK_NO_ERROR) return status;

		wcscpy_s(w_value, wcslen(w_str) + 1, w_str);

		return PRO_TK_NO_ERROR;
	}

	ProError UI::GetInputpanelValue(char *dialog, char *component, int *value)
	{
		return  ProUIInputpanelIntegerGet(dialog, component, value);
	}

	ProError UI::GetInputpanelValue(char *dialog, char *component, double *value)
	{
		return ProUIInputpanelDoubleGet(dialog, component, value);
	}

	ProError UI::SetInputpanelValue(char *dialog, char *component, wchar_t *w_value)
	{
		return ProUIInputpanelWidestringSet(dialog, component, w_value);
	}

	ProError UI::SetInputpanelValue(char *dialog, char *component, int value)
	{
		return  ProUIInputpanelIntegerSet(dialog, component, value);
	}

	ProError UI::SetInputpanelValue(char *dialog, char *component, double value)
	{
		return ProUIInputpanelDoubleSet(dialog, component, value);
	}



	ProError UI::GetOptionMenuSelectedLabel(char *dialog, char *component, wchar_t *w_selected_label)
	{
		ProError	status;
        wchar_t     *w_value;

		*w_selected_label = 0;
        status = ProUIOptionmenuValueGet(dialog, component, &w_value);
        wcscpy(w_selected_label, w_value);
        ProWstringFree(w_value);

		return status;
	}

	//ProError UI::GetOptionMenuSelectedName(char *dialog, char *component, wchar_t *w_selected_name)
	//{
	//	ProError	status;
	//	char		**names;
	//	int			n_count;

	//	*w_selected_name = 0;
	//	status = ProUIOptionmenuSelectednamesGet(dialog, component, &n_count, &names);
	//	if (n_count < 1) return PRO_TK_BAD_INPUTS;

	//	size_t n_converted;
	//	mbstowcs_s(&n_converted, w_selected_name, strlen(names[0]) + 1, names[0], _TRUNCATE);
	//	ProStringarrayFree(names, n_count);

	//	return status;
	//}

	ProError UI::SetOptionMenuSelectedLabel(char *dialog, char *component, wchar_t *w_value)
	{
        return ProUIOptionmenuValueSet(dialog, component, w_value);
	}



	ProError UI::SetOptionMenuSelectedIndex(char *dialog, char *component, int index)
	{
		ProError	status;
		int			count;
		char		**names;

		status = ProUIOptionmenuNamesGet(dialog, component, &count, &names);
		status = ProUIOptionmenuSelectednamesSet(dialog, component, 1, &names[index]);
		status = ProStringarrayFree(names, count);

		return PRO_TK_NO_ERROR;
	}

	ProError UI::SetOptionMenuItemCount(char *dialog, char *component, wchar_t *w_name, int max_count)
	{
		ProError	status;
        wchar_t     **w_labels;
        int         n_count;

		std::vector<wstring> list;
        status = ProUIOptionmenuLabelsGet(dialog, component, &n_count, &w_labels);
        for (int i=0; i<n_count; i++)
        {
            list.push_back(std::wstring(w_labels[i]));
        }
        status = ProWstringarrayFree(w_labels, n_count);

        std::wstring w_str(w_name);
		std::vector<std::wstring>::iterator it = find(list.begin(), list.end(), w_str);
		if (it != list.end())
		{
			list.erase(it);
		}

		list.insert(list.begin(), w_str);

		int n_list = static_cast<int>(list.size());
        n_list = n_list < max_count ? n_list : max_count;

        char **names = (char **) calloc(n_list, sizeof(char *));
        w_labels = (wchar_t **)calloc(n_list, sizeof(wchar_t *));
        for (int i=0; i<n_list; i++)
        {
            names[i] = (char *)calloc(3, sizeof(char));
            int l = sizeof(ProPath);
            w_labels[i] = (wchar_t *)calloc(sizeof(ProPath), sizeof(wchar_t));

            sprintf(names[i], "%d", i);
            wcscpy_s(w_labels[i], wcslen(list[i].c_str()) + 1, list[i].c_str());
        }

        status = ProUIOptionmenuNamesSet(dialog, component, n_list, names);
        status = ProUIOptionmenuLabelsSet(dialog, component, n_list, w_labels);
        status = ProUIOptionmenuValueSet(dialog, component, w_name);
        status = ProUIOptionmenuVisiblerowsSet(dialog, component, n_list);
        for (int i = 0; i < n_list; i ++)
        {
            free(names[i]); 
            free(w_labels[i]);
        }
        free (names);
        free (w_labels);

        return PRO_TK_NO_ERROR;
    }



	//ProError UI::GetOptionMenuLabels(char *dialog, char *component, std::vector<std::wstring> &list)
	//{
	//	ProError	status;
	//	char		**names;
	//	wchar_t     **w_labels;
	//	int		n_count;

	//	status = ProUIOptionmenuNamesGet(dialog, component, &n_count, &names);
	//	status = ProUIOptionmenuLabelsGet(dialog, component, &n_count, &w_labels);

	//	for (int i = 0; i<n_count; i++)
	//	{
	//		list.push_back(wstring(w_labels[i]));
	//	}

	//	ProStringarrayFree(names, n_count);
	//	ProWstringarrayFree(w_labels, n_count);

	//	return status;
	//}

 //   
	//ProError UI::SetOptionMenuNames(char *dialog, char *component, std::vector<std::wstring> &list)
	//{
	//	ProError	status;

	//	size_t n_count = list.size();
	//	char **names = (char **)calloc(n_count, sizeof(char*));
	//	wchar_t **w_labels = (wchar_t **)calloc(n_count, sizeof(wchar_t *));

	//	for (int i = 0; i < n_count; i++)
	//	{
	//		names[i] = (char *)calloc(4, sizeof(char));
	//		sprintf(names[i], "%d", i);

	//		w_labels[i] = (wchar_t *)calloc(256, sizeof(wchar_t));
	//		wsprintf(w_labels[i], list[i].c_str());
	//	}

	//	status = ProUIOptionmenuNamesSet(dialog, component, n_count, names);
	//	status = ProUIOptionmenuLabelsSet(dialog, component, n_count, w_labels);

	//	for (int i = 0; i<n_count; i++)
	//	{
	//		free(names[i]);
	//		free(w_labels[i]);
	//	}

	//	free(names);
	//	free(w_labels);

	//	return status;
	//}



	ProError UI::GetRadioGroupSelectedName(char *dialog, char *component, wchar_t *w_value)
	{
		ProError	status;
		int			n_names;
		char		**names;

		status = ProUIRadiogroupSelectednamesGet(dialog, component, &n_names, &names);
		if (n_names < 1) return PRO_TK_E_NOT_FOUND;

		size_t n_converted;
		mbstowcs_s(&n_converted, w_value, strlen(names[0]) + 1, names[0], _TRUNCATE);
		status = ProStringarrayFree(names, n_names);

		return PRO_TK_NO_ERROR;
	}


	ProError UI::SetRadioGroupSelectedName(char *dialog, char *component, wchar_t *w_value)
	{
		ProError	status;
		size_t		n_converted;
		char		*name = new char[wcslen(w_value) + 1];

		wcstombs_s(&n_converted, name, wcslen(w_value) + 1, w_value, _TRUNCATE);
		status = ProUIRadiogroupSelectednamesSet(dialog, component, 1, &name);

		delete[] name;

		return status;
	}



	ProError UI::GetCheckboxStatus(char *dialog, char *component, bool *checked)
	{
		ProError	status;
		ProBoolean  set;
		status = ProUICheckbuttonGetState(dialog, component, &set);

		*checked = set == PRO_B_TRUE;

		return status;
	}


	ProError UI::GetCheckboxStatus(char *dialog, char *component, ProBoolean *checked)
	{
		ProError	status;
		status = ProUICheckbuttonGetState(dialog, component, checked);

		return status;
	}


	ProError UI::SetCheckboxStatus(char *dialog, char *component, bool checked)
	{
		if (checked)
		{
			ProUICheckbuttonSet(dialog, component);
		}
		else
		{
			ProUICheckbuttonUnset(dialog, component);
		}

		return PRO_TK_NO_ERROR;;
	}


	ProError UI::SetCheckboxStatus(char *dialog, char *component, ProBoolean checked)
	{
		if (checked == PRO_B_TRUE)
		{
			ProUICheckbuttonSet(dialog, component);
		}
		else
		{
			ProUICheckbuttonUnset(dialog, component);
		}

		return PRO_TK_NO_ERROR;
	}

	bool UI::TableSingleCellSelected(char *dialog, char *table)
	{
		ProError    status;
		char        **names;
		char        *row;
		int         n_count;
		/*--------------------------------------------------------------------*\
		Get all the selected rows. If more thatn one row is selected, do nothing
		\*--------------------------------------------------------------------*/
		status = ProUITableSelectednamesGet(dialog, table, &n_count, &names);
		if ((status == PRO_TK_NO_ERROR) && (n_count > 0))
		{
			row = names[0];
			for (int i = 2; i<n_count; i++)
			{
				if (strcmp(row, names[i]) != 0)
				{
					ProStringarrayFree(names, n_count);
					return false;
				}
			}
		}
		ProStringarrayFree(names, n_count);

		return true;
	}


	ProError UI::ShowPrinters(char *dialog, char *component)
	{
		ProError	status;
		DWORD       needed, returned;
		DWORD       level = 2;

		EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_NETWORK, NULL, level, NULL, 0, &needed, &returned);
		PRINTER_INFO_2 *printer_info = (PRINTER_INFO_2 *)malloc(needed);

		if (!EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_NETWORK, NULL, level, (LPBYTE)printer_info, needed, &needed, &returned))
		{
			free(printer_info);
			return PRO_TK_GENERAL_ERROR;
		}

        char **names = new char *[returned];
        wchar_t **w_names = new wchar_t *[returned];
        
		for (size_t i = 0; i < returned; i++)
		{
            names[i] = new char[10];
            w_names[i] = new wchar_t[80];
            sprintf(names[i], "%d", i);
            wcscpy_s(w_names[i], wcslen(printer_info[i].pPrinterName) + 1, printer_info[i].pPrinterName);
        }
        free(printer_info);

        status = ProUIOptionmenuNamesSet (dialog, component, returned, names);
        status = ProUIOptionmenuLabelsSet (dialog, component, returned, w_names);
        status = ProUIOptionmenuVisiblerowsSet(dialog, component, returned);

        for (int i = 0; i < (int) returned; i ++)
        {
            delete[] names[i]; 
            delete[] w_names[i];
        }
        delete[] names;
        delete[] w_names;

        DWORD length = MAX_PATH;
        ProPath w_default_printer;
        if (GetDefaultPrinter(w_default_printer, &length))
        {
            status = ProUIOptionmenuValueSet(dialog, component, w_default_printer);
        }

        return PRO_TK_NO_ERROR;
	}


	ProError UI::ShowPapers(char *dialog, char *component)
	{
        ProError status;
        int n_count = 5;
        char **names = new char *[n_count];
        wchar_t **w_names = new wchar_t *[n_count];

        for (int i=0; i<n_count; i++)
        {
            names[i] = new char[2];
            w_names[i] = new wchar_t[3];

            sprintf(names[i], "%d", i);
            wsprintf(w_names[i], L"A%d", i);
        }

        status = ProUIOptionmenuNamesSet (dialog, component, n_count, names);
        status = ProUIOptionmenuLabelsSet (dialog, component, n_count, w_names);
        status = ProUIOptionmenuVisiblerowsSet(dialog, component, n_count);

        for (int i = 0; i < n_count; i ++)
        {
            delete[] names[i]; 
            delete[] w_names[i];
        }
        delete[] names;
        delete[] w_names;

        status = ProUIOptionmenuValueSet(dialog, component, L"A3");

        return PRO_TK_NO_ERROR;
    }


    ProError UI::ShowFolders(char *dialog, char *component)
    {
        ProError    status;
        ProPath     w_path;

        status = Option::GetRootDirectory(w_path);
        wcscat(w_path, L"\\config\\folder_names.xml");

        pugi::xml_document xml;
        pugi::xml_parse_result result = xml.load_file(w_path);
        if (!result) return PRO_TK_INVALID_FILE;

        pugi::xpath_node_set node_set = xml.select_nodes(L"/Configuration/Folders/Folder");
        int n_count = static_cast<int>(node_set.size());
        if (n_count < 1) return PRO_TK_E_NOT_FOUND;
        
        char **names = (char **) calloc(n_count, sizeof(char *));
        wchar_t **w_labels = (wchar_t **) calloc(n_count, sizeof(wchar_t *));
        int index = 0;
        for(auto it = node_set.begin(); it != node_set.end(); it++)
        {
            names[index] = (char *) calloc(3, sizeof(char));
            w_labels[index] = (wchar_t *) calloc(MAX_PATH + 1, sizeof(wchar_t));
            sprintf(names[index], "%d", index);
            wcscpy(w_labels[index], it->node().text().as_string());

            index++;
        }

        status = ProUIOptionmenuNamesSet(dialog, component, n_count, names);
        status = ProUIOptionmenuLabelsSet(dialog, component, n_count, w_labels);

        for (int i = 0; i < n_count; i++)
        {
            free (names [i]);
            free (w_labels [i]);
        }
        free (names);
        free (w_labels);

        return PRO_TK_NO_ERROR;
    }

    ProError UI::SaveFolders(char *dialog, char *component)
    {
        ProError    status;
        int         n_count;
        wchar_t     **w_labels;

        status = ProUIOptionmenuLabelsGet(dialog, component, &n_count, &w_labels);
        if (status != PRO_TK_NO_ERROR || n_count < 1) return status;

		pugi::xml_document xml;
		pugi::xml_node decl = xml.prepend_child(pugi::node_declaration);
		decl.append_attribute(L"version") = L"1.0";
		decl.append_attribute(L"encoding") = L"UTF-8";
		decl.append_attribute(L"standalone") = L"yes";

		pugi::xml_node root = xml.append_child(L"Configuration");
		pugi::xml_node node = root.append_child(L"Folders");

        for (int i=0; i<n_count; i++)
        {
            pugi::xml_node child_node = node.append_child(L"Folder");
            child_node.text().set(w_labels[i]);

        }

        ProWstringarrayFree(w_labels, n_count);

        ProPath w_path;
        status = Option::GetRootDirectory(w_path);
        wcscat(w_path, L"\\config\\folder_names.xml");

        xml.save_file(w_path);

        return PRO_TK_NO_ERROR;
    }


#pragma endregion
}