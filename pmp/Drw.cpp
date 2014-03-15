#include "Drw.h"

namespace Gui
{
    Drw::Drw(ProDrawing drawing, const wchar_t *w_target_folder)
        :_drawing(drawing)
    {
        ProError	status;
        ProName		w_option_name;

        this->_option = Mirim::Option::GetUniqueInstance();

        this->pdf_generated = false;
        this->hpgl_generated = false;

        wcscpy(w_option_name, L"axis_display");
        status = ProConfigoptGet(w_option_name, this->_w_axis_display);
        status = ProConfigoptSet(w_option_name, L"no");

        wcscpy(w_option_name,  L"datum_display");
        status = ProConfigoptGet(w_option_name, this->_w_datum_display);
        status = ProConfigoptSet(w_option_name, L"no");

        status = Mirim::Option::GetRootDirectory(this->_w_temp_folder);
        wcscat(this->_w_temp_folder, L"\\work");
        wcscpy(this->_w_target_folder, w_target_folder);

        status = ProMdlNameGet(this->_drawing, this->w_mdl_name);
        status = ProObjectwindowCreate(this->w_mdl_name, PRO_DRAWING, &this->_window_id);
        status = ProMdlDisplay(this->_drawing);

        return;
    }

    Drw::~Drw(void)
    {
        ProError	status;
        ProName		w_option_name;

        status = ProWindowDelete(this->_window_id);

        wcscpy(w_option_name, L"axis_display");
        status = ProConfigoptSet(w_option_name, this->_w_axis_display);

        wcscpy(w_option_name, L"datum_display");
        status = ProConfigoptSet(w_option_name, this->_w_datum_display);

        return;
    }


    ProError Drw::CopyTo(const wchar_t *w_from, const wchar_t *w_to)
    {
        CopyFile(w_from, w_to, false);
        if (_waccess(w_to, 00) != -1)
        {
            TLog::Print(L"File Copied: %s ===> %s", w_from,  w_to);
            return PRO_TK_NO_ERROR;
        }
        else
        {
            TLog::Print(L"ERROR: Failed to copy file: %s ===> %s", w_from,  w_to);
            return PRO_TK_GENERAL_ERROR;
        }
    }

    ProError Drw::GetPaperSize(const wchar_t *w_paper_name, ProPlotPaperSize *size)
    {
        ProPath		w_name;

        wcscpy(w_name, w_paper_name);
        wcsupr(w_name);

        if (wcsstr(w_name, L"A4") != NULL)
            *size =  A4_SIZE_PLOT;
        else if (wcsstr(w_name, L"A3") != NULL)
            *size =   A3_SIZE_PLOT;
        else if (wcsstr(w_name, L"A2") != NULL)
            *size =   A2_SIZE_PLOT;
        else if (wcsstr(w_name, L"A1") != NULL)
            *size =    A1_SIZE_PLOT;
        else if (wcsstr(w_name, L"A0") != NULL)
            *size =   A0_SIZE_PLOT;
        else 
            PRO_TK_E_NOT_FOUND;

        return PRO_TK_NO_ERROR;
    }

    ProError Drw::SetFileNames(const wchar_t *w_extension)
    {
        _wmakepath(this->_w_temp_path, NULL, this->_w_temp_folder, this->w_mdl_name, w_extension);
        _wmakepath(this->_w_target_path, NULL, this->_w_target_folder, this->w_mdl_name, w_extension);

        return PRO_TK_NO_ERROR;
    }

    ProError Drw::SetFileNames(const wchar_t *w_path, const wchar_t *w_extension)
    {
        ProPath	w_drive, w_folder, w_name, w_ext;
        _wsplitpath(w_path, w_drive, w_folder, w_name, w_ext);

        _wmakepath(this->_w_temp_path, NULL, this->_w_temp_folder, w_name, w_extension);
        _wmakepath(this->_w_target_path, NULL, this->_w_target_folder, w_name, w_extension);

        return PRO_TK_NO_ERROR;
    }

