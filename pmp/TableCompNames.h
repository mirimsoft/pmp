#pragma once
class TableCompNames
{
public:
	char row_name[32];
	char lb_name[32];
	char ip_name[32];
	char om_name[32];
	char cb_name[32];
public:
	TableCompNames(char *name);
	TableCompNames(int row_index);
	~TableCompNames(void);
};

