#include "stdafx.h"
#include "AsmRename.h"

namespace Gui
{
	AsmRename::AsmRename(void)
	{
	}


	AsmRename::~AsmRename(void)
	{
	}

	ProError AsmRename::ShowNames(Table *table, std::vector<Model> &mdl_list)
	{
		ProError	status;
		char		**row_names;
		wchar_t		w_row_label[32];
		char		label_name[32];
		char		lb_name[32];
		char		cb_name[32];
		wchar_t		*w_common_name;
		ProBoolean  is_modifiable;

		table->Initialize();
		Mirim::Option *option = Mirim::Option::GetUniqueInstance();

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

			status = ProUITableCellLabelSet(table->dialog, table->table, row_names[i], "Type", mdl_list[i].mdl_data.type);
			status = ProUITableCellLabelSet(table->dialog, table->table, row_names[i], "Name1", mdl_list[i].mdl_data.name);
			status = ProUITableCellBackgroundColorSet(table->dialog, table->table, row_names[i], "Name1", PRO_UI_COLOR_HOVER_TEXT);

			status = ProMdlCommonnameGet(mdl_list[i].mdl, &w_common_name, &is_modifiable);
			if (status == PRO_TK_NO_ERROR) 
			{
				status = ProUITableCellLabelSet(table->dialog, table->table, row_names[i], "CommonName", w_common_name);
				if (is_modifiable == PRO_B_TRUE)				
					status = ProUITableCellBackgroundColorSet(table->dialog, table->table, row_names[i], "CommonName", PRO_UI_COLOR_HOVER_TEXT);
				else
					status = ProUITableCellBackgroundColorSet(table->dialog, table->table, row_names[i], "CommonName", PRO_UI_COLOR_3D_DARK_SHADOW);
			}
			else
			{
				status = ProUITableCellLabelSet(table->dialog, table->table, row_names[i], "CommonName", w_common_name);
				status = ProUITableCellBackgroundColorSet(table->dialog, table->table, row_names[i], "CommonName", PRO_UI_COLOR_YELLOW);
			}

			// Show drawing status
			sprintf(lb_name, "%s_Drw", row_names[i]);
			status = ProUITableCellComponentCopy(table->dialog, table->table, row_names[i], "Drw", table->dialog, table->lb_source, lb_name);
			status = ProUILabelEnable(table->dialog, lb_name);
			status = ProUILabelShow(table->dialog, lb_name);
			status = ProUILabelTextSet(table->dialog, lb_name, L"");
			if (mdl_list[i].drawing_exists)
				status = ProUILabelBitmapSet(table->dialog, lb_name, "drw_icon.gif");
			else
				status = ProUILabelBitmapSet(table->dialog, lb_name, "emp_icon.gif");


			// Show modify status
			sprintf(cb_name, "%s_Modify", row_names[i]);
			status = ProUITableCellComponentCopy(table->dialog, table->table, row_names[i], "Modify", table->dialog, table->cb_source, cb_name);
			status = ProUICheckbuttonEnable(table->dialog, cb_name);
			status = ProUICheckbuttonShow(table->dialog, cb_name);
			if (wcslen(mdl_list[i].mdl_data.name) == option->TotalLength)
			{
				status = ProUICheckbuttonSet(table->dialog, cb_name);
			}
			else
			{
				status = ProUICheckbuttonUnset(table->dialog, cb_name);
			}
		}

