#include "BatchPlot.h"
#include "UI.h"	

namespace Gui
{
	BatchPlot::BatchPlot(void)
	{
	}


	BatchPlot::~BatchPlot(void)
	{
	}


	ProError BatchPlot::ShowTable(Table *table, std::vector<Gui::Model> &mdl_list)
	{
		ProError	status;
		char		**row_names;
		wchar_t		w_row_label[32];
		int			n_rows = static_cast<int>(mdl_list.size());

		status = Table::PrepareRows(table->dialog, table->table, n_rows);
		status = ProUITableRownamesGet(table->dialog, table->table, &n_rows, &row_names);

		for (int i=0; i<n_rows; i++)
		{
            status = BatchPlot::ShowRow(table->dialog, table->table, row_names[i], mdl_list[i]);
		}

		return PRO_TK_NO_ERROR;
	}

	ProError BatchPlot::ShowTable(Table *table, std::vector<Model> &mdl_list, bool include_asm, bool include_drw)
	{
		if (!include_asm && !include_drw)
		{
			include_asm = include_drw = true;
		}

		std::vector<Model> list;
		for (auto it = mdl_list.begin(); it != mdl_list.end(); it++)
		{
			if ((include_asm && it->type == PRO_MDL_ASSEMBLY) || (include_drw && it->type == PRO_MDL_DRAWING))
			{
				list.push_back(*it);
			}
		}

		return BatchPlot::ShowTable(table, list);
	}

	ProError BatchPlot::GetFileFilter(bool include_asm, bool include_drw, wchar_t *w_filter)
	{
		*w_filter = 0;
		if (include_asm && include_drw)
		{
			wcscpy(w_filter, L"*.asm,*.drw");
		}
		else if (!include_asm && include_drw)
		{
			wcscpy(w_filter, L"*.drw");
		}
		else if (include_asm && !include_drw)
		{
			wcscpy(w_filter, L"*.asm");
		}
		else
		{
			return PRO_TK_GENERAL_ERROR;
		}

		return PRO_TK_NO_ERROR;
	}


	ProError BatchPlot::ReadDirectory(wchar_t *w_directory, wchar_t *w_filter, std::vector<Model> &list)
	{
		ProError	status;
		ProPath		*w_file_names;
		ProPath		*w_directories;
		int			n_count;

		status = ProArrayAlloc(0, sizeof(ProPath), 1,(ProArray*)&w_file_names);
		status = ProArrayAlloc(0, sizeof(ProPath), 1,(ProArray*)&w_directories);
		status = ProFilesList(w_directory, w_filter, PRO_FILE_LIST_LATEST_SORTED,  &w_file_names, &w_directories);
		status = ProArraySizeGet(w_file_names, &n_count);
		for(int i=0; i<n_count; i++)
		{
			Model m(w_file_names[i]);
			list.push_back(m);
		}

		status = ProArraySizeGet(w_directories, &n_count);
		for(int i=0; i<n_count; i++)
		{
			status = BatchPlot::ReadDirectory(w_directories[i], w_filter, list);
		}

		ProArrayFree((ProArray *) &w_file_names);
		ProArrayFree((ProArray *) &w_directories);

		return PRO_TK_NO_ERROR;
	}


	ProError BatchPlot::GetDiskItems(wchar_t *w_directory, bool recursive, std::vector<Gui::Model> &list)
	{
		ProError	status;
		ProLine		w_filter;
		ProPath		*w_file_names;
		ProPath		*w_directories;
		int			n_count;

		if (_waccess(w_directory, 00) == -1)
		{
			Mirim::MsgBox::Show(L"PMP", L"Select valid folder");
			return PRO_TK_NO_ERROR;
		}

		status = BatchPlot::GetFileFilter(true, true, w_filter);
		if (status != PRO_TK_NO_ERROR)
		{
			Mirim::MsgBox::Show(L"PMP", L"Select file type");
			return status;
		}

		status = ProArrayAlloc(0, sizeof(ProPath), 1,(ProArray*)&w_file_names);
		status = ProArrayAlloc(0, sizeof(ProPath), 1,(ProArray*)&w_directories);
		status = ProFilesList(w_directory, w_filter, PRO_FILE_LIST_LATEST_SORTED,  &w_file_names, &w_directories);
		status = ProArraySizeGet(w_file_names, &n_count);
		for(int i=0; i<n_count; i++)
		{
			Model m(w_file_names[i]);
			list.push_back(m);
		}

		if (!recursive) return PRO_TK_NO_ERROR;

		status = ProArraySizeGet(w_directories, &n_count);
		for(int i=0; i<n_count; i++)
		{
			status = BatchPlot::ReadDirectory(w_directories[i], w_filter, list);
		}

		ProArrayFree((ProArray *) &w_file_names);
		ProArrayFree((ProArray *) &w_directories);

		return PRO_TK_NO_ERROR;
	}

