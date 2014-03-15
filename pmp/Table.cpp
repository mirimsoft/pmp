#include "Table.h"
#include "UI.h"


namespace Gui
{
	int Table::row_number = 0;

	Table::Table(char *dialog, char *table)
		:dialog(dialog), table(table)
	{
	}


	Table::~Table(void)
	{
	}

	ProError Table::Initialize()
	{
		this->undo_list = deque<std::vector<Cell>>();
		this->redo_list = stack<std::vector<Cell>>();

		return PRO_TK_NO_ERROR;
	}

#pragma region Common Methods

	ProError Table::SaveColumnWidths(char *dialog, char *table, Mirim::Option *option)
	{
		ProError    status;
		int        *widths;
		int         n_count;
		wchar_t     w_text[32];

		status = ProUITableColumnwidthsGet(dialog, table, &n_count, &widths);
		if (n_count <= 3) return PRO_TK_BAD_CONTEXT;

        std::wstring w_str;
		for (int i = 0; i < n_count; i++)
		{
			w_str += _itow(widths[i], w_text, 10);
			w_str += L",";
		}

		ProIntarrayFree(widths);
		if (option->ColumnWidths != NULL)
            delete[] option->ColumnWidths;

        option->ColumnWidths = new wchar_t [w_str.size() + 1];
        wcscpy_s(option->ColumnWidths, w_str.size() + 1, w_str.c_str());

		return PRO_TK_NO_ERROR;
	}

	ProError Table::RestoreColumnWidths(char *dialog, char *table, Mirim::Option *option)
	{
		ProError status;

		int length = wcslen(option->ColumnWidths) + 1;
		wchar_t *w_widths = new wchar_t[length];
		wcscpy_s(w_widths, length, option->ColumnWidths);

		std::vector<int> widths;
		wchar_t *w_pointer = wcstok(w_widths, L",");
		if (!w_pointer) return PRO_TK_E_NOT_FOUND;

		widths.push_back(_wtoi(w_pointer));
		while (w_pointer = wcstok(NULL, L","))
		{
			widths.push_back(_wtoi(w_pointer));
		}
		delete[] w_widths;

		int n_count = static_cast<int>(widths.size());
		int *values = new int[n_count];
		for (int i = 0; i < n_count; i++)
		{
			values[i] = widths[i];
		}

		status = ProUITableColumnwidthsSet(dialog, table, n_count, values);
		delete[] values;

		return (PRO_TK_NO_ERROR);
	}

	ProError Table::GetFirstRowName(char *dialog, char *table, char *row_name)
	{
		ProError  status;
		int       n_count;
		char      **values;

		/*--------------------------------------------------------------------*\
		Get all the rows in the table and the return the row with the smallest index.
		\*--------------------------------------------------------------------*/
		status = ProUITableRownamesGet(dialog, table, &n_count, &values);
		if ((status != PRO_TK_NO_ERROR) || (n_count < 1))
		{
			*row_name = NULL;
		}
		else
		{
			strcpy_s(row_name, strlen(values[0]) + 1, values[0]);
		}

		ProStringarrayFree(values, n_count);

		return (PRO_TK_NO_ERROR);
	}

	ProError Table::GetLastRowName(char *dialog, char *table, char *row_name)
	{
		ProError  status;
		int       n_count;
		char      **values;

		/*--------------------------------------------------------------------*\
		Get all the rows in the table and the return the row with the
		greatest index.
		\*--------------------------------------------------------------------*/
		status = ProUITableRownamesGet(dialog, table, &n_count, &values);
		if ((status != PRO_TK_NO_ERROR) || (n_count < 1))
		{
			*row_name = NULL;
		}
		else
		{
			strcpy_s(row_name, strlen(values[n_count - 1]) + 1, values[n_count - 1]);
		}

		ProStringarrayFree(values, n_count);

		return (PRO_TK_NO_ERROR);
	}

	ProError Table::PrepareRows(char *dialog, char *table, int n_rows)
	{
		ProError    status;
		char		**row_names;
		int		    n_count;

		// Remove all rows
		status = ProUITableRownamesGet(dialog, table, &n_count, &row_names);
		if (n_count > 0)
		{
			status = ProUITableRowsDelete(dialog, table, n_count, row_names);
			ProStringarrayFree(row_names, n_count);
		}

		if (n_rows < 1) return PRO_TK_NO_ERROR;

		// Add New Rows
		row_names = (char **)calloc(n_rows, sizeof(char *));
		for (int i = 0; i < n_rows; i++)
		{
			Gui::Table::row_number++;
			row_names[i] = (char *)calloc(32, sizeof(char));
			sprintf(row_names[i], "%d", Gui::Table::row_number);
		}
		status = ProUITableRowsInsert(dialog, table, NULL, n_rows, row_names);

		for (int i = 0; i < n_rows; i++)
		{
			free(row_names[i]);
		}

		free(row_names);

		return PRO_TK_NO_ERROR;
	}

