#pragma once


// CNoteModelDlg 对话框

class CNoteModelDlg : public CDialog
{
	DECLARE_DYNAMIC(CNoteModelDlg)

public:
	CNoteModelDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNoteModelDlg();

// 对话框数据
	enum { IDD = IDD_NOTE_STYLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 选中的注释模板
	int m_noteModelSelect;
	CString m_filePath;

public:
	//方法
	CString GetNoteFirstLineModel(int noteModelType=-1);
	CString GetNoteSecondLineModel(int noteModelType=-1);
	CString GetNoteThirdLineModel(int noteModelType=-1);

	CString GetFirstModel(int nLine);
	CString GetSecondModel(int nLine);
	CString GetThirdModel(int nLine);

private:
	void InitMineModelFromFile();
	void StoreMineModelToFile();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
