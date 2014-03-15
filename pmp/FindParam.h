#pragma once
#include "ProTk.h"
#include "Model.h"

namespace Gui
{

    class FindParam
    {
    public:
        FindParam(void);
        ~FindParam(void);

    public:
        static ProError FindParam::ShowDialog();

        static ProError FindParam::CLOSE_ACTION(char *dialog, char *component, ProAppData app_data);
        static ProError FindParam::PB_FIND_ACTION(char *dialog, char *component, ProAppData app_data);


    };

}