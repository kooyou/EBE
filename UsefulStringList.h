#pragma once

#include "ItemEditCtrl.h"
// CUsefulStringList

class CUsefulStringList : public CMFCListCtrl
{
	DECLARE_DYNAMIC(CUsefulStringList)

public:
	CUsefulStringList();
	virtual ~CUsefulStringList();

public:
	void GetDataFromTxt();
	CString GetItemTextFromShortcut(int nItem);
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


