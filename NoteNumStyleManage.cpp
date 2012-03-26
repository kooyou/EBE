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

	CString noteNumStyle=_T("<**##**>");//标识注释符
	if(pRichEditCtrl->GetSelText().GetLength()>0){
		long selStart,selEnd;
		pRichEditCtrl->GetSel(selStart,selEnd);
		noteNumStyle.Replace(_T("##"),pRichEditCtrl->GetSelText());
		//改为注释码字型
		CHARFORMAT cf;
		pRichEditCtrl->GetSelectionCharFormat(cf);
		cf.yHeight=175;//标识大小(标识阿拉伯数字注释的文字高度为175)
		cf.crTextColor=RGB(0,0,255);
		pRichEditCtrl->ReplaceSel(noteNumStyle);
		pRichEditCtrl->SetSel(selStart,selStart+noteNumStyle.GetLength());
		pRichEditCtrl->SetSelectionCharFormat(cf);
	}
}