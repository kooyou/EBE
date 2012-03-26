// ModelManageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EBE.h"
#include "ModelManageDlg.h"
#include "MainFrm.h"


// CModelManageDlg �Ի���

IMPLEMENT_DYNAMIC(CModelManageDlg, CDialog)

CModelManageDlg::CModelManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModelManageDlg::IDD, pParent)
{

}

CModelManageDlg::~CModelManageDlg()
{
}

void CModelManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODEL_LIST, m_modelListCtrl);
}


BEGIN_MESSAGE_MAP(CModelManageDlg, CDialog)
	ON_BN_CLICKED(IDC_MODEL_DEL, &CModelManageDlg::OnBnClickedModelDel)
	ON_BN_CLICKED(IDOK, &CModelManageDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_MANAGEFILE_OPEN, &CModelManageDlg::OnBnClickedManagefileOpen)
END_MESSAGE_MAP()


// CModelManageDlg ��Ϣ�������

void CModelManageDlg::OnBnClickedModelDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int delItem=this->m_modelListCtrl.GetSelectionMark();
	CString modelFile=m_modelListCtrl.GetItemText(delItem,1);
	this->m_modelListCtrl.DeleteItem(delItem);
	((CMainFrame*)AfxGetApp()->GetMainWnd())->m_mapModel.DelModel(modelFile);
}

void CModelManageDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CMainFrame*)AfxGetApp()->GetMainWnd())->RefreshModelProList();
	OnOK();
}


void CModelManageDlg::OnBnClickedManagefileOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int delItem=this->m_modelListCtrl.GetSelectionMark();
	if(delItem>0){
		CString modelFile=m_modelListCtrl.GetItemText(delItem,1);
		((CMainFrame*)AfxGetApp()->GetMainWnd())->
			m_mapModel.OpenModelFile(modelFile);
	}
}
