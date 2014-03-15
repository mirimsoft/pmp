#include "StdParam.h"
#include "MsExcel.h"
#include "Table.h"

namespace Gui
{
	std::vector<StdParam>  *StdParam::_unique_param_list = new std::vector<StdParam>();
	std::vector<std::pair<bool, wstring>> *StdParam::_delete_param_list = new std::vector<std::pair<bool, wstring>>();
	int StdParam::row_number = 0;

	StdParam::StdParam(void)
	{
	}

	StdParam::StdParam(char *name)
	{
		size_t n_converted;
		mbstowcs_s(&n_converted, this->Name, name, _TRUNCATE);
	}

	StdParam::~StdParam(void)
	{
	}

	std::vector<StdParam> *StdParam::GetUniqueParamList()
	{
		ProError status;

		StdParam::_unique_param_list = new vector<StdParam>();
		StdParam::_delete_param_list = new vector<std::pair<bool, wstring>>();
		status = StdParam::ReadXml(_unique_param_list, _delete_param_list);
		if (status != PRO_TK_NO_ERROR)
			return NULL;
		else
			return StdParam::_unique_param_list;
	}

	std::vector<std::pair<bool, wstring>> *StdParam::GetDeleteParamNames()
	{
		ProError status;

		StdParam::_unique_param_list = new vector<StdParam>();
		StdParam::_delete_param_list = new vector<std::pair<bool, wstring>>();
		status = StdParam::ReadXml(_unique_param_list, _delete_param_list);
		if (status != PRO_TK_NO_ERROR)
			return NULL;
		else
			return StdParam::_delete_param_list;
	}

	ProError StdParam::GetXmlFileName(wchar_t *w_path)
	{
		ProError    status;

		status = ProToolkitApplTextPathGet(w_path);
		wsprintf(w_path, L"%s\\config\\std_param_definition.xml", w_path);

		return status;
	}

	ProError StdParam::GetExcelFileName(wchar_t *w_path)
	{
		ProError    status;

		status = ProToolkitApplTextPathGet(w_path);
		wsprintf(w_path, L"%s\\config\\std_param_template.xls", w_path);

		return status;
	}




	ProError StdParam::ReadExcel(wchar_t *w_file_path, std::vector<StdParam> &list, std::vector<std::pair<bool, wstring>> &list1)
	{
		MsExcel excel(false);
		if (!excel.OpenWorkbook(w_file_path)) return PRO_TK_INVALID_FILE;
		if (!excel.GetWorksheet(1)) return PRO_TK_E_NOT_FOUND;

		excel.ReadStdParams(list);
		excel.ReadParamNames(list1);

		excel.Quit();

		return PRO_TK_NO_ERROR;
	}


	ProError StdParam::SaveExcel(wchar_t *w_file_path, std::vector<StdParam> &list, std::vector<std::pair<bool, wstring>> &list1)
	{
		ProError    status;
		ProPath     w_path;

		status = StdParam::GetExcelFileName(w_path);
		try
		{
			if (!CopyFile(w_path, w_file_path, false))
			{
				return PRO_TK_BAD_INPUTS;
			}

			MsExcel excel(true);
			if (!excel.OpenWorkbook(w_file_path)) return PRO_TK_INVALID_FILE;
			if (!excel.GetWorksheet(1)) return PRO_TK_E_NOT_FOUND;

			excel.SaveStdParams(list);
			excel.SaveParamNames(list1);

			ProName w_extension;
			status = ProFilenameParse(w_file_path, NULL, NULL, w_extension, NULL);
			bool save_as_2003 = wcsicmp(w_extension, L"XLS") == 0;
			if (excel.SaveAs(w_file_path, save_as_2003))
			{
				return PRO_TK_NO_ERROR;
			}
			else
			{
				return PRO_TK_CANT_WRITE;
			}
		}
		catch (...)
		{
			Mirim::MsgBox::Show(L"Message", L"ERROR: Failed to save Excel file...");
			return PRO_TK_GENERAL_ERROR;
		}
	}

