#include "Dialog.h"
#include "AsmRename.h"
#include "BatchPlot.h"
#include "FindParam.h"
#include "Drw.h"

#pragma region CONSTANT DEFINITIONS

#define DIALOG "BatchTools"

// Menu
#define PB_OPTION			"PB_OPTION"
#define PB_EXIT			    "PB_EXIT"
#define PB_FIND			    "PB_FIND"
#define PB_LOAD_DRAWING		"PB_LOAD_DRAWING"
#define PB_SESSION_BOM		"PB_SESSION_BOM"
#define PB_SESSION_PARTLIST	"PB_SESSION_PARTLIST"
#define PB_FIND_PARAMETER   "PB_FIND_PARAMETER"
#define PB_HELP_CONTENTS	"PB_HELP_CONTENTS"
#define PB_SHOW_LOG		    "PB_SHOW_LOG"
#define PB_SET_LICENSE		"PB_SET_LICENSE"
#define PB_ABOUT			"PB_ABOUT"
#define PB_ADMIN			"PB_ADMIN"

// Define Parameter
#define TABLE1			    "TABLE1"
#define TABLE2			    "TABLE2"
#define IP_SOURCE           "IP_SOURCE"
#define OM_SOURCE           "OM_SOURCE"
#define CB_SOURCE           "CB_SOURCE"
#define LB_SOURCE           "LB_SOURCE"
#define PB_READ_EXCEL		"PB_READ_EXCEL"
#define PB_SAVE_EXCEL		"PB_SAVE_EXCEL"
#define PB_SAVE_XML		    "PB_SAVE_XML"
#define PB_ADD_ROW1         "PB_ADD_ROW1"
#define PB_REMOVE_ROW1      "PB_REMOVE_ROW1"
#define PB_MOVE_UP1         "PB_MOVE_UP1"
#define PB_MOVE_DOWN1       "PB_MOVE_DOWN1"
#define IP_TOTAL_LENGTH		"IP_TOTAL_LENGTH"
#define IP_PARTNR_START		"IP_PARTNR_START"

#define PB_ADD_ROW2         "PB_ADD_ROW2"
#define PB_REMOVE_ROW2      "PB_REMOVE_ROW2"
#define PB_MOVE_UP2         "PB_MOVE_UP2"
#define PB_MOVE_DOWN2       "PB_MOVE_DOWN2"

// Edit parameter
#define TABLE3			    "TABLE3"

#define PB_COPY1            "PB_COPY1"
#define PB_PASTE1           "PB_PASTE1"
#define PB_CLEAR1           "PB_CLEAR1"
#define PB_UNDO1			"PB_UNDO1"
#define PB_REDO1			"PB_REDO1"
#define IP_FIND1			"IP_FIND1"
#define PB_FIND1            "PB_FIND1"
#define OM_FIND_TARGET1     "OM_FIND_TARGET1"
#define IP_REPLACE1			"IP_REPLACE1"
#define PB_REPLACE1			"PB_REPLACE1"
#define OM_REPLACE_TARGET1	"OM_REPLACE_TARGET1"

#define PB_STANDARDIZE		"PB_STANDARDIZE"
#define CB_ASM1			    "CB_ASM1"
#define CB_PRT1			    "CB_PRT1"
#define PB_READ_PARAM	    "PB_READ_PARAM"
#define PB_APPLY_PARAM		"PB_APPLY_PARAM"

// Assembly Rename
#define TABLE4			    "TABLE4"
#define IP_PREFIX			"IP_PREFIX"
#define PB_ADD_PREFIX		"PB_ADD_PREFIX"
#define PB_REMOVE_PREFIX	"PB_REMOVE_PREFIX"
#define IP_SURFIX			"IP_SURFIX"
#define PB_ADD_SURFIX		"PB_ADD_SURFIX"
#define PB_REMOVE_SURFIX	"PB_REMOVE_SURFIX"
#define PB_READ_NAMES		"PB_READ_NAMES"
#define PB_APPLY_RENAME		"PB_APPLY_RENAME"
#define PB_SYNC_NAMES		"PB_SYNC_NAMES"

#define PB_COPY2            "PB_COPY2"
#define PB_PASTE2           "PB_PASTE2"
#define PB_CLEAR2           "PB_CLEAR2"
#define PB_UNDO2			"PB_UNDO2"
#define PB_REDO2			"PB_REDO2"
#define IP_FIND2			"IP_FIND2"
#define PB_FIND2            "PB_FIND2"
#define OM_FIND_TARGET2     "OM_FIND_TARGET2"
#define IP_REPLACE2			"IP_REPLACE2"
#define PB_REPLACE2			"PB_REPLACE2"
#define OM_REPLACE_TARGET2	"OM_REPLACE_TARGET2"

