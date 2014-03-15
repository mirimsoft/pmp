#pragma once
#include "ProTk.h"

namespace Mirim
{
	class UI
	{
	public:
		static bool UI::CopyToClipboard(const wchar_t *w_text);
		static bool UI::PasteFromClipBoard(wchar_t **w_text);

		//static ProError UI::GetOptionMenuSelectedName(char *dialog, char *component, char *selected_name);
		//static ProError UI::GetOptionMenuSelectedName(char *dialog, char *component, wchar_t *selected_name);
		static ProError UI::GetOptionMenuSelectedLabel(char *dialog, char *component, wchar_t *w_selected_label);
		static ProError UI::GetOptionMenuLabels(char *dialog, char *component, int *n_count, wchar_t ***w_labels);
		//static ProError UI::GetOptionMenuLabels(char *dialog, char *component, wchar_t ***w_list);
						
		static ProError UI::SetOptionMenuSelectedLabel(char *dialog, char *component, wchar_t *w_value);
		static ProError UI::SetOptionMenuSelectedIndex(char *dialog, char *component, int index);
		static ProError UI::SetOptionMenuItemCount(char *dialog, char *component, wchar_t *w_name, int count);
		static ProError UI::SetOptionMenuLabels(char *dialog, char *component, wchar_t **w_labels);
						
		static ProError UI::GetRadioGroupSelectedName(char *dialog, char *component, wchar_t *w_value);
		static ProError UI::SetRadioGroupSelectedName(char *dialog, char *component, wchar_t *w_value);
						
		static ProError UI::GetCheckboxStatus(char *dialog, char *component, bool *checked);
		static ProError UI::GetCheckboxStatus(char *dialog, char *component, ProBoolean *checked);
		static ProError UI::SetCheckboxStatus(char *dialog, char *component, bool checked);
		static ProError UI::SetCheckboxStatus(char *dialog, char *component, ProBoolean checked);

		static ProError UI::SetInputpanelValue(char *dialog, char *component, wchar_t *w_value);
		static ProError UI::SetInputpanelValue(char *dialog, char *component, int value);
		static ProError UI::SetInputpanelValue(char *dialog, char *component, double w_value);

		static ProError UI::GetInputpanelValue(char *dialog, char *component, wchar_t *w_value);
		static ProError UI::GetInputpanelValue(char *dialog, char *component, int *value);
		static ProError UI::GetInputpanelValue(char *dialog, char *component, double *w_value);


		static bool UI::TableSingleCellSelected(char *dailog, char *table);

		static ProError UI::ShowPrinters(char *dialog, char *component);
		static ProError UI::ShowPapers(char *dialog, char *component);

        static ProError UI::ShowFolders(char *dialog, char *component);
        static ProError UI::SaveFolders(char *dialog, char *component);
	};
}