    ProError Drw::GetFileList(std::vector<std::wstring> &list)
    {
        ProError	status;
        ProPath		w_path;

        status = Mirim::Option::GetRootDirectory(w_path);
        wcscat(w_path, L"\\work");

        Mirim::Util::GetFilesList(w_path, list);

        return status;
    }

    ProError Drw::GetNewFileList(std::vector<std::wstring> &list)
    {
        ProError	status;
        ProPath		w_path;

        status = Mirim::Option::GetRootDirectory(w_path);
        wcscat(w_path, L"\\work");

        std::vector<std::wstring> list1;
        Mirim::Util::GetFilesList(w_path, list1);

        this->file_list.clear();
        for(std::vector<std::wstring>::iterator it = list1.begin(); it != list1.end(); it++)
        {
            std::vector<std::wstring>::iterator found = std::find(list.begin(),list.end(), *it);
            if (found == list.end())
            {
                this->file_list.push_back(*it);
            }
        }

        return PRO_TK_NO_ERROR;
    }

    ProError Drw::ExportDXF()
    {
        ProError		status;
        Pro2dExportdata export_data;

        status = Pro2dExportdataAlloc(&export_data);

        int n_sheets;
        status = ProDrawingSheetsCount(this->_drawing, &n_sheets);
        if (n_sheets == 1)
        {
            status = Pro2dExportdataSheetoptionSet(export_data, PRO2DEXPORT_CURRENT_TO_MODEL_SPACE);
            status = Pro2dExportdataModelspacesheetSet(export_data, 1);
        }
        else
        {
            status = Pro2dExportdataSheetoptionSet(export_data, PRO2DEXPORT_ALL);
        }

        this->SetFileNames(L"dxf");
        status = Pro2dExport(PRO_DXF_FILE, this->_w_temp_path, this->_drawing, export_data);
        if (status == PRO_TK_NO_ERROR)
        {
            TLog::Print(L"DXF File: %s", this->_w_temp_path);
        }
        else
        {
            TLog::Print(L"ERROR: DXF File: %s", this->_w_temp_path);
            return status;
        }

        this->CopyTo(this->_w_temp_path, this->_w_target_path);

        return status;
    }

    ProError Drw::ExportDWG()
    {
        ProError		status;
        Pro2dExportdata export_data;

        status = Pro2dExportdataAlloc(&export_data);

        int n_sheets;
        status = ProDrawingSheetsCount(this->_drawing, &n_sheets);
        if (n_sheets == 1)
        {
            status = Pro2dExportdataSheetoptionSet(export_data, PRO2DEXPORT_CURRENT_TO_MODEL_SPACE);
            status = Pro2dExportdataModelspacesheetSet(export_data, 1);
        }
        else
        {
            status = Pro2dExportdataSheetoptionSet(export_data, PRO2DEXPORT_ALL);
        }

        this->SetFileNames(L"dwg");
        status = Pro2dExport(PRO_DWG_FILE, this->_w_temp_path, this->_drawing, export_data);
        if (status == PRO_TK_NO_ERROR)
        {
            TLog::Print(L"DXF File: %s", this->_w_temp_path);
        }
        else
        {
            TLog::Print(L"ERROR: DXF File: %s", this->_w_temp_path);
            return status;
        }

        this->CopyTo(this->_w_temp_path, this->_w_target_path);

        return status;
    }

    ProError Drw::CreatePDF()
    {
        ProError		status;
        ProPDFOptions	pdf_options;

        

        status = ProPDFoptionsAlloc(&pdf_options);
        status = ProPDFoptionsBoolpropertySet(pdf_options, PRO_PDFOPT_LAUNCH_VIEWER, PRO_B_FALSE);
        status = ProPDFoptionsBoolpropertySet(pdf_options, PRO_PDFOPT_PENTABLE, PRO_B_TRUE);
        status = ProPDFoptionsIntpropertySet(pdf_options, PRO_PDFOPT_FONT_STROKE, PRO_PDF_STROKE_ALL_FONTS);
        status = ProPDFoptionsIntpropertySet(pdf_options, PRO_PDFOPT_SHEETS, PRINT_ALL_SHEETS);


        status = ProPDFExport(this->_drawing, this->_w_temp_path, pdf_options);
        if (status == PRO_TK_NO_ERROR)
        {
            TLog::Print(L"PDF File: %s", this->_w_temp_path);
        }
        else
        {
            TLog::Print(L"ERROR: PDF File: %s", this->_w_temp_path);
            return status;
        }

        this->pdf_generated = true;

        return status;
    }

