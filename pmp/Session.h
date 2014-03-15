#pragma once

#include "ProTk.h"
#include "Model.h"
#include "StdParam.h"


namespace Gui
{

	class Session
	{
	public:
		Session(void);
		~Session(void);

	public:
		static ProError Session::CollectModels(std::vector<Model> &list);
		static ProError Session::CollectModels(wchar_t *w_file_path, std::vector<Model> &mdl_list);
        static ProError Session::LoadDrawings(std::vector<Model> &mdl_list, std::vector<ProDrawing> &drw_list);
		static bool Session::IsAssembly(ProMdl *mdl);

		static ProError Session::ShowStdParamValues(Table *table, std::vector<Model> &list);
		static ProError Session::ModifyParamValues(Table *table);

	private:
		static ProError Session::CollectModels(ProMdl mdl, std::vector<Model> &mdl_list);


	};

}