#pragma once
#include "ProTk.h"
#include "Model.h"
#include "Table.h"

namespace Gui
{
	class BatchPlot
	{
	public:
		BatchPlot(void);
		~BatchPlot(void);

	public:
		static ProError BatchPlot::GetDiskItems(wchar_t *w_directory, bool recursive, std::vector<Gui::Model> &list);
		static ProError BatchPlot::GetSessionItems(std::vector<Gui::Model> &list);
		static ProError BatchPlot::GetWorkspaceItems(std::vector<Gui::Model> &list);

		static ProError BatchPlot::ShowTable(Table *table, std::vector<Gui::Model> &list);
		static ProError BatchPlot::ShowTable(Table *table, std::vector<Gui::Model> &list, bool include_asm, bool include_drw);
		static ProError BatchPlot::GetFileFilter(bool include_asm, bool include_drw, wchar_t *w_filter);
		static ProError BatchPlot::ReadDirectory(wchar_t *w_directory, wchar_t *w_filter,  std::vector<Model> &list);

        static ProError BatchPlot::ShowRow(char *dialog, char *table, char *row_name, Model &m);
		static ProError BatchPlot::AddItems(char *Table5, Table *table, bool selected);
		static ProError BatchPlot::AddItems(char *dialog, char *Table5, char *Table6, bool selected);
		static ProError BatchPlot::RemoveItems(Table *table);
	};

}