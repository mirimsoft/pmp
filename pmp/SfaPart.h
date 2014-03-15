#pragma once
#include "ProTk.h"


namespace Gui
{
    class SfaPart
    {
    public:
        ProMdl      mdl;
        bool        is_valid;
        ProMdldata  mdl_data;
        int         level;
        int         set_qty;
        int         total_qty;
        ProPath     w_part_no;
        ProPath     w_description;
        ProPath     w_drawing_nr;
        ProPath     w_material;
        ProPath     w_spec_or_size;
        ProPath     w_remark;

    public:
        SfaPart(ProMdl mdl, int level);
        SfaPart::~SfaPart(void);

        bool operator==(SfaPart other)
        {
            return wcsicmp(this->mdl_data.name, other.mdl_data.name) == 0 &&
                   wcsicmp(this->mdl_data.type, other.mdl_data.type) == 0 &&
                   this->level == other.level;
        }

    private:
        ProError SfaPart::GetParamValue(ProModelitem model_item, wchar_t *w_name, wchar_t *w_value);
        bool SfaPart::IsBomItem(ProModelitem model_item);

    };
}


