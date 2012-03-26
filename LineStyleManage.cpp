#include "StdAfx.h"
#include "LineStyleManage.h"

LineStyleManage::LineStyleManage(void)
{
}

LineStyleManage::~LineStyleManage(void)
{
}

void LineStyleManage::addStyle(CString styleStr,CRichEditView* pRichEditView)
{
}

void LineStyleManage::addLineStyle(int styleType, CRichEditView *pRichEditView)
{
	switch(styleType){
		case STYLE_NOBR:
			addNOBR(pRichEditView);
			break;
		case STYLE_LETTERSPACE:
			addLETTERSPACE(pRichEditView);
			break;
		case STYLE_EM:
			addEM(pRichEditView);
			break;
		case STYLE_SPACE:
			addSpace(pRichEditView);
			break;
		default:
			break;
	}
}

void LineStyleManage::addSpace(CRichEditView *pRichEditView)
{
	CRichEditCtrl* pRichEditCtrl=&pRichEditView->GetRichEditCtrl();
	long selStart,selEnd;
	pRichEditCtrl->GetSel(selStart,selEnd);
	pRichEditCtrl->ReplaceSel(_T("&nbsp;"));
	pRichEditCtrl->SetSel(selStart,selStart+6);
	CHARFORMAT cf;
	pRichEditCtrl->GetSelectionCharFormat(cf);
	cf.yHeight=184;//��ʶ��С
	wcscpy_s(cf.szFaceName,_T("����"));//����Ϊ����
	cf.crTextColor=RGB(0,0,255);//��ɫΪ��ɫ
	pRichEditCtrl->SetSelectionCharFormat(cf);
}


void LineStyleManage::addNOBR(CRichEditView *pRichEditView)
{
	//��ʶ��ǰ����Ҫ���nobr��ǩ
	CRichEditCtrl* pRichEditCtrl=&pRichEditView->GetRichEditCtrl();
	long selStart,selEnd;
	pRichEditCtrl->GetSel(selStart,selEnd);
	long lineIndex=pRichEditCtrl->LineFromChar(selStart);
	long indexOfline=pRichEditCtrl->LineIndex(lineIndex+1);
	pRichEditCtrl->SetSel(indexOfline-1,
								indexOfline-1);
	pRichEditCtrl->ReplaceSel(_T("<nobr>"));
	pRichEditCtrl->SetSel(indexOfline-1,indexOfline+5);
	CHARFORMAT cf;
	pRichEditCtrl->GetSelectionCharFormat(cf);
	cf.yHeight=184;//��ʶ��С
	wcscpy_s(cf.szFaceName,_T("����"));//����Ϊ����
	cf.crTextColor=RGB(0,0,255);//��ɫΪ��ɫ
	pRichEditCtrl->SetSelectionCharFormat(cf);
}

void LineStyleManage::addLETTERSPACE(CRichEditView *pRichEditView)
{
	CRichEditCtrl* pRichEditCtrl=&pRichEditView->GetRichEditCtrl();

	long selStart,selEnd;
	pRichEditCtrl->GetSel(selStart,selEnd);
	long lineIndex=pRichEditCtrl->LineFromChar(selStart);
	long indexOfline=pRichEditCtrl->LineIndex(lineIndex+1);
	pRichEditCtrl->SetSel(indexOfline-1,indexOfline-1);
	CString let=_T("<LS=-1>");
	pRichEditCtrl->ReplaceSel(let);
	pRichEditCtrl->SetSel(indexOfline-1,indexOfline-1+let.GetLength());
	CHARFORMAT cf;
	pRichEditCtrl->GetSelectionCharFormat(cf);
	cf.dwMask=CFM_COLOR|CFM_SIZE;
	cf.yHeight=180;//��ʶ��С
	wcscpy_s(cf.szFaceName,_T("����"));//����Ϊ����
	cf.crTextColor=RGB(0,0,255);//��ɫΪ��ɫ
	pRichEditCtrl->SetSelectionCharFormat(cf);
}