	ProError Table::SwapRows(char *dialog, char *table, int row1, int row2)
	{
		ProError	status;
        ProError    status1;
		int			col_count, row_count;
		char		**row_values;
		char		**col_values;
		wchar_t		*w_label1;
		wchar_t		*w_label2;
        char        *name1;
        char        *name2;
        char        *bitmap1;
        char        *bitmap2;

		if (row1 == row2) return PRO_TK_BAD_INPUTS;
		/*--------------------------------------------------------------------*\
		Get the rows in the table
		\*--------------------------------------------------------------------*/
		status = ProUITableRownamesGet(dialog, table, &row_count, &row_values);
		if ((status == PRO_TK_NO_ERROR) && (row_count > 1))
		{
			if ((row1 >= 0) && (row1 < row_count) && (row2 >= 0) && (row2 < row_count))
			{
				/*--------------------------------------------------------------------*\
				Get the columns in the table
				\*--------------------------------------------------------------------*/
				status = ProUITableColumnnamesGet(dialog, table, &col_count, &col_values);
				if ((status == PRO_TK_NO_ERROR) && (col_count > 0))
				{
					/*--------------------------------------------------------------------*\
					Swap the cell values
					\*--------------------------------------------------------------------*/
					for (int i = 0; i < col_count; i++)
					{
                        status = ProUITableCellLabelGet(dialog, table, row_values[row1], col_values[i], &w_label1);
                        status = ProUITableCellLabelGet(dialog, table, row_values[row2], col_values[i], &w_label2);
                        status = ProUITableCellLabelSet(dialog, table, row_values[row1], col_values[i], w_label2);
                        status = ProUITableCellLabelSet(dialog, table, row_values[row2], col_values[i], w_label1);

                        ProWstringFree(w_label1);
                        ProWstringFree(w_label2);

                        status1 = ProUITableCellComponentNameGet(dialog, table, row_values[row1], col_values[i], &name1);
                        if (status1 != PRO_TK_NO_ERROR) continue;

                        status1 = ProUITableCellComponentNameGet(dialog, table, row_values[row2], col_values[i], &name2);
                        if (status1 != PRO_TK_NO_ERROR) continue;

                        status1 = ProUILabelBitmapGet(dialog, name1, &bitmap1);
                        status1 = ProUILabelBitmapGet(dialog, name2, &bitmap2);

                        status1 = ProUILabelBitmapSet(dialog, name2, bitmap1);
                        status1 = ProUILabelBitmapSet(dialog, name1, bitmap2);
                    }
				}
				ProStringarrayFree(col_values, col_count);
			}
			else
			{
				status = PRO_TK_BAD_INPUTS;
			}
		}
		ProStringarrayFree(row_values, row_count);

		return status;
	}

	ProError Table::MoveRow(char *dialog, char *table, int direction)
	{
		ProError  status;
		int       n_count;
		char      **names;
		int       selected_row;
		int       index;
		int       new_row;

		// Get all the selected rows 
		status = ProUITableSelectednamesGet(dialog, table, &n_count, &names);
		if ((status != PRO_TK_NO_ERROR) || (n_count < 1))
		{
			ProStringarrayFree(names, n_count);
			return status;
		}

		//Get the row with the lowest index 
		selected_row = -1;
		for (int i = 0; i<n_count; i = i + 2)
		{
			status = ProUITableRowIndexGet(dialog, table, names[i], &index);
			if ((status == PRO_TK_NO_ERROR) && (selected_row == -1) || (selected_row > index))
			{
				selected_row = index;
			}
		}

		// Swap the values of the selected row
		new_row = selected_row + direction;
		status = Table::SwapRows(dialog, table, new_row, selected_row);

		if (status != PRO_TK_NO_ERROR)
		{
			ProStringarrayFree(names, n_count);
			return status;
		}

		// Deselect all the rows
		for (int i = 0; i < n_count; i = i + 2)
		{
			status = ProUITableRowCellsDeselect(dialog, table, 1, &(names[i]));
		}

		ProStringarrayFree(names, n_count);

		// Highlight the new row 
		status = ProUITableRownamesGet(dialog, table, &n_count, &names);
		if ((status != PRO_TK_NO_ERROR) || (n_count < 1))
		{
			ProStringarrayFree(names, n_count);
			return status;
		}

		// Save new row name
		size_t length = strlen(names[new_row]) + 1;
		char *new_row_name = (char *)std::calloc(length, sizeof(char));
		strcpy_s(new_row_name, length, names[new_row]);

		ProUISelectionpolicy policy;
		status = ProUITableSelectionpolicyGet(dialog, table, &policy);
		if (policy == PROUISELPOLICY_MULTIPLE || policy == PROUISELPOLICY_EXTENDED)
		{
			status = ProUITableRowCellsSelect(dialog, table, 1, &new_row_name);
		}
		else
		{

			ProStringarrayFree(names, n_count);
			status = ProUITableSelectednamesGet(dialog, table, &n_count, &names);
			if ((status == PRO_TK_NO_ERROR) && (n_count > 0))
			{
				strcpy_s(names[0], length, new_row_name);
				status = ProUITableSelectednamesSet(dialog, table, 2, names);
			}
		}

		free(new_row_name);
		ProStringarrayFree(names, n_count);

		return PRO_TK_NO_ERROR;
	}


	ProError Table::MoveDownRow(char *dialog, char *table)
	{
		return Table::MoveRow(dialog, table, 1);
	}

	ProError Table::MoveUpRow(char *dialog, char *table)
	{
		return Table::MoveRow(dialog, table, -1);
	}

	ProError Table::AddRow(char *dialog, char *table)
	{
		ProError  status;
		char      last_row_name[16];
		char      new_row_name[16];
		char      *pointer = &new_row_name[0];

		/*--------------------------------------------------------------------*\
		Add a row after the last row
		\*--------------------------------------------------------------------*/
		status = Table::GetLastRowName(dialog, table, last_row_name);

		Table::row_number++;
		ProTKSprintf(new_row_name, "%d", Table::row_number);
		status = ProUITableRowsInsert(dialog, table, last_row_name, 1, &pointer);

		int n_count;
		char **names;
		status = ProUITableColumnnamesGet(dialog, table, &n_count, &names);
		if (n_count > 0)
		{
			status = ProUITableFocusCellSet(dialog, table, new_row_name, names[0]);
			status = ProUITableAnchorCellSet(dialog, table, new_row_name, names[0]);
		}

		return PRO_TK_NO_ERROR;
	}