	ProError StdParam::ReadXml(std::vector<StdParam> *list, std::vector<std::pair<bool, wstring>> *list1)
	{
		ProError    status;
		ProPath     w_path;

		try
		{
			status = StdParam::GetXmlFileName(w_path);
			pugi::xml_document xml;
			pugi::xml_parse_result success = xml.load_file(w_path);
			if (!success) return PRO_TK_GENERAL_ERROR;

			pugi::xpath_node node;
			*list = std::vector<StdParam>();
			pugi::xpath_node_set node_set = xml.select_nodes(L"/Configuration/StdParam/Param");
			for (pugi::xpath_node_set::const_iterator it = node_set.begin(); it != node_set.end(); it++)
			{
				StdParam param;

				node = it->node().select_single_node(L"Name");
				wcscpy(param.Name, node.node().text().as_string());

				node = it->node().select_single_node(L"Type");
				wcscpy(param.Type, node.node().text().as_string());

				node = it->node().select_single_node(L"ReadOnly");
				wcscpy(param.ReadOnly, node.node().text().as_string());

				node = it->node().select_single_node(L"Default");
				wcscpy(param.Default, node.node().text().as_string());

				node = it->node().select_single_node(L"Names");
				wcscpy(param.Names, node.node().text().as_string());

				node = it->node().select_single_node(L"Remark");
				wcscpy(param.Remark, node.node().text().as_string());

				list->push_back(param);
			}

			*list1 = std::vector<std::pair<bool, wstring>>();
			node_set = xml.select_nodes(L"/Configuration/ParameterToDelete");
			for (pugi::xpath_node_set::const_iterator it = node_set.begin(); it != node_set.end(); it++)
			{
				node = it->node().select_single_node(L"Checked");
				bool checked = true;
				if (node != NULL)
				{
					checked = node.node().text().as_bool();
				}

				node = it->node().select_single_node(L"Name");
				list1->push_back(make_pair(checked, wstring(node.node().text().as_string())));
			}
		}
		catch (...)
		{
			Mirim::MsgBox::Show(L"ERROR: Failed to read xml file", L"Exception");
			return PRO_TK_GENERAL_ERROR;
		}

		return PRO_TK_NO_ERROR;
	}

	ProError StdParam::SaveXml(std::vector<StdParam> *list, std::vector<std::pair<bool, wstring>> *list1)
	{
		ProError   status;
		ProPath     w_path;

		try
		{
			status = StdParam::GetXmlFileName(w_path);
			pugi::xml_document xml;
			pugi::xml_node decl = xml.prepend_child(pugi::node_declaration);
			decl.append_attribute(L"version") = L"1.0";
			decl.append_attribute(L"encoding") = L"UTF-8";
			decl.append_attribute(L"standalone") = L"yes";

			pugi::xml_node root = xml.append_child(L"Configuration");
			pugi::xml_node node = root.append_child(L"StdParam");

			for (auto it = list->begin(); it != list->end(); it++)
			{
				pugi::xml_node param = node.append_child(L"Param");
				param.append_child(L"Name").text().set(it->Name);
				param.append_child(L"Type").text().set(it->Type);
				param.append_child(L"ReadOnly").text().set(it->ReadOnly);
				param.append_child(L"Default").text().set(it->Default);
				param.append_child(L"Names").text().set(it->Names);
				param.append_child(L"Remark").text().set(it->Remark);
			}

			pugi::xml_node param = root.append_child(L"ParameterToDelete");
			for (auto it = list1->begin(); it != list1->end(); it++)
			{
				param.append_child(L"Name").text().set(it->second.c_str());
				param.append_child(L"Checked").text().set(it->first);
			}
			xml.save_file(w_path);

			status = StdParam::ReadXml(StdParam::_unique_param_list, StdParam::_delete_param_list);
		}
		catch (...)
		{
			Mirim::MsgBox::Show(L"ERROR: Failed to save xml file", L"Exception");
			return PRO_TK_GENERAL_ERROR;
		}

		return PRO_TK_NO_ERROR;
	}

	ProError StdParam::GetStdParamNames(std::vector<wstring> &list)
	{
		ProError    status;
		ProPath     w_path;

		list = std::vector<wstring>();
		status = StdParam::GetXmlFileName(w_path);
		pugi::xml_document xml;
		pugi::xml_parse_result success = xml.load_file(w_path);

		pugi::xpath_node_set node_set = xml.select_nodes(L"/Configuration/StdParam/Param");

		for (pugi::xpath_node_set::const_iterator it = node_set.begin(); it != node_set.end(); it++)
		{
			pugi::xpath_node node = it->node().select_single_node(L"Name");

			list.push_back(wstring(node.node().text().as_string()));
		}

		return PRO_TK_NO_ERROR;
	}


