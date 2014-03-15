#pragma once
#include "ProTk.h"
#include "Model.h"
#include "Session.h"
#include "License.h"

namespace Gui
{

    class Drw
    {
    public:
        bool	pdf_generated;
        bool	hpgl_generated;
        ProName	w_mdl_name;

        std::vector<std::wstring> file_list;

    private:
        ProDrawing      _drawing;
        int			    _window_id;
        ProPath		    _w_target_folder;
        ProPath		    _w_temp_folder;
        ProPath		    _w_target_path;
        ProPath		    _w_temp_path;
        ProLine		    _w_axis_display;
        ProLine		    _w_datum_display;
        Mirim::Option	*_option;

    public:
        Drw(ProDrawing drawing, const wchar_t *w_target_folder);
        ~Drw(void);

    public:
        ProError    Drw::CreatePDF();
        ProError	Drw::CreateHpgl(std::vector<std::wstring> &list);
        ProError	Drw::ExportDXF();
        ProError	Drw::ExportDWG();
        ProError    Drw::ExportPDF();
        ProError	Drw::ExportHPGL();
        ProError	Drw::Print();

        ProError	Drw::GetPaperSize(const wchar_t *w_paper_name, ProPlotPaperSize *size);
        ProError	Drw::CopyTo(const wchar_t *w_from, const wchar_t *w_to);
        ProError	Drw::SetFileNames(const wchar_t *w_extension);
        ProError	Drw::SetFileNames(const wchar_t *w_path, const wchar_t *w_extension);

        ProError	Drw::GetFileList(std::vector<std::wstring> &list);
        ProError	Drw::GetNewFileList(std::vector<std::wstring> &list);

        ProError	Drw::PrintUsingHpgl();
        ProError    Drw::PrintUsingPdf();
        ProError	Drw::PrintUsingPostscript();


    public:
        static ProError Drw::Export(std::vector<Gui::Model> &list, const wchar_t *w_target_folder);
        static ProError Drw::GetDrawingList(const wchar_t *w_type, wchar_t *w_source_path, std::vector<ProDrawing> &list);
    };

}