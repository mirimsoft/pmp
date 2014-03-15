#include "stdafx.h"
#include "TableCompNames.h"


TableCompNames::TableCompNames(char *name)
{
	strcpy_s(this->row_name, name);
	sprintf_s(this->cb_name, "CB_%s", name);
	sprintf_s(this->ip_name, "IP_%s", name);
	sprintf_s(this->lb_name, "LB_%s", name);
	sprintf_s(this->om_name, "OM_%s", name);
}

TableCompNames::TableCompNames(int row_index)
{
	sprintf_s(this->row_name, "%d", row_index);
	sprintf_s(this->cb_name, "CB_%d", row_index);
	sprintf_s(this->ip_name, "IP_%d", row_index);
	sprintf_s(this->lb_name, "LB_%d", row_index);
	sprintf_s(this->om_name, "OM_%d", row_index);
}


TableCompNames::~TableCompNames(void)
{
}
