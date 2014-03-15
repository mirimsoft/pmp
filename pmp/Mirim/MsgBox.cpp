#include "MsgBox.h"

namespace Mirim
{
	char MsgBox::DIALOG[32] = "MsgBox";
	char MsgBox::LAYOUT1[32] = "Layout1";
	char MsgBox::LAYOUT2[32] = "Layout2";
	char MsgBox::LAYOUT3[32] = "Layout3";
	char MsgBox::LAYOUT4[32] = "Layout4";
	char MsgBox::BUTTON_YES[32] = "Button1";
	char MsgBox::BUTTON_NO[32] = "Button2";
	char MsgBox::LABEL1[32] = "Label1";

	bool MsgBox::Initialize(bool yes_only)
	{
		return MsgBox::Create(yes_only);
	}

	bool MsgBox::Create(bool yes_only)
	{
		ProError		status;
		ProUIGridopts	grid_options;

		status = ProUIDialogCreate(MsgBox::DIALOG, NULL);

		PRO_UI_GRIDOPTS_DEFAULT(grid_options);
		grid_options.row = 0;
		grid_options.column = 0;
		status = ProUIDialogLayoutAdd(MsgBox::DIALOG, MsgBox::LAYOUT1, &grid_options);	

		status = ProUILayoutLabelAdd(MsgBox::DIALOG, MsgBox::LAYOUT1, MsgBox::LABEL1, &grid_options);
		status = ProUILabelTopoffsetSet(MsgBox::DIALOG, MsgBox::LABEL1, 10);
		status = ProUILabelBottomoffsetSet(MsgBox::DIALOG, MsgBox::LABEL1, 10);

		grid_options.row = 1;
		grid_options.column = 0;
		status = ProUIDialogLayoutAdd(MsgBox::DIALOG, MsgBox::LAYOUT2, &grid_options);	

		if (yes_only)
		{
			MsgBox::Create1();
			status = ProUILayoutUndecorate(MsgBox::DIALOG, MsgBox::LAYOUT1);
			status = ProUILayoutUndecorate(MsgBox::DIALOG, MsgBox::LAYOUT2);
		}
		else
		{
			MsgBox::Create2();
			status = ProUILayoutUndecorate(MsgBox::DIALOG, MsgBox::LAYOUT1);
			status = ProUILayoutUndecorate(MsgBox::DIALOG, MsgBox::LAYOUT2);
			status = ProUILayoutUndecorate(MsgBox::DIALOG, MsgBox::LAYOUT3);
			status = ProUILayoutUndecorate(MsgBox::DIALOG, MsgBox::LAYOUT4);
		}

		status = ProUIDialogHeightSet(MsgBox::DIALOG, 100);
		status = ProUIDialogWidthSet(MsgBox::DIALOG, 400);

		return true;
	}

	bool MsgBox::Create1()
	{
		ProError		status;
		ProUIGridopts	grid_options;

		PRO_UI_GRIDOPTS_DEFAULT(grid_options);

		status = ProUILayoutPushbuttonAdd(MsgBox::DIALOG, MsgBox::LAYOUT2, MsgBox::BUTTON_YES,  &grid_options);
		status = ProUIPushbuttonTextSet(MsgBox::DIALOG, MsgBox::BUTTON_YES, L"YES");
		status = ProUIPushbuttonSizeSet(MsgBox::DIALOG, MsgBox::BUTTON_YES, 100, 24);
		status = ProUIPushbuttonBottomoffsetSet(MsgBox::DIALOG, MsgBox::BUTTON_YES, 4);
		status = ProUIPushbuttonTopoffsetSet(MsgBox::DIALOG, MsgBox::BUTTON_YES, 4);
		status = ProUIPushbuttonLeftoffsetSet(MsgBox::DIALOG, MsgBox::BUTTON_YES, 24);
		status = ProUIPushbuttonRightoffsetSet(MsgBox::DIALOG, MsgBox::BUTTON_YES, 24);
		status = ProUIPushbuttonUnattachTop(MsgBox::DIALOG, MsgBox::BUTTON_YES);
		status = ProUIPushbuttonUnattachBottom(MsgBox::DIALOG, MsgBox::BUTTON_YES);

		return true;
	}