//���б����ʽ<em>
void LineStyleManage::addEM(CRichEditView *pRichEditView)
{
	CRichEditCtrl* pRichEditCtrl=&pRichEditView->GetRichEditCtrl();

	long selStart,selEnd;
	pRichEditCtrl->GetSel(selStart,selEnd);

	CString styleStrBegin=_T("<em>");
	CString styleStrEnd=_T("</em>");

	//��ӿ�ʼ��ǩ
	pRichEditCtrl->SetSel(selStart,selStart);
	pRichEditCtrl->ReplaceSel(styleStrBegin);
	pRichEditCtrl->SetSel(selStart,selEnd+styleStrBegin.GetLength());
	CHARFORMAT cf;
	pRichEditCtrl->GetSelectionCharFormat(cf);
	cf.dwMask=CFM_COLOR|CFM_SIZE;
	cf.yHeight=180;//��ʶ��С
	wcscpy_s(cf.szFaceName,_T("����"));//����Ϊ����
	cf.crTextColor=RGB(0,0,255);//��ɫΪ��ɫ
	pRichEditCtrl->SetSelectionCharFormat(cf);

	selEnd=selEnd+styleStrBegin.GetLength();//���������ı�
	//��ӽ�����ǩ
	pRichEditCtrl->SetSel(selEnd,selEnd);
	pRichEditCtrl->ReplaceSel(styleStrEnd);
	pRichEditCtrl->SetSel(selEnd,selEnd+styleStrEnd.GetLength());
	pRichEditCtrl->GetSelectionCharFormat(cf);
	cf.dwMask=CFM_COLOR|CFM_SIZE;
	cf.yHeight=180;//��ʶ��С
	wcscpy_s(cf.szFaceName,_T("����"));//����Ϊ����
	cf.crTextColor=RGB(0,0,255);//��ɫΪ��ɫ
	pRichEditCtrl->SetSelectionCharFormat(cf);
	selEnd=selEnd+styleStrEnd.GetLength();//���������ı�

	//�ж��Ƿ���
	long index=selStart;
	long EachLineIndex=pRichEditCtrl->LineIndex(selStart);
	long lastLineIndex=pRichEditCtrl->LineIndex(selStart);
	while(index<selEnd){
		EachLineIndex=pRichEditCtrl->LineIndex(index++);
		if(EachLineIndex>selEnd)
			break;//�����˳�ѭ�����ж�
		if(EachLineIndex>lastLineIndex){//�µ�һ�У�����±�ǩ
			//��ӿ�ʼ��ǩ
			pRichEditCtrl->SetSel(EachLineIndex,EachLineIndex);
			pRichEditCtrl->ReplaceSel(styleStrBegin);
			pRichEditCtrl->SetSel(EachLineIndex,EachLineIndex+
					styleStrBegin.GetLength());
			pRichEditCtrl->GetSelectionCharFormat(cf);
			cf.dwMask=CFM_COLOR|CFM_SIZE;
			cf.yHeight=180;//��ʶ��С
			wcscpy_s(cf.szFaceName,_T("����"));//����Ϊ����
			cf.crTextColor=RGB(0,0,255);//��ɫΪ��ɫ
			pRichEditCtrl->SetSelectionCharFormat(cf);

			selEnd=selEnd+styleStrBegin.GetLength();//���������ı�
			//��ӽ�����ǩ
			pRichEditCtrl->SetSel(EachLineIndex-1,EachLineIndex-1);
			pRichEditCtrl->ReplaceSel(styleStrEnd);
			pRichEditCtrl->SetSel(EachLineIndex-1,EachLineIndex-1+
						styleStrEnd.GetLength());
			pRichEditCtrl->GetSelectionCharFormat(cf);
			cf.dwMask=CFM_COLOR|CFM_SIZE;
			cf.yHeight=180;//��ʶ��С
			wcscpy_s(cf.szFaceName,_T("����"));//����Ϊ����
			cf.crTextColor=RGB(0,0,255);//��ɫΪ��ɫ
			pRichEditCtrl->SetSelectionCharFormat(cf);

			selEnd=selEnd+styleStrEnd.GetLength();//���������ı�

			lastLineIndex=EachLineIndex;
		}
	}
}