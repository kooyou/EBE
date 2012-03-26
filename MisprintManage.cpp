#include "StdAfx.h"
#include "MisprintManage.h"
#include "MainFrm.h"
#include "EBEView.h"

#include <locale>

MisprintManage::MisprintManage(void)
{
	CreateMisprintTipLib();
	GetMisprintLibFromFile();

}

MisprintManage::~MisprintManage(void)
{
}

//�����滻�б�����滻
void MisprintManage::replaceListAll(CRichEditView* pRichEditView)
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CMainRichEditView* pMainRichEditView=(CMainRichEditView*)pRichEditView;
	CString FindStr;
	CString ReplaceStr;
	//��ȡ�滻�б������ݲ��滻
	for(int i=0;i<pFrame->m_replaceListCtrl.GetItemCount();i++)
		if(pFrame->m_replaceListCtrl.GetCheck(i)){
			FindStr=pFrame->m_replaceListCtrl.GetItemText(i,1);
			ReplaceStr=pFrame->m_replaceListCtrl.GetItemText(i,2);
			//����ϵͳ��ȫ���滻����
			pMainRichEditView->ReplaceAll(FindStr, ReplaceStr, 
				pMainRichEditView->m_repSetDlg.m_fullword,
				pMainRichEditView->m_repSetDlg.m_capitzlization);
		}
}

void MisprintManage::MisprintTip(CRichEditView *pRichEditView)
{
	//Ϊ�˶����ͼ��Ӵ��������ô��ֿ�ͬ����
	//����ÿ��ִ�д��ּ��ʱ�����¶�ȡ���ֿ��ļ���
	//���Ǹ��۳�ķ���
	this->GetMisprintLibFromFile();

	//������ʾ
	CMainRichEditView* pMainRichEditView=(CMainRichEditView*)pRichEditView;
	CRichEditCtrl* pRichEditCtrl=&pRichEditView->GetRichEditCtrl();
	CString strFind;
	for(std::vector<CString>::iterator i=m_vecMisprintLib.begin();
		i!=m_vecMisprintLib.end();i++){

		pRichEditCtrl->SetSel(0,0);
		strFind=*i;
		while(0!=pMainRichEditView->FindText(strFind,FALSE,FALSE,TRUE)){
				CHARFORMAT cf;
				pRichEditCtrl->GetSelectionCharFormat(cf);
				cf.dwMask|=CFM_UNDERLINE;
				cf.dwEffects|=CFE_UNDERLINE;//�����»���
				cf.crTextColor=RGB(255,0,0);
				pRichEditCtrl->SetSelectionCharFormat(cf);
		}
	}
}

bool MisprintManage::CreateMisprintTipLib()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CString bookName=pFrame->m_wndProperties.m_pHtmlProperty->GetBookName();
	bookName.TrimLeft(_T(" "));
	bookName.TrimRight(_T(" "));

	//��õ�ǰ��ִ���ļ���·��  
	CString sModFileName; 
	GetModuleFileName(NULL,sModFileName.GetBuffer(MAX_PATH),MAX_PATH);
	sModFileName.ReleaseBuffer(); 
	sModFileName.MakeReverse(); 
	CString sIniFilePath;
	sIniFilePath=sModFileName.Right(sModFileName.GetLength()-sModFileName.Find( '\\')); 
	sIniFilePath.MakeReverse();

	//��ǰ·�����½��ļ�����
	CString newFileName=sIniFilePath+bookName;

	if(!PathFileExists(newFileName)){
		//�����ļ���
		if(!CreateDirectory(newFileName,NULL)) {
			AfxMessageBox(_T("�����ļ���ʧ��!"));
			return false;
		}
	}
	if(!PathFileExists(newFileName+_T("\\system"))){
		if(!CreateDirectory(newFileName+_T("\\system"),NULL)) {
			AfxMessageBox(_T("�����ļ���ʧ��!"));
			return false;
		}
	}
	//���ֿ��ļ���
	m_libFileName.Format(_T("%s\\system\\%s_���ֿ�.txt"),newFileName,bookName);

	try{
		if(!PathFileExists(m_libFileName)){
			m_misprintLibFile.Open(m_libFileName,CFile::modeCreate);
			m_misprintLibFile.Close();
		}
	}
	catch(CFileException fe)
	{
		AfxMessageBox(_T("�������ֿ��ļ�ʧ��!"));
		return false;
	}
	return true;
}

//�Ӵ��ֿ��ж�ȡ����
void MisprintManage::GetMisprintLibFromFile()
{
	//�����趨
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//�趨
	if(!m_misprintLibFile.Open(m_libFileName,CFile::modeRead))
		return;

	CString rString;
	m_vecMisprintLib.clear();
	while(m_misprintLibFile.ReadString(rString))
	{
		m_vecMisprintLib.push_back(rString);
	}
	m_misprintLibFile.Close();

	//�ָ������趨
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//��ԭ�����趨
}

//��Ӵ���
void MisprintManage::AddMisprint(CString addString)
{
	//�����趨
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//�趨

	m_vecMisprintLib.push_back(addString);
	try{
		m_misprintLibFile.Open(m_libFileName,CFile::modeWrite);
	}
	catch(CFileException fc){
		AfxMessageBox(_T("�򿪴��ֿ��ļ�ʧ��!"));
	}
	m_misprintLibFile.SeekToEnd();
	m_misprintLibFile.WriteString(_T("\n"));
	m_misprintLibFile.WriteString(addString);
	m_misprintLibFile.Close();

	//�ָ������趨
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//��ԭ�����趨
}

/*
void MisprintManage::SetMisprintLib()
{
	//�����趨
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//�趨

	//���ļ���ȡ��Ϣ
	if(!m_misprintLibFile.Open(m_libFileName,CFile::modeRead))
		return;

	m_misprintManageDlg.m_misprintListCtrl.DeleteAllItems();
	CString rString;
	while(m_misprintLibFile.ReadString(rString))
	{
		m_misprintManageDlg.m_misprintListCtrl.InsertItem(0,rString);
	}
	m_misprintManageDlg.ShowWindow(SW_NORMAL);
	
	m_misprintLibFile.Close();
	//�ָ������趨
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//��ԭ�����趨
}
*/