// MisprintManageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EBE.h"
#include "MisprintManageDlg.h"
#include <locale>
#include <vector>


// CMisprintManageDlg �Ի���

IMPLEMENT_DYNAMIC(CMisprintManageDlg, CDialog)

CMisprintManageDlg::CMisprintManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMisprintManageDlg::IDD, pParent)
{

}

CMisprintManageDlg::~CMisprintManageDlg()
{
}

void CMisprintManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MISPRINT_LIST, m_misprintListCtrl);
}


BEGIN_MESSAGE_MAP(CMisprintManageDlg, CDialog)
	ON_BN_CLICKED(IDC_DEL_MISPRINT, &CMisprintManageDlg::OnBnClickedDelMisprint)
END_MESSAGE_MAP()


// CMisprintManageDlg ��Ϣ�������

BOOL CMisprintManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_misprintListCtrl.ModifyStyle(0,LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL);
	m_misprintListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_misprintListCtrl.InsertColumn(0,_T("�����ַ�"),LVCFMT_CENTER,150);
	m_misprintListCtrl.InsertColumn(1,_T("�滻�ַ�"),LVCFMT_LEFT,150);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMisprintManageDlg::OnBnClickedDelMisprint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_misprintListCtrl.GetSelectedCount()<1)
		return;
	int selMark=m_misprintListCtrl.GetSelectionMark();
	CString selItemTxt=m_misprintListCtrl.GetItemText(selMark,0);
	m_misprintListCtrl.DeleteItem(selMark);
	
	RemoveMisprint(selItemTxt);
}

//������
void CMisprintManageDlg::OnMisprintCheck(CRichEditView* pRichEditView)
{
	this->m_misprintManage.MisprintTip(pRichEditView);
}

//��Ӵ���
void CMisprintManageDlg::OnMisprintAddmisprint(CString AddMisprint)
{
	this->m_misprintManage.AddMisprint(AddMisprint);
}

//���ô����б�ؼ�
void CMisprintManageDlg::SetMisprintSet()
{
	//�����趨
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//�趨

	CStdioFile misprintLibFile;
	//���ļ���ȡ��Ϣ
	if(!misprintLibFile.Open(m_misprintManage.m_libFileName,CFile::modeRead))
		return;

	m_misprintListCtrl.DeleteAllItems();
	CString rString;
	while(misprintLibFile.ReadString(rString))
	{
		m_misprintListCtrl.InsertItem(0,rString);
	}
	
	misprintLibFile.Close();
	//�ָ������趨
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//��ԭ�����趨

	ShowWindow(SW_NORMAL);
}

//�Ƴ���������
void CMisprintManageDlg::RemoveMisprint(CString misprintString)
{
	std::vector<CString> eachLine;
	//�����趨
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//�趨

	CStdioFile misprintLibFile;
	//���ļ���ȡ��Ϣ
	if(!misprintLibFile.Open(m_misprintManage.m_libFileName,CFile::modeRead))
		return;
	CString rString;
	while(misprintLibFile.ReadString(rString))
	{
		if(0!=misprintString.Compare(rString)){
			eachLine.push_back(rString);
		}
	}
	misprintLibFile.Close();

	//�������ļ�д������
	if(!misprintLibFile.Open(m_misprintManage.m_libFileName,CFile::modeCreate|CFile::modeWrite))
		return;

	for(int i=0;i<(int)eachLine.size();i++){
		misprintLibFile.WriteString(eachLine[i]);
		misprintLibFile.WriteString(_T("\n"));
	}
	misprintLibFile.Close();

	//ɾ�����������е��ַ���
	for(std::vector<CString>::iterator index=eachLine.begin();
		index!=eachLine.end();index++){
			if(misprintString.Compare(*index)!=0){
				eachLine.erase(index);
				break;
			}
	}

	//�ָ������趨
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//��ԭ�����趨

}