    ProError Drw::CreateHpgl(std::vector<std::wstring> &list)
    {
        ProError				status;
        ProPrintPrinterOpts		printer_options;
        ProPrintMdlOpts			mdl_options;
        ProPrintPlacementOpts	place_options;
        ProPath					w_pcf_file;
        ProName					w_option_name;

        list.clear();
        this->SetFileNames(L"plt");

        status = Mirim::Option::GetRootDirectory(w_pcf_file);
        wcscat(w_pcf_file, L"\\config\\designjet.pcf");
        status = ProPrintPCFOptionsGet(w_pcf_file, this->_drawing, &printer_options, &mdl_options, &place_options);

        mdl_options.sheets = PRINT_ALL_SHEETS;

        printer_options.save_to_file = PRO_B_TRUE;
        printer_options.delete_after = PRO_B_FALSE;
        printer_options.send_to_printer = PRO_B_FALSE;
        printer_options.save_method = PRINT_SAVE_MULTIPLE_FILE;
        wcscpy(printer_options.filename, this->_w_temp_path);

        // pen table from config.pro
        wcscpy(w_option_name, L"pen_table_file");
        status = ProConfigoptGet(w_option_name, printer_options.pen_table);
        TLog::Print(L"Use pen_table_file from config.pro: %s", printer_options.pen_table); 

        status = this->GetPaperSize(this->_option->PaperSize, &printer_options.paper_size.size);

        std::vector<std::wstring> list1;
        this->GetFileList(list1);
        status = ProPrintExecute(this->_window_id, &printer_options, &mdl_options, &place_options);
        if (status == PRO_TK_NO_ERROR)
        {
            TLog::Print(L"HP-GL File: %s", this->_w_temp_path);
        }
        else
        {
            TLog::Print(L"ERROR: HP-GL File: %s", this->_w_temp_path);
        }

        this->GetNewFileList(list1);
        this->hpgl_generated = true;

        return PRO_TK_NO_ERROR;
    }


    ProError Drw::ExportHPGL()
    {
        ProError	status;

        this->CreateHpgl(this->file_list);
        for(std::vector<std::wstring>::iterator it = file_list.begin();it != file_list.end(); it++)
        {
            this->SetFileNames(it->c_str(), L"plt");
            status = this->CopyTo(this->_w_temp_path, this->_w_target_path);
        }

        return PRO_TK_NO_ERROR;
    }


    ProError Drw::ExportPDF()
    {
        this->SetFileNames(L"pdf");
        this->CreatePDF();
        return this->CopyTo(this->_w_temp_path, this->_w_target_path);
    }