	bool compare_model(const Model &m1, const Model &m2)
	{
		if ( wcsicmp(m1.mdl_data.name, m2.mdl_data.name) == 0)
			return wcsicmp(m1.mdl_data.type, m2.mdl_data.type) < 0;
		else 
			return wcsicmp(m1.mdl_data.name, m2.mdl_data.name) < 0;
	}

	ProError BatchPlot::GetSessionItems(std::vector<Gui::Model> &list)
	{
		ProError	status;
		ProMdl		*p_mdls;
		int			n_mdls;

		status = ProSessionMdlList(PRO_MDL_ASSEMBLY, &p_mdls, &n_mdls);
		if (status == PRO_TK_NO_ERROR)
		{
			for (int i=0; i<n_mdls; i++)
			{
				Model m(p_mdls[i]);
				list.push_back(m);
			}
		}

		status = ProSessionMdlList(PRO_MDL_DRAWING, &p_mdls, &n_mdls);
		if (status == PRO_TK_NO_ERROR)
		{
			for (int i=0; i<n_mdls; i++)
			{
				Model m(p_mdls[i]);
				list.push_back(m);
			}
		}

		std::sort(list.begin(), list.end(), compare_model);

		return PRO_TK_NO_ERROR;
	}


	ProError BatchPlot::GetWorkspaceItems(std::vector<Gui::Model> &list)
	{
		ProError		status;
		ProFileListOpt	option = PRO_FILE_LIST_LATEST_SORTED;
		wchar_t			*w_server_alias;
		wchar_t			*w_workspace_name;
		ProPath			*w_file_names;
		ProPath			*w_folder_names;
		ProPath			w_path;
		ProPath			w_filter;

		status = BatchPlot::GetFileFilter(true, true, w_filter);

		status = ProServerActiveGet(&w_server_alias);
		if (status != PRO_TK_NO_ERROR)
		{
			Mirim::MsgBox::Show(L"Server Alias", L"Could not find Active PDMLink Server");
			return PRO_TK_E_NOT_FOUND;
		}

		status = ProServerWorkspaceGet(w_server_alias, &w_workspace_name);
		if (status != PRO_TK_NO_ERROR)
		{
			Mirim::MsgBox::Show(L"Workspace", L"Could not find Active Workspace.");
			return PRO_TK_E_NOT_FOUND;
		}

		wsprintf(w_path, L"wtws://%s/%s", w_server_alias, w_workspace_name);

		status = ProArrayAlloc(0, sizeof(ProPath), 1,(ProArray*)&w_file_names);
		status = ProArrayAlloc(0, sizeof(ProPath), 1,(ProArray*)&w_folder_names);
		status = ProFilesList(w_path, w_filter, option, &w_file_names, &w_folder_names); 
		int n_count = -1;
		status = ProArraySizeGet(w_file_names, &n_count);

		for(int i=0; i<n_count; i++)
		{
			Model m(w_file_names[i]);
			list.push_back(m);
		}

		status = ProWstringFree(w_server_alias);
		status = ProWstringFree(w_workspace_name);

		status = ProArrayFree((ProArray *) &w_file_names);
		status = ProArrayFree((ProArray *) &w_folder_names);

		return PRO_TK_NO_ERROR;
	}

	ProError BatchPlot::AddItems(char *Table5, Table *table, bool selected)
	{
		ProError	status;
		int			n_names;
		char		**names;

		if (selected)
		{
			status = ProUITableSelectednamesGet(table->dialog, Table5, &n_names, &names);
			if (status != PRO_TK_NO_ERROR || n_names < 1) return PRO_TK_E_NOT_FOUND;

			for (int i=0; i<n_names; i+= 2)
			{
				Model m(table->dialog, Table5, names[i]);
				auto it = find(table->mdl_list.begin(), table->mdl_list.end(), m);
				if (it == table->mdl_list.end())
				{
					table->mdl_list.push_back(m);
				}
			}
		}
		else
		{
			status = ProUITableRownamesGet(table->dialog, Table5, &n_names, &names);
			if (status != PRO_TK_NO_ERROR || n_names < 1) return PRO_TK_E_NOT_FOUND;

			for (int i=0; i<n_names; i++)
			{
				Model m(table->dialog, Table5, names[i]);
				auto it = find(table->mdl_list.begin(), table->mdl_list.end(), m);
				if (it == table->mdl_list.end())
				{
					table->mdl_list.push_back(m);
				}
			}
		}

		return PRO_TK_NO_ERROR;
	}