// Batch Convert
#define RG_SOURCE			"RG_SOURCE"
#define PB_REFRESH			"PB_REFRESH"
#define CB_SUBFOLDER		"CB_SUBFOLDER"
#define OM_FORMAT			"OM_FORMAT"
#define OM_FOLDER			"OM_FOLDER"
#define PB_SELECT_FOLDER	"PB_SELECT_FOLDER"
#define TABLE5			    "TABLE5"
#define CB_ASM2				"CB_ASM2"
#define CB_DRW2				"CB_DRW2"
#define PB_ADD			    "PB_ADD"
#define PB_ADD_ALL			"PB_ADD_ALL"
#define PB_REMOVE			"PB_REMOVE"
#define PB_REMOVE_ALL		"PB_REMOVE_ALL"
#define CB_DXF			    "CB_DXF"
#define CB_DWG			    "CB_DWG"
#define CB_HPGL				"CB_HPGL"
#define CB_PDF			    "CB_PDF"
#define CB_PRINT			"CB_PRINT"
#define TABLE6			    "TABLE6"
#define OM_PRINTER			"OM_PRINTER"
#define OM_PAPER			"OM_PAPER"
#define PB_EXECUTE			"PB_EXECUTE"
#define PB_MOVE_UP3         "PB_MOVE_UP3"
#define PB_MOVE_DOWN3       "PB_MOVE_DOWN3"

// Family Table
#define PB_MODEL_BACKUP		"PB_MODEL_BACKUP"
#define PB_SAVE_NAMES		"PB_SAVE_NAMES"
#define PB_SHOW_FAMTAB		"PB_SHOW_FAMTAB"
#define PB_SHOW_ALL			"PB_SHOW_ALL"
#define PB_RESTORE_NAMES	"PB_RESTORE_NAMES"
#define PB_SAVE_ALL			"PB_SAVE_ALL"

#define DIALOG_FIND         "FindAndReplace"


#pragma endregion

namespace Gui
{
	ProError Dialog::Show()
	{
		ProError	status;
		int			error;

		TLog(L"Gui::Dialog::Show()");
		Mirim::Option *option = Mirim::Option::GetUniqueInstance();
		status = ProUIDialogCreate(DIALOG, DIALOG);
		status = Dialog::SetTitle(DIALOG, option->ProductName);
		status = Dialog::ShowOption(DIALOG, option);

		status = ProUIDialogCloseActionSet(DIALOG, (ProUIAction)Dialog::CLOSE_ACTION, option);

#pragma region Menu Action
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_FIND_PARAMETER,    (ProUIAction) Dialog::PB_FIND_PARAMETER_ACTION, NULL);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_LOAD_DRAWING,      (ProUIAction) Dialog::PB_LOAD_DRAWING_ACTION, NULL);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_SESSION_BOM,       (ProUIAction) Dialog::PB_SESSION_BOM_ACTION, NULL);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_SESSION_PARTLIST,  (ProUIAction) Dialog::PB_SESSION_PARTLIST_ACTION, NULL);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_SHOW_LOG,          (ProUIAction) Dialog::PB_SHOW_LOG_ACTION, NULL);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_SET_LICENSE,       (ProUIAction) Dialog::PB_SET_LICENSE_ACTION, NULL);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_ADMIN,             (ProUIAction) Dialog::PB_ADMIN_ACTION, NULL);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_ABOUT,             (ProUIAction) Dialog::PB_ABOUT_ACTION, NULL);
#pragma endregion

#pragma region Define Parameter Action
		Table table1(DIALOG, TABLE1);
		table1.ip_source = IP_SOURCE;
		table1.om_source = OM_SOURCE;
		table1.cb_source = CB_SOURCE;

		Table table2(DIALOG, TABLE2);
		table2.ip_source = IP_SOURCE;

		status = Dialog::ShowStdParams();

		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_READ_EXCEL,    (ProUIAction) Dialog::PB_READ_EXCEL_ACTION, &table1);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_SAVE_EXCEL,    (ProUIAction) Dialog::PB_SAVE_EXCEL_ACTION, &table1);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_SAVE_XML,      (ProUIAction) Dialog::PB_SAVE_XML_ACTION, &table1);

		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_ADD_ROW1,      (ProUIAction)Dialog::PB_ADD_ROW_ACTION, &table1);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_REMOVE_ROW1,   (ProUIAction)Dialog::PB_REMOVE_ROW_ACTION, &table1);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_MOVE_UP1,      (ProUIAction)Dialog::PB_MOVE_UP_ACTION, &table1);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_MOVE_DOWN1,    (ProUIAction)Dialog::PB_MOVE_DOWN_ACTION, &table1);
		status = ProUITableSelectActionSet(DIALOG, TABLE1, (ProUIAction)Dialog::TABLE_SELECT_ACTION, &table1);   

		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_ADD_ROW2,      (ProUIAction)Dialog::PB_ADD_ROW_ACTION, &table2);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_REMOVE_ROW2,   (ProUIAction)Dialog::PB_REMOVE_ROW_ACTION, &table2);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_MOVE_UP2,      (ProUIAction)Dialog::PB_MOVE_UP_ACTION, &table2);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_MOVE_DOWN2,    (ProUIAction)Dialog::PB_MOVE_DOWN_ACTION, &table2);
		status = ProUITableSelectActionSet(DIALOG, TABLE2, (ProUIAction)Dialog::TABLE_SELECT_ACTION, &table2);   
#pragma endregion

