#pragma once


// CReplaceSetDlg 对话框

class CReplaceSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CReplaceSetDlg)

public:
	CReplaceSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReplaceSetDlg();

// 对话框数据
	enum { IDD = IDD_REPLACESETDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 全字匹配
	BOOL m_fullword;
	// 大小写匹配
	BOOL m_capitzlization;
	BOOL m_IsAutoReplace;
};