    ProError Drw::PrintUsingHpgl()
    {
        ProError	status;

        if (!this->hpgl_generated)
        {
            this->CreateHpgl(this->file_list);
        }

        if (!this->hpgl_generated) 
        {
            TLog::Print(L"ERROR in printing: Could not create HP-GL File: %s", this->_w_temp_path);
            return PRO_TK_GENERAL_ERROR;
        }


        /* hpglview -wdrv infile[,cfg_file[,page]] outfile:printerqueue[,rotate[,scale[,fitmode]]] */

        //Only on Windows. Output infile to outfile or printer using the specified Windows printer
        //driver with queue name printerqueue. If outfile is the literal string printer, output goes to
        //the printer, otherwise to file outfile. If fitmode is 1, the page will be printed in absolute
        //scale (1=1), otherwise it will be scaled to fit on page

        ProPath		w_command;
        status = Mirim::Option::GetRootDirectory(w_command);
        wcscat(w_command, L"\\bin\\hpglview.exe");

        wchar_t		w_option[1024];
        for(std::vector<std::wstring>::iterator it = this->file_list.begin(); it != this->file_list.end(); it++)
        {
            this->SetFileNames(it->c_str(), L"plt");

            wsprintf(w_option, L"-wdrv %s printer:%s,90", it->c_str(), this->_option->PrinterName);
            try
            {
                status = Mirim::Util::ExecuteCommand(true, w_command, w_option);
            }
            catch(...)
            {
                Mirim::MsgBox::Show(L"BatchTools", L"Could not open HP-GL file...\n\n This problem may be caused by \"Document Security System...\"");
            }

            //this->SetFileNames(it->c_str(), L"eps");
            //wsprintf(w_option, L"-eps %s %s", it->c_str(), this->_w_target_path);
            //try
            //{
            //	status = Util::ExecuteCommand(true, w_command, w_option);
            //}
            //catch(...)
            //{
            //	Mirim::MsgBox::Show(L"BatchTools", L"Could not open HP-GL file...\n\n This problem may be caused by \"Document Security System...\"");
            //}
        }
        return PRO_TK_NO_ERROR;
    }

    ProError Drw::PrintUsingPdf()
    {
        this->SetFileNames(L"pdf");
        if (!this->pdf_generated)
        {
            this->CreatePDF();
        }

        if (!this->pdf_generated) 
        {
            TLog::Print(L"ERROR in printing: Could not create PDF File: %s", this->_w_temp_path);
            return PRO_TK_GENERAL_ERROR;
        }

        ProError	status;
        ProPath		w_command;
        wchar_t		w_option[1024];

        status = Mirim::Option::GetRootDirectory(w_command);
        wcscat(w_command, L"\\bin\\clprint.exe");
        wsprintf(w_option, L"/print /printer:\"%s\" /setsize:\"%s\" /pdffile:\"%s\"", this->_option->PrinterName, this->_option->PaperSize, this->_w_temp_path);
        try
        {
            status = Mirim::Util::ExecuteCommand(false, w_command, w_option);
        }
        catch(...)
        {
            Mirim::MsgBox::Show(L"BatchTools", L"Could not open pdf file...\n\n This problem may be caused by \"Document Security System...\"");
        }

        return PRO_TK_NO_ERROR;

    }

    ProError Drw::PrintUsingPostscript()
    {
        ProError				status;
        ProPrintPrinterOpts		printer_options;
        ProPrintMdlOpts			mdl_options;
        ProPrintPlacementOpts	place_options;
        ProPath					w_pcf_file;
        ProName					w_option_name;

        status = Mirim::Option::GetRootDirectory(w_pcf_file);
        wcscat(w_pcf_file, L"\\config\\postscript.pcf");
        status = ProPrintPCFOptionsGet(w_pcf_file, this->_drawing, &printer_options, &mdl_options, &place_options);

        mdl_options.sheets = PRINT_ALL_SHEETS;

        printer_options.save_to_file = PRO_B_TRUE;
        printer_options.delete_after = PRO_B_FALSE;
        printer_options.send_to_printer = PRO_B_TRUE;
        printer_options.save_method = PRINT_SAVE_MULTIPLE_FILE;

        status = Mirim::Option::GetRootDirectory(this->_w_temp_path);
        wsprintf(this->_w_temp_path, L"%s\\work\\%s.ps", this->_w_temp_folder, this->w_mdl_name);
        wcscpy(printer_options.filename, this->_w_temp_path);

        // pen table from config.pro
        wcscpy(w_option_name, L"pen_table_file");
        status = ProConfigoptGet(w_option_name, printer_options.pen_table);
        TLog::Print(L"Use pen_table_file from config.pro: %s", printer_options.pen_table); 

        status = this->GetPaperSize(this->_option->PrinterName, &printer_options.paper_size.size);

        status = ProPrintExecute(this->_window_id, &printer_options, &mdl_options, &place_options);
        if (status == PRO_TK_NO_ERROR)
        {
            TLog::Print2(L"Printed: %s", this->_w_temp_path);
        }
        else
        {
            TLog::Print2(L"ERROR: CODE = %d: Print: %s", status, this->_w_temp_path);
        }

        return PRO_TK_NO_ERROR;
    }