#pragma region Edit Parameter Action
		Table table3(DIALOG, TABLE3);
		table3.ip_source = "IP_SOURCE";
		table3.om_source = "OM_SOURCE";
		table3.lb_source = "LB_SOURCE";
		table3.ip_find = "IP_FIND1";
		table3.om_find_target = OM_FIND_TARGET1;
		table3.ip_replace = "IP_REPLACE1";
		table3.om_replace_target = OM_REPLACE_TARGET1;

		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_READ_PARAM,    (ProUIAction)Dialog::PB_READ_PARAM_ACTION, &table3);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_COPY1,         (ProUIAction)Dialog::PB_COPY_ACTION, &table3);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_PASTE1,        (ProUIAction)Dialog::PB_PASTE_ACTION, &table3);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_CLEAR1,        (ProUIAction)Dialog::PB_CLEAR_ACTION, &table3);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_FIND1,         (ProUIAction)Dialog::PB_FIND_ACTION, &table3);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_REPLACE1,      (ProUIAction)Dialog::PB_REPLACE_ACTION, &table3);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_UNDO1,         (ProUIAction)Dialog::PB_UNDO_ACTION, &table3);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_REDO1,         (ProUIAction)Dialog::PB_REDO_ACTION, &table3);

		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_STANDARDIZE, (ProUIAction)Dialog::PB_STANDARDIZE_ACTION, &table3);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_APPLY_PARAM, (ProUIAction)Dialog::PB_APPLY_PARAM_ACTION, &table3);
		status = ProUITableSelectActionSet(DIALOG, TABLE3, (ProUIAction)Dialog::TABLE_SELECT_ACTION, &table3);  

		status = ProUICheckbuttonActivateActionSet(DIALOG, CB_ASM1, (ProUIAction)Dialog::CB_FILTER_ACTION, &table3);
		status = ProUICheckbuttonActivateActionSet(DIALOG, CB_PRT1, (ProUIAction)Dialog::CB_FILTER_ACTION, &table3);
#pragma endregion

#pragma region Assembly Rename Parameter Action
		Table table4(DIALOG, TABLE4);
		table4.ip_source = "IP_SOURCE";
		table4.om_source = "OM_SOURCE";
		table4.lb_source = "LB_SOURCE";
		table4.cb_source = "CB_SOURCE";
		table4.ip_find = "IP_FIND2";
		table4.om_find_target = OM_FIND_TARGET2;
		table4.ip_replace = "IP_REPLACE2";
		table4.om_replace_target = OM_REPLACE_TARGET2;

		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_READ_NAMES,    (ProUIAction)Dialog::PB_READ_NAMES_ACTION, &table4);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_COPY2,         (ProUIAction)Dialog::PB_COPY_ACTION, &table4);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_PASTE2,        (ProUIAction)Dialog::PB_PASTE_ACTION, &table4);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_CLEAR2,        (ProUIAction)Dialog::PB_CLEAR_ACTION, &table4);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_FIND2,         (ProUIAction)Dialog::PB_FIND_ACTION, &table4);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_REPLACE2,      (ProUIAction)Dialog::PB_REPLACE_ACTION, &table4);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_UNDO2,         (ProUIAction)Dialog::PB_UNDO_ACTION, &table4);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_REDO2,         (ProUIAction)Dialog::PB_REDO_ACTION, &table4);

		status = ProUITableSelectActionSet(DIALOG, TABLE4, (ProUIAction)Dialog::TABLE_SELECT_ACTION, &table4);  

		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_READ_NAMES,    (ProUIAction)Dialog::PB_READ_NAMES_ACTION, &table4);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_SYNC_NAMES,    (ProUIAction)Dialog::PB_SYNC_NAMES_ACTION, &table4);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_APPLY_RENAME,  (ProUIAction)Dialog::PB_APPLY_RENAME_ACTION, &table4);

		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_ADD_PREFIX,    (ProUIAction)Dialog::PB_ADD_PREFIX_ACTION, &table4);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_REMOVE_PREFIX, (ProUIAction)Dialog::PB_REMOVE_PREFIX_ACTION, &table4);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_ADD_SURFIX,    (ProUIAction)Dialog::PB_ADD_SURFIX_ACTION, &table4);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_REMOVE_SURFIX, (ProUIAction)Dialog::PB_REMOVE_SURFIX_ACTION, &table4);

#pragma endregion

#pragma region Batch Convert Action

		Table table5(DIALOG, TABLE5);
		table5.dialog = DIALOG;
		table5.table = TABLE5;
		table5.lb_source = "LB_SOURCE";

		status = ProUILayoutDisable(DIALOG, "Layout36");
		status = ProUIOptionmenuDisable(DIALOG,  OM_FOLDER);
		status = ProUIPushbuttonDisable(DIALOG, PB_SELECT_FOLDER);
		status = ProUICheckbuttonDisable(DIALOG, CB_SUBFOLDER);

		status = ProUIRadiogroupSelectActionSet(DIALOG, RG_SOURCE, (ProUIAction)Dialog::RG_SOURCE_SELECT_ACTION, &table5);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_SELECT_FOLDER, (ProUIAction)Dialog::PB_SELECT_FOLDER_ACTION, &table5);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_REFRESH,       (ProUIAction)Dialog::RG_SOURCE_SELECT_ACTION, &table5);
		status = ProUIOptionmenuSelectActionSet(DIALOG, OM_FOLDER,(ProUIAction)Dialog::RG_SOURCE_SELECT_ACTION, &table5); 

		Table table6(DIALOG, TABLE6);
		table6.dialog = DIALOG;
        table6.lb_source = "LB_SOURCE";
        status = ProUIPushbuttonActivateActionSet(DIALOG, PB_ADD,           (ProUIAction)Dialog::PB_ADD_ACTION,  &table6);
        status = ProUIPushbuttonActivateActionSet(DIALOG, PB_ADD_ALL,       (ProUIAction)Dialog::PB_ADD_ALL_ACTION, &table6);
        status = ProUIPushbuttonActivateActionSet(DIALOG, PB_REMOVE,        (ProUIAction)Dialog::PB_REMOVE_ACTION, &table6);
        status = ProUIPushbuttonActivateActionSet(DIALOG, PB_REMOVE_ALL,    (ProUIAction)Dialog::PB_REMOVE_ALL_ACTION, &table6);
        status = ProUIPushbuttonActivateActionSet(DIALOG, PB_EXECUTE,       (ProUIAction)Dialog::PB_EXECUTE_ACTION, option);

        status = ProUIPushbuttonActivateActionSet(DIALOG, PB_MOVE_UP3,   (ProUIAction)Dialog::PB_MOVE_UP_ACTION, &table6);
        status = ProUIPushbuttonActivateActionSet(DIALOG, PB_MOVE_DOWN3, (ProUIAction)Dialog::PB_MOVE_DOWN_ACTION, &table6);

		//status = ProUITableSelectActionSet(DIALOG, TABLE5, (ProUIAction)Dialog::TABLE_SELECT_ACTION1, &table5);  

		status = ProUICheckbuttonActivateActionSet(DIALOG, CB_ASM2, (ProUIAction)Dialog::CB_FILTER_ACTION2, &table5);
		status = ProUICheckbuttonActivateActionSet(DIALOG, CB_DRW2, (ProUIAction)Dialog::CB_FILTER_ACTION2, &table5);
