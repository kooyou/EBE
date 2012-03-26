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

//根据替换列表进行替换
void MisprintManage::replaceListAll(CRichEditView* pRichEditView)
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CMainRichEditView* pMainRichEditView=(CMainRichEditView*)pRichEditView;
	CString FindStr;
	CString ReplaceStr;
	//获取替换列表中数据并替换
	for(int i=0;i<pFrame->m_replaceListCtrl.GetItemCount();i++)
		if(pFrame->m_replaceListCtrl.GetCheck(i)){
			FindStr=pFrame->m_replaceListCtrl.GetItemText(i,1);
			ReplaceStr=pFrame->m_replaceListCtrl.GetItemText(i,2);
			//调用系统的全部替换函数
			pMainRichEditView->ReplaceAll(FindStr, ReplaceStr, 
				pMainRichEditView->m_repSetDlg.m_fullword,
				pMainRichEditView->m_repSetDlg.m_capitzlization);
		}
}

void MisprintManage::MisprintTip(CRichEditView *pRichEditView)
{
	//为了多个视图添加错字是能让错字库同步，
	//所以每次执行错字检测时都重新读取错字库文件，
	//这是个折冲的方法
	this->GetMisprintLibFromFile();

	//错字提示
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
				cf.dwEffects|=CFE_UNDERLINE;//设置下划线
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

	//获得当前可执行文件的路径  
	CString sModFileName; 
	GetModuleFileName(NULL,sModFileName.GetBuffer(MAX_PATH),MAX_PATH);
	sModFileName.ReleaseBuffer(); 
	sModFileName.MakeReverse(); 
	CString sIniFilePath;
	sIniFilePath=sModFileName.Right(sModFileName.GetLength()-sModFileName.Find( '\\')); 
	sIniFilePath.MakeReverse();

	//当前路径和新建文件夹名
	CString newFileName=sIniFilePath+bookName;

	if(!PathFileExists(newFileName)){
		//创建文件夹
		if(!CreateDirectory(newFileName,NULL)) {
			AfxMessageBox(_T("创建文件夹失败!"));
			return false;
		}
	}
	if(!PathFileExists(newFileName+_T("\\system"))){
		if(!CreateDirectory(newFileName+_T("\\system"),NULL)) {
			AfxMessageBox(_T("创建文件夹失败!"));
			return false;
		}
	}
	//错字库文件名
	m_libFileName.Format(_T("%s\\system\\%s_错字库.txt"),newFileName,bookName);

	try{
		if(!PathFileExists(m_libFileName)){
			m_misprintLibFile.Open(m_libFileName,CFile::modeCreate);
			m_misprintLibFile.Close();
		}
	}
	catch(CFileException fe)
	{
		AfxMessageBox(_T("创建错字库文件失败!"));
		return false;
	}
	return true;
}

//从错字库中读取数据
void MisprintManage::GetMisprintLibFromFile()
{
	//区域设定
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//设定
	if(!m_misprintLibFile.Open(m_libFileName,CFile::modeRead))
		return;

	CString rString;
	m_vecMisprintLib.clear();
	while(m_misprintLibFile.ReadString(rString))
	{
		m_vecMisprintLib.push_back(rString);
	}
	m_misprintLibFile.Close();

	//恢复区域设定
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定
}

//添加错字
void MisprintManage::AddMisprint(CString addString)
{
	//区域设定
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//设定

	m_vecMisprintLib.push_back(addString);
	try{
		m_misprintLibFile.Open(m_libFileName,CFile::modeWrite);
	}
	catch(CFileException fc){
		AfxMessageBox(_T("打开错字库文件失败!"));
	}
	m_misprintLibFile.SeekToEnd();
	m_misprintLibFile.WriteString(_T("\n"));
	m_misprintLibFile.WriteString(addString);
	m_misprintLibFile.Close();

	//恢复区域设定
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定
}

/*
void MisprintManage::SetMisprintLib()
{
	//区域设定
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//设定

	//从文件读取信息
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
	//恢复区域设定
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定
}
*/