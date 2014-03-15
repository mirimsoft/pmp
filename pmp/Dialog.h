#pragma once
#include "ProTk.h"
#include "UI.h"
#include "StdParam.h"
#include "Session.h"

namespace Gui
{

	class Dialog
	{
	public:
		static ProError Dialog::Show();


	private:
		static ProError Dialog::SetTitle(char *dialog, wchar_t *w_product_name);
		static ProError Dialog::ShowOption(char *dialog, Mirim::Option *option);
		static ProError Dialog::SaveOption(char *dialog, Mirim::Option *option);

		static ProError Dialog::PB_FIND_PARAMETER_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_LOAD_DRAWING_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_SESSION_BOM_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_SESSION_PARTLIST_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_SHOW_LOG_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_SET_LICENSE_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_ADMIN_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_ABOUT_ACTION(char *dialog, char *component, ProAppData app_data);
        static ProError Dialog::PB_GENERATE_ACTION(char *dialog, char *component, ProAppData app_data);



		static ProError Dialog::ShowStdParams();

		static ProError Dialog::CLOSE_ACTION(char *dialog, char *component, ProAppData app_data);

        static ProError Dialog::PB_READ_EXCEL_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_SAVE_EXCEL_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_SAVE_XML_ACTION(char *dialog, char *component, ProAppData app_data);

		static ProError Dialog::PB_ADD_ROW_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_REMOVE_ROW_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_MOVE_UP_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_MOVE_DOWN_ACTION(char *dialog, char *component, ProAppData app_data);

		static ProError Dialog::TABLE_SELECT_ACTION(char *dialog, char *component, ProAppData app_data);

		static ProError Dialog::PB_COPY_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_PASTE_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_CLEAR_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_FIND_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_REPLACE_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_UNDO_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_REDO_ACTION(char *dialog, char *component, ProAppData app_data);

		static ProError Dialog::PB_READ_PARAM_ACTION(char *dialog, char *component, ProAppData app_data); 
		static ProError Dialog::CB_FILTER_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_STANDARDIZE_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_APPLY_PARAM_ACTION(char *dialog, char *component, ProAppData app_data);

		static ProError Dialog::PB_READ_NAMES_ACTION(char *dialog, char *component, ProAppData app_data); 
		static ProError Dialog::PB_SYNC_NAMES_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_APPLY_RENAME_ACTION(char *dialog, char *component, ProAppData app_data);

		static ProError Dialog::PB_ADD_PREFIX_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_REMOVE_PREFIX_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_ADD_SURFIX_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_REMOVE_SURFIX_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::CB_FILTER_ACTION2(char *dialog, char *component, ProAppData app_data);

		static ProError Dialog::RG_SOURCE_SELECT_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_SELECT_FOLDER_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_ADD_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_ADD_ALL_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_REMOVE_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_REMOVE_ALL_ACTION(char *dialog, char *component, ProAppData app_data);
		static ProError Dialog::PB_EXECUTE_ACTION(char *dialog, char *component, ProAppData app_data);

		static ProError Dialog::TABLE_SELECT_ACTION1(char *dialog, char *component, ProAppData app_data);

		static ProError Dialog::ShowPlotItems(Table *table);

	};

}