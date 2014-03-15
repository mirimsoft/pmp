#pragma once
#include "ProTk.h"
#include "SfaPart.h"
namespace Gui
{


    class SfaBom
    {
    public:
        SfaBom(void);
        ~SfaBom(void);

    public:
        ProError SfaBom::CreateBom();
        ProError SfaBom::CreatePartList();
        bool SfaBom::IsAssembly(ProMdl *mdl);
        bool SfaBom::Contains(std::vector<SfaPart> &list, SfaPart part);

        ProError SfaBom::CollectBom(ProMdl mdl, int level, std::vector<SfaPart> &bom_list);
        ProError SfaBom::CollectPartList(ProMdl mdl, std::vector<SfaPart> &part_list);

    };

}