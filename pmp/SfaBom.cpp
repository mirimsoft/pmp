#include "SfaBom.h"
#include "SfaPart.h"
#include "Session.h"


namespace Gui
{
    SfaBom::SfaBom(void)
    {
    }


    SfaBom::~SfaBom(void)
    {
    }

    bool SfaBom::IsAssembly(ProMdl *mdl)
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


    ProError SfaBom::CollectBom(ProMdl mdl, int level, std::vector<SfaPart> &list)
    {
        ProError                status;
        ProAsmcomp              *p_asmcomps;
        int                     n_asmcomps;
        ProMdl                  mdl_handle;
        std::vector<SfaPart>    bom_list;

        level++;
        status = ProUtilCollectAsmcomp((ProAssembly) mdl, &p_asmcomps);
        if (status != PRO_TK_NO_ERROR) return status;

        std::vector<ProMdl> mdl_list;
        status = ProArraySizeGet(p_asmcomps, &n_asmcomps);
        for (int i=0; i<n_asmcomps; i++)
        {
            status = ProAsmcompMdlGet(&p_asmcomps[i], &mdl_handle);
            if (status != PRO_TK_NO_ERROR) continue;

            SfaPart part(mdl_handle, level);
            if (!part.is_valid) continue;

            std::vector<SfaPart>::iterator it = std::find(bom_list.begin(), bom_list.end(), part);
            if (it == bom_list.end())
            {
                bom_list.push_back(part);
            }
            else
            {
                it->set_qty++;
                it->total_qty++;
            }
        }

        for (auto it = bom_list.begin(); it != bom_list.end(); it++)
        {
            list.push_back(*it);
            if (wcsicmp(it->mdl_data.type, L"ASM") == 0)
            {
                status = this->CollectBom(it->mdl, level, list);
            }
        }

        return PRO_TK_NO_ERROR;
    }

    ProError SfaBom::CreateBom()
    {
        ProError    status;
        ProMdl      mdl;

        if (this->IsAssembly(&mdl)) return PRO_TK_BAD_CONTEXT;

        std::vector<SfaPart> list;
        list.push_back(SfaPart(mdl, 0));

        status = this->CollectBom(mdl, 0, list);

        return PRO_TK_NO_ERROR;
    }

    ProError SfaBom::CollectPartList(ProMdl mdl, std::vector<SfaPart> &part_list)
    {
        ProError                status;
        ProAsmcomp              *p_asmcomps;
        int                     n_asmcomps;
        ProMdl                  mdl_handle;

        status = ProUtilCollectAsmcomp((ProAssembly) mdl, &p_asmcomps);
        if (status != PRO_TK_NO_ERROR) return status;

        std::vector<ProMdl> mdl_list;
        status = ProArraySizeGet(p_asmcomps, &n_asmcomps);
        for (int i=0; i<n_asmcomps; i++)
        {
            status = ProAsmcompMdlGet(&p_asmcomps[i], &mdl_handle);
            if (status != PRO_TK_NO_ERROR) continue;

            SfaPart part(mdl_handle, 0);
            if (!part.is_valid) continue;

            std::vector<SfaPart>::iterator it = std::find(part_list.begin(), part_list.end(), part);
            if (it == part_list.end())
            {
                part_list.push_back(part);
            }
            else
            {
                it->set_qty++;
                it->total_qty++;
            }

            if (wcsicmp(part.mdl_data.type, L"ASM") == 0)
            {
                this->CollectPartList(mdl_handle, part_list);
            }
        }

        return PRO_TK_NO_ERROR;
    }


    ProError SfaBom::CreatePartList()
    {
        ProError    status;
        ProMdl      mdl;

        if (this->IsAssembly(&mdl)) return PRO_TK_BAD_CONTEXT;

        std::vector<SfaPart> list;
        list.push_back(SfaPart(mdl, 0));
        status = this->CollectBom(mdl, 0, list);

        return PRO_TK_NO_ERROR;
    }
}