	ProError Table::RemoveRow(char *dialog, char *table)
	{
		ProError	status;
		int			count, sel_row, index;
		char		**del_values;
		char		**values;

		/*--------------------------------------------------------------------*\
		Get all the selected rows
		\*--------------------------------------------------------------------*/
		status = ProUITableSelectednamesGet(dialog, table, &count, &del_values);
		if ((status == PRO_TK_NO_ERROR) && (count > 0))
		{
			/*--------------------------------------------------------------------*\
			Get the row with the lowest index
			\*--------------------------------------------------------------------*/
			sel_row = -1;
			for (int i = 0; i<count; i = i + 2)
			{
				status = ProUITableRowIndexGet(dialog, table, del_values[i], &index);
				if ((status == PRO_TK_NO_ERROR) && (sel_row == -1) || (sel_row > index))
				{
					sel_row = index;
				}
			}

			/*--------------------------------------------------------------------*\
			Delete the selected rows
			\*--------------------------------------------------------------------*/
			for (int i = 0; i<count; i = i + 2)
			{
				status = ProUITableRowsDelete(dialog, table, 1, &(del_values[i]));
			}

			/*--------------------------------------------------------------------*\
			Highlight the row with the lowest index
			\*--------------------------------------------------------------------*/
			if (sel_row > -1)
			{
				status = ProUITableRownamesGet(dialog,table, &index, &values);
				if ((status == PRO_TK_NO_ERROR) && (index > 0))
				{
					if (sel_row >= index)
					{
						sel_row = index - 1;
					}
					status = ProUITableRowCellsSelect(dialog, table, 1, &(values[sel_row]));
				}

				ProStringarrayFree(values, index);
			}
		}

		ProStringarrayFree(del_values, count);
		return PRO_TK_NO_ERROR;
	}


	bool Table::SingleCellSelected(char *dialog, char *table)
	{
		ProError    status;
		char        **names;
		char        *row;
		int         n_count;
		/*--------------------------------------------------------------------*\ 
		Get all the selected rows. If more thatn one row is selected, do nothing
		\*--------------------------------------------------------------------*/  
		status = ProUITableSelectednamesGet(dialog, table, &n_count, &names);
		if((status == PRO_TK_NO_ERROR) && (n_count > 0))
		{
			row = names[0];
			for(int i = 2; i<n_count; i++)
			{
				if(strcmp(row, names[i]) != 0)
				{
					ProStringarrayFree(names, n_count);
					return false;
				}
			}
		}

		ProStringarrayFree(names, n_count);

		return true;
	}


	ProError Table::BeginEditWithCheckbutton()
	{

		return PRO_TK_NO_ERROR;
	}

	ProError Table::BeginEditWithInputpanel()
	{
		ProError    status;
		char        inputpanel[32];
		int         width;
		wchar_t     *w_label;



		status = ProUITableCellLabelGet(dialog, this->table, this->row, this->col, &w_label);
		ProTKSprintf(inputpanel, "%s_%s", this->row, this->col);
		status = ProUITableCellComponentCopy(dialog, this->table, this->row, this->col, dialog, this->ip_source, inputpanel);
		if (status == PRO_TK_NO_ERROR)
		{
			/*--------------------------------------------------------------------*\
			Setup the properties of the input panel
			\*--------------------------------------------------------------------*/
			status = ProUITableColumnWidthGet(dialog, this->table, this->col, &width);
			status = ProUIInputpanelColumnsSet(dialog, inputpanel, width);
			status = ProUIInputpanelEnable(dialog, inputpanel);
			status = ProUIInputpanelShow(dialog, inputpanel);
			status = ProUIInputpanelValueSet(dialog, inputpanel, w_label);
			status = ProUIDialogFocusSet(dialog, inputpanel);
			status = ProUIInputpanelFocusoutActionSet(dialog, inputpanel, (ProUIAction)Table::EndEditWithInputpanel, this);
		}

		ProWstringFree(w_label);

		return PRO_TK_NO_ERROR;
	}

	ProError Table::EndEditWithInputpanel(char *dialog, char *table, ProAppData app_data)
	{
		ProError	status;
		wchar_t		*w_label;
		wchar_t		*w_label1;
		char		input_panel[32];
		ProUIColor  ui_color;

		Table *table_data = (Table *) app_data;

		ProTKSprintf(input_panel, "%s_%s", table_data->row, table_data->col);

		/*--------------------------------------------------------------------*\
		Copy the input panel label to the cell
		\*--------------------------------------------------------------------*/
		status = ProUIInputpanelValueGet(dialog, input_panel, &w_label);
		if ((status == PRO_TK_NO_ERROR) && (w_label != NULL))
		{
			status = ProUITableCellLabelGet(dialog, table_data->table, table_data->row, table_data->col, &w_label1);
			if (wcsicmp(w_label1, w_label) != 0)
			{
				status = ProUITableCellBackgroundColorGet(dialog, table_data->table, table_data->row, table_data->col, &ui_color);
				status = ProUITableCellBackgroundColorSet(dialog, table_data->table, table_data->row, table_data->col, PRO_UI_COLOR_WHITE);
				table_data->redo_list = stack<std::vector<Cell>>();

				Cell cell(table_data->row, table_data->col, w_label1, ui_color);
				std::vector<Cell> cell_list;
				cell_list.push_back(cell);
				table_data->undo_list.push_back(cell_list);

				status = ProUITableCellLabelSet(dialog, table_data->table, table_data->row, table_data->col, w_label);
			}

			ProWstringFree(w_label1);
		}
		ProWstringFree(w_label);

		/*--------------------------------------------------------------------*\
		Delete the input panel label from the cell
		\*--------------------------------------------------------------------*/
		status = ProUITableCellComponentDelete(dialog, table_data->table, table_data->row, table_data->col);
		ProStringFree(table_data->row);
		ProStringFree(table_data->col);

		return PRO_TK_NO_ERROR;
	}



