// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// EBEView.h : CMainRichEditView 类的接口
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
protected: // 仅从序列化创建
	CMainRichEditView();
	DECLARE_DYNCREATE(CMainRichEditView)

// 属性
public:
	CEBEDoc* GetDocument() const;

	CReplaceSetDlg m_repSetDlg;
	StyleManageSuper* m_pStyleManageSuper;
	MisprintManage m_misprintManage;
	CMisprintAddDlg m_misprintDlg;
	CPropertyManage* m_pPropertyManage;
	CMisprintManageDlg m_misprintManageDlg;

//属性
private:
	HACCEL hAccel;//快捷键

// 操作
public:
	void AddStyle(int ADD_TYPE,CString styleStr);
	void WriteText(CString text);

	void ReplaceAll(CString FindStr,CString ReplaceStr, BOOL IsFullword, BOOL IsCapitzlization);
	void NewOpenAutoRun();

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMainRichEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // EBEView.cpp 中的调试版本
inline CEBEDoc* CMainRichEditView::GetDocument() const
   { return reinterpret_cast<CEBEDoc*>(m_pDocument); } 
#endif

