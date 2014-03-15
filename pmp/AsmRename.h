#pragma once
#include "ProTk.h"
#include "Table.h"
#include "Model.h"

namespace Gui
{
	class AsmRename
	{
	public:
		AsmRename(void);
		~AsmRename(void);

	public:
		static ProError AsmRename::ShowNames(Table *table, std::vector<Model> &list);
		static ProError AsmRename::SyncNames(Table *table);
		static ProError AsmRename::ApplyNames(Table *table);
	};

}