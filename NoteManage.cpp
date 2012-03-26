#include "StdAfx.h"
#include "NoteManage.h"

NoteManage::NoteManage(void)
{
}

NoteManage::~NoteManage(void)
{
}

void NoteManage::addStyle(CString styleStr, CRichEditView *pRichEditView)
{
	CRichEditCtrl* pRichEditCtrl=&pRichEditView->GetRichEditCtrl();
	long selStart,selEnd;
	CString tableEnd=_T("**ע��**");
	pRichEditCtrl->GetSel(selStart,selEnd);
	pRichEditCtrl->SetSel(selStart,selStart);
	pRichEditCtrl->ReplaceSel(tableEnd);
	pRichEditCtrl->SetSel(selStart,selStart+tableEnd.GetLength());
	CHARFORMAT cf;
	pRichEditCtrl->GetSelectionCharFormat(cf);
	cf.yHeight=210;//��ʶ��С(��ʶ���ı�ʶ���ָ߶�Ϊ210)
	wcscpy_s(cf.szFaceName,_T("����"));//����Ϊ����
	cf.crTextColor=RGB(0,0,255);//��ɫΪ��ɫ
	pRichEditCtrl->SetSelectionCharFormat(cf);
}