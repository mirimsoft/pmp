#include "Option.h"

ProPath Mirim::Option::ProductName = L"PMP 4.0.0.1";
ProPath Mirim::Option::ApplicationRoot = L"";
ProPath Mirim::Option::FilePath = L"";

Mirim::Option *Mirim::Option::_uniqueInstance = NULL;


namespace Mirim
{
	Option::Option(void)
	{
		this->ShowAsm1 = true;
		this->ShowPrt1 = true;

		this->ShowAsm2 = true;
		this->ShowDrw2 = true;

		this->ExportDwg = true;
		this->ExportDxf = false;
		this->ExportHpgl = false;
		this->ExportPdf = false;
		this->Print = false;

		*this->SourceFolder = 0;
		*this->PrinterName = 0;
		*this->PaperSize = 0;
		*this->LicenseFile = 0;
		*this->PrintFormat = 0;

		this->TotalLength = 16;
		this->PartNrStart = 13;
		this->PartNrLength = 4;

        this->ColumnWidths = NULL;
        this->n_folders = 0;
	}

    Option::~Option(void)
    {
        Option::Save(*this);
    }

 


	// Singleton
	Option *Option::GetUniqueInstance()
	{
		ProError status;
		ProPath	 w_path;

		status = ProToolkitApplTextPathGet(w_path);
		wsprintf(Option::ApplicationRoot, L"%s", w_path);
		wsprintf(Option::FilePath, L"%s\\config\\configuration.xml", w_path);

		if (Mirim::Util::FileExists(Option::FilePath))
		{
			_uniqueInstance = Option::Read();
		}
		else
		{
			_uniqueInstance = new Option();
		}

		return Option::_uniqueInstance;
	}


	Mirim::Option *Option::Read()
	{
		Option *option = new Option();
		pugi::xml_document xml;
		pugi::xml_parse_result success = xml.load_file(Option::FilePath);
		if (!success) return option;

		option->ExportDwg = xml.select_single_node(L"/Configuration/Option/ExportDwg").node().text().as_bool();
		option->ExportDxf = xml.select_single_node(L"/Configuration/Option/ExportDxf").node().text().as_bool();
		option->ExportHpgl = xml.select_single_node(L"/Configuration/Option/ExportHpgl").node().text().as_bool();
		option->ExportPdf = xml.select_single_node(L"/Configuration/Option/ExportPdf").node().text().as_bool();
		option->Print = xml.select_single_node(L"/Configuration/Option/Print").node().text().as_bool();

		option->ShowAsm1 = xml.select_single_node(L"/Configuration/Option/ShowAsm1").node().text().as_bool();
		option->ShowPrt1 = xml.select_single_node(L"/Configuration/Option/ShowPrt1").node().text().as_bool();
		option->ShowAsm2 = xml.select_single_node(L"/Configuration/Option/ShowAsm2").node().text().as_bool();
		option->ShowDrw2 = xml.select_single_node(L"/Configuration/Option/ShowDrw2").node().text().as_bool();

		option->TotalLength = xml.select_single_node(L"/Configuration/Option/TotalLength").node().text().as_int();
		option->PartNrStart = xml.select_single_node(L"/Configuration/Option/PartNrStart").node().text().as_int();
		option->PartNrLength = xml.select_single_node(L"/Configuration/Option/PartNrLength").node().text().as_int();


		wcscpy(option->SourceFolder, xml.select_single_node(L"/Configuration/Option/SourceFolder").node().text().as_string());
		wcscpy(option->PrinterName, xml.select_single_node(L"/Configuration/Option/PrinterName").node().text().as_string());
		wcscpy(option->PaperSize, xml.select_single_node(L"/Configuration/Option/PaperSize").node().text().as_string());
		wcscpy(option->PrintFormat, xml.select_single_node(L"/Configuration/Option/PrintFormat").node().text().as_string());
		wcscpy(option->LicenseFile, xml.select_single_node(L"/Configuration/Option/LicenseFile").node().text().as_string());

        if (option->ColumnWidths != NULL)
        {
            delete[] option->ColumnWidths;
        }

        const wchar_t *w_text = xml.select_single_node(L"/Configuration/Option/ColumnWidths").node().text().as_string();
        option->ColumnWidths = new wchar_t [wcslen(w_text) + 1];
		wcscpy(option->ColumnWidths, w_text);

		return option;
	}


	ProError Option::Save(Mirim::Option &option)
	{
		pugi::xml_document xml;
		pugi::xml_node decl = xml.prepend_child(pugi::node_declaration);
		decl.append_attribute(L"version") = L"1.0";
		decl.append_attribute(L"encoding") = L"UTF-8";
		decl.append_attribute(L"standalone") = L"yes";

		pugi::xml_node root = xml.append_child(L"Configuration");
		pugi::xml_node node = root.append_child(L"Option");

		pugi::xml_node child_node = node.append_child(L"ExportDxf");
		child_node.text().set(option.ExportDxf);

		child_node = node.append_child(L"ExportDwg");
		child_node.text().set(option.ExportDwg);

		child_node = node.append_child(L"ExportHpgl");
		child_node.text().set(option.ExportHpgl);

		child_node = node.append_child(L"ExportPdf");
		child_node.text().set(option.ExportPdf);

		child_node = node.append_child(L"Print");
		child_node.text().set(option.Print);

		child_node = node.append_child(L"ExportDwg");
		child_node.text().set(option.ExportDwg);

		child_node = node.append_child(L"ShowAsm1");
		child_node.text().set(option.ShowAsm1);

		child_node = node.append_child(L"ShowPrt1");
		child_node.text().set(option.ShowPrt1);

		child_node = node.append_child(L"ShowAsm2");
		child_node.text().set(option.ShowAsm2);

		child_node = node.append_child(L"ShowDrw2");
		child_node.text().set(option.ShowDrw2);

		child_node = node.append_child(L"SourceFolder");
		child_node.text().set(option.SourceFolder);

		wchar_t w_text[32];
		child_node = node.append_child(L"TotalLength");
		child_node.text().set(_itow(option.TotalLength, w_text, 10));

		child_node = node.append_child(L"PartNrStart");
		child_node.text().set(_itow(option.PartNrStart, w_text, 10));

		child_node = node.append_child(L"PartNrLength");
		child_node.text().set(_itow(option.PartNrLength, w_text, 10));

		child_node = node.append_child(L"PrinterName");
		child_node.text().set(option.PrinterName);

		child_node = node.append_child(L"PaperSize");
		child_node.text().set(option.PaperSize);

		child_node = node.append_child(L"PrintFormat");
		child_node.text().set(option.PrintFormat);	

		child_node = node.append_child(L"LicenseFile");
        child_node.text().set(option.LicenseFile);	

        if (option.ColumnWidths != NULL)
        {
            child_node = node.append_child(L"ColumnWidths");
            child_node.text().set(option.ColumnWidths);
        }

		xml.save_file(Option::FilePath);

        return PRO_TK_NO_ERROR;
    }

    ProError Option::GetRootDirectory(wchar_t *w_path)
    {
        return ProToolkitApplTextPathGet(w_path);
    }
}