    ProError BatchPlot::ShowRow(char *dialog, char *table, char *row_name, Model &m)
    {
        ProError    status;
        wchar_t     w_row_label[32];
        char        label_name[32];
        int         index;

        status = ProUITableRowIndexGet(dialog, table,row_name, &index);
        wsprintf(w_row_label, L"%d", index + 1);
        status = ProUITableRowLabelSet(dialog, table, row_name, w_row_label);

        sprintf(label_name, "%s_LB", row_name);
        status = ProUITableCellComponentCopy(dialog, table, row_name, "Icon", dialog, "LB_SOURCE", label_name);

        status = ProUILabelEnable(dialog, label_name);
        status = ProUILabelShow(dialog, label_name);

        if (m.type == PRO_MDL_ASSEMBLY)
            status = ProUILabelBitmapSet(dialog, label_name, "asm_icon.gif");
        else if (m.type == PRO_MDL_PART)
            status = ProUILabelBitmapSet(dialog, label_name, "prt_icon.gif");
        else
            status = ProUILabelBitmapSet(dialog, label_name, "drw_icon.gif");

        status = ProUITableCellLabelSet(dialog, table, row_name, "Name",m.mdl_data.name);
        status = ProUITableCellLabelSet(dialog, table, row_name, "Type",m.mdl_data.type);
        status = ProUITableCellLabelSet(dialog, table, row_name, "Device", m.mdl_data.device);
        status = ProUITableCellLabelSet(dialog, table, row_name, "Path", m.mdl_data.path);

        return PRO_TK_NO_ERROR;
    }

    ProError BatchPlot::AddItems(char *dialog, char *Table5, char *Table6, bool selected)
	{
		ProError	status;
		int			n_names;
		char		**names;
        int         n_rows;
        char        **row_names;
        char        last_row[32] = { NULL };

        // List selected items
        std::vector<Model> mdl_list;
        status = ProUITableRownamesGet(dialog, Table6, &n_rows, &row_names);
        for (int i=0; i<n_rows; i++)
        {
            Model m(dialog, Table6, row_names[i]);
            mdl_list.push_back(m);
        }

        if (n_rows > 0) strcpy(last_row, row_names[n_rows - 1]);

        // Find source items
        std::vector<Model> list;
		if (selected)
		{
			status = ProUITableSelectednamesGet(dialog, Table5, &n_names, &names);
			if (status != PRO_TK_NO_ERROR || n_names < 1) return PRO_TK_E_NOT_FOUND;

			for (int i=0; i<n_names; i+= 2)
			{
				Model m(dialog, Table5, names[i]);
				auto it = find(mdl_list.begin(), mdl_list.end(), m);
                if (it == mdl_list.end())
                {
                    list.push_back(m);
                }
			}

            ProStringarrayFree(names, n_names);
		}
		else
		{
			status = ProUITableRownamesGet(dialog, Table5, &n_names, &names);
			if (status != PRO_TK_NO_ERROR || n_names < 1) return PRO_TK_E_NOT_FOUND;

			for (int i=0; i<n_names; i++)
			{
				Model m(dialog, Table5, names[i]);
				auto it = find(mdl_list.begin(), mdl_list.end(), m);
				if (it == mdl_list.end())
				{
					list.push_back(m);
				}
			}

            ProStringarrayFree(names, n_names);
		}

        if (list.size() < 1) return PRO_TK_E_NOT_FOUND;

        n_names = list.size();
        names = new char *[n_names];
        for (int i=0; i<n_names; i++)
        {
            names[i] = new char[32];
            Table::row_number++;
            sprintf(names[i], "%d", Table::row_number);
        }

        status = ProUITableRowsInsert(dialog, Table6, last_row, n_names, names);
        for (int i=0; i<n_names; i++)
		{
		    status = BatchPlot::ShowRow(dialog, Table6, names[i], list[i]);
		}

		return PRO_TK_NO_ERROR;
	}

	ProError BatchPlot::RemoveItems(Table *table)
	{
        ProError    status;
        int         n_names;
        char        **names;
       
        status = ProUITableSelectednamesGet(table->dialog, table->table, &n_names, &names);
        if (status != PRO_TK_NO_ERROR || n_names < 1) return status;

        int n_rows = n_names / 2;
        char **row_names = new char *[n_names / 2];       
        for (int i=0; i<n_rows; i++)
        {
            row_names[i] = new char[32];
            strcpy(row_names[i], names[i * 2]);
        }

        status = ProUITableRowsDelete(table->dialog, table->table, n_rows, row_names);

		return PRO_TK_NO_ERROR;
	}

}