	ProError StdParam::ShowStdParams(char *dialog, char *table, std::vector<StdParam> &list)
	{
		ProError	status;
		char		**row_names;
		wchar_t		w_row_label[32];
		int			n_rows = static_cast<int>(list.size());

		status = Table::PrepareRows(dialog, table, n_rows);
		if (status != PRO_TK_NO_ERROR) return status;

		status = ProUITableRownamesGet(dialog, table, &n_rows, &row_names);
		if (status != PRO_TK_NO_ERROR) return status;

		for (int i=0; i<n_rows; i++)
		{
			wsprintf(w_row_label, L"%d", i + 1);

			status = ProUITableRowLabelSet(dialog, table, row_names[i], w_row_label);
			status = ProUITableCellLabelSet(dialog, table, row_names[i], "Name", list[i].Name);
			status = ProUITableCellLabelSet(dialog, table, row_names[i], "Names", list[i].Names);
			status = ProUITableCellLabelSet(dialog, table, row_names[i], "Type", list[i].Type);
			status = ProUITableCellLabelSet(dialog, table, row_names[i], "ReadOnly", list[i].ReadOnly);
			status = ProUITableCellLabelSet(dialog, table, row_names[i], "Default", list[i].Default);
			status = ProUITableCellLabelSet(dialog, table, row_names[i], "Remark", list[i].Remark);
		}

		ProStringarrayFree(row_names, n_rows);

		return PRO_TK_NO_ERROR;
	}

	ProError StdParam::ShowParamsToDelete(char *dialog, char *table, std::vector<std::pair<bool, wstring>> &list)
	{
		ProError	status;
		char		**row_names;
		wchar_t		w_row_label[32];
		wchar_t		w_name[32];
		char		cb_name[32];
		int			n_rows = static_cast<int>(list.size());
		if (n_rows < 1) return PRO_TK_NO_ERROR;

		status = Table::PrepareRows(dialog, table, n_rows);
		if (status != PRO_TK_NO_ERROR) return status;

		status = ProUITableRownamesGet(dialog, table, &n_rows, &row_names);
		if (status != PRO_TK_NO_ERROR) return status;

		for (int i=0; i<n_rows; i++)
		{
			wsprintf(w_row_label, L"%d", i + 1);

			status = ProUITableRowLabelSet(dialog, table, row_names[i], w_row_label);
			sprintf(cb_name,"CB_%s", row_names[i]);
			status = ProUITableCellComponentCopy(dialog, table, row_names[i], "Checked", dialog, "CB_SOURCE2", cb_name);
			if (list[i].first)
			{
				status = ProUICheckbuttonSet(dialog, cb_name);
			}
			else
			{
				status = ProUICheckbuttonUnset(dialog, cb_name);
			}

			wcscpy_s(w_name, list[i].second.c_str());
			status = ProUITableCellLabelSet(dialog, table, row_names[i], "Name", w_name);
		}

		ProStringarrayFree(row_names, n_rows);

		return PRO_TK_NO_ERROR;
	}


	ProError StdParam::ReadStdParams(char *dialog, char *table, std::vector<StdParam> &list)
	{
		ProError    status;
		int         n_count;
		char        **row_names;
		wchar_t     *w_pointer;

		status = ProUITableRownamesGet(dialog, table, &n_count, &row_names);

		list = std::vector<StdParam>();
		for (int i = 0; i < n_count; i++)
		{
			StdParam param;

			status = ProUITableCellLabelGet(dialog, table, row_names[i], "Name", &w_pointer);
			wcscpy(param.Name, w_pointer);
			ProWstringFree(w_pointer);

			status = ProUITableCellLabelGet(dialog, table, row_names[i], "Type", &w_pointer);
			wcscpy(param.Type, w_pointer);
			ProWstringFree(w_pointer);

			status = ProUITableCellLabelGet(dialog, table, row_names[i], "ReadOnly", &w_pointer);
			wcscpy(param.ReadOnly, w_pointer);
			ProWstringFree(w_pointer);

			status = ProUITableCellLabelGet(dialog, table, row_names[i], "Default", &w_pointer);
			wcscpy(param.Default, w_pointer);
			ProWstringFree(w_pointer);

			status = ProUITableCellLabelGet(dialog, table, row_names[i], "Names", &w_pointer);
			wcscpy(param.Names, w_pointer);
			ProWstringFree(w_pointer);

			status = ProUITableCellLabelGet(dialog, table, row_names[i], "Remark", &w_pointer);
			wcscpy(param.Remark, w_pointer);
			ProWstringFree(w_pointer);

			list.push_back(param);
		}

		return PRO_TK_NO_ERROR;
	}

