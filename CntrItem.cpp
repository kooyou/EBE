// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

// CntrItem.cpp : CEBECntrItem ���ʵ��
//

#include "stdafx.h"
#include "EBE.h"

#include "EBEDoc.h"
#include "EBEView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEBECntrItem ��ʵ��

IMPLEMENT_SERIAL(CEBECntrItem, CRichEditCntrItem, 0)

CEBECntrItem::CEBECntrItem(REOBJECT* preo, CEBEDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: �ڴ����һ���Թ������
}

CEBECntrItem::~CEBECntrItem()
{
	// TODO: �ڴ˴�����������
}


// CEBECntrItem ���

#ifdef _DEBUG
void CEBECntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CEBECntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

