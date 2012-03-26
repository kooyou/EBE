// SymbolReplaceSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EBE.h"
#include "SymbolReplaceSetDlg.h"


// CSymbolReplaceSetDlg �Ի���

IMPLEMENT_DYNAMIC(CSymbolReplaceSetDlg, CDialog)

CSymbolReplaceSetDlg::CSymbolReplaceSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSymbolReplaceSetDlg::IDD, pParent)
	, m_Symbol1(TRUE)
	, m_Symbol2(TRUE)
	, m_Symbol3(TRUE)
	, m_Symbol4(TRUE)
	, m_Symbol5(TRUE)
	, m_Symbol6(TRUE)
	, m_Symbol7(TRUE)
	, m_Symbol8(TRUE)
	, m_nSelect(0)
	, m_IsDoubleDash(TRUE)
	, m_editString3(_T(""))
	, m_editString1(_T(""))
	, m_editString2(_T(""))
	, m_editString4(_T(""))
	, m_editString5(_T(""))
	, m_editString6(_T(""))
	, m_editString8(_T(""))
	, m_editString7(_T(""))
{

}

CSymbolReplaceSetDlg::~CSymbolReplaceSetDlg()
{
}

void CSymbolReplaceSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_Symbol1);
	DDX_Check(pDX, IDC_CHECK2, m_Symbol2);
	DDX_Check(pDX, IDC_CHECK3, m_Symbol3);
	DDX_Check(pDX, IDC_CHECK4, m_Symbol4);
	DDX_Check(pDX, IDC_CHECK5, m_Symbol5);
	DDX_Check(pDX, IDC_CHECK6, m_Symbol6);
	DDX_Check(pDX, IDC_CHECK7, m_Symbol7);
	DDX_Check(pDX, IDC_CHECK8, m_Symbol8);
	DDX_Radio(pDX, IDC_ALLTEXT, m_nSelect);
	DDX_Check(pDX, IDC_CHECK9, m_IsDoubleDash);
	DDX_Control(pDX, IDC_DOUBLE_DASH, m_doubleDashEdit);
	DDX_Text(pDX, IDC_EDIT3, m_editString3);
	DDX_Text(pDX, IDC_EDIT1, m_editString1);
	DDX_Text(pDX, IDC_EDIT2, m_editString2);
	DDX_Text(pDX, IDC_EDIT4, m_editString4);
	DDX_Text(pDX, IDC_EDIT5, m_editString5);
	DDX_Text(pDX, IDC_EDIT6, m_editString6);
	DDX_Text(pDX, IDC_EDIT8, m_editString8);
	DDX_Text(pDX, IDC_EDIT7, m_editString7);
}


BEGIN_MESSAGE_MAP(CSymbolReplaceSetDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK9, &CSymbolReplaceSetDlg::OnBnClickedDoubleDash)
END_MESSAGE_MAP()


// CSymbolReplaceSetDlg ��Ϣ�������

BOOL CSymbolReplaceSetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_brush.CreateSolidBrush(RGB(255,255,255));


	//����˫���ۺ��滻�ַ���
	m_doubleDashEdit.SetWindowTextW(
		_T("<b style=\"letter-spacing:-5px;\">����</b>"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

HBRUSH CSymbolReplaceSetDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	//
	//return hbr;
	return m_brush;
}

void CSymbolReplaceSetDlg::OnBnClickedDoubleDash()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(TRUE==m_IsDoubleDash){
		this->m_doubleDashEdit.EnableWindow(TRUE);
	}
	else{
		this->m_doubleDashEdit.EnableWindow(FALSE);
	}
}
