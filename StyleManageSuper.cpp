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
	cf.yHeight=210;//��ʶ��С(��ʶ���ı�ʶ���ָ߶�Ϊ210)
	wcscpy_s(cf.szFaceName,_T("����"));//����Ϊ����
	cf.crTextColor=RGB(0,0,255);//��ɫΪ��ɫ
	pRichEditCtrl->SetSelectionCharFormat(cf);
}
