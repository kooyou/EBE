#pragma once

#include "ItemEditCtrl.h"
// CReplaceListCtrl

class CReplaceListCtrl : public CMFCListCtrl
{
	DECLARE_DYNAMIC(CReplaceListCtrl)

public:
	CReplaceListCtrl();
	virtual ~CReplaceListCtrl();
	
	// 从txt文件中读取相应的数据并写入list控件
	bool GetDataFromTxt(void);
	void ItemEditEnd();

public:
	CItemEditCtrl m_edit;
	int m_nItem;
	int m_nSubItem;

private:
	CString m_fPath;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
};


