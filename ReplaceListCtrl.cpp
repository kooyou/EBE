// ReplaceListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EBE.h"
#include "ReplaceListCtrl.h"

#include <locale.h>				//�������


// CReplaceListCtrl

IMPLEMENT_DYNAMIC(CReplaceListCtrl, CMFCListCtrl)

CReplaceListCtrl::CReplaceListCtrl()
{

}

CReplaceListCtrl::~CReplaceListCtrl()
{
}


BEGIN_MESSAGE_MAP(CReplaceListCtrl, CMFCListCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CReplaceListCtrl::OnNMDblclk)
	ON_WM_CLOSE()
END_MESSAGE_MAP()



// CReplaceListCtrl ��Ϣ�������



BOOL CReplaceListCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(CMFCListCtrl::Create(dwStyle, rect, pParentWnd, nID)){
		//�����б�ؼ�����ʽ
		this->ModifyStyle(0,LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL);
		this->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
		CString strTemp;
		ASSERT(strTemp.LoadString(IDS_REPLACELIST_SELECTED));
		this->InsertColumn(0,strTemp,LVCFMT_LEFT,40);
		ASSERT(strTemp.LoadString(IDS_REPLACELIST_FINDSTRING));
		this->InsertColumn(1,strTemp,LVCFMT_LEFT,100);
		ASSERT(strTemp.LoadString(IDS_REPLACELIST_REPLACESTRING));
		this->InsertColumn(2,strTemp,LVCFMT_LEFT,100);
		this->CheckAutoCenter();
	
		//��ؼ�д������
		GetDataFromTxt();

		//�����ɱ༭Item�õ���Edit�ؼ�
		CRect rc;
		int style = WS_CHILD | WS_CLIPSIBLINGS | WS_EX_TOOLWINDOW | WS_BORDER;
		if(m_edit.Create(style, rc, this, ID_LIST_EDIT)==FALSE )
			return FALSE;
		m_edit.m_hWndOwner=this->m_hWnd;

		return TRUE;
	}
	else
		return FALSE;
}

// ��txt�ļ��ж�ȡ��Ӧ�����ݲ�д��list�ؼ�
bool CReplaceListCtrl::GetDataFromTxt(void)
{

	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//�趨

	//��õ�ǰ��ִ���ļ���·��  
	CString sModFileName; 
	GetModuleFileName(NULL,sModFileName.GetBuffer(MAX_PATH),MAX_PATH);
	sModFileName.ReleaseBuffer(); 
	sModFileName.MakeReverse(); 
	CString sIniFilePath;
	sIniFilePath=sModFileName.Right(sModFileName.GetLength()-sModFileName.Find( '\\')); 
	sIniFilePath.MakeReverse();

	//���ļ��ж�ȡ����
	CStdioFile fReplaceList;
	m_fPath.Format(_T("%s//replaceList.txt"),sIniFilePath);
	if(fReplaceList.Open(m_fPath,CFile::modeRead)){
		CString readStr;
		if(fReplaceList.ReadString(readStr)){
			int strNum;
			strNum=_wtoi(readStr);
			for(int i=0;i<strNum;i++){
				fReplaceList.ReadString(readStr);
				InsertItem(i,_T(""));
				if(readStr.Compare(_T("checked"))==0){
					SetCheck(i,true);
				}
				else{
					SetCheck(i,false);
				}
				fReplaceList.ReadString(readStr);
				SetItemText(i,1,readStr);
				fReplaceList.ReadString(readStr);
				SetItemText(i,2,readStr);
			}
		}
		fReplaceList.Close();
	}

	//�ָ������趨
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//��ԭ�����趨
	return false;
}

void CReplaceListCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//û��ѡ��Item
	if(this->GetSelectedCount()<=0)
		return;

	//��ӱ༭��
	CRect rc;
	m_nItem=pNMItemActivate->iItem;
	//m_rowΪ��ѡ���е�����ţ�int���ͳ�Ա������
	m_nSubItem=pNMItemActivate->iSubItem;
	//m_columnΪ��ѡ���е�����ţ�int���ͳ�Ա������

	//��һ�в��ܱ༭
	if(0==m_nSubItem)
		return;

	GetSubItemRect(pNMItemActivate->iItem, 
		pNMItemActivate->iSubItem,LVIR_LABEL,rc);
	//ȡ������ľ���
	rc.left+=3;
	rc.top+=2;
	rc.right+=3;
	rc.bottom+=2;
	wchar_t * ch=new wchar_t [128];
	GetItemText(pNMItemActivate->iItem, pNMItemActivate->iSubItem,ch,128);
	//ȡ�����������
	m_edit.SetWindowText(ch);//�������������ʾ���༭����
	m_edit.ShowWindow(SW_SHOW);//��ʾ�༭��
	m_edit.MoveWindow(&rc);//���༭���ƶ����������棬������������
	m_edit.SetFocus();//ʹ�༭��ȡ�ý���
	m_edit.CreateSolidCaret(1,rc.Height()-5);//����һ�����
	m_edit.ShowCaret();//��ʾ���
	m_edit.SetSel(-1);//ʹ����Ƶ������

	*pResult = 0;
}

void CReplaceListCtrl::ItemEditEnd()
{
	CString txtItem;
    m_edit.GetWindowText(txtItem );
    SetItemText(m_nItem, m_nSubItem, txtItem);
}
void CReplaceListCtrl::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//�趨

	//�����ַ����滻�б�
	CStdioFile fReplaceList;
	if(fReplaceList.Open(m_fPath,CFile::modeWrite)){
		int lineNum;
		CString itemStr;
		lineNum=this->GetItemCount();
		itemStr.Format(_T("%d"),lineNum);
		fReplaceList.WriteString(itemStr);//д������
		fReplaceList.WriteString(_T("\n"));
		for(int i=0;i<lineNum;i++){
			if(this->GetCheck(i)){
				itemStr=_T("checked");
			}
			else{
				itemStr=_T("nochecked");
			}

			fReplaceList.WriteString(itemStr);
			fReplaceList.WriteString(_T("\n"));
			itemStr=GetItemText(i,1);
			fReplaceList.WriteString(itemStr);
			fReplaceList.WriteString(_T("\n"));
			itemStr=GetItemText(i,2);
			fReplaceList.WriteString(itemStr);
			fReplaceList.WriteString(_T("\n"));
		}
		fReplaceList.Close();
	}

	//�ָ������趨
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//��ԭ�����趨
}