	ProError Table::BeginEditWithOptionmenu(int n_count, char **names, wchar_t **w_names)
	{
		ProError    status;
		char        optionmenu[32];
		int         width;
		wchar_t     *w_label;

		status = ProUITableCellLabelGet(dialog, this->table, this->row, this->col, &w_label);
		ProTKSprintf(optionmenu, "%s_%s", this->row, this->col);
		status = ProUITableCellComponentCopy(dialog, this->table, this->row, this->col, dialog, this->om_source, optionmenu);
		if (status == PRO_TK_NO_ERROR)
		{
			/*--------------------------------------------------------------------*\
			Setup the properties of the optionmenu
			\*--------------------------------------------------------------------*/
			status = ProUITableColumnWidthGet(dialog, this->table, this->col, &width);
			status = ProUIOptionmenuColumnsSet(dialog, optionmenu, width);
            status = ProUIOptionmenuEditable(dialog, optionmenu);
            status = ProUIOptionmenuShow(dialog, optionmenu);
            status = ProUIOptionmenuNamesSet (dialog, optionmenu, n_count, names);
            status = ProUIOptionmenuLabelsSet (dialog, optionmenu, n_count, w_names);
            status = ProUIOptionmenuValueSet(dialog, optionmenu, w_label);
            status = ProUIDialogFocusSet(dialog, optionmenu);
            status = ProUIOptionmenuFocusoutActionSet(dialog, optionmenu, (ProUIAction)Table::EndEditWithOptionmenu, this);
		}

		ProWstringFree(w_label);
        for (int i=0; i<n_count; i++)
        {
            free(names[i]);
            free(w_names[i]);
        }
        free(names);
        free(w_names);

		return PRO_TK_NO_ERROR;
	}

	ProError Table::EndEditWithOptionmenu(char *dialog, char *table, ProAppData app_data)
	{
		ProError	status;
		wchar_t		*w_label;
		wchar_t		*w_label1;
		char		optionmenu[32];
		ProUIColor  ui_color;

		Table *table_data = (Table *)app_data;
		ProTKSprintf(optionmenu, "%s_%s", table_data->row, table_data->col);

		/*--------------------------------------------------------------------*\
		Copy the Optionmenu label to the cell
		\*--------------------------------------------------------------------*/
		status = ProUIOptionmenuValueGet(dialog, optionmenu, &w_label);
		if ((status == PRO_TK_NO_ERROR) && (w_label != NULL))
		{
			if (wcsicmp(w_label, L"FALSE") == 0) *w_label = 0; // Clear the label			
			status = ProUITableCellLabelGet(dialog, table_data->table, table_data->row, table_data->col, &w_label1);
			if (wcsicmp(w_label1, w_label) != 0)
			{
				status = ProUITableCellBackgroundColorGet(dialog, table_data->table, table_data->row, table_data->col, &ui_color);
				status = ProUITableCellBackgroundColorSet(dialog, table_data->table, table_data->row, table_data->col, PRO_UI_COLOR_WHITE);
				table_data->redo_list = stack<std::vector<Cell>>();

				Cell cell(table_data->row, table_data->col, w_label1, ui_color);
				std::vector<Cell> cell_list;
			    cell_list.push_back(cell);
				table_data->undo_list.push_back(cell_list);
				status = ProUITableCellLabelSet(dialog, table_data->table, table_data->row, table_data->col, w_label);
			}

			ProWstringFree(w_label1);
		}

        ProWstringFree(w_label);
		/*--------------------------------------------------------------------*\
		Delete the input panel label from the cell
		\*--------------------------------------------------------------------*/
		status = ProUITableCellComponentDelete(dialog, table_data->table, table_data->row, table_data->col);
		ProStringFree(table_data->row);
		ProStringFree(table_data->col);

		return PRO_TK_NO_ERROR;
	}


	ProError Table::CopyToClipboard()
	{
		ProError    status;
		char        **names;
		int         n_count;

		status = ProUITableSelectednamesGet(this->dialog, this->table, &n_count, &names);
		if (status != PRO_TK_NO_ERROR || n_count < 1) return PRO_TK_BAD_INPUTS;

		wchar_t *w_label;
		wstring w_text;
		for (int i = 0; i < n_count; i += 2)
		{
			status = ProUITableCellLabelGet(this->dialog, this->table, names[i], names[i + 1], &w_label);
			if (status != PRO_TK_NO_ERROR) w_label = NULL;

			if (i + 2 == n_count || stricmp(names[i], names[i + 2]) != 0)
				w_text += wstring(w_label) + wstring(L"\r\n");
			else	
				w_text += wstring(w_label) + wstring(L"\t");

		}

		if (Mirim::UI::CopyToClipboard(w_text.c_str()))
			return PRO_TK_NO_ERROR;
		else
			return PRO_TK_GENERAL_ERROR;
	}

