#pragma once
#include "stylemanagesuper.h"

enum{STYLE_NOBR=1,STYLE_LETTERSPACE,STYLE_EM,STYLE_SPACE};

class LineStyleManage :
	public StyleManageSuper
{
public:
	LineStyleManage(void);
	~LineStyleManage(void);

public:
	void addStyle(CString styleStr,CRichEditView* pRichEditView);
	void addLineStyle(int styleType,CRichEditView* pRichEditView);

private:
	void addNOBR(CRichEditView* pRichEditView);
	void addLETTERSPACE(CRichEditView *pRichEditView);
	void addEM(CRichEditView* pRichEditView);
	void addSpace(CRichEditView* pRichEditView);
};
