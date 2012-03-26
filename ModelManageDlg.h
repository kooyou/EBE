#pragma once
#include "afxcmn.h"


// CModelManageDlg �Ի���

class CModelManageDlg : public CDialog
{
	DECLARE_DYNAMIC(CModelManageDlg)

public:
	CModelManageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModelManageDlg();

// �Ի�������
	enum { IDD = IDD_MODEL_MANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_modelListCtrl;
	afx_msg void OnBnClickedModelDel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedManagefileOpen();
};
