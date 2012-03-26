// ReplaceListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "EBE.h"
#include "ReplaceListCtrl.h"

#include <locale.h>				//局域化设计


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



// CReplaceListCtrl 消息处理程序



BOOL CReplaceListCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(CMFCListCtrl::Create(dwStyle, rect, pParentWnd, nID)){
		//设置列表控件的样式
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
	
		//向控件写入数据
		GetDataFromTxt();

		//创建可编辑Item用到的Edit控件
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

// 从txt文件中读取相应的数据并写入list控件
bool CReplaceListCtrl::GetDataFromTxt(void)
{

	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//设定

	//获得当前可执行文件的路径  
	CString sModFileName; 
	GetModuleFileName(NULL,sModFileName.GetBuffer(MAX_PATH),MAX_PATH);
	sModFileName.ReleaseBuffer(); 
	sModFileName.MakeReverse(); 
	CString sIniFilePath;
	sIniFilePath=sModFileName.Right(sModFileName.GetLength()-sModFileName.Find( '\\')); 
	sIniFilePath.MakeReverse();

	//从文件中读取数据
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

	//恢复区域设定
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定
	return false;
}

void CReplaceListCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	//没有选择Item
	if(this->GetSelectedCount()<=0)
		return;

	//添加编辑框
	CRect rc;
	m_nItem=pNMItemActivate->iItem;
	//m_row为被选中行的行序号（int类型成员变量）
	m_nSubItem=pNMItemActivate->iSubItem;
	//m_column为被选中行的列序号（int类型成员变量）

	//第一列不能编辑
	if(0==m_nSubItem)
		return;

	GetSubItemRect(pNMItemActivate->iItem, 
		pNMItemActivate->iSubItem,LVIR_LABEL,rc);
	//取得子项的矩形
	rc.left+=3;
	rc.top+=2;
	rc.right+=3;
	rc.bottom+=2;
	wchar_t * ch=new wchar_t [128];
	GetItemText(pNMItemActivate->iItem, pNMItemActivate->iSubItem,ch,128);
	//取得子项的内容
	m_edit.SetWindowText(ch);//将子项的内容显示到编辑框中
	m_edit.ShowWindow(SW_SHOW);//显示编辑框
	m_edit.MoveWindow(&rc);//将编辑框移动到子项上面，覆盖在子项上
	m_edit.SetFocus();//使编辑框取得焦点
	m_edit.CreateSolidCaret(1,rc.Height()-5);//创建一个光标
	m_edit.ShowCaret();//显示光标
	m_edit.SetSel(-1);//使光标移到最后面

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
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//设定

	//保存字符串替换列表
	CStdioFile fReplaceList;
	if(fReplaceList.Open(m_fPath,CFile::modeWrite)){
		int lineNum;
		CString itemStr;
		lineNum=this->GetItemCount();
		itemStr.Format(_T("%d"),lineNum);
		fReplaceList.WriteString(itemStr);//写入行数
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

	//恢复区域设定
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定
}
