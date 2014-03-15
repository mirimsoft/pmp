#include "Session.h"
namespace Gui
{

	Session::Session(void)
	{
	}


	Session::~Session(void)
	{
	}


	bool Session::IsAssembly(ProMdl *mdl)
	{   
		ProError    status;
		ProMdlType  mdl_type;

		status = ProMdlCurrentGet(mdl);
		if (status != PRO_TK_NO_ERROR) 
		{
			Mirim::MsgBox::Show(L"ERROR", L"There are no models loaded...");
			return false;
		}

		status = ProMdlTypeGet(*mdl, &mdl_type);

		if (status != PRO_TK_NO_ERROR || mdl_type != PRO_MDL_ASSEMBLY)
		{
			Mirim::MsgBox::Show(L"ERROR", L"Current model is not assembly...");
			return false;
		}

		return true;
	}

	ProError Session::CollectModels(ProMdl mdl, std::vector<Model> &list)
	{
		ProError    status;
		ProAsmcomp  *p_asmcomps;
		int         n_asmcomps;
		ProMdl      mdl_handle;

		status = ProUtilCollectAsmcomp((ProAssembly) mdl, &p_asmcomps);
		status = ProArraySizeGet(p_asmcomps, &n_asmcomps);
		for (int i=0; i<n_asmcomps; i++)
		{
			status = ProAsmcompMdlGet(&p_asmcomps[i], &mdl_handle);
			if (status != PRO_TK_NO_ERROR) continue;

			Model m(mdl_handle);
			auto it = find(list.begin(), list.end(), m);
			if (it == list.end())
			{
				list.push_back(m);
			}
			else
			{
				it->qty++;
			}

			if (m.type == PRO_MDL_ASSEMBLY)
			{
				status = Session::CollectModels(mdl_handle, list);
			}
		}

		return PRO_TK_NO_ERROR;
	}


	ProError Session::CollectModels(std::vector<Model> &list)
	{
		ProError	status;
		ProMdl		mdl;
		ProPath		w_file_path;

		list = std::vector<Model>();

		if (!Session::IsAssembly(&mdl)) return PRO_TK_BAD_CONTEXT;
		list.push_back(Model(mdl));

		status = Session::CollectModels(mdl, list);

		TLog::Print(L"$$$ Total %d models are collected...", list.size());

		for (auto it = list.begin(); it != list.end(); it ++)
		{
			status = ProPathCreate(it->mdl_data.path, it->mdl_data.name, L"DRW", PRO_VALUE_UNUSED, w_file_path);
			status = ProMdlLoad(w_file_path, PRO_MDL_DRAWING, PRO_B_FALSE, &mdl);
			if (status == PRO_TK_NO_ERROR)
			{
				TLog::Print(L"Drawing found = %s.drw", it->mdl_data.name);
				it->drawing_exists = true;
			}
			else
				it->drawing_exists = false;
		}

		return PRO_TK_NO_ERROR;
	}

    ProError Session::CollectModels(wchar_t *w_file_path, std::vector<Model> &list)
	{
		ProError	status;
		ProMdl		mdl;

		list = std::vector<Model>();

		status = ProMdlLoad(w_file_path, PRO_MDL_ASSEMBLY, PRO_B_FALSE, &mdl);
        if (status != PRO_TK_NO_ERROR) 
        {
            TLog::Print(L"ERROR: Failed to load file: %s", w_file_path);
            return status;
        }

		status = Session::CollectModels(mdl, list);

		TLog::Print(L"$$$ Total %d models are collected...", list.size());



		return PRO_TK_NO_ERROR;
	}


    ProError Session::LoadDrawings(std::vector<Model> &mdl_list, std::vector<ProDrawing> &drw_list)
    {
        ProError    status;
        ProPath     w_file_path;
        ProDrawing  drawing;

        drw_list = std::vector<ProDrawing>();

        for (auto it = mdl_list.begin(); it != mdl_list.end(); it ++)
        {
            status = ProMdlInit(it->mdl_data.name, PRO_MDL_DRAWING, (ProMdl *) &drawing);
            if (status != PRO_TK_NO_ERROR)
            {
                status = ProPathCreate(it->mdl_data.path, it->mdl_data.name, L"DRW", PRO_VALUE_UNUSED, w_file_path);
                status = ProMdlLoad(w_file_path, PRO_MDL_DRAWING, PRO_B_FALSE, (ProMdl *) &drawing);
            }

            if (status == PRO_TK_NO_ERROR)
            {
                TLog::Print(L"Drawing found = %s.drw", it->mdl_data.name);
                it->drawing_exists = true;
                drw_list.push_back(drawing);
            }
            else
            {
                it->drawing_exists = false;
            }
        }

        return PRO_TK_NO_ERROR;
    }



}