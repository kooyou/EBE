// CSSListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "EBE.h"
#include "CSSListCtrl.h"
#include "EBEView.h"
#include "MainFrm.h"

#include <locale>


// CCSSListCtrl

IMPLEMENT_DYNAMIC(CCSSListCtrl, CMFCListCtrl)

CCSSListCtrl::CCSSListCtrl()
{

}

CCSSListCtrl::~CCSSListCtrl()
{
}


BEGIN_MESSAGE_MAP(CCSSListCtrl, CMFCListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CCSSListCtrl::OnNMClick)
END_MESSAGE_MAP()



// CCSSListCtrl 消息处理程序



BOOL CCSSListCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(CMFCListCtrl::Create(dwStyle, rect, pParentWnd, nID)){
		ModifyStyle(0,LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL);
		SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		CString strTemp;
		ASSERT(strTemp.LoadString(IDS_CSSLISTCTRLCOLUM1));
		InsertColumn(0,_T("CSS"),LVCFMT_LEFT,100);
		InsertColumn(1,_T("Style"),LVCFMT_LEFT,500);

		//载入数据
		GetDataFromTxt();
		return TRUE;
	}
	return FALSE;
}

void CCSSListCtrl::GetDataFromTxt()
{
	/*
	//读取数据
	CStdioFile fCssList;
	if(fCssList.Open(_T("CssList.txt"),CFile::modeRead)){
		CString readStr;
		if(fCssList.ReadString(readStr)){
			int strNum;
			strNum=_wtoi(readStr);
			for(int i=0;i<strNum;i++){
				fCssList.ReadString(readStr);
				InsertItem(i,readStr);
			}
		}
		fCssList.Close();
	}*/
}

void CCSSListCtrl::ChangeDataFromModelTxt(CString ModelFilePath)
{
	std::vector<CString> vecCss=GetCssFromFile(ModelFilePath);
	this->DeleteAllItems();
	for(int i=0;i<(int)vecCss.size();i++){
		InsertItem(i-1,vecCss[i]);
		SetItemText(i-1,1,m_vecCssStyle[i]);
	}
	UpdateData();
}

std::vector<CString> CCSSListCtrl::GetCssFromFile(CString modelFileName)
{
	//区域设定
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//设定

	m_vecCssStyle.clear();

	std::vector<CString> vecCss;
	CStdioFile file;
	if(!file.Open(modelFileName,CFile::modeRead))
		return vecCss;
	CString readLine;
	bool IsStyle=false;
	while(file.ReadString(readLine))
	{
		if(readLine.Find(_T("<style"))!=-1)
			IsStyle=true;
		if(readLine.Find(_T("</style>"))!=-1){
			IsStyle=false;
			break;
		}
		if(IsStyle){
			int pos=readLine.Find(_T("{"));
			int posEnd=readLine.Find(_T("}"));
			CString cssStyle=readLine.Left(posEnd);
			cssStyle=readLine.Right(posEnd-pos);
			m_vecCssStyle.push_back(cssStyle);

			CString css=readLine.Left(pos);
			css.Replace(_T("."),_T(""));
			vecCss.push_back(css);
		}
	}
	file.Close();

	//恢复区域设定
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定

	return vecCss;
}
void CCSSListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int selItem=this->GetSelectionMark();
	CString selText=this->GetItemText(selItem,0);
	
	CMainRichEditView* pview;
	pview=(CMainRichEditView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveFrame()->GetActiveView();
	if(NULL==pview)
		return;
	pview->AddStyle(SECTIONSTYLE,selText);
	*pResult = 0;
}