#pragma endregion

		status = ProUIDialogActivate(DIALOG, &error);
		status = ProUIDialogDestroy(DIALOG);

		return PRO_TK_NO_ERROR;
	}


#pragma region Common Actions
	ProError Dialog::SetTitle(char *dialog, wchar_t *w_prodcut_name)
	{
		ProError	status;
		ProPath		w_title;

		wcscpy(w_title, Mirim::Option::ProductName);

		//Mirim::License license;
		//if (!license.IsValid(false))
		//{
		//	wcscat(w_title, L" Demo Version");
		//}

		status = ProUIDialogTitleSet(DIALOG, w_title);

		return status;
	}

	ProError Dialog::ShowOption(char *dialog, Mirim::Option *option)
	{
		ProError status;

        Mirim::UI::ShowFolders(dialog, OM_FOLDER);

		status = Mirim::UI::SetOptionMenuSelectedLabel(dialog, OM_FORMAT, option->PrintFormat);
		status = Mirim::UI::SetOptionMenuSelectedLabel(dialog, OM_FOLDER, option->SourceFolder);
				
		status = Mirim::UI::SetCheckboxStatus(dialog, CB_ASM1, option->ShowAsm1);
		status = Mirim::UI::SetCheckboxStatus(dialog, CB_PRT1, option->ShowPrt1);

		status = Mirim::UI::SetCheckboxStatus(dialog, CB_ASM2, option->ShowAsm2);
		status = Mirim::UI::SetCheckboxStatus(dialog, CB_DRW2, option->ShowDrw2);
		status = Mirim::UI::SetCheckboxStatus(dialog, CB_DXF, option->ExportDxf);
		status = Mirim::UI::SetCheckboxStatus(dialog, CB_DWG, option->ExportDwg);
		status = Mirim::UI::SetCheckboxStatus(dialog, CB_HPGL, option->ExportHpgl);
		status = Mirim::UI::SetCheckboxStatus(dialog, CB_PDF, option->ExportPdf);
		status = Mirim::UI::SetCheckboxStatus(dialog, CB_PRINT, option->Print);
		status = Mirim::UI::SetInputpanelValue(dialog, IP_TOTAL_LENGTH, option->TotalLength);
		status = Mirim::UI::SetInputpanelValue(dialog, IP_PARTNR_START, option->PartNrStart);

		Mirim::UI::ShowPrinters(dialog, OM_PRINTER);
		Mirim::UI::ShowPapers(dialog, OM_PAPER);

		return PRO_TK_NO_ERROR;
	}

	ProError Dialog::SaveOption(char *dialog, Mirim::Option *option)
	{
		ProError status;

        Mirim::UI::SaveFolders(dialog, OM_FOLDER);

		status = Mirim::UI::GetOptionMenuSelectedLabel(dialog, OM_FORMAT, option->PrintFormat);
		status = Mirim::UI::GetOptionMenuSelectedLabel(dialog, OM_FOLDER, option->SourceFolder);
		status = Mirim::UI::GetOptionMenuSelectedLabel(dialog, OM_PRINTER, option->PrinterName);
		status = Mirim::UI::GetOptionMenuSelectedLabel(dialog, OM_PAPER, option->PaperSize);

		status = Mirim::UI::GetCheckboxStatus(dialog, CB_ASM1, &option->ShowAsm2);
		status = Mirim::UI::GetCheckboxStatus(dialog, CB_PRT1, &option->ShowPrt1);

		status = Mirim::UI::GetCheckboxStatus(dialog, CB_ASM2, &option->ShowAsm2);
		status = Mirim::UI::GetCheckboxStatus(dialog, CB_DRW2, &option->ShowDrw2);
		status = Mirim::UI::GetCheckboxStatus(dialog, CB_DXF, &option->ExportDxf);
		status = Mirim::UI::GetCheckboxStatus(dialog, CB_DWG, &option->ExportDwg);
		status = Mirim::UI::GetCheckboxStatus(dialog, CB_HPGL, &option->ExportHpgl);
		status = Mirim::UI::GetCheckboxStatus(dialog, CB_PDF, &option->ExportPdf);
		status = Mirim::UI::GetCheckboxStatus(dialog, CB_PRINT, &option->Print);
		status = Mirim::UI::GetInputpanelValue(dialog, IP_TOTAL_LENGTH, &option->TotalLength);
		status = Mirim::UI::GetInputpanelValue(dialog, IP_PARTNR_START, &option->PartNrStart);

		Mirim::Option::Save(*option);
		return PRO_TK_NO_ERROR;
	}



	ProError Dialog::CLOSE_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		ProError	status;
		Mirim::Option *option = (Mirim::Option *) app_data;

		status = Table::SaveColumnWidths(dialog, TABLE3, option);
		Dialog::SaveOption(dialog, option);

		status = ProUIDialogExit(dialog, PRO_TK_NO_ERROR);

		return PRO_TK_NO_ERROR;
	}

