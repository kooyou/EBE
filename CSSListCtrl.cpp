// CSSListCtrl.cpp : ʵ���ļ�
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



// CCSSListCtrl ��Ϣ�������



BOOL CCSSListCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(CMFCListCtrl::Create(dwStyle, rect, pParentWnd, nID)){
		ModifyStyle(0,LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL);
		SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		CString strTemp;
		ASSERT(strTemp.LoadString(IDS_CSSLISTCTRLCOLUM1));
		InsertColumn(0,_T("CSS"),LVCFMT_LEFT,100);
		InsertColumn(1,_T("Style"),LVCFMT_LEFT,500);

		//��������
		GetDataFromTxt();
		return TRUE;
	}
	return FALSE;
}

void CCSSListCtrl::GetDataFromTxt()
{
	/*
	//��ȡ����
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
	//�����趨
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//�趨

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

	//�ָ������趨
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//��ԭ�����趨

	return vecCss;
}
void CCSSListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int selItem=this->GetSelectionMark();
	CString selText=this->GetItemText(selItem,0);
	
	CMainRichEditView* pview;
	pview=(CMainRichEditView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveFrame()->GetActiveView();
	if(NULL==pview)
		return;
	pview->AddStyle(SECTIONSTYLE,selText);
	*pResult = 0;
}

