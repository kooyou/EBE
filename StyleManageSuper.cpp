#include "StdAfx.h"
#include "StyleManageSuper.h"

StyleManageSuper::StyleManageSuper(void)
{
}

StyleManageSuper::~StyleManageSuper(void)
{
}

void StyleManageSuper::addStyle(CString styleStr,CRichEditView* pRichEditView)
{
	CRichEditCtrl* pRichEditCtrl=&pRichEditView->GetRichEditCtrl();
	long selStart,selEnd;
	pRichEditCtrl->GetSel(selStart,selEnd);
	pRichEditCtrl->SetSel(selStart,selStart);
	CString picStart=styleStr;
	pRichEditCtrl->ReplaceSel(picStart);
	pRichEditCtrl->SetSel(selStart,selStart+picStart.GetLength());
	CHARFORMAT cf;
	pRichEditCtrl->GetSelectionCharFormat(cf);
	cf.yHeight=210;//标识大小(标识表格的标识文字高度为210)
	wcscpy_s(cf.szFaceName,_T("宋体"));//设置为宋体
	cf.crTextColor=RGB(0,0,255);//颜色为蓝色
	pRichEditCtrl->SetSelectionCharFormat(cf);
}
