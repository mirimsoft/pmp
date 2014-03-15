#include "StdAfx.h"
#include "SfaPart.h"

namespace Gui
{

    SfaPart::SfaPart(ProMdl mdl, int level)
        :mdl(mdl), level(level)
    {
        ProError        status;
        ProModelitem    model_item;
        ProPath         w_value;

        this->is_valid = false;

        status = ProMdlToModelitem(this->mdl, &model_item);
        if (status != PRO_TK_NO_ERROR) return;

        if (!this->IsBomItem(model_item)) return;

        status = ProMdlDataGet(this->mdl, &this->mdl_data);
        if (status != PRO_TK_NO_ERROR) return;

        status = this->GetParamValue(model_item, L"S01_PART_NO", w_value);
        if (status != PRO_TK_NO_ERROR) return;

        Mirim::Option *option = Mirim::Option::GetUniqueInstance();
        if (wcslen(w_value) == option->TotalLength)
        {
            wcsncpy(this->w_part_no, w_value + option->PartNrStart, option->PartNrLength);
        }

        status = this->GetParamValue(model_item, L"S01_PART_NO", this->w_drawing_nr);
        if (status != PRO_TK_NO_ERROR) return;

        status = this->GetParamValue(model_item, L"S03_MATERIAL", this->w_material);
        if (status != PRO_TK_NO_ERROR) return;

        status = this->GetParamValue(model_item, L"S04_SPEC_OR_SIZE", this->w_spec_or_size);
        if (status != PRO_TK_NO_ERROR) return;

        status = this->GetParamValue(model_item, L"S05_REMARK", this->w_remark);
        if (status != PRO_TK_NO_ERROR) return;

        this->set_qty = this->total_qty = 1;
        this->is_valid = true;

        return;
    }


    SfaPart::~SfaPart(void)
    {
    }

    bool SfaPart::IsBomItem(ProModelitem model_item)
    {
        ProError    status;
        ProName     w_name = L"S11_INCLUDE_BOM";
        ProParameter    param;
        ProParamvalue   param_value;

        status = ProParameterInit(&model_item, w_name, &param);
        if (status != PRO_TK_NO_ERROR) return false;


        status = ProParameterValueGet(&param, &param_value);
        if (status != PRO_TK_NO_ERROR) return false;

        if (param_value.type != PRO_PARAM_BOOLEAN) return false;

        return param_value.value.l_val != 0;
    }

    ProError SfaPart::GetParamValue(ProModelitem model_item, wchar_t *w_name, wchar_t *w_value)
    {
        ProError    status;
        ProParameter    param;
        ProParamvalue   param_value;

        status = ProParameterInit(&model_item, w_name, &param);
        if (status != PRO_TK_NO_ERROR) return status;

        status = ProParameterValueGet(&param, &param_value);
        if (status != PRO_TK_NO_ERROR) return status;

        if (param_value.type != PRO_PARAM_STRING) return PRO_TK_INVALID_TYPE;

        wcscpy(w_value, param_value.value.s_val);

        return PRO_TK_NO_ERROR;
    }

}