	ProError Table::PasteFromClipboard()
	{
		ProError	status;
		wchar_t		*w_data;
		int			n_selected;
		char		**names;
		int			row_index, col_index;
		int			n_rows, n_cols;
		char		**row_names, **col_names;
		wchar_t		*w_pointer;
		wchar_t		*w_curr_word;
		wchar_t     *w_next_word;
		ProUIColor  ui_color;
		wchar_t		*w_label;

		if (!Mirim::UI::PasteFromClipBoard(&w_data)) return PRO_TK_EMPTY;
		if (wcslen(w_data) < 1) return PRO_TK_E_NOT_FOUND;

		status = this->IsOneCellSelected(this->dialog, this->table, &row_index, &col_index);
		if (status != PRO_TK_NO_ERROR) return status;

		this->redo_list = stack<std::vector<Cell>>();
		std::vector<Cell> cell_list;

		// Single cell data
		if (wcschr(w_data, L'\t') == NULL && wcschr(w_data, L'\r') == wcsrchr(w_data, L'\r'))
		{
			w_curr_word = w_data;
			if (wcschr(w_data, L'\r') != NULL)
			{
				w_curr_word[wcschr(w_curr_word, L'\r') - w_curr_word] = 0;
			}

			status = ProUITableSelectednamesGet(this->dialog, this->table, &n_selected, &names);
			if (status != PRO_TK_NO_ERROR) return status;

			for (int i=0; i<n_selected; i+=2)
			{
				status = ProUITableCellBackgroundColorGet(this->dialog, this->table, names[i], names[i + 1], &ui_color);
				if (ui_color != PRO_UI_COLOR_3D_DARK_SHADOW)
				{
					status = ProUITableCellLabelGet(this->dialog, this->table, names[i],  names[i + 1], &w_label);
					if (wcsicmp(w_label, w_curr_word) != 0)
					{
						status = ProUITableCellLabelSet(this->dialog, this->table, names[i],  names[i + 1], w_curr_word);
						status = ProUITableCellBackgroundColorSet(this->dialog, this->table,names[i],  names[i + 1], PRO_UI_COLOR_WHITE);

						Cell cell(names[i], names[i + 1], w_label, ui_color);
						cell_list.push_back(cell);
					}

					ProWstringFree(w_label);
				}
			}

			if (cell_list.size() > 0) this->undo_list.push_back(cell_list);

			return PRO_TK_NO_ERROR;
		}


		status = ProUITableRownamesGet(this->dialog, this->table, &n_rows, &row_names);
		status = ProUITableColumnnamesGet(this->dialog, this->table, &n_cols, &col_names);

		w_pointer = w_data;
		w_curr_word = w_data;
		w_next_word = w_data;	
		int fir_col = col_index;
		int n_count = static_cast<int>(wcslen(w_data));
		bool finished = false;
		for (int i = 0; i <= n_count; i++)
		{
			bool go_to_next_row = false;
			bool go_to_first_col = false;

			if (*w_pointer == '\t')
			{
				*w_pointer = NULL;
				w_next_word = w_pointer + 1;
			}
			else if (wcsncmp(w_pointer, L"\r\n", 2) == 0)
			{
				*w_pointer = NULL;
				w_next_word = w_pointer + 2;
				if (wcslen(w_next_word) < 1) finished = true;
				go_to_next_row = true;
				go_to_first_col = true;
			}

			if (*w_pointer == NULL)
			{
				if (row_index < n_rows && col_index < n_cols)
				{
					status = ProUITableCellBackgroundColorGet(this->dialog, this->table, row_names[row_index], col_names[col_index], &ui_color);
					if (ui_color != PRO_UI_COLOR_3D_DARK_SHADOW)
					{
						status = ProUITableCellLabelGet(this->dialog, this->table, row_names[row_index], col_names[col_index], &w_label);
						if (wcsicmp(w_label, w_curr_word) != 0)
						{
							status = ProUITableCellLabelSet(this->dialog, this->table, row_names[row_index], col_names[col_index], w_curr_word);
							status = ProUITableCellBackgroundColorSet(this->dialog, this->table, row_names[row_index], col_names[col_index], PRO_UI_COLOR_WHITE);

							Cell cell(row_names[row_index], col_names[col_index], w_label, ui_color);
							cell_list.push_back(cell);
						}

						ProWstringFree(w_label);
					}
				}

				w_curr_word = w_next_word;
				if (go_to_next_row) row_index++;
				if (go_to_first_col) col_index = fir_col;
				else                 col_index ++;			
			}

			w_pointer++;

			if (finished) break;
		}


		this->undo_list.push_back(cell_list);

		ProStringarrayFree(row_names, n_rows);
		ProStringarrayFree(col_names, n_cols);

		return PRO_TK_NO_ERROR;
	}


