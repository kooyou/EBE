// MisprintManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EBE.h"
#include "MisprintManageDlg.h"
#include <locale>
#include <vector>


// CMisprintManageDlg 对话框

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


// CMisprintManageDlg 消息处理程序

BOOL CMisprintManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_misprintListCtrl.ModifyStyle(0,LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL);
	m_misprintListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_misprintListCtrl.InsertColumn(0,_T("错误字符"),LVCFMT_CENTER,150);
	m_misprintListCtrl.InsertColumn(1,_T("替换字符"),LVCFMT_LEFT,150);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CMisprintManageDlg::OnBnClickedDelMisprint()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_misprintListCtrl.GetSelectedCount()<1)
		return;
	int selMark=m_misprintListCtrl.GetSelectionMark();
	CString selItemTxt=m_misprintListCtrl.GetItemText(selMark,0);
	m_misprintListCtrl.DeleteItem(selMark);
	
	RemoveMisprint(selItemTxt);
}

//错误检测
void CMisprintManageDlg::OnMisprintCheck(CRichEditView* pRichEditView)
{
	this->m_misprintManage.MisprintTip(pRichEditView);
}

//添加错字
void CMisprintManageDlg::OnMisprintAddmisprint(CString AddMisprint)
{
	this->m_misprintManage.AddMisprint(AddMisprint);
}

//设置错字列表控件
void CMisprintManageDlg::SetMisprintSet()
{
	//区域设定
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//设定

	CStdioFile misprintLibFile;
	//从文件读取信息
	if(!misprintLibFile.Open(m_misprintManage.m_libFileName,CFile::modeRead))
		return;

	m_misprintListCtrl.DeleteAllItems();
	CString rString;
	while(misprintLibFile.ReadString(rString))
	{
		m_misprintListCtrl.InsertItem(0,rString);
	}
	
	misprintLibFile.Close();
	//恢复区域设定
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定

	ShowWindow(SW_NORMAL);
}

//移除错字条项
void CMisprintManageDlg::RemoveMisprint(CString misprintString)
{
	std::vector<CString> eachLine;
	//区域设定
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//设定

	CStdioFile misprintLibFile;
	//从文件读取信息
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

	//重新向文件写入数据
	if(!misprintLibFile.Open(m_misprintManage.m_libFileName,CFile::modeCreate|CFile::modeWrite))
		return;

	for(int i=0;i<(int)eachLine.size();i++){
		misprintLibFile.WriteString(eachLine[i]);
		misprintLibFile.WriteString(_T("\n"));
	}
	misprintLibFile.Close();

	//删除错误容器中的字符串
	for(std::vector<CString>::iterator index=eachLine.begin();
		index!=eachLine.end();index++){
			if(misprintString.Compare(*index)!=0){
				eachLine.erase(index);
				break;
			}
	}

	//恢复区域设定
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定

}