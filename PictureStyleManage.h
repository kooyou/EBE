#pragma once
#include "stylemanagesuper.h"

enum{PICTURE_START=1,PICTURE_END};

class PictureStyleManage :
	public StyleManageSuper
{
public:
	PictureStyleManage(void);
	~PictureStyleManage(void);

public:
	void AddPictureStyle(int type,CRichEditView* pRichEditView);
	//void AddStyle(CString styleString, CRichEditView *pRichEditView);
};