	ProError Table::Remember()
	{
		ProError	status;
		char	    **row_names;
		int			n_rows;
		char		**col_names;
		int			n_cols;
		wchar_t		*w_label;
		ProUIColor  ui_color;

		status = ProUITableRownamesGet(this->dialog, this->table, &n_rows, &row_names);
		if (status != PRO_TK_NO_ERROR || n_rows < 1) return status;

		status = ProUITableColumnnamesGet(this->dialog, this->table, &n_cols, &col_names);
		if (status != PRO_TK_NO_ERROR || n_cols < 1) return status;

		std::vector<Cell> cell_list;
		for (int i = 0; i < n_rows; i++)
		{
			for (int j = 0; j < n_cols; j++)
			{
				status = ProUITableCellLabelGet(this->dialog, this->table, row_names[i], col_names[j], &w_label);
				if (status != PRO_TK_NO_ERROR) continue;

				status = ProUITableCellBackgroundColorGet(this->dialog, this->table, row_names[i], col_names[j], &ui_color);
				if (status != PRO_TK_NO_ERROR) continue;

				Cell cell(row_names[i], col_names[j], w_label, ui_color);
				cell_list.push_back(cell);
			}
		}

		this->undo_list.push_back(cell_list);

		ProStringarrayFree(row_names, n_rows);
		ProStringarrayFree(col_names, n_cols);

		return PRO_TK_NO_ERROR;
	}

	ProError Table::Undo()
	{
		ProError	status;
		char		row[32];
		char		col[32];
		wchar_t		w_value[256];
		ProUIColor  ui_color;

		if (this->undo_list.empty())
		{
			Mirim::MsgBox::Show(L"ERROR", L"No items to undo...");
			return PRO_TK_NO_ERROR;
		}

		std::vector<Cell> cell_list;
		for (auto it = this->undo_list.back().begin(); it != this->undo_list.back().end(); it++)
		{
			strcpy(row, it->row.c_str());
			strcpy(col, it->col.c_str());
			wcscpy(w_value, it->w_value.c_str());
			Cell cell(this->dialog, this->table, row, col);
			cell_list.push_back(cell);

			status = ProUITableCellLabelSet(this->dialog, this->table, row,col, w_value);
			ui_color = it->color;
			status = ProUITableCellBackgroundColorSet(this->dialog, this->table, row, col, it->color);
		}

		this->redo_list.push(cell_list);
		this->undo_list.pop_back();

		return PRO_TK_NO_ERROR;
	}


	ProError Table::Redo()
	{
		char		row[32];
		char		col[32];
		wchar_t		w_value[256];
		ProError	status;

		if (this->redo_list.empty())
		{
			Mirim::MsgBox::Show(L"ERROR", L"No Items to redo...");
			return PRO_TK_NO_ERROR;
		}

		std::vector<Cell> cell_list;
		for (auto it = this->redo_list.top().begin(); it != this->redo_list.top().end(); it++)
		{
			strcpy(row, it->row.c_str());
			strcpy(col, it->col.c_str());
			wcscpy(w_value, it->w_value.c_str());
			Cell cell(this->dialog, this->table, row, col);
			cell_list.push_back(cell);

			status = ProUITableCellLabelSet(this->dialog,this-> table, row, col, w_value);
			status = ProUITableCellBackgroundColorSet(this->dialog, this->table, row, col, it->color);
		}

		this->undo_list.push_back(cell_list);
		this->redo_list.pop();

		return PRO_TK_NO_ERROR;
	}


	ProError Table::ClearSelectedCell()
	{
		ProError    status;
		wchar_t     w_text[] = L"";
		char        **names;
		int         n_names;
		ProUIColor  ui_color;

		status = ProUITableSelectednamesGet(this->dialog, this->table, &n_names, &names);
		if (status != PRO_TK_NO_ERROR || n_names < 1) return PRO_TK_BAD_CONTEXT;

		this->redo_list = stack<std::vector<Cell>>();
		std::vector<Cell> cell_list;
		for (int i = 0; i < n_names; i = i + 2)
		{
			status = ProUITableCellBackgroundColorGet(this->dialog, this->table, names[i], names[i + 1], &ui_color);
			if (ui_color == PRO_UI_COLOR_LT_GREY) continue;

			Cell cell(this->dialog, this->table, names[i], names[i + 1]);
			cell_list.push_back(cell);

			status = ProUITableCellLabelSet(this->dialog, this->table, names[i], names[i + 1], w_text);
			status = ProUITableCellBackgroundColorSet(this->dialog, this->table, names[i], names[i+1], PRO_UI_COLOR_WHITE);
		}

		this->undo_list.push_back(cell_list);

		return PRO_TK_NO_ERROR;
	}

	ProError Table::SelectCell(char *dialog, char *table, char *row, char *col)
	{
		ProError	status;
		char		**names;

		names = (char **)calloc(2, sizeof(char *));
		names[0] = (char *)calloc(32, sizeof(char));
		names[1] = (char *)calloc(32, sizeof(char));
		strcpy(names[0], row);
		strcpy(names[1], col);
		status = ProUITableSelectednamesSet(dialog, table, 2, names);
		status = ProUITableFocusCellSet(dialog, table, names[0], names[1]);
		status = ProUITableAnchorCellSet(dialog, table, names[0], names[1]);
		free(names[0]);
		free(names[1]);
		free(names);

		return PRO_TK_NO_ERROR;
	}

