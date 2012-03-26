#pragma once


// CMisprintSetDlg 对话框

class CMisprintSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CMisprintSetDlg)

public:
	CMisprintSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMisprintSetDlg();

// 对话框数据
	enum { IDD = IDD_MISPRINTSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
