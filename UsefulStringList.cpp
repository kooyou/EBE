// UsefulStringList.cpp : 实现文件
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



// CUsefulStringList 消息处理程序



BOOL CUsefulStringList::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(CMFCListCtrl::Create(dwStyle, rect, pParentWnd, nID)){
		ModifyStyle(0,LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL);
		SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		InsertColumn(0,_T("常用字符串"),LVCFMT_LEFT,200);
		InsertColumn(1,_T("快捷键"),LVCFMT_LEFT,70);

		//从文件中获取数据
		GetDataFromTxt();

		//创建可编辑Item用到的Edit控件
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
	setlocale( LC_CTYPE, "chs" );//设定

	//获得当前可执行文件的路径  
	CString sModFileName; 
	GetModuleFileName(NULL,sModFileName.GetBuffer(MAX_PATH),MAX_PATH);
	sModFileName.ReleaseBuffer(); 
	sModFileName.MakeReverse(); 
	CString sIniFilePath;
	sIniFilePath=sModFileName.Right(sModFileName.GetLength()-sModFileName.Find( '\\')); 
	sIniFilePath.MakeReverse();

	//从文件中读取以前的信息

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
				//快捷键
				shortcut.Format(_T("Ctrl+%d"),i);
				}
				else{
					shortcut=_T("无快捷键");
				}
				this->SetItemText(i-1,1,shortcut);
			}
		}
		fOftenUseList.Close();
	}
	//恢复区域设定
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定
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

	//第二列不能编辑
	if(1==m_nSubItem)
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


void CUsefulStringList::ItemEditEnd()
{
	CString txtItem;
    m_edit.GetWindowText( txtItem );
    SetItemText(m_nItem, m_nSubItem, txtItem);
}
void CUsefulStringList::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//设定

	//保存常用字符串列表
	CStdioFile fOftenUseList;
	if(fOftenUseList.Open(m_fPath,CFile::modeWrite)){
		int lineNum;
		CString itemStr;
		lineNum=GetItemCount();
		itemStr.Format(_T("%d"),lineNum);
		fOftenUseList.WriteString(itemStr);//写入行数
		fOftenUseList.WriteString(_T("\n"));
		for(int i=0;i<lineNum;i++){
			itemStr=GetItemText(i,0);
			fOftenUseList.WriteString(itemStr);
			fOftenUseList.WriteString(_T("\n"));
		}
		fOftenUseList.Close();
	}
	//恢复区域设定
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定
}
