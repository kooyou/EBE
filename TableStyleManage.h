#pragma once
#include "stylemanagesuper.h"

enum{TABLE_START=1,TABLE_END};

class TableStyleManage :
	public StyleManageSuper
{
public:
	TableStyleManage(void);
	~TableStyleManage(void);
public:
	void AddTalbeStyle(int tableType,CRichEditView* pRichEditView);
	//virtual AddStyle(CString styleString,CRichEditView* pRichEditView);
};
