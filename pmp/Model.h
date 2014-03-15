#pragma once

#include "ProTk.h"

namespace Gui
{
	class Model
	{
	public:
		ProMdl		mdl;
		ProMdldata  mdl_data;
		ProMdlType	type;
		int			qty;
		bool		drawing_exists;
		ProPath		w_target;

	public:
		// Copy Constructor
		//Model(const Model &model)
		//{
		//	this->mdl = model.mdl;
		//	wcscpy_s(mdl_data.device, model.mdl_data.device);
		//	wcscpy_s(mdl_data.host, model.mdl_data.host);
		//	wcscpy_s(mdl_data.name, model.mdl_data.name);
		//	wcscpy_s(mdl_data.path, model.mdl_data.path);
		//	wcscpy_s(mdl_data.type, model.mdl_data.type);
		//	this->mdl_data.subclass = model.mdl_data.subclass;
		//	this->mdl_data.version = model.mdl_data.version;

		//	this->type = model.type;
		//	this->drawing_exists = model.drawing_exists;
		//	wcscpy_s(this->w_target, model.w_target);
		//}

		Model(ProMdl mdl)
			:mdl(mdl)
		{
			ProError	status;
			this->qty = 0;

			status = ProMdlDataGet(mdl, &this->mdl_data);
			if (status != PRO_TK_NO_ERROR) return;

			status = ProMdlTypeGet(mdl, &this->type);
			if (status != PRO_TK_NO_ERROR) return;

			this->qty = 1;
		}

		Model(wchar_t *w_file_path)
		{
			ProPath w_path;
			ProName w_name, w_type;
			int     version;

			ProFilenameParse(w_file_path, w_path, w_name, w_type, &version);
			wcscpy_s(mdl_data.path, w_path);
			wcscpy_s(mdl_data.name, w_name);
			wcscpy_s(mdl_data.type, w_type);
			*this->mdl_data.host = NULL;
			*this->mdl_data.device = NULL;
			this->mdl_data.subclass = PRO_VALUE_UNUSED;
			this->mdl_data.version = PRO_VALUE_UNUSED;
			if (wcsicmp(mdl_data.type, L"ASM") == 0)
				this->type = PRO_MDL_ASSEMBLY;
			else if (wcsicmp(mdl_data.type, L"PRT") == 0)
				this->type = PRO_MDL_PART;
			else if (wcsicmp(mdl_data.type, L"DRW") == 0)
				this->type = PRO_MDL_DRAWING;
			else
				this->type = PRO_MDL_UNUSED;

			this->qty = 0;
			*this->w_target = NULL;
		}

		Model(char *dialog, char *table, char *row_name)
		{
			ProError	status;
			wchar_t		*w_text;

			status = ProUITableCellLabelGet(dialog, table, row_name, "Name", &w_text);
			wcscpy_s(this->mdl_data.name, w_text);
			ProWstringFree(w_text);

			status = ProUITableCellLabelGet(dialog, table, row_name, "Type", &w_text);
			wcscpy_s(this->mdl_data.type, w_text);
			ProWstringFree(w_text);

			if (wcsicmp(this->mdl_data.type, L"ASM") == 0)
				this->type = PRO_MDL_ASSEMBLY;
			else if (wcsicmp(this->mdl_data.type, L"PRT") == 0)
				this->type = PRO_MDL_PART;
			else if (wcsicmp(this->mdl_data.type, L"DRW") == 0)
				this->type = PRO_MDL_DRAWING;
			else 
				this->type = PRO_MDL_UNUSED;
			
			status = ProUITableCellLabelGet(dialog, table, row_name, "Path", &w_text);
			wcscpy_s(this->mdl_data.path, w_text);
			ProWstringFree(w_text);

			status = ProUITableCellLabelGet(dialog, table, row_name, "Device", &w_text);
			wcscpy_s(this->mdl_data.device, w_text);
			ProWstringFree(w_text);

		}

		bool operator==(const Model &other)
		{
			return wcsicmp(this->mdl_data.name, other.mdl_data.name) == 0 && this->type == other.type;
		}

		// Assignment Operator
		//Model &operator=(const Model &model)
		//{
		//	if (this == &model) return *this;

		//	this->mdl = model.mdl;
		//	wcscpy_s(mdl_data.device, model.mdl_data.device);
		//	wcscpy_s(mdl_data.host, model.mdl_data.host);
		//	wcscpy_s(mdl_data.name, model.mdl_data.name);
		//	wcscpy_s(mdl_data.path, model.mdl_data.path);
		//	wcscpy_s(mdl_data.type, model.mdl_data.type);
		//	this->mdl_data.subclass = model.mdl_data.subclass;
		//	this->mdl_data.version = model.mdl_data.version;

		//	this->type = model.type;
		//	this->drawing_exists = model.drawing_exists;
		//	wcscpy_s(this->w_target, model.w_target);
		//	return *this;
		//}
	};
}