#pragma endregion

#pragma region Menu Action
    ProError Dialog::PB_FIND_PARAMETER_ACTION(char *dialog, char *component, ProAppData app_data)
    {
        ProError    status;

        status = FindParam::ShowDialog();

		return PRO_TK_NO_ERROR;
    }

    ProError Dialog::PB_LOAD_DRAWING_ACTION(char *dialog, char *component, ProAppData app_data)
    {
        ProError    status;
        ProPath     w_message;

        std::vector<Gui::Model> mdl_list;
        status = Session::CollectModels(mdl_list);

        std::vector<ProDrawing> drw_list;
        status = Session::LoadDrawings(mdl_list, drw_list);

        if (drw_list.size() == 0)
        {
            wsprintf(w_message, L"No drawings found...");
        }
        else
        {
            wsprintf(w_message, L"Total %d drawings found...", drw_list.size());
        }
        
        Mirim::MsgBox::Show(L"PMP", w_message);

        return PRO_TK_NO_ERROR;
    }


    ProError Dialog::PB_SESSION_BOM_ACTION(char *dialog, char *component, ProAppData app_data)
    {
        ProError    status;



        return PRO_TK_NO_ERROR;   
    }


    ProError Dialog::PB_SESSION_PARTLIST_ACTION(char *dialog, char *component, ProAppData app_data)
    {
        ProError    status;



        return PRO_TK_NO_ERROR;   
    }


    ProError Dialog::PB_SHOW_LOG_ACTION(char *dialog, char *component, ProAppData app_data)
    {
        ProError    status;



        return PRO_TK_NO_ERROR;   
    }


    ProError Dialog::PB_SET_LICENSE_ACTION(char *dialog, char *component, ProAppData app_data)
    {
        ProError    status;



        return PRO_TK_NO_ERROR;   
    }


    ProError Dialog::PB_ADMIN_ACTION(char *dialog, char *component, ProAppData app_data)
    {
        ProError    status;



        return PRO_TK_NO_ERROR;   
    }


    ProError Dialog::PB_ABOUT_ACTION(char *dialog, char *component, ProAppData app_data)
    {
        ProError    status;



        return PRO_TK_NO_ERROR;   
    }



#pragma endregion

