#pragma once
#include "stylemanagesuper.h"

class SectionStyleManage :
	public StyleManageSuper
{
public:
	SectionStyleManage(void);
	~SectionStyleManage(void);

public:
	void addStyle(CString styleStr,CRichEditView* pRichEditView);
};
