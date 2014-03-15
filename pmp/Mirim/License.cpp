#include "License.h"

namespace Mirim
{
	License::License()
	{
		Option *option = Option::GetUniqueInstance();
		wcscpy(this->w_file_path, option->LicenseFile);
	}

	License::License(const wchar_t *w_file_path, const wchar_t *w_mac_address)
	{
		pugi::xml_document xml_doc;
		pugi::xml_node decl = xml_doc.prepend_child(pugi::node_declaration);
		decl.append_attribute(L"version") = L"1.0";
		decl.append_attribute(L"encoding") = L"UTF-8";
		decl.append_attribute(L"standalone") = L"yes";

		pugi::xml_node root = xml_doc.append_child(L"Configuration");
		pugi::xml_node node = root.append_child(L"Product");

		pugi::xml_node child_node = node.append_child(L"Developer");
		child_node.text().set(L"Mirim System Co., Ltd");

		child_node = node.append_child(L"Name");
		child_node.text().set(L"BatchTools");

		child_node = node.append_child(L"Version");
		child_node.text().set(L"Unknown");

		node = root.append_child(L"License");

		child_node = node.append_child(L"MacAddress");
		child_node.text().set(w_mac_address);

		Mirim::Base64 b;
		ProPath w_output;

		b.Encode(w_mac_address, w_output);
		child_node = node.append_child(L"Key");
		child_node.text().set(w_output);

		xml_doc.save_file(w_file_path);
	}

	License::~License(void)
	{
	}

	bool License::IsValid(bool verbose)
	{
		wchar_t		w_message[512];
		pugi::xml_document xml_doc;
		
		pugi::xml_parse_result result = xml_doc.load_file(this->w_file_path);
		if (!result)
		{
			if (verbose)
			{
				wsprintf(w_message, L"ERROR: Could not find license file: %s", this->w_file_path);
				Mirim::MsgBox::Show(L"BatchTools", w_message);
			}

			return false;
		}

		ProName w_mac_address;
		
		pugi::xpath_node node = xml_doc.select_single_node(L"/Configuration/License/Key");
		if (node == NULL)
		{
			if (verbose)
			{
				Mirim::MsgBox::Show(L"BatchTools", L"ERROR: Invalid license file format");
			}
			return false;		
		}
		
		Mirim::Base64 b;
		b.Decode(node.node().text().as_string(), w_mac_address);
		
		if (!Util::MacAddressExists(w_mac_address))
		{
			if (verbose)
			{
				Mirim::MsgBox::Show(L"BatchTools", L"ERROR: Invalid license code...");
			}
			return false;		
		}

		return true;
	}
}