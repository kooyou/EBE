#pragma once
#include "afxcmn.h"
#include "Resource.h"
#include "MisprintManage.h"


// CMisprintManageDlg 对话框

class CMisprintManageDlg : public CDialog
{
	DECLARE_DYNAMIC(CMisprintManageDlg)

public:
	CMisprintManageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMisprintManageDlg();

// 对话框数据
	enum { IDD = IDD_MisprintManageDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 错字列表
	CListCtrl m_misprintListCtrl;
	afx_msg void OnBnClickedDelMisprint();
	virtual BOOL OnInitDialog();

	void OnMisprintCheck(CRichEditView* pRichEditView);
	void OnMisprintAddmisprint(CString AddMisprint);

	void SetMisprintSet();

private:
	void RemoveMisprint(CString misprintString);

private:
	MisprintManage m_misprintManage;
};