	ProError StdParam::ReadParamsToDelete(char *dialog, char *table, std::vector<std::pair<bool, wstring>> &list)
	{
		ProError    status;
		int         n_rows;
		char        **row_names;
		wchar_t     *w_pointer;
		char		cb_name[32];
		ProBoolean  checked;

		status = ProUITableRownamesGet(dialog, table, &n_rows, &row_names);
		list = std::vector<std::pair<bool, wstring>>();
		for (int i = 0; i < n_rows; i++)
		{
			sprintf(cb_name, "CB_%s", row_names[i]);
			status = ProUICheckbuttonGetState(dialog, cb_name, &checked);
			status = ProUITableCellLabelGet(dialog, table, row_names[i], "Name", &w_pointer);
			list.push_back(std::make_pair(PRO_B_TRUE == checked, std::wstring(w_pointer)));		
			ProWstringFree(w_pointer);
		}

		ProStringarrayFree(row_names, n_rows);

		return PRO_TK_NO_ERROR;
	}



	ProError StdParam::EditSelectedCell(ProAppData app_data)
	{
		ProError  status;
		Table *table = (Table *)app_data;

		if (!Mirim::UI::TableSingleCellSelected(table->dialog, table->table)) return PRO_TK_BAD_CONTEXT;

		/*--------------------------------------------------------------------*\
		Get the focus cell
		\*--------------------------------------------------------------------*/
		status = ProUITableFocusCellGet(table->dialog, table->table, &table->row, &table->col);
		if (status != PRO_TK_NO_ERROR) return status;

		if (stricmp(table->table, "TABLE3") == 0)
		{
			StdParam param(table->col);
			std::vector<StdParam> *list = StdParam::GetUniqueParamList();
			auto found = find(list->begin(), list->end(), param);
			if (found == list->end() || wcsicmp(found->ReadOnly, L"True") == 0) return PRO_TK_NO_ERROR;

			if (stricmp(table->col, "Name") == 0 ||
				stricmp(table->col, "Type") == 0 ||
				stricmp(table->col, "Qty") == 0)
			{
				return PRO_TK_NO_ERROR;
			}
			else if (wcsncmp(found->Type, L"True", 4) == 0)
			{
                char **names = (char **) calloc(2, sizeof(char *));
                wchar_t **w_names = (wchar_t **) calloc(2, sizeof(wchar_t *));
                names[0] = "0";
                names[1] = "1";
                w_names[0] = L"False";
                w_names[1] = L"True";

				status = table->BeginEditWithOptionmenu(2, names, w_names);
			}
			else 
			{
				status = table->BeginEditWithInputpanel();
			}
		}
		else
		{
			if (stricmp(table->col, "Type") == 0)
			{
    //            char names[4][2] = {"0", "1", "2", "3"};
    //            wchar_t w_names[4][12] = {L"문자열", L"정수", L"실수", L"True/False"};

				//status = table->BeginEditWithOptionmenu(4, names, w_names);
			}
			else if (stricmp(table->col, "ReadOnly") == 0)
			{
                char **names = (char **) calloc(2, sizeof(char *));
                wchar_t **w_names = (wchar_t **) calloc(2, sizeof(wchar_t *));
                names[0] = "0";
                names[1] = "1";
                w_names[0] = L"False";
                w_names[1] = L"True";

				status = table->BeginEditWithOptionmenu(2, names, w_names);
			}
			else 
			{
				status = table->BeginEditWithInputpanel();
			}
		}

		return PRO_TK_NO_ERROR;
	}


	ProError StdParam::AddStdParamColumns(Table *table)
	{
		ProError	status;

		std::vector<StdParam> *list = StdParam::GetUniqueParamList();
		int n_columns = static_cast<int>(list->size() + 3);

		char **column_names = new char *[n_columns];
		wchar_t **w_column_labels = new wchar_t *[n_columns];

		int length = 32;
		for (int i=0; i<n_columns; i++)
		{
			column_names[i] = new char[length];
			w_column_labels[i] = new wchar_t[length];
		}

		size_t n_converted;
		strcpy_s(column_names[0], length, "Name");
		strcpy_s(column_names[1], length, "Type");
		strcpy_s(column_names[2], length, "Qty");	
		wcscpy_s(w_column_labels[0], length, L"Name");
		wcscpy_s(w_column_labels[1], length, L"Type");
		wcscpy_s(w_column_labels[2], length, L"Qty");

		for (int i=3; i<n_columns; i++)
		{
			wcscpy_s(w_column_labels[i], length, (*list)[i-3].Name);
			wcstombs_s(&n_converted, column_names[i], wcslen(w_column_labels[i]) + 1, w_column_labels[i], _TRUNCATE);
		}

		status = ProUITableColumnnamesSet(table->dialog, table->table, n_columns, column_names);
		status = ProUITableColumnlabelsSet(table->dialog, table->table, n_columns, w_column_labels);

		for (int i=0; i<n_columns; i++)
		{
			delete[] column_names[i];
			delete[] w_column_labels[i];
		}

		delete[] column_names;
		delete[] w_column_labels;

		return PRO_TK_NO_ERROR;
	}

