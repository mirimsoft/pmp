#pragma once
#include "ProTk.h"
#include "Model.h"
#include "Table.h"
#include "UI.h"


namespace Gui
{
	class StdParam
	{
	public:
		ProPath Name;
		ProPath Type;
		ProPath	Names;
		ProName ReadOnly;
		ProPath Default;
		ProPath	Remark;

		bool operator==(const StdParam other)
		{
			return wcsicmp(this->Name, other.Name) == 0;
		}

	public:
		StdParam(void);
		explicit StdParam(char * name);
		~StdParam(void);

	public:
		static std::vector<StdParam> *GetUniqueParamList();
		static std::vector<std::pair<bool, wstring>> *GetDeleteParamNames();

		static ProError StdParam::ReadExcel(wchar_t *w_file_path, std::vector<StdParam> &list, std::vector<std::pair<bool, wstring>> &list1);
		static ProError StdParam::SaveExcel(wchar_t *w_file_path, std::vector<StdParam> &list, std::vector<std::pair<bool, wstring>> &list1);
		static ProError StdParam::ReadXml(std::vector<StdParam> *list, std::vector<std::pair<bool, wstring>> *list1);
		static ProError StdParam::SaveXml(std::vector<StdParam> *list, std::vector<std::pair<bool, wstring>> *list1);

		static ProError StdParam::ReadStdParams(char *dialog, char *table, std::vector<StdParam> &list);
		static ProError StdParam::ReadParamsToDelete(char *dialog, char *table, std::vector<std::pair<bool, wstring>> &list1);

		static ProError StdParam::GetXmlFileName(wchar_t *w_path);
		static ProError StdParam::GetExcelFileName(wchar_t *w_path);
		//static ProError StdParam::ReadStdNames(char ***names, int *n_count);
		static ProError StdParam::GetStdParamNames(std::vector<wstring> &list);

		static ProError StdParam::EditSelectedCell(ProAppData data);

		static ProError StdParam::ShowStdParams(char *dialog, char *table, std::vector<StdParam> &list);
		static ProError StdParam::ShowParamsToDelete(char *dialog, char *component, std::vector<std::pair<bool, wstring>> &list); 

		static ProError StdParam::AddStdParamColumns(Table *table);
		static ProError StdParam::ShowParamValues(Table *table, std::vector<Model> &list);
		static ProError StdParam::ShowParamValues(Table *table, std::vector<Model> &list, bool show_asm, bool show_prt);

		static ProError StdParam::GetParamValueToString(ProModelitem model_item, wchar_t *w_name, wchar_t *w_names, wchar_t *w_value);
		static ProError StdParam::SetParamValueWithString(ProModelitem model_item, wchar_t *w_name, wchar_t *w_type, wchar_t *w_names, wchar_t *w_value);
		static ProError StdParam::GetParamValue(wchar_t *w_type, wchar_t *w_value, ProParamvalue *param_value);
		static ProError StdParam::CreateReadOnlyParameter(ProModelitem model_item, wchar_t *w_name, wchar_t *w_type);
		static ProError StdParam::SetStdRelations(ProMdl mdl);
		static ProError StdParam::GetLegacyParam(ProModelitem model_item, wchar_t *w_names, ProParameter *param);

		static ProError StdParam::Standardize(Table *table, Mirim::Option *option);
		static ProError StdParam::ApplyParams(char *dialog, char *table);

	private:
		static int row_number;
		static std::vector<StdParam> *_unique_param_list;
		static std::vector<std::pair<bool, wstring>> *_delete_param_list;
	};

}