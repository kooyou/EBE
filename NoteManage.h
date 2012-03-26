#pragma once
#include "stylemanagesuper.h"

class NoteManage :
	public StyleManageSuper
{
public:
	NoteManage(void);
	~NoteManage(void);

public:
	void addStyle(CString styleStr, CRichEditView *pRichEditView);
};