	ProError StdParam::ShowParamValues(Table *table, std::vector<Model> &mdl_list, bool show_asm, bool show_prt)
	{
		std::vector<Model> list;

		if (!show_asm && !show_prt)
		{
			show_asm = show_prt = true;
		}

		for (auto it = mdl_list.begin(); it != mdl_list.end(); it++)
		{
			if ((show_asm && it->type == PRO_MDL_ASSEMBLY) || (show_prt && it->type == PRO_MDL_PART))
			{
				list.push_back(*it);
			}
		}

		return StdParam::ShowParamValues(table, list);
	}

	ProError StdParam::ShowParamValues(Table *table, std::vector<Model> &mdl_list)
	{
		ProError	status;
		char		**row_names;
		char		column_name[32];
		wchar_t		w_row_label[32];
		char		label_name[32];
		wchar_t		w_value[32];

		std::vector<StdParam> *param_list = StdParam::GetUniqueParamList();

		int n_rows = static_cast<int>(mdl_list.size());
		status = Table::PrepareRows(table->dialog, table->table, n_rows);
		status = ProUITableRownamesGet(table->dialog, table->table, &n_rows, &row_names);
		for (int i=0; i<n_rows; i++)
		{
			wsprintf(w_row_label, L"%d", i+1);
			status = ProUITableRowLabelSet(table->dialog, table->table, row_names[i], w_row_label);

			// Show Name and Icon
			sprintf(label_name, "%s_Name", row_names[i]);
			status = ProUITableCellComponentCopy(table->dialog, table->table, row_names[i], "Name", table->dialog, table->lb_source, label_name);
			status = ProUILabelEnable(table->dialog, label_name);
			status = ProUILabelShow(table->dialog, label_name);
			status = ProUILabelTextSet(table->dialog, label_name, mdl_list[i].mdl_data.name);
			if (mdl_list[i].type == PRO_MDL_ASSEMBLY)
				status = ProUILabelBitmapSet(table->dialog, label_name, "asm_icon.gif");
			else if (mdl_list[i].type == PRO_MDL_PART)
				status = ProUILabelBitmapSet(table->dialog, label_name, "prt_icon.gif");
			else
				status = ProUILabelBitmapSet(table->dialog, label_name, "drw_icon.gif");

			// Show Type and Qty
			status = ProUITableCellLabelSet(table->dialog, table->table, row_names[i], "Type", mdl_list[i].mdl_data.type);
			wsprintf(w_value, L"%d", mdl_list[i].qty);
			status = ProUITableCellLabelSet(table->dialog, table->table, row_names[i], "Qty", w_value);

			ProModelitem model_item;
			status = ProMdlToModelitem(mdl_list[i].mdl, &model_item);
			if (status != PRO_TK_NO_ERROR) continue;

			// Show Parameter Values
			size_t n_converted;
			for (size_t j = 0; j < param_list->size(); j++)
			{
				status = StdParam::GetParamValueToString(model_item, (*param_list)[j].Name, (*param_list)[j].Names, w_value);
				wcstombs_s(&n_converted, column_name, (*param_list)[j].Name, _TRUNCATE);
				if (status == PRO_TK_NO_ERROR)
				{
					status = ProUITableCellLabelSet(table->dialog, table->table, row_names[i], column_name, w_value);
					if (wcsncmp((*param_list)[j].ReadOnly, L"True", 4) == 0)
					{
						status = ProUITableCellBackgroundColorSet(table->dialog, table->table, row_names[i], column_name, PRO_UI_COLOR_3D_DARK_SHADOW);
					}
					else
					{
						status = ProUITableCellBackgroundColorSet(table->dialog, table->table, row_names[i], column_name, PRO_UI_COLOR_HOVER_TEXT);
					}
				}
				else
				{
					if (wcsncmp((*param_list)[j].ReadOnly, L"True", 4) == 0)
					{
						status = ProUITableCellBackgroundColorSet(table->dialog, table->table, row_names[i], column_name, PRO_UI_COLOR_3D_DARK_SHADOW);
					}
					else
					{
						status = ProUITableCellBackgroundColorSet(table->dialog, table->table, row_names[i], column_name, PRO_UI_COLOR_YELLOW);
					}				
				}
			}
		}
		ProStringarrayFree(row_names, n_rows);

		return PRO_TK_NO_ERROR;
	}


