#pragma once


// CItemEditCtrl

class CItemEditCtrl : public CEdit
{
	DECLARE_DYNAMIC(CItemEditCtrl)

public:
	CItemEditCtrl();
	virtual ~CItemEditCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


