#pragma once
#include "Resource.h"
#include "afxwin.h"

// CSymbolReplaceSetDlg ¶Ô»°¿ò

class CSymbolReplaceSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSymbolReplaceSetDlg)

public:
	CSymbolReplaceSetDlg(CWnd* pParent = NULL);   // ±ê×¼¹¹Ôìº¯Êý
	virtual ~CSymbolReplaceSetDlg();

// ¶Ô»°¿òÊý¾Ý
	enum { IDD = IDD_SYMBOL_REPLACE_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö

	DECLARE_MESSAGE_MAP()
public:

	// ¶ººÅ
	BOOL m_Symbol1;
	// ¾äºÅ
	BOOL m_Symbol2;
	// ·ÖºÅ
	BOOL m_Symbol3;
	// Ã°ºÅ
	BOOL m_Symbol4;
	// ²¨ÀËºÅ
	BOOL m_Symbol5;
	// ÆÆÕÛºÅ
	BOOL m_Symbol6;
	// À¨ºÅ
	BOOL m_Symbol7;
	// µ¥ÆÆÕÛºÅ
	BOOL m_Symbol8;

private:
	CBrush m_brush;
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	// È«ÎÄÌæ»»»¹ÊÇ²¿·ÖÌæ»»
	int m_nSelect;
	// Ë«ÆÆÕÛºÅÌæ»»
	BOOL m_IsDoubleDash;
	afx_msg void OnBnClickedDoubleDash();
	// Ë«ÆÆÕÛºÅÌæ»»×Ö·û´®
	CEdit m_doubleDashEdit;
	// ·ÖºÅ
	CString m_editString3;
	// ¶ººÅ
	CString m_editString1;
	// ¾äºÅ
	CString m_editString2;
	// Ã°ºÅ
	CString m_editString4;
	// ²¨ÀËºÅ
	CString m_editString5;
	// ÆÆÕÛºÅ
	CString m_editString6;
	// µ¥ÆÆÕÛºÅ
	CString m_editString8;
	// À¨ºÅ
	CString m_editString7;
};