	ProError StdParam::GetLegacyParam(ProModelitem model_item, wchar_t *w_names, ProParameter *param)
	{
		ProError	status;
		ProPath		w_name;
		int			length = wcslen(w_names);
		if (length < 1) return PRO_TK_BAD_INPUTS;

		wchar_t *w_str = new wchar_t[length + 1];
		wcscpy_s(w_str, length + 1, w_names);

		wchar_t *w_pointer = wcstok(w_str, L",");
		while(w_pointer)
		{
			Mirim::Util::TrimString(w_pointer, w_name);
			status = ProParameterInit(&model_item, w_name, param);
			if (status == PRO_TK_NO_ERROR) 
			{
				delete[] w_str;
				return PRO_TK_NO_ERROR;
			}

			w_pointer = wcstok(NULL, L",");
		}

		delete[] w_str;
		return PRO_TK_E_NOT_FOUND;
	}

	ProError StdParam::GetParamValueToString(ProModelitem model_item, wchar_t *w_name, wchar_t *w_names, wchar_t *w_value)
	{
		ProError        status;
		ProParameter    param;
		ProParamvalue	param_value;

		*w_value = 0;
		status = ProParameterInit(&model_item, w_name, &param);
		if (status != PRO_TK_NO_ERROR)
		{
			status = StdParam::GetLegacyParam(model_item, w_names, &param);
			if (status != PRO_TK_NO_ERROR) return status;
		}

		status = ProParameterValueGet(&param, &param_value);
		if (status != PRO_TK_NO_ERROR) return PRO_TK_BAD_INPUTS;

		switch (param_value.type)
		{
		case PRO_PARAM_INTEGER:
		case PRO_PARAM_NOTE_ID:
			_itow(param_value.value.i_val, w_value, 10);
			return PRO_TK_NO_ERROR;
		case PRO_PARAM_DOUBLE:
			char value[MAX_PATH];
			sprintf(value, "%G", param_value.value.d_val);
			mbstowcs(w_value, value, MAX_PATH);
			return PRO_TK_NO_ERROR;
		case PRO_PARAM_BOOLEAN:
			if (param_value.value.l_val)
				wcscpy(w_value, L"true");
			else
				wcscpy(w_value, L"false");
			return PRO_TK_NO_ERROR;
		case PRO_PARAM_STRING: 
			wcscpy(w_value, param_value.value.s_val);
			return PRO_TK_NO_ERROR;
		default:
			return PRO_TK_INVALID_TYPE;
		}

		return PRO_TK_NO_ERROR;
	}

	ProError StdParam::GetParamValue(wchar_t *w_type, wchar_t *w_value, ProParamvalue *param_value)
	{
		if (wcsicmp(w_type, L"문자열") == 0)
		{
			param_value->type = PRO_PARAM_STRING;
			wcscpy(param_value->value.s_val, w_value);
		}
		else if (wcsicmp(w_type, L"정수") == 0)
		{
			param_value->type = PRO_PARAM_INTEGER;
			param_value->value.i_val = _wtoi(w_value);
		}
		else if (wcsicmp(w_type, L"실수") == 0)
		{
			param_value->type = PRO_PARAM_DOUBLE;
			swscanf(w_value, L"%lf", &param_value->value.d_val);
		}
		else
		{
			param_value->type = PRO_PARAM_BOOLEAN;
			if (wcsicmp(w_value, L"TRUE") == 0)
				param_value->value.l_val = 1;
			else
				param_value->value.l_val = 0;
		}


		return PRO_TK_NO_ERROR;
	}

	ProError StdParam::SetParamValueWithString(ProModelitem model_item, wchar_t *w_name, wchar_t *w_type, wchar_t *w_names, wchar_t *w_value)
	{
		ProError        status;
		ProParameter    param;
		ProParamvalue   param_value;

		status = StdParam::GetParamValue(w_type, w_value, &param_value);

		status = ProParameterInit(&model_item, w_name, &param);
		if (status == PRO_TK_NO_ERROR)
		{
			status = ProParameterValueSet(&param, &param_value);

			return status;
		}

		if (wcslen(w_names) > 0) 
		{
			wchar_t *w_pointer = wcstok(w_names, L",");
			while(w_pointer)
			{
				status = ProParameterInit(&model_item, w_pointer, &param);
				if (status == PRO_TK_NO_ERROR) 
				{
					status = ProParameterDelete(&param);
				}

				w_pointer = wcstok(NULL, L",");
			}
		}

		status = ProParameterCreate(&model_item, w_name, &param_value, &param);

		return PRO_TK_NO_ERROR;
	}