    ProError Drw::Print()
    {
        ProError	status;

        if (wcsicmp(this->_option->PrintFormat, L"HP-GL") == 0)
        {
            status = this->PrintUsingHpgl();
        }
        else if (wcsicmp(this->_option->PrintFormat, L"PDF") == 0)
        {
            status = this->PrintUsingPdf();
        }
        else
        {
            status = this->PrintUsingPostscript();
        }

        return PRO_TK_NO_ERROR;
    }

    ProError Drw::GetDrawingList(const wchar_t *w_type, wchar_t *w_source_path, std::vector<ProDrawing> &list)
    {
        ProError	status;
        ProMdl		mdl;

        if (wcsicmp(w_type, L"ASM") == 0)
        {
            std::vector<Gui::Model> model_list;
            status = Gui::Session::CollectModels(w_source_path, model_list);
            for(auto it = model_list.begin(); it != model_list.end(); it++)
            {
                if (it->drawing_exists)
                {
                    status = ProMdlInit(it->mdl_data.name, PRO_MDL_DRAWING, &mdl);
                    if (status != PRO_TK_NO_ERROR) continue;

                    list.push_back((ProDrawing) mdl);
                }
            }
        }
        else
        {
            status = ProMdlLoad(w_source_path, PRO_MDL_DRAWING, PRO_B_FALSE, &mdl);
            if (status != PRO_TK_NO_ERROR) return status;

            list.push_back((ProDrawing) mdl);
        }

        return PRO_TK_NO_ERROR;

    }


    ProError Drw::Export(std::vector<Gui::Model> &item_list, const wchar_t *w_target_folder)
    {
        ProError	status;
        ProPath     w_source_path;
        ProPath		w_working_folder;

        Mirim::License license;
        //bool licensed = license.IsValid(true);
        bool licensed = true;

        if (!licensed)
        {
            Mirim::MsgBox::Show(L"Trial Notice", L"This trial version can convert only 5 drawings...");
        }

        Mirim::Option *option = Mirim::Option::GetUniqueInstance();

        status = Mirim::Option::GetRootDirectory(w_working_folder);
        wcscat(w_working_folder, L"\\work");
        Mirim::Util::DeleteFiles(w_working_folder);

        int n_count = 0;
        int length = static_cast<int>(item_list.size());
        for(size_t i=0; i<item_list.size(); i++)
        {
            wsprintf(w_source_path, L"%s\\%s.%s", item_list[i].mdl_data.path, item_list[i].mdl_data.name, item_list[i].mdl_data.type);

            std::vector<ProDrawing> list;
            status = Drw::GetDrawingList(item_list[i].mdl_data.type, w_source_path, list);
            for(std::vector<ProDrawing>::iterator it = list.begin(); it != list.end(); it++)
            {
                n_count++;
                if (!licensed && n_count > 5) 
                {
                    return PRO_TK_NO_ERROR;
                }

                TLog::Print(L"===>");
                TLog::Print(L"%d of %d: %s", n_count, length, w_source_path); 

                Drw drw(*it, w_target_folder);

                if (option->ExportDwg)
                {
                    drw.ExportDWG();
                }

                if (option->ExportDxf)
                {
                    drw.ExportDXF();
                }

                if (option->ExportHpgl)
                {
                    drw.ExportHPGL();
                }

                if (option->ExportPdf)
                {
                    drw.ExportPDF();
                }

                if (option->Print)
                {
                    drw.Print();
                }
            }

            status = ProMdlEraseNotDisplayed();
        }

        TLog::Close();

        Mirim::MsgBox::Show(L"PMP", L"Finished...");
        return PRO_TK_NO_ERROR;
    }

}