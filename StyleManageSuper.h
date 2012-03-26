#pragma once

enum{SECTIONSTYLE=1,LINESTYLE=2,NOTE=3};

class StyleManageSuper
{
public:
	StyleManageSuper(void);
	virtual ~StyleManageSuper(void);

public:
	void virtual addStyle(CString styleStr,CRichEditView* pRichEditView);
};