	ProError StdParam::CreateReadOnlyParameter(ProModelitem model_item, wchar_t *w_name, wchar_t *w_type)
	{
		ProError        status;
		ProParameter    param;
		ProParamvalue   param_value;


		status = ProParameterInit(&model_item, w_name, &param);
		if (status == PRO_TK_NO_ERROR) return PRO_TK_NO_ERROR;

		status = StdParam::GetParamValue(w_type, L"", &param_value);
		status = ProParameterCreate(&model_item, w_name, &param_value, &param);

		return PRO_TK_NO_ERROR;
	}



	ProError StdParam::SetStdRelations(ProMdl mdl)
	{
		ProError		status;
		ProModelitem	model_item;
		ProRelset		rel_set;
		ProWstring		*w_relations;
		ProLine			w_relation;
		ProMdlType		mdl_type;
		int				n_count;
		bool			relation_added = false;

		status = ProMdlToModelitem(mdl, &model_item);
		if (status != PRO_TK_NO_ERROR) return status;

		status = ProModelitemToRelset(&model_item, &rel_set);
		if (status != PRO_TK_NO_ERROR) return status;

		status = ProArrayAlloc(0, sizeof(ProWstring *), 1, (ProArray *) &w_relations);
		status = ProRelsetRelationsGet(&rel_set, &w_relations);
		if (status != PRO_TK_NO_ERROR) return status;

		status = ProArraySizeGet(w_relations, &n_count);
		std::vector<wstring> list;
		for (int i=0; i<n_count; i++)
		{
			status = Mirim::Util::RemoveWhiteSpace(w_relations[i], w_relation);
			list.push_back(wstring(wcsupr(w_relation)));
		}

		wchar_t *w_std_relation = L"S10_WEIGHT=PRO_MP_MASS";
		wstring w_common_relation(w_std_relation);
		std::vector<wstring>::iterator it = find(list.begin(), list.end(), w_common_relation);
		if (it == list.end())
		{
			status = ProArrayObjectAdd((ProArray *) &w_relations, 0, 1, &w_std_relation);
			relation_added = true;
		}

		status = ProMdlTypeGet(mdl, &mdl_type);
		if (status != PRO_TK_NO_ERROR) return status;

		if (mdl_type == PRO_MDL_PART)
		{
			wchar_t *w_part_relation = L"S03_MATERIAL=PTC_MATERIAL_NAME";
			w_common_relation = std::wstring(w_part_relation);
			std::vector<wstring>::iterator it = find(list.begin(), list.end(), w_common_relation);
			if (it == list.end())
			{
				if (relation_added)
				{
					status = ProArrayObjectAdd((ProArray *) &w_relations, 1, 1, &w_part_relation);
				}
				else
				{
					status = ProArrayObjectAdd((ProArray *) &w_relations, 0, 1, &w_part_relation);
				}
			}
		}

		status = ProArraySizeGet(w_relations, &n_count);
		status = ProRelsetRelationsSet(&rel_set, w_relations, n_count); 
		if (status != PRO_TK_NO_ERROR) return PRO_TK_BAD_INPUTS;

		status = ProRelsetRegenerate(&rel_set);

		return PRO_TK_NO_ERROR;
	}


