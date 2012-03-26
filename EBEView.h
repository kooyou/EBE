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

// EBEView.h : CMainRichEditView ��Ľӿ�
//

#pragma once

#include "ReplaceSetDlg.h"
#include "StyleManageSuper.h"
#include "MisprintManage.h"
#include "MisprintAddDlg.h"
#include "PropertyManage.h"
#include "MisprintManageDlg.h"

class CEBECntrItem;
class CEBEDoc;

class CMainRichEditView : public CRichEditView
{
protected: // �������л�����
	CMainRichEditView();
	DECLARE_DYNCREATE(CMainRichEditView)

// ����
public:
	CEBEDoc* GetDocument() const;

	CReplaceSetDlg m_repSetDlg;
	StyleManageSuper* m_pStyleManageSuper;
	MisprintManage m_misprintManage;
	CMisprintAddDlg m_misprintDlg;
	CPropertyManage* m_pPropertyManage;
	CMisprintManageDlg m_misprintManageDlg;

//����
private:
	HACCEL hAccel;//��ݼ�

// ����
public:
	void AddStyle(int ADD_TYPE,CString styleStr);
	void WriteText(CString text);

	void ReplaceAll(CString FindStr,CString ReplaceStr, BOOL IsFullword, BOOL IsCapitzlization);
	void NewOpenAutoRun();

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMainRichEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnDestroy();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReplaceListAll();
	afx_msg void OnFormat();
	afx_msg void OnBrowserBtn();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnReplacelistSet();
	afx_msg void OnFormatDelspacelines();
	afx_msg void OnDeluselessspaces();
	afx_msg void OnUnionfontsize();
	afx_msg void OnChangelinesauto();
	afx_msg void OnDelfrontspaces();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRMenu();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMisprintCheck();

	afx_msg void OnMisprintAddmisprint();
	afx_msg void OnMisprintSet();
	afx_msg void OnOutputHtml();
	afx_msg void OnGbtobig5();
	afx_msg void OnBig5togb();
	afx_msg void OnChnengSymbolReplace();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#ifndef _DEBUG  // EBEView.cpp �еĵ��԰汾
inline CEBEDoc* CMainRichEditView::GetDocument() const
   { return reinterpret_cast<CEBEDoc*>(m_pDocument); } 
#endif