		return PRO_TK_NO_ERROR;
	}


	ProError AsmRename::SyncNames(Table *table)
	{
		ProError	status;
		int			n_rows;
		char		**row_names;
		wchar_t		*w_name;
		wchar_t		*w_type;
		ProPath		w_common_name;
		wchar_t		*w_common_name1;
		ProUIColor	ui_color;

		status = ProUITableRownamesGet(table->dialog, table->table, &n_rows, &row_names);
		if (status != PRO_TK_NO_ERROR) return status;

		std::vector<Cell> cell_list;
		for (int i=0; i<n_rows; i++)
		{
			status = ProUITableCellLabelGet(table->dialog, table->table, row_names[i], "Name1", &w_name);
			if (status != PRO_TK_NO_ERROR) continue;

			status = ProUITableCellLabelGet(table->dialog, table->table, row_names[i], "Type", &w_type);
			if (status != PRO_TK_NO_ERROR) continue;

			status = ProUITableCellLabelGet(table->dialog, table->table, row_names[i], "CommonName", &w_common_name1);
			if (status != PRO_TK_NO_ERROR) continue;

			wsprintf(w_common_name, L"%s.%s", w_name, w_type);
			if (wcsicmp(w_common_name1, w_common_name) != 0)
			{
				status = ProUITableCellBackgroundColorGet(table->dialog, table->table, row_names[i], "CommonName", &ui_color);
				if (status != PRO_TK_NO_ERROR) continue;

				cell_list.push_back(Cell(row_names[i], "CommonName", w_common_name1, ui_color)); 
				status = ProUITableCellLabelSet(table->dialog, table->table, row_names[i], "CommonName", w_common_name);
				status = ProUITableCellBackgroundColorSet(table->dialog, table->table, row_names[i], "CommonName",PRO_UI_COLOR_WHITE);
			}

			ProWstringFree(w_name);
			ProWstringFree(w_type);
			ProWstringFree(w_common_name1);			
		}

		if (cell_list.size() > 0)
		{
			table->undo_list.push_back(cell_list);
		}

		return PRO_TK_NO_ERROR;
	}

	ProError AsmRename::ApplyNames(Table *table)
	{
		ProError	status;
		char		*label_name;
		int			n_rows;
		char		**row_names;
		wchar_t		*w_name;
		wchar_t		*w_name1;
		wchar_t		*w_type;
		wchar_t		*w_common_name;
		wchar_t		*w_common_name1;
		ProMdl		mdl;
		ProMdl		drawing;
		ProBoolean  is_modifiable;

		status = ProUITableRownamesGet(table->dialog, table->table, &n_rows, &row_names);
		if (status != PRO_TK_NO_ERROR) return status;

		for (int i=0; i<n_rows; i++)
		{
			status = ProUITableCellComponentNameGet(table->dialog, table->table, row_names[i], "Name", &label_name); 
			status = ProUILabelTextGet(table->dialog, label_name, &w_name);
			ProStringFree(label_name);

			status = ProUITableCellLabelGet(table->dialog, table->table, row_names[i], "Type", &w_type);
			status = ProUITableCellLabelGet(table->dialog, table->table, row_names[i], "CommonName", &w_common_name);
			status = ProUITableCellLabelGet(table->dialog, table->table, row_names[i], "Name1", &w_name1);
			if (wcsicmp(w_type, L"ASM") == 0)
			{
				status = ProMdlInit(w_name, PRO_MDL_ASSEMBLY, &mdl);
			}
			else if (wcsicmp(w_type, L"PRT") == 0)
			{
				status = ProMdlInit(w_name, PRO_MDL_PART, &mdl);
			}
			else 
			{
				continue;
			}

			TLog::Print(L"");
			status = ProMdlCommonnameGet(mdl, &w_common_name1, &is_modifiable);
			if (is_modifiable)
			{
				status = ProMdlCommonnameSet(mdl, w_common_name);
				if (status == PRO_TK_NO_ERROR)
					TLog::Print2(L"Common Name is modified: MDL: %s.%s, %s ===> %s", w_name, w_type, w_common_name1, w_common_name);
				else
					TLog::Print2(L"### Failed to Modify Common Name: MDL: %s.%s, %s ===> %s", w_name, w_type, w_common_name1, w_common_name);
			}
			else
			{
				TLog::Print2(L"Common Name is not modifable: %s.%s", w_name, w_type);
			}

			status = ProMdlRename(mdl, w_name1);
			if (status == PRO_TK_NO_ERROR)
				TLog::Print2(L"Model Renamed: %s.%s ===> %s.%s", w_name, w_type, w_name1, w_type);
			else
				TLog::Print2(L"### Failed to Rename Model:  %s.%s ===> %s.%s", w_name, w_type, w_name1, w_type);

			status = ProMdlInit(w_name, PRO_MDL_DRAWING, &drawing);
			if (status == PRO_TK_NO_ERROR)
			{
				status = ProMdlRename(drawing, w_name1);
				if (status == PRO_TK_NO_ERROR)
					TLog::Print2(L"Drawing Renamed: %s.%s ===> %s.%s", w_name, w_type, w_name1, w_type);
				else
					TLog::Print2(L"### Failed to Rename Drawing:  %s.%s ===> %s.%s", w_name, w_type, w_name1, w_type);
			}
			else
			{
					TLog::Print2(L"### Drawing not exists:  %s.drw", w_name);
			}

			ProWstringFree(w_name);
			ProWstringFree(w_name1);
			ProWstringFree(w_type);
			ProWstringFree(w_common_name);			
			ProWstringFree(w_common_name1);			
		}

		Mirim::MsgBox::Show(L"PMP", L"Finished...");

		return PRO_TK_NO_ERROR;
	}
}