	ProError Table::IsOneCellSelected(char *dialog, char *table, int *row_index, int *col_index)
	{
		ProError	status;
		int			n_names;
		char		**names;

		// Get Focused Cell
		status = status = ProUITableSelectednamesGet(dialog, table, &n_names, &names);
		if (status != PRO_TK_NO_ERROR || n_names != 2) return PRO_TK_BAD_CONTEXT;

		status = ProUITableRowIndexGet(dialog, table, names[0], row_index);
		status = ProUITableColumnIndexGet(dialog, table, names[1], col_index);

		ProStringarrayFree(names, n_names);

		return PRO_TK_NO_ERROR;
	}

	
	ProError Table::GetTargetCells(char *dialog, char *table, wchar_t *w_target, std::vector<std::pair<string, string>> &cell_list, bool *in_selection)
	{
		ProError	status;
		int			n_names;
		char		**names;
		char		row_name[32];
		char		col_name[32];
		int			n_rows;
		char		**row_names;
		int			selected_row = -1;
		int			selected_col = -1;

		cell_list = std::vector<std::pair<string, string>>();
		status = ProUITableSelectednamesGet(dialog, table, &n_names, &names);
		if (status != PRO_TK_NO_ERROR || n_names < 1)
		{
			Mirim::MsgBox::Show(L"PMP", L"Select Cells...");
			return status;
		}

		if (n_names > 2)
		{
			for(int i=0; i<n_names / 2; i++)
			{
				cell_list.push_back(std::make_pair(std::string((names)[2*i]), std::string((names)[2*i + 1])));
			}
			*in_selection = true;
			status =  ProUITableSelectednamesSet(dialog, table, 0, NULL);

			return PRO_TK_NO_ERROR;
		}

		if (wcsicmp(w_target, L"CurrentColumn") == 0)
		{
			strcpy_s(row_name, names[0]);
			strcpy_s(col_name, names[1]);

			status = ProUITableRownamesGet(dialog, table, &n_rows, &row_names);
			if (status != PRO_TK_NO_ERROR || n_rows < 1) return PRO_TK_E_FOUND;
			for (int i=0; i<n_rows; i++)
			{
				cell_list.push_back(std::make_pair(std::string(row_names[i % n_rows]), std::string(col_name)));
			}
		}
		else
		{
			int n_rows, n_cols;
			char **row_names, **col_names;

			status = ProUITableRownamesGet(dialog, table, &n_rows, &row_names);
			if (status != PRO_TK_NO_ERROR || n_rows < 1) return PRO_TK_E_FOUND;

			status = ProUITableColumnnamesGet(dialog, table, &n_cols, &col_names);
			if (status != PRO_TK_NO_ERROR || n_cols < 1) return PRO_TK_E_FOUND;

			status = this->IsOneCellSelected(dialog, table, &selected_row, &selected_col);
			if (status != PRO_TK_NO_ERROR) return status;
			selected_row++;
			for (int j=0; j<n_cols; j++)
			{
				for (int i=0; i<n_rows; i++)
				{
					int row_index = (selected_row + i) % n_rows;
					int col_index = (selected_col + j) % n_cols;
					if (selected_row + i >= n_rows) col_index = (col_index + 1) % n_cols;

					cell_list.push_back(std::make_pair(std::string(row_names[row_index]), std::string(col_names[col_index])));
				}
			}

			ProStringarrayFree(row_names, n_rows);
			ProStringarrayFree(col_names, n_cols);
		}

		status =  ProUITableSelectednamesSet(dialog, table, 0, NULL);

		return PRO_TK_NO_ERROR;
	}

	//ProError Table::GetTargetCells(char *dialog, char *table, wchar_t *w_target, std::vector<std::pair<string, string>> &cell_list)
	//{
	//	ProError	status;
	//	int			n_names;
	//	char		**names;
	//	char		row_name[32];
	//	char		col_name[32];
	//	int			n_rows;
	//	char		**row_names;
	//	int			selected_row = -1;
	//	int			selected_col = -1;

	//	cell_list = std::vector<std::pair<string, string>>();
	//	if (wcsicmp(w_target, L"Selection") == 0)
	//	{
	//		status = ProUITableSelectednamesGet(dialog, table, &n_names, &names);
	//		if (status != PRO_TK_NO_ERROR || n_names < 1)
	//		{
	//			Mirim::MsgBox::Show(L"PMP", L"Select Cells...");
	//			return status;
	//		}
	//		for(int i=0; i<n_names / 2; i++)
	//		{
	//			cell_list.push_back(std::make_pair(std::string((names)[2*i]), std::string((names)[2*i + 1])));
	//		}
	//	}
	//	else if (wcsicmp(w_target, L"CurrentColumn") == 0)
	//	{
	//		status = ProUITableSelectednamesGet(dialog, table, &n_names, &names);
	//		if (status != PRO_TK_NO_ERROR || n_names != 2)
	//		{
	//			Mirim::MsgBox::Show(L"PMP", L"Select One Cell...");
	//			return status;
	//		}

	//		strcpy_s(row_name, names[0]);
	//		strcpy_s(col_name, names[1]);

	//		status = ProUITableRownamesGet(dialog, table, &n_rows, &row_names);
	//		if (status != PRO_TK_NO_ERROR || n_rows < 1) return PRO_TK_E_FOUND;
	//		for (int i=0; i<n_rows; i++)
	//		{
	//			cell_list.push_back(std::make_pair(std::string(row_names[i % n_rows]), std::string(col_name)));
	//		}
	//	}
	//	else
	//	{
	//		int n_rows, n_cols;
	//		char **row_names, **col_names;

	//		status = ProUITableRownamesGet(dialog, table, &n_rows, &row_names);
	//		if (status != PRO_TK_NO_ERROR || n_rows < 1) return PRO_TK_E_FOUND;

	//		status = ProUITableColumnnamesGet(dialog, table, &n_cols, &col_names);
	//		if (status != PRO_TK_NO_ERROR || n_cols < 1) return PRO_TK_E_FOUND;

