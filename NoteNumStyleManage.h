#pragma once
#include "stylemanagesuper.h"

class NoteNumStyleManage :
	public StyleManageSuper
{
public:
	NoteNumStyleManage(void);
	~NoteNumStyleManage(void);

public:
	void addStyle(CString styleStr, CRichEditView *pRichEditView);
};