	ProError StdParam::ApplyParams(char *dialog, char *table)
	{
		ProError		status;
		int				n_rows;
		char			**row_names;
		char			col_name[32];
		char			*label_name;
		wchar_t			*w_mdl_name;
		wchar_t			*w_type;
		wchar_t			*w_value;
		ProMdl			mdl;
		ProModelitem	model_item;

		status = ProUITableRownamesGet(dialog, table, &n_rows, &row_names);
		if (status != PRO_TK_NO_ERROR || n_rows < 1) return status;

		std::vector<StdParam> *param_list = StdParam::GetUniqueParamList();
		for (int i=0; i<n_rows; i++)
		{
			status = ProUITableCellComponentNameGet(dialog, table, row_names[i], "Name", &label_name);
			if (status != PRO_TK_NO_ERROR) continue;

			status = ProUILabelTextGet(dialog, label_name, &w_mdl_name);
			ProStringFree(label_name);

			status = ProUITableCellLabelGet(dialog, table, row_names[i], "Type", &w_type);
			if (status != PRO_TK_NO_ERROR) continue;

			if (wcsicmp(w_type, L"ASM") == 0)
			{
				status = ProMdlInit(w_mdl_name, PRO_MDL_ASSEMBLY, &mdl);
			}
			else if (wcsicmp(w_type, L"PRT") == 0)
			{
				status = ProMdlInit(w_mdl_name, PRO_MDL_PART, &mdl);
			}
			else
				continue;

			status = ProMdlToModelitem(mdl, &model_item);
			if (status != PRO_TK_NO_ERROR) continue;

			for (auto it = param_list->begin(); it != param_list->end(); it++)
			{
				wcstombs(col_name, it->Name, MAX_PATH);
				status = ProUITableCellLabelGet(dialog, table, row_names[i], col_name, &w_value);
				if (status != PRO_TK_NO_ERROR) continue;

				status = StdParam::SetParamValueWithString(model_item, it->Name, it->Type, it->Names, w_value);
				ProWstringFree(w_value);

				status = StdParam::SetStdRelations(mdl);

				TLog::Print2(L"Processing %d of %d, mdl = %s, param = %s", i + 1, n_rows, w_mdl_name, it->Name);
			}

			ProWstringFree(w_mdl_name);
			ProWstringFree(w_type);
		}

		return PRO_TK_NO_ERROR;
	}


	ProError StdParam::Standardize(Table *table, Mirim::Option *option)
	{
		ProError	status;
		int			n_rows;
		char		**row_names;
		char		*label_name;
		wchar_t		*w_mdl_name;
		wchar_t		*w_pointer;
		wchar_t		w_partnr[32];
		wchar_t		*w_label;
		ProUIColor  ui_color;
		wchar_t		*w_type;

		status = ProUITableRownamesGet(table->dialog, table->table, &n_rows, &row_names);
		if (status != PRO_TK_NO_ERROR) return status;

		std::vector<Cell> cell_list;
		for (int i=0; i<n_rows; i++)
		{
			status = ProUITableCellLabelGet(table->dialog, table->table, row_names[i], "Type", &w_type);
			if (status != PRO_TK_NO_ERROR || wcslen(w_type) < 1)
			{
				ProWstringFree(w_type);
				continue;
			}

			status = ProUITableCellBackgroundColorGet(table->dialog, table->table, row_names[i], "S15_CAD_TYPE", &ui_color);
			status = ProUITableCellLabelGet(table->dialog, table->table, row_names[i], "S15_CAD_TYPE", &w_label);
			if (wcscmp(w_label, L"PROE") != 0)
			{
				status = ProUITableCellLabelSet(table->dialog, table->table, row_names[i], "S15_CAD_TYPE", L"PROE");
				cell_list.push_back(Cell(row_names[i], "S15_CAD_TYPE", w_label, ui_color));
				status = ProUITableCellBackgroundColorSet(table->dialog, table->table, row_names[i], "S15_CAD_TYPE", PRO_UI_COLOR_WHITE);
			}
			ProWstringFree(w_label);

			status = ProUITableCellComponentNameGet(table->dialog, table->table, row_names[i], "Name", &label_name);
			if (status != PRO_TK_NO_ERROR) continue;

			status = ProUILabelTextGet(table->dialog, label_name, &w_mdl_name);
			if (status != PRO_TK_NO_ERROR) continue;

			if (wcslen(w_mdl_name) != option->PartNrLength) 
			{
				w_partnr[0] = 0;
			}
			else
			{
				w_pointer = w_mdl_name + option->PartNrStart;
				int n = 4;
				wcsncpy(w_partnr, w_pointer, n);
				w_partnr[n] = 0;
			}

			status = ProUITableCellBackgroundColorGet(table->dialog, table->table, row_names[i], "S01_PART_NO", &ui_color);
			status = ProUITableCellLabelGet(table->dialog, table->table, row_names[i], "S01_PART_NO", &w_label);
			if (wcsicmp(w_label, w_partnr) != 0)
			{
				status = ProUITableCellLabelSet(table->dialog, table->table, row_names[i], "S01_PART_NO", w_partnr);
				cell_list.push_back(Cell(row_names[i], "S01_PART_NO", w_label, ui_color));
				status = ProUITableCellBackgroundColorSet(table->dialog, table->table, row_names[i], "S01_PART_NO", PRO_UI_COLOR_WHITE);
			}
			ProWstringFree(w_label);
		}

		if (cell_list.size() > 0)
		{
			table->undo_list.push_back(cell_list);
		}

		return PRO_TK_NO_ERROR;
	}
}