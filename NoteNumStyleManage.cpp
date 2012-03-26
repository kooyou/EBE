#include "StdAfx.h"
#include "NoteNumStyleManage.h"

NoteNumStyleManage::NoteNumStyleManage(void)
{
}

NoteNumStyleManage::~NoteNumStyleManage(void)
{
}

void NoteNumStyleManage::addStyle(CString styleStr, CRichEditView *pRichEditView)
{
	CRichEditCtrl* pRichEditCtrl=&pRichEditView->GetRichEditCtrl();

	CString noteNumStyle=_T("<**##**>");//��ʶע�ͷ�
	if(pRichEditCtrl->GetSelText().GetLength()>0){
		long selStart,selEnd;
		pRichEditCtrl->GetSel(selStart,selEnd);
		noteNumStyle.Replace(_T("##"),pRichEditCtrl->GetSelText());
		//��Ϊע��������
		CHARFORMAT cf;
		pRichEditCtrl->GetSelectionCharFormat(cf);
		cf.yHeight=175;//��ʶ��С(��ʶ����������ע�͵����ָ߶�Ϊ175)
		cf.crTextColor=RGB(0,0,255);
		pRichEditCtrl->ReplaceSel(noteNumStyle);
		pRichEditCtrl->SetSel(selStart,selStart+noteNumStyle.GetLength());
		pRichEditCtrl->SetSelectionCharFormat(cf);
	}
}