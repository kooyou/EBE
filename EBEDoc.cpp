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

// EBEDoc.cpp : CEBEDoc ���ʵ��
//

#include "stdafx.h"
#include "EBE.h"

#include "EBEDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEBEDoc

IMPLEMENT_DYNCREATE(CEBEDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CEBEDoc, CRichEditDoc)
	// ����Ĭ�ϵ� OLE ����ʵ��
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, &CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()


// CEBEDoc ����/����

CEBEDoc::CEBEDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CEBEDoc::~CEBEDoc()
{
}

BOOL CEBEDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}

CRichEditCntrItem* CEBEDoc::CreateClientItem(REOBJECT* preo) const
{
	return new CEBECntrItem(preo, const_cast<CEBEDoc*>(this));
}




// CEBEDoc ���л�

void CEBEDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}

	// ���û��� CRichEditDoc ������
	//  �����ĵ��� COleClientItem ��������л���
	// TODO: �����Ϊ�ı��������л��������� CRichEditDoc::m_bRTF = FALSE
	CString fileStyle=ar.GetFile()->GetFileName().Right(3);
	if(fileStyle.Compare(_T("txt"))==0){
		this->m_bRTF=FALSE;//��TXT
	}
	else{
		this->m_bRTF=TRUE;//��RTF
	}

	CRichEditDoc::Serialize(ar);
}


// CEBEDoc ���

#ifdef _DEBUG
void CEBEDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CEBEDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG


// CEBEDoc ����
