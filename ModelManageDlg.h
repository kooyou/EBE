#pragma once
#include "afxcmn.h"


// CModelManageDlg 对话框

class CModelManageDlg : public CDialog
{
	DECLARE_DYNAMIC(CModelManageDlg)

public:
	CModelManageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModelManageDlg();

// 对话框数据
	enum { IDD = IDD_MODEL_MANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_modelListCtrl;
	afx_msg void OnBnClickedModelDel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedManagefileOpen();
};