#pragma region Define Parameter Action

	ProError Dialog::ShowStdParams()
	{
		ProError	status;
		std::vector<StdParam> list;
		std::vector<std::pair<bool, wstring>> list1;

		status = StdParam::ReadXml(&list, &list1);

		status = StdParam::ShowStdParams(DIALOG, TABLE1, list);
		status = StdParam::ShowParamsToDelete(DIALOG, TABLE2, list1);

		return PRO_TK_NO_ERROR;
	}

	ProError Dialog::PB_READ_EXCEL_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		ProError	status;
		ProPath		w_path;
		ProPath		w_file_path;
		Table		*table = (Table *) app_data;

		status = ProToolkitApplTextPathGet(w_path);
		status = ProFileOpen(L"Select Excel File", L"*.xls,*.xlsx", NULL, NULL, w_path, NULL, w_file_path);
		if (status != PRO_TK_NO_ERROR) return status;

		std::vector<StdParam> list;
		std::vector<std::pair<bool, wstring>> list1;

		status = StdParam::ReadExcel(w_file_path, list, list1);
		status = StdParam::ShowStdParams(DIALOG, TABLE1, list);
		status = StdParam::ShowParamsToDelete(DIALOG, TABLE2, list1);

		return PRO_TK_NO_ERROR;
	}

	ProError Dialog::PB_SAVE_EXCEL_ACTION(char *dialog, char *component, ProAppData app_data)
	{ 
		ProError	status;
		ProPath		w_path;
		ProPath		w_file_path;

		std::vector<StdParam> list;
		std::vector<std::pair<bool, std::wstring>> list1;

		status = StdParam::ReadStdParams(DIALOG, TABLE1, list);
		status = StdParam::ReadParamsToDelete(DIALOG, TABLE2, list1);

		status = ProToolkitApplTextPathGet(w_path);
		status = ProFileSave(L"Select Excel File", L"*.xls,*.xlsx", NULL, NULL, w_path, NULL, w_file_path);
		if (status != PRO_TK_NO_ERROR) return status;

		status = StdParam::SaveXml(&list, &list1);
		status = StdParam::SaveExcel(w_file_path, list, list1);
		if (status == PRO_TK_NO_ERROR)
		{
			Mirim::MsgBox::Show(L"SUCCESS", L"Saved...");
		}
		else
		{
			Mirim::MsgBox::Show(L"SUCCESS", L"Failed to save Excel file...");
		}

		return PRO_TK_NO_ERROR;
	}

	ProError Dialog::PB_SAVE_XML_ACTION(char *dialog, char *component, ProAppData app_data)
	{ 
		ProError	status;

		std::vector<StdParam> list;
		std::vector<std::pair<bool, std::wstring>> list1;

		status = StdParam::ReadStdParams(DIALOG, TABLE1, list);
		status = StdParam::ReadParamsToDelete(DIALOG, TABLE2, list1);

		Mirim::Option *option = Mirim::Option::GetUniqueInstance();
		status = Mirim::UI::GetInputpanelValue(DIALOG, IP_TOTAL_LENGTH, &option->TotalLength);
		status = Mirim::UI::GetInputpanelValue(DIALOG, IP_PARTNR_START, &option->PartNrStart);
		Mirim::Option::Save(*option);

		status = StdParam::SaveXml(&list, &list1);
		if (status == PRO_TK_NO_ERROR)
		{
			Mirim::MsgBox::Show(L"SUCCESS", L"Saved...");
		}
		else
		{
			Mirim::MsgBox::Show(L"SUCCESS", L"Failed to save XML file...");
		}

		return PRO_TK_NO_ERROR;
	}

	ProError Dialog::PB_ADD_ROW_ACTION(char *dialog, char *component, ProAppData app_data)
	{ 
		Table *table = (Table *) app_data;
		return Table::AddRow(dialog, table->table);
	}

	ProError Dialog::PB_REMOVE_ROW_ACTION(char *dialog, char *component, ProAppData app_data)
	{ 
		Table *table = (Table *) app_data;
		return Table::RemoveRow(dialog, table->table);
	}

	ProError Dialog::PB_MOVE_UP_ACTION(char *dialog, char *component, ProAppData app_data)
	{ 
		Table *table = (Table *) app_data;
		return Table::MoveUpRow(dialog, table->table);
	}
	ProError Dialog::PB_MOVE_DOWN_ACTION(char *dialog, char *component, ProAppData app_data)
	{ 
		Table *table = (Table *) app_data;
		return Table::MoveDownRow(dialog, table->table);
	}

	ProError Dialog::TABLE_SELECT_ACTION(char *dialog, char *component, ProAppData app_data)
	{ 
		return StdParam::EditSelectedCell(app_data);
	}


#pragma endregion

#pragma region Edit Parameter Action



	ProError Dialog::PB_COPY_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		Table *table = (Table *) app_data;
		return table->CopyToClipboard();
	}

	ProError Dialog::PB_PASTE_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		Table *table = (Table *) app_data;
		return table->PasteFromClipboard();
	}

	ProError Dialog::PB_CLEAR_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		Table *table = (Table *) app_data;
		return table->ClearSelectedCell();
	}

	ProError Dialog::PB_FIND_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		ProError	status;
		ProPath		w_what;
		wchar_t		*w_name;
		Table *table = (Table *) app_data;

		status = Mirim::UI::GetInputpanelValue(table->dialog, table->ip_find, w_what);
		if (status != PRO_TK_NO_ERROR) return status;

		status = ProUIOptionmenuValueGet(table->dialog, table->om_find_target, &w_name);
		if (status != PRO_TK_NO_ERROR) return status;

		status = table->Find(w_what, w_name);
        ProWstringFree(w_name);

        return status;
	}

	ProError Dialog::PB_REPLACE_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		ProError	status;
		ProPath		w_what;
		ProPath		w_with;
		wchar_t     *w_target;
		Table *table = (Table *) app_data;

		status = Mirim::UI::GetInputpanelValue(table->dialog, table->ip_find, w_what);
		if (status != PRO_TK_NO_ERROR) return status;	

		status = Mirim::UI::GetInputpanelValue(table->dialog, table->ip_replace, w_with);
		if (status != PRO_TK_NO_ERROR) return status;

		status = ProUIOptionmenuValueGet(table->dialog, table->om_replace_target, &w_target);
		if (status != PRO_TK_NO_ERROR) return status;

		status = table->Replace(w_what, w_with, w_target);
        ProWstringFree(w_target);

        return status;
	}

	ProError Dialog::PB_UNDO_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		Table *table = (Table *) app_data;
		return table->Undo();
	}

	ProError Dialog::PB_REDO_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		Table *table = (Table *) app_data;
		return table->Redo();
	}

	ProError Dialog::PB_READ_PARAM_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		ProError	status;
		ProBoolean  checked;

		Table		*table = (Table *) app_data;
		table->Initialize();

		status = Session::CollectModels(table->mdl_list);
		if (status != PRO_TK_NO_ERROR) return status;

		status = StdParam::AddStdParamColumns(table);
		
		status = ProUICheckbuttonGetState(DIALOG, CB_ASM1, &checked);
		bool show_asm = checked == PRO_B_TRUE;

		status = ProUICheckbuttonGetState(DIALOG, CB_PRT1, &checked);
		bool show_prt = checked == PRO_B_TRUE;

		status = StdParam::ShowParamValues(table, table->mdl_list, show_asm, show_prt);
		Mirim::Option *option = Mirim::Option::GetUniqueInstance();
		status = Table::RestoreColumnWidths(table->dialog, table->table, option);

		return PRO_TK_NO_ERROR;
	}

	ProError Dialog::CB_FILTER_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		ProError	status;
		ProBoolean  checked;

		Table		*table = (Table *) app_data;
		
		status = ProUICheckbuttonGetState(DIALOG, CB_ASM1, &checked);
		bool show_asm = checked == PRO_B_TRUE;

		status = ProUICheckbuttonGetState(DIALOG, CB_PRT1, &checked);
		bool show_prt = checked == PRO_B_TRUE;

		status = StdParam::ShowParamValues(table, table->mdl_list, show_asm, show_prt);
		Mirim::Option *option = Mirim::Option::GetUniqueInstance();
		status = Table::RestoreColumnWidths(table->dialog, table->table, option);

		return PRO_TK_NO_ERROR;
	}

	ProError Dialog::PB_STANDARDIZE_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		ProError	status;
		Table *table = (Table *) app_data;
		Mirim::Option *option = Mirim::Option::GetUniqueInstance();

		status = StdParam::Standardize(table, option);
		Mirim::MsgBox::Show(L"PMP", L"Finished...");

		return status;
	}	

	ProError Dialog::PB_APPLY_PARAM_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		ProError	status;
		Table *table = (Table *) app_data;

		status = StdParam::ApplyParams(table->dialog, table->table);
		Mirim::MsgBox::Show(L"PMP", L"Finished...");

		return status;
	}



