#pragma once


// CNoteModelDlg �Ի���

class CNoteModelDlg : public CDialog
{
	DECLARE_DYNAMIC(CNoteModelDlg)

public:
	CNoteModelDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNoteModelDlg();

// �Ի�������
	enum { IDD = IDD_NOTE_STYLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ѡ�е�ע��ģ��
	int m_noteModelSelect;
	CString m_filePath;

public:
	//����
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
