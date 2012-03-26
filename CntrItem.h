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

// CntrItem.h : CEBECntrItem ��Ľӿ�
//

#pragma once

class CEBEDoc;
class CMainRichEditView;

class CEBECntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CEBECntrItem)

// ���캯��
public:
	CEBECntrItem(REOBJECT* preo = NULL, CEBEDoc* pContainer = NULL);
		// ע��: ���� pContainer Ϊ NULL ������ IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE Ҫ������д���
		//  �����Ĺ��캯����OLE ��ͨ������
		//  �� NULL �ĵ�ָ�빹���

// ����
public:
	CEBEDoc* GetDocument()
		{ return reinterpret_cast<CEBEDoc*>(CRichEditCntrItem::GetDocument()); }
	CMainRichEditView* GetActiveView()
		{ return reinterpret_cast<CMainRichEditView*>(CRichEditCntrItem::GetActiveView()); }

// ʵ��
public:
	~CEBECntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