	bool MsgBox::Create2()
	{
		ProError		status;
		ProUIGridopts	grid_options;

		PRO_UI_GRIDOPTS_DEFAULT(grid_options);

		grid_options.row = 0;
		grid_options.column = 0;
		status = ProUILayoutLayoutAdd(MsgBox::DIALOG, MsgBox::LAYOUT2, MsgBox::LAYOUT3, &grid_options);

		grid_options.row = 0;
		grid_options.column = 1;
		status = ProUILayoutLayoutAdd(MsgBox::DIALOG, MsgBox::LAYOUT2, MsgBox::LAYOUT4, &grid_options);

		status = ProUILayoutPushbuttonAdd(MsgBox::DIALOG, MsgBox::LAYOUT3, MsgBox::BUTTON_YES,  &grid_options);
		status = ProUIPushbuttonTextSet(MsgBox::DIALOG, MsgBox::BUTTON_YES, L"YES");
		status = ProUIPushbuttonSizeSet(MsgBox::DIALOG, MsgBox::BUTTON_YES, 100, 24);
		status = ProUIPushbuttonBottomoffsetSet(MsgBox::DIALOG, MsgBox::BUTTON_YES, 4);
		status = ProUIPushbuttonTopoffsetSet(MsgBox::DIALOG, MsgBox::BUTTON_YES, 4);
		status = ProUIPushbuttonLeftoffsetSet(MsgBox::DIALOG, MsgBox::BUTTON_YES, 24);
		status = ProUIPushbuttonRightoffsetSet(MsgBox::DIALOG, MsgBox::BUTTON_YES, 24);
		status = ProUIPushbuttonUnattachTop(MsgBox::DIALOG, MsgBox::BUTTON_YES);
		status = ProUIPushbuttonUnattachBottom(MsgBox::DIALOG, MsgBox::BUTTON_YES);

		status = ProUILayoutPushbuttonAdd(MsgBox::DIALOG, MsgBox::LAYOUT4, MsgBox::BUTTON_NO,  &grid_options);
		status = ProUIPushbuttonTextSet(MsgBox::DIALOG, MsgBox::BUTTON_NO, L"NO");
		status = ProUIPushbuttonSizeSet(MsgBox::DIALOG, MsgBox::BUTTON_NO, 100, 24);
		status = ProUIPushbuttonBottomoffsetSet(MsgBox::DIALOG, MsgBox::BUTTON_NO, 4);
		status = ProUIPushbuttonTopoffsetSet(MsgBox::DIALOG, MsgBox::BUTTON_NO, 4);
		status = ProUIPushbuttonLeftoffsetSet(MsgBox::DIALOG, MsgBox::BUTTON_NO, 24);
		status = ProUIPushbuttonRightoffsetSet(MsgBox::DIALOG, MsgBox::BUTTON_NO, 24);
		status = ProUIPushbuttonUnattachTop(MsgBox::DIALOG, MsgBox::BUTTON_NO);
		status = ProUIPushbuttonUnattachBottom(MsgBox::DIALOG, MsgBox::BUTTON_NO);

		return true;
	}

	static ProError ButtonOKPressed(char* dialog, char* component, ProAppData data)
	{
		ProError status;

		status = ProUIDialogExit(dialog, PRO_TK_NO_ERROR);
		return status; 
	}

	static ProError ButtonNoPressed(char* dialog, char* component, ProAppData data)
	{
		ProError status;

		status = ProUIDialogExit(dialog, PRO_TK_GENERAL_ERROR);
		return status; 
	}

	bool MsgBox::Show(const wchar_t *w_title, const wchar_t *w_text, bool yes_only)
	{
		ProError		status;
		int				error;
		ProPath			w_title1, w_text1;

		MsgBox::Initialize(yes_only);

		wcscpy(w_title1, w_title);
		wcscpy(w_text1, w_text);

		status = ProUIDialogTitleSet(MsgBox::DIALOG, w_title1);
		status = ProUILabelTextSet(MsgBox::DIALOG, MsgBox::LABEL1, w_text1);

		status = ProUIDialogCloseActionSet(MsgBox::DIALOG,(ProUIAction)ButtonOKPressed, NULL);
		status = ProUIPushbuttonActivateActionSet(MsgBox::DIALOG, MsgBox::BUTTON_YES,(ProUIAction)ButtonOKPressed, NULL);
		status = ProUIPushbuttonActivateActionSet(MsgBox::DIALOG,MsgBox::BUTTON_NO,(ProUIAction)ButtonNoPressed, NULL);

		//typedef enum
		//{
		//	PROUIDIALOGSTYLE_MENU_MODAL = 0,
		//	PROUIDIALOGSTYLE_MODELESS =1,
		//	PROUIDIALOGSTYLE_PARENT_MODAL =2,
		//	PROUIDIALOGSTYLE_APPLICATION_MODAL =3,
		//	PROUIDIALOGSTYLE_MESSAGE_MODELESS =4,
		//	PROUIDIALOGSTYLE_MENU_MODELESS =5,
		//	PROUIDIALOGSTYLE_WORKING =6
		//}ProUIDialogStyle;

		status = ProUIDialogDialogstyleSet(MsgBox::DIALOG, PROUIDIALOGSTYLE_MENU_MODAL);
		status = ProUIDialogActivate(MsgBox::DIALOG, &error);
		status = ProUIDialogDestroy(MsgBox::DIALOG);

		if (error == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}