#pragma endregion

#pragma region Assembly Rename Parameter Action

	ProError Dialog::PB_READ_NAMES_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		ProError	status;
		Table		*table = (Table *) app_data;
		table->Initialize();

		std::vector<Model> list;
		status = Session::CollectModels(list);
		if (status != PRO_TK_NO_ERROR) return status;

		status = AsmRename::ShowNames(table, list);

		return PRO_TK_NO_ERROR;
	}

	ProError Dialog::PB_SYNC_NAMES_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		Table *table = (Table *) app_data;
		return AsmRename::SyncNames(table);
	}
	ProError Dialog::PB_APPLY_RENAME_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		Table *table = (Table *) app_data;
		return AsmRename::ApplyNames(table);
	}

	ProError Dialog::PB_ADD_PREFIX_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		Table *table = (Table *) app_data;

		return AsmRename::ApplyNames(table);
	}

	ProError Dialog::PB_REMOVE_PREFIX_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		Table *table = (Table *) app_data;
		return AsmRename::ApplyNames(table);
	}

	ProError Dialog::PB_ADD_SURFIX_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		Table *table = (Table *) app_data;
		return AsmRename::ApplyNames(table);
	}

	ProError Dialog::PB_REMOVE_SURFIX_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		Table *table = (Table *) app_data;
		return AsmRename::ApplyNames(table);
	}


#pragma endregion

