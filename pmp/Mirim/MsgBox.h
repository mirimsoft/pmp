#pragma once
#include "ProTk.h"

namespace Mirim
{
	class MsgBox
	{
	private:
		static char DIALOG[32];
		static char LAYOUT1[32];
		static char LAYOUT2[32];
		static char LAYOUT3[32];
		static char LAYOUT4[32];
		static char BUTTON_YES[32];
		static char BUTTON_NO[32];
		static char LABEL1[32];

	public:
		static bool MsgBox::Show(const wchar_t *w_title, const wchar_t *w_text, bool yes_only = true);

	private:
		static bool MsgBox::Initialize(bool yes_only = true);
		static bool MsgBox::Create(bool yes_only);
		static bool MsgBox::Create1();
		static bool MsgBox::Create2();
	};
}