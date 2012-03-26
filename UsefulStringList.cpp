// UsefulStringList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EBE.h"
#include "UsefulStringList.h"
#include <locale>


// CUsefulStringList

IMPLEMENT_DYNAMIC(CUsefulStringList, CMFCListCtrl)

CUsefulStringList::CUsefulStringList()
{
	 m_nItem=-1;
	 m_nSubItem=-1;
}

CUsefulStringList::~CUsefulStringList()
{
}


BEGIN_MESSAGE_MAP(CUsefulStringList, CMFCListCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CUsefulStringList::OnNMDblclk)
	ON_WM_CLOSE()
END_MESSAGE_MAP()



// CUsefulStringList ��Ϣ�������



BOOL CUsefulStringList::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(CMFCListCtrl::Create(dwStyle, rect, pParentWnd, nID)){
		ModifyStyle(0,LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL);
		SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		InsertColumn(0,_T("�����ַ���"),LVCFMT_LEFT,200);
		InsertColumn(1,_T("��ݼ�"),LVCFMT_LEFT,70);

		//���ļ��л�ȡ����
		GetDataFromTxt();

		//�����ɱ༭Item�õ���Edit�ؼ�
		CRect rc;
		int style = WS_CHILD | WS_CLIPSIBLINGS | WS_EX_TOOLWINDOW | WS_BORDER;
		if(m_edit.Create(style, rc, this, ID_LIST_EDIT)==FALSE )
			return FALSE;
		m_edit.m_hWndOwner=this->m_hWnd;

		return TRUE;
	}
	return FALSE;
}

void CUsefulStringList::GetDataFromTxt()
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

	//���ļ��ж�ȡ��ǰ����Ϣ

	CStdioFile fOftenUseList;
	m_fPath.Format(_T("%s//oftenUseList.txt"),sIniFilePath);
	if(fOftenUseList.Open(m_fPath,CFile::modeRead)){
		CString readStr;
		CString shortcut;
		if(fOftenUseList.ReadString(readStr)){
			int strNum;
			strNum=_wtoi(readStr);
			for(int i=1;i<=strNum;i++){
				fOftenUseList.ReadString(readStr);
				InsertItem(i-1,readStr);
				if(i<=9){
				//��ݼ�
				shortcut.Format(_T("Ctrl+%d"),i);
				}
				else{
					shortcut=_T("�޿�ݼ�");
				}
				this->SetItemText(i-1,1,shortcut);
			}
		}
		fOftenUseList.Close();
	}
	//�ָ������趨
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//��ԭ�����趨
}

CString CUsefulStringList::GetItemTextFromShortcut(int nItem)
{
	if(nItem>this->GetItemCount())
		return _T("");
	return this->GetItemText(nItem,0);
}


void CUsefulStringList::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
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

	//�ڶ��в��ܱ༭
	if(1==m_nSubItem)
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


void CUsefulStringList::ItemEditEnd()
{
	CString txtItem;
    m_edit.GetWindowText( txtItem );
    SetItemText(m_nItem, m_nSubItem, txtItem);
}
void CUsefulStringList::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//�趨

	//���泣���ַ����б�
	CStdioFile fOftenUseList;
	if(fOftenUseList.Open(m_fPath,CFile::modeWrite)){
		int lineNum;
		CString itemStr;
		lineNum=GetItemCount();
		itemStr.Format(_T("%d"),lineNum);
		fOftenUseList.WriteString(itemStr);//д������
		fOftenUseList.WriteString(_T("\n"));
		for(int i=0;i<lineNum;i++){
			itemStr=GetItemText(i,0);
			fOftenUseList.WriteString(itemStr);
			fOftenUseList.WriteString(_T("\n"));
		}
		fOftenUseList.Close();
	}
	//�ָ������趨
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//��ԭ�����趨
}
