#pragma once

#include "ProTk.h"
#include <deque>
#include <stack>
#include "Model.h"

namespace Gui
{
	class Cell
	{
	public:
		string		row;
		string		col;
		wstring		w_value;
		ProUIColor	color;

		Cell::Cell(char *row, char *col, wchar_t *w_value, ProUIColor color)
			:color(color)
		{
			this->row = string(row);
			this->col = string(col);
			this->w_value = wstring(w_value);
		}

		Cell::Cell(char *dialog, char *table, char *row, char *col)
		{
			ProError	status;
			wchar_t		*w_label;

			status = ProUITableCellLabelGet(dialog, table, row, col, &w_label);
			w_value = wstring(w_label);
			ProWstringFree(w_label);

			this->row = string(row);
			this->col = string(col);
			status = ProUITableCellBackgroundColorGet(dialog, table, row, col, &this->color);
		}
	};

	class Table
	{
	public:
		static int row_number;
		deque <std::vector<Cell>> undo_list;
		stack <std::vector<Cell>> redo_list;

		std::vector<Model> mdl_list;

	public:
		char *dialog;
		char *table;
		char *row;
		char *col;
		
		char *lb_source;
		char *ip_source;
		char *om_source;
		char *cb_source;

		char *ip_find;
		char *ip_replace;
		char *om_find_target;
		char *om_replace_target;

	public:
		Table(char *dialog, char *table);
		~Table(void);

	public:
		ProError Table::Initialize();

		ProError Table::BeginEditWithCheckbutton();
		ProError Table::BeginEditWithInputpanel();
		ProError Table::BeginEditWithOptionmenu(int n_count, char **names, wchar_t **w_names);

		static ProError Table::EndEditWithCheckbutton(char *dialog, char *table, ProAppData app_data);
		static ProError Table::EndEditWithInputpanel(char *dialog, char *table, ProAppData app_data);
		static ProError Table::EndEditWithOptionmenu(char *dialog, char *table, ProAppData app_data);

		ProError Table::CopyToClipboard();
		ProError Table::PasteFromClipboard();
		static ProError Table::SelectCell(char *dialog, char *table, char *row, char *col);
		ProError Table::ClearSelectedCell();
		ProError Table::Find(wchar_t *w_what, wchar_t *w_target);
		ProError Table::Replace(wchar_t *w_what, wchar_t *w_with,  wchar_t *w_target);
		ProError Table::FindRepalce(bool replace, wchar_t *w_what, wchar_t *w_with,  wchar_t *w_target);

		ProError Table::Remember();
		ProError Table::Undo();
		ProError Table::Redo();



	public:
		static ProError Table::SaveColumnWidths(char *dialog, char *table, Mirim::Option *option);
		static ProError Table::RestoreColumnWidths(char *dialog, char *table, Mirim::Option *option);
		static ProError Table::GetLastRowName(char *dialog, char *table, char *row_name);
		static ProError Table::GetFirstRowName(char *dialog, char *table, char *row_name);
		static ProError Table::PrepareRows(char *dialog, char *table, int n_rows);

		static ProError Table::SwapRows(char *dialog, char *table, int row1, int row2);
		static ProError Table::MoveRow(char *dialog, char *table, int direction);
		static ProError Table::MoveUpRow(char *dialog, char *table);
		static ProError Table::MoveDownRow(char *dialog, char *table);
		static ProError Table::AddRow(char *dialog, char *table);
		static ProError Table::RemoveRow(char *dialog, char *table);

		static bool Table::SingleCellSelected(char *dialog, char *table);

		ProError Table::IsOneCellSelected(char *dialog, char *table, int *row_index, int *col_index);
		ProError Table::GetTargetCells(char *dialog, char *table, wchar_t *w_target, std::vector<std::pair<string, string>> &cell_list, bool *in_selection);






	};

}