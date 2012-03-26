#pragma once

#include <vector>
// CCSSListCtrl

class CCSSListCtrl : public CMFCListCtrl
{
	DECLARE_DYNAMIC(CCSSListCtrl)

public:
	CCSSListCtrl();
	virtual ~CCSSListCtrl();
	void GetDataFromTxt();
	void ChangeDataFromModelTxt(CString ModelFilePath);
	std::vector<CString> GetCssFromFile(CString modelFileName);

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);

private:
	std::vector<CString> m_vecCssStyle;
};