	//		status = this->IsOneCellSelected(dialog, table, &selected_row, &selected_col);
	//		if (status != PRO_TK_NO_ERROR) return status;
	//		selected_row++;
	//		for (int j=0; j<n_cols; j++)
	//		{
	//			for (int i=0; i<n_rows; i++)
	//			{
	//				int row_index = (selected_row + i) % n_rows;
	//				int col_index = (selected_col + j) % n_cols;
	//				if (selected_row + i >= n_rows) col_index = (col_index + 1) % n_cols;

	//				cell_list.push_back(std::make_pair(std::string(row_names[row_index]), std::string(col_names[col_index])));
	//			}
	//		}

	//		ProStringarrayFree(row_names, n_rows);
	//		ProStringarrayFree(col_names, n_cols);
	//	}

	//	status =  ProUITableSelectednamesSet(dialog, table, 0, NULL);

	//	return PRO_TK_NO_ERROR;
	//}

	ProError Table::FindRepalce(bool replace, wchar_t *w_what, wchar_t *w_with, wchar_t *w_target)
	{
		ProError	status;
		char		row_name[32];
		char		col_name[32];
		wchar_t		*w_label1;
		wchar_t		*w_upper;
		wchar_t		*w_upper1;
		bool		in_selection = false;

		status = Mirim::Util::TrimString(w_what, w_what);
		if (wcslen(w_what) < 1) return status;

		w_upper = wcsupr(w_what); 

		std::vector<std::pair<std::string, std::string>> target_cells;
		status = this->GetTargetCells(dialog, table, w_target, target_cells, &in_selection);
		if (status != PRO_TK_NO_ERROR)
		{
			Mirim::MsgBox::Show(L"PMP", L"Select target...");
			return status;
		}


		bool found = false;
		std::vector<std::pair<string, string>> cells_found;
		for(auto it = target_cells.begin(); it != target_cells.end(); ++it)
		{
			if (stricmp(it->second.c_str(), "Name") == 0 ||
				stricmp(it->second.c_str(), "Type") == 0 ||
				stricmp(it->second.c_str(), "Qty") == 0) continue;

			strcpy(row_name, it->first.c_str());
			strcpy(col_name, it->second.c_str());
			status = ProUITableCellLabelGet(this->dialog, this->table, row_name, col_name, &w_label1);
			if (status != PRO_TK_NO_ERROR) continue;

			w_upper1 = wcsupr(w_label1);
			if (wcsstr(w_upper1, w_upper) != NULL)
			{
				cells_found.push_back(make_pair(string(row_name), string(col_name)));
				if (wcsicmp(w_target, L"NextCell") == 0 && !in_selection)
				{
					ProWstringFree(w_label1);
					found = true;
					break;
				}
			}

			ProWstringFree(w_label1);
		}

		int n_cells = static_cast<int>(cells_found.size());
		if (n_cells < 1)
		{
			Mirim::MsgBox::Show(L"PMP", L"No items are found...");
			return PRO_TK_NO_ERROR;
		}

		std::vector<Cell> cell_list;
		char		**selected_names = new char *[n_cells * 2];
		wchar_t		*w_value;
		ProPath		w_output;
		ProUIColor	ui_color;
		int			n_replaced = 0;
		for (int i=0; i<n_cells * 2; i = i+2)
		{
			selected_names[i] = new char[32];
			selected_names[i+1] = new char[32];
			strcpy(selected_names[i], cells_found[i/2].first.c_str());
			strcpy(selected_names[i + 1], cells_found[i/2].second.c_str());
			if (replace)
			{
				if (wcslen(w_with) < 1) continue;
				status = ProUITableCellBackgroundColorGet(this->dialog, this->table, selected_names[i], selected_names[i+1], &ui_color);
				if (ui_color == PRO_UI_COLOR_3D_DARK_SHADOW) continue;

				status = ProUITableCellLabelGet(this->dialog, this->table, selected_names[i], selected_names[i+1], &w_value);
				if (status != PRO_TK_NO_ERROR) continue;

				cell_list.push_back(Cell(selected_names[i], selected_names[i+1], w_value, ui_color));
				status = Mirim::Util::ReplaceString(w_value, w_what, w_with, w_output);
				status = ProUITableCellLabelSet(this->dialog, this->table, selected_names[i], selected_names[i+1], w_output);
				status = ProUITableCellBackgroundColorSet(this->dialog, this->table, selected_names[i], selected_names[i+1], PRO_UI_COLOR_WHITE);
				n_replaced++;

				ProWstringFree(w_value);
			}
		}

		if (cell_list.size() > 0) this->undo_list.push_back(cell_list);
		status = ProUITableSelectednamesSet(this->dialog, this->table, n_cells * 2, selected_names);

		for (int i=0; i < (n_cells)*2; i++)
			delete[] selected_names[i];
		delete[] selected_names;

		if (n_cells == 1) return PRO_TK_NO_ERROR;

		ProPath w_log;
		if (replace) wsprintf(w_log, L"%d items replaced: [%s] ===> [%s]", n_replaced, w_what, w_with);
		else         wsprintf(w_log, L"%d items found", n_cells);

		Mirim::MsgBox::Show(L"PMP", w_log);

		return PRO_TK_NO_ERROR;
	}

	ProError Table::Find(wchar_t *w_what, wchar_t *w_type)
	{
		return this->FindRepalce(false, w_what, NULL, w_type);
	}

	ProError Table::Replace(wchar_t *w_what, wchar_t *w_with, wchar_t *w_type)
	{
		return this->FindRepalce(true, w_what, w_with, w_type);
	}

#pragma endregion

}