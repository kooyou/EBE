#pragma once
#include "SymbolReplaceSetDlg.h"

class CFormat
{
public:
	CFormat(void);
	virtual ~CFormat(void);
	void DelSpaceLines(CRichEditView* pRichEditView);//ɾ���������
	void UnionFontSize(CRichEditView* pRichEditView,CFont* pfont);//ͳһ����
	void DelUselessSpaces(CRichEditView* pRichEditView);//ɾ������Ŀո�
	void ChangeLineAuto(CRichEditView* pRichEditView);//�Զ�����
	void DelFrontSpaces(CRichEditView* pRichEditView);//ɾ��ѡ�����ݵ���ǰ�ո�
	void ReplaceKeySymbol(CSymbolReplaceSetDlg* pSymbolReplaceSetDlg, CRichEditView* pRichEditView);//�滻��Ӧ�ı�����

};
