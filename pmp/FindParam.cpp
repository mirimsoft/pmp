#include "StdAfx.h"
#include "FindParam.h"
#include "Session.h"

#define DIALOG "FindParam"
#define IP_WHAT "InputPanel1"
#define PB_FIND "PushButton1"
#define PB_CLOSE "PushButton2"
#define TEXT_AREA "TextArea1"

namespace Gui
{

    FindParam::FindParam(void)
    {
    }


    FindParam::~FindParam(void)
    {
    }


    ProError FindParam::ShowDialog()
    {
        ProError    status;
        int         error;

        status = ProUIDialogCreate(DIALOG, DIALOG);

        status = ProUIDialogCloseActionSet(DIALOG, (ProUIAction)FindParam::CLOSE_ACTION, NULL);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_CLOSE, (ProUIAction) FindParam::CLOSE_ACTION, NULL);
		status = ProUIPushbuttonActivateActionSet(DIALOG, PB_FIND, (ProUIAction) FindParam::PB_FIND_ACTION, NULL);

        status = ProUIDialogActivate(DIALOG, &error);
        status = ProUIDialogDestroy(DIALOG);

        return PRO_TK_NO_ERROR;
    }


    ProError FindParam::CLOSE_ACTION(char *dialog, char *component, ProAppData app_data)
    {
        return ProUIDialogExit(dialog, PRO_TK_NO_ERROR);
    }

    ProError FindParam::PB_FIND_ACTION(char *dialog, char *component, ProAppData app_data)
    {
        ProError        status;
        wchar_t         *w_what;
        ProModelitem    model_item;
        ProParameter    param;
        ProMdldata      mdl_data;
        ProPath         w_text;

        status = ProUIInputpanelWidestringGet(DIALOG, IP_WHAT, &w_what);
        if (status != PRO_TK_NO_ERROR) return status;
        wcsupr(w_what);

        std::vector<Model> mdl_list;
        status = Session::CollectModels(mdl_list);

        CString c_str;
        for (int i=0; i<mdl_list.size(); i++)
        {
            status = ProMdlToModelitem(mdl_list[i].mdl, &model_item);
            if (status != PRO_TK_NO_ERROR) continue;

            status = ProParameterInit(&model_item, w_what, &param);
            if (status != PRO_TK_NO_ERROR) continue;

            status = ProMdlDataGet(mdl_list[i].mdl, &mdl_data);
            if (status != PRO_TK_NO_ERROR) continue;

            wsprintf(w_text, L"%3d: %s.%s\n", i+1, mdl_data.name, mdl_data.type);
            c_str += w_text;
        }

        if (c_str.GetLength() < 1) c_str = L"Could not find paramter..."; 

        status = ProUITextareaValueSet(DIALOG, TEXT_AREA, c_str.GetBuffer());
        ProWstringFree(w_what);

        return PRO_TK_NO_ERROR;
    }
}