#pragma region Batch Convert Action

	ProError Dialog::ShowPlotItems(Table *table)
	{
		ProError	status;
		ProPath     w_source;
		ProBoolean  include_asm, include_drw, recursive;
        wchar_t     *w_path;

		status = Mirim::UI::GetRadioGroupSelectedName(table->dialog, RG_SOURCE, w_source);
		if (wcslen(w_source) < 1) return PRO_TK_E_NOT_FOUND;

        Table::PrepareRows(DIALOG, TABLE5, 0);

		if (wcsicmp(w_source, L"Disk") == 0)
		{
			status = ProUILayoutEnable(DIALOG, "Layout36");
			status = ProUIOptionmenuEnable(DIALOG,  OM_FOLDER);
			status = ProUIPushbuttonEnable(DIALOG, PB_SELECT_FOLDER);
			status = ProUICheckbuttonEnable(DIALOG, CB_SUBFOLDER);
		}
		else 
		{
			status = ProUILayoutDisable(DIALOG, "Layout36");
			status = ProUIOptionmenuDisable(DIALOG,  OM_FOLDER);
			status = ProUIPushbuttonDisable(DIALOG, PB_SELECT_FOLDER);
			status = ProUICheckbuttonDisable(DIALOG, CB_SUBFOLDER);
		}

		status = ProUICheckbuttonGetState(DIALOG, CB_ASM2, &include_asm);
		if (status != PRO_TK_NO_ERROR) return status;
		
		status = ProUICheckbuttonGetState(DIALOG, CB_DRW2, &include_drw);
		if (status != PRO_TK_NO_ERROR) return status;

		table->mdl_list = std::vector<Model>();
		if (wcsicmp(w_source, L"Session") == 0)
		{
			status = BatchPlot::GetSessionItems(table->mdl_list);
		}
		else if (wcsicmp(w_source, L"Workspace") == 0)
		{
			status = BatchPlot::GetWorkspaceItems(table->mdl_list);
		}
		else
		{
			status = ProUIOptionmenuValueGet(table->dialog, OM_FOLDER, &w_path);
			status = ProUICheckbuttonGetState(DIALOG, CB_SUBFOLDER, &recursive);
			if (status != PRO_TK_NO_ERROR) return status;

			status = BatchPlot::GetDiskItems(w_path, recursive == PRO_B_TRUE, table->mdl_list);

            ProWstringFree(w_path);
		}

		if (status != PRO_TK_NO_ERROR) return status;

		status = BatchPlot::ShowTable(table, table->mdl_list);

		return PRO_TK_NO_ERROR;
	}

	ProError Dialog::RG_SOURCE_SELECT_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		return Dialog::ShowPlotItems((Table *) app_data);
	}

	ProError Dialog::PB_SELECT_FOLDER_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		ProError	status;
		ProPath		w_path;
        wchar_t     *w_value;
		ProBoolean  checked;
		bool		include_asm, include_drw, recursive;

		Table *table = (Table *) app_data;
		status = ProUIOptionmenuValueGet(DIALOG, OM_FOLDER, &w_value);
		if (_waccess(w_value, 00) == -1)
		{
			wcscpy(w_value, L"");
		}

		status = ProDirectoryChoose(L"Select Source Folder", NULL, NULL, w_value, w_path);
		if (status != PRO_TK_NO_ERROR) return PRO_TK_USER_ABORT;

		Mirim::Option *option = Mirim::Option::GetUniqueInstance();
		wcscpy(option->SourceFolder, w_path);

        status = Mirim::UI::SetOptionMenuItemCount(dialog, OM_FOLDER, w_path, 12);

		status = ProUICheckbuttonGetState(DIALOG, CB_ASM2, &checked);
		if (status != PRO_TK_NO_ERROR) return status;
		include_asm = checked == PRO_B_TRUE;
		
		status = ProUICheckbuttonGetState(DIALOG, CB_DRW2, &checked);
		if (status != PRO_TK_NO_ERROR) return status;
		include_drw = checked == PRO_B_TRUE;

		status = ProUICheckbuttonGetState(DIALOG, CB_SUBFOLDER, &checked);
		if (status != PRO_TK_NO_ERROR) return status;
		recursive = checked == PRO_B_TRUE;
		
        status = Mirim::UI::GetOptionMenuSelectedLabel(dialog, OM_FOLDER, w_path);

		std::vector<Model> mdl_list;
		status = BatchPlot::GetDiskItems(w_path, recursive == PRO_B_TRUE, mdl_list);

		status = BatchPlot::ShowTable(table, mdl_list, include_asm, include_drw);

		return PRO_TK_NO_ERROR;
	}


	ProError Dialog::CB_FILTER_ACTION2(char *dialog, char *component, ProAppData app_data)
	{
		ProError	status;
		ProBoolean  checked;
		bool		include_asm, include_drw;
		Table *table = (Table *) app_data;

		status = ProUICheckbuttonGetState(DIALOG, CB_ASM2, &checked);
		if (status != PRO_TK_NO_ERROR) return status;
		include_asm = checked == PRO_B_TRUE;

		status = ProUICheckbuttonGetState(DIALOG, CB_DRW2, &checked);
		if (status != PRO_TK_NO_ERROR) return status;
		include_drw = checked == PRO_B_TRUE;

		status = BatchPlot::ShowTable(table, table->mdl_list, include_asm, include_drw);

		return PRO_TK_NO_ERROR;
	}


	ProError Dialog::PB_ADD_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		return BatchPlot::AddItems(DIALOG, TABLE5, TABLE6, true);
	}

	ProError Dialog::PB_ADD_ALL_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		return BatchPlot::AddItems(DIALOG, TABLE5, TABLE6, false);
	}

	ProError Dialog::PB_REMOVE_ACTION(char *dialog, char *component, ProAppData app_data)
	{
        Table *table = (Table *) app_data;
        BatchPlot::RemoveItems(table);
		return PRO_TK_NO_ERROR;
	}

	ProError Dialog::PB_REMOVE_ALL_ACTION(char *dialog, char *component, ProAppData app_data)
	{
        Table::PrepareRows(dialog, TABLE6, 0);
		return PRO_TK_NO_ERROR;
	}

	ProError Dialog::PB_EXECUTE_ACTION(char *dialog, char *component, ProAppData app_data)
	{
		ProError	status;
        ProPath     w_target_folder;
        int         n_rows;
        char        **row_names;

        Mirim::Option *option = (Mirim::Option *)app_data;
        Dialog::SaveOption(DIALOG, option);
        if (wcsicmp(option->PrintFormat, L"HP-GL") == 0 && option->Print)
        {
            if (wcsstr(option->PrinterName, L" ") != NULL)
            {
                Mirim::MsgBox::Show(L"pmp", L"   ERROR: When using HP-GL as print format, the printer name must not contain \"White Space\"   ");
                return PRO_TK_E_FOUND;
            }
        }

        *w_target_folder = NULL;
        if (option->ExportDwg || option->ExportDxf || option->ExportHpgl || option->ExportPdf)
        {
            status = ProDirectoryCurrentGet(w_target_folder);
            status = ProDirectoryChoose(L"Select Target Folder", NULL, NULL, w_target_folder, w_target_folder);
            if (status != PRO_TK_NO_ERROR)
            {
                Mirim::MsgBox::Show(L"pmp", L"User aborted...");
                return PRO_TK_USER_ABORT;
            }
        }

        status = ProUITableRownamesGet(DIALOG, TABLE6, &n_rows, &row_names);
        if (n_rows < 1) 
        {
            Mirim::MsgBox::Show(L"ERROR", L"Select items to convert...");
            return PRO_TK_E_NOT_FOUND;
        }

        std::vector<Model> mdl_list;
        for (int i=0; i<n_rows; i++)
        {
            Model m(DIALOG, TABLE6, row_names[i]);
            mdl_list.push_back(m);
        }

        ProStringarrayFree(row_names, n_rows);

        Gui::Drw::Export(mdl_list, w_target_folder);

		return PRO_TK_NO_ERROR;
	}

#pragma endregion

}