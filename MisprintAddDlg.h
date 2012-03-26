#pragma once


// CMisprintAddDlg 对话框

class CMisprintAddDlg : public CDialog
{
	DECLARE_DYNAMIC(CMisprintAddDlg)

public:
	CMisprintAddDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMisprintAddDlg();

// 对话框数据
	enum { IDD = IDD_ADDMISPRINT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 错字
	CString m_misprintString;
	// 替换字符串
	CString m_replaceString;
protected:
	virtual void OnOK();
};
