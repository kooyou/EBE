// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// EBEView.cpp : CMainRichEditView 类的实现
//

#include "stdafx.h"
#include "EBE.h"

#include "EBEDoc.h"
#include "CntrItem.h"
#include "EBEView.h"
#include "MainFrm.h"
#include "Format.h"
#include "SectionStyleManage.h"
#include "LineStyleManage.h"
#include "NoteNumStyleManage.h"
#include "NoteManage.h"
#include "OutputManage.h"
#include "TableStyleManage.h"
#include "PictureStyleManage.h"
#include "GBtoBig5.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainRichEditView

IMPLEMENT_DYNCREATE(CMainRichEditView, CRichEditView)

BEGIN_MESSAGE_MAP(CMainRichEditView, CRichEditView)
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMainRichEditView::OnFilePrintPreview)
	ON_COMMAND(ID_REPLACE_LIST, &CMainRichEditView::OnReplaceListAll)
	ON_COMMAND(ID_REPLACELIST_SET, &CMainRichEditView::OnReplacelistSet)
	ON_COMMAND(IDS_FORMAT,&CMainRichEditView::OnFormat)
	ON_COMMAND(IDS_FORMAT_DELSPACELINES, &CMainRichEditView::OnFormatDelspacelines)
	ON_COMMAND(IDS_DELUSELESSSPACES, &CMainRichEditView::OnDeluselessspaces)
	ON_COMMAND(IDS_UNIONFONTSIZE, &CMainRichEditView::OnUnionfontsize)
	ON_COMMAND(IDS_CHANGELINESAUTO, &CMainRichEditView::OnChangelinesauto)
	ON_COMMAND(IDS_DELFRONTSPACES, &CMainRichEditView::OnDelfrontspaces)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_RMENU_NOBR, &CMainRichEditView::OnRMenu)
	ON_COMMAND(ID_RMENU_LETTERSPACE, &CMainRichEditView::OnRMenu)
	ON_COMMAND(ID_NOTENUM, &CMainRichEditView::OnRMenu)
	ON_COMMAND(ID_RMENU_NOTEBEGIN, &CMainRichEditView::OnRMenu)
	ON_COMMAND(ID_RMENU_EM, &CMainRichEditView::OnRMenu)
	ON_COMMAND(ID_PIC_START,&CMainRichEditView::OnRMenu)
	ON_COMMAND(ID_PIC_END,&CMainRichEditView::OnRMenu)
	ON_COMMAND(ID_TABLE_START,&CMainRichEditView::OnRMenu)
	ON_COMMAND(ID_TABLE_END,&CMainRichEditView::OnRMenu)
	ON_COMMAND(ID_SPACE,&CMainRichEditView::OnRMenu)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDS_MISPRINTMANAGE, &CMainRichEditView::OnMisprintCheck)
	ON_COMMAND(ID_MISPRINT_ADDMISPRINT, &CMainRichEditView::OnMisprintAddmisprint)
	ON_COMMAND(ID_RMENU_ADDMISPRINT, &CMainRichEditView::OnMisprintAddmisprint)
	ON_COMMAND(ID_MISPRINTSET, &CMainRichEditView::OnMisprintSet)
	ON_COMMAND(IDS_OUTPUT_HTML,&CMainRichEditView::OnOutputHtml)
	ON_COMMAND(IDS_HTML_BROWSER_BTN, &CMainRichEditView::OnBrowserBtn)
	ON_COMMAND(ID_GBTOBIG5, &CMainRichEditView::OnGbtobig5)
	ON_COMMAND(ID_BIG5TOGB, &CMainRichEditView::OnBig5togb)
	ON_COMMAND(ID_CHNENG_SYMBOL_REPLACE, &CMainRichEditView::OnChnengSymbolReplace)
END_MESSAGE_MAP()

// CMainRichEditView 构造/析构

CMainRichEditView::CMainRichEditView()
{
	// TODO: 在此处添加构造代码

}

CMainRichEditView::~CMainRichEditView()
{
	m_pPropertyManage=NULL;
}

BOOL CMainRichEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CRichEditView::PreCreateWindow(cs);
}

void CMainRichEditView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// 设置打印边距(720 缇 = 1/2 英寸)
	SetMargins(CRect(720, 720, 720, 720));
}


// CMainRichEditView 打印


void CMainRichEditView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CMainRichEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}


void CMainRichEditView::OnDestroy()
{
	// 析构时停用此项；这在
	// 使用拆分视图时非常重要 
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }

   if(m_pPropertyManage!=NULL)
	   delete m_pPropertyManage;//析构对象

   CRichEditView::OnDestroy();
}


void CMainRichEditView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMainRichEditView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMainRichEditView 诊断

#ifdef _DEBUG
void CMainRichEditView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CMainRichEditView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CEBEDoc* CMainRichEditView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEBEDoc)));
	return (CEBEDoc*)m_pDocument;
}
#endif //_DEBUG


// CMainRichEditView 消息处理程序


void CMainRichEditView::OnReplaceListAll()
{
	MisprintManage misprintManage;
	misprintManage.replaceListAll(this);
}

void CMainRichEditView::OnReplacelistSet()
{
	// TODO: 在此添加命令处理程序代码
	m_repSetDlg.DoModal();
}

void CMainRichEditView::OnFormat()
{
	CFormat format;
	format.DelSpaceLines(this);
	format.DelUselessSpaces(this);
	CFont font;
	VERIFY(font.CreateFont(
		16,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("宋体")));                 // lpszFacename
//	format.UnionFontSize(this,&font);
	format.ChangeLineAuto(this);
}

void CMainRichEditView::OnFormatDelspacelines()
{
	// TODO: 在此添加命令处理程序代码
	CFormat format;
	format.DelSpaceLines(this);
}

void CMainRichEditView::OnDeluselessspaces()
{
	// TODO: 在此添加命令处理程序代码
	CFormat format;
	format.DelUselessSpaces(this);
}

void CMainRichEditView::OnUnionfontsize()
{
	// TODO: 在此添加命令处理程序代码
	CFormat format;
	CFont font;
	VERIFY(font.CreateFont(
		16,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("宋体")));                 // lpszFacename
	format.UnionFontSize(this,&font);
}

void CMainRichEditView::OnChangelinesauto()
{
	// TODO: 在此添加命令处理程序代码
	CFormat format;
	format.ChangeLineAuto(this);
}

void CMainRichEditView::OnDelfrontspaces()
{
	// TODO: 在此添加命令处理程序代码
	CFormat format;
	format.DelFrontSpaces(this);
}

void CMainRichEditView::AddStyle(int ADD_TYPE, CString styleStr)
{
	switch(ADD_TYPE){
		case SECTIONSTYLE:
			this->m_pStyleManageSuper=new SectionStyleManage();
			m_pStyleManageSuper->addStyle(styleStr,this);
			break;
		default:
			break;
	}
	delete m_pStyleManageSuper;
}
//捕获快捷键
void CMainRichEditView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//判断是否是Ctrl+X组合键，
	//如果是则将相应的常用字符列表的文本项复制到视图上
	if(::GetKeyState(VK_CONTROL)<0){
		CString usefulListItemText;
		switch(nChar){
			case '1':
				//获取常用字符串列表中相应的文本
				usefulListItemText=((CMainFrame*)AfxGetApp()->m_pMainWnd)->
					m_usefulStringList.GetItemTextFromShortcut(0);
				break;
			case '2':
				usefulListItemText=((CMainFrame*)AfxGetApp()->m_pMainWnd)->
					m_usefulStringList.GetItemTextFromShortcut(1);
				break;
			case '3':
				usefulListItemText=((CMainFrame*)AfxGetApp()->m_pMainWnd)->
					m_usefulStringList.GetItemTextFromShortcut(2);
				break;
			case '4':
				usefulListItemText=((CMainFrame*)AfxGetApp()->m_pMainWnd)->
					m_usefulStringList.GetItemTextFromShortcut(3);
				break;
			case '5':
				usefulListItemText=((CMainFrame*)AfxGetApp()->m_pMainWnd)->
					m_usefulStringList.GetItemTextFromShortcut(4);
				break;
			case '6':
				usefulListItemText=((CMainFrame*)AfxGetApp()->m_pMainWnd)->
					m_usefulStringList.GetItemTextFromShortcut(5);
				break;
			case '7':
				usefulListItemText=((CMainFrame*)AfxGetApp()->m_pMainWnd)->
					m_usefulStringList.GetItemTextFromShortcut(6);
				break;
			case '8':
				usefulListItemText=((CMainFrame*)AfxGetApp()->m_pMainWnd)->
					m_usefulStringList.GetItemTextFromShortcut(7);
				break;
			case '9':
				usefulListItemText=((CMainFrame*)AfxGetApp()->m_pMainWnd)->
					m_usefulStringList.GetItemTextFromShortcut(8);
				break;
			default:
				break;
		}
		if(!usefulListItemText.IsEmpty())
			WriteText(usefulListItemText);
	}
	CRichEditView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMainRichEditView::WriteText(CString text)
{
	CRichEditCtrl* pRichEditCtrl=&this->GetRichEditCtrl();
	pRichEditCtrl->ReplaceSel(text);
}
void CMainRichEditView::OnRMenu()
{
	// TODO: 在此添加命令处理程序代码
	LineStyleManage lineStyleManage;//行样式
	NoteNumStyleManage noteNumStyleManage;//注释号
	NoteManage noteManage;//注释
	TableStyleManage tableStyleManage;//表格
	PictureStyleManage pictureStyleManage;//图片

	MSG* pMsg=::AfxGetCurrentMessage();
	switch(LOWORD(pMsg->wParam)){
		case ID_RMENU_NOBR:
			lineStyleManage.addLineStyle(STYLE_NOBR,this);		
			break;
		case ID_RMENU_LETTERSPACE:
			lineStyleManage.addLineStyle(STYLE_LETTERSPACE,this);
			break;
		case ID_NOTENUM:
			noteNumStyleManage.addStyle(_T(""),this);
			break;
		case ID_RMENU_NOTEBEGIN:
			noteManage.addStyle(_T(""),this);
			break;
		case ID_RMENU_EM:
			lineStyleManage.addLineStyle(STYLE_EM,this);
			break;
		case ID_PIC_START:
			pictureStyleManage.AddPictureStyle(PICTURE_START,this);
			break;
		case ID_PIC_END:
			pictureStyleManage.AddPictureStyle(PICTURE_END,this);
			break;
		case ID_TABLE_START:
			tableStyleManage.AddTalbeStyle(TABLE_START,this);
			break;
		case ID_TABLE_END:
			tableStyleManage.AddTalbeStyle(TABLE_END,this);
			break;
		case ID_SPACE:
			lineStyleManage.addLineStyle(STYLE_SPACE,this);
			break;
		default:
			break;
	}
}

void CMainRichEditView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMenu menu;
	menu.LoadMenu(IDR_VIEW_RMENU);
	CMenu *pop = menu.GetSubMenu(0);
	ClientToScreen(&point);
	pop->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x,point.y,GetParent());
	CRichEditView::OnRButtonDown(nFlags, point);
}

void CMainRichEditView::ReplaceAll(CString FindStr, CString ReplaceStr, BOOL IsFullword, BOOL IsCapitzlization)
{
	this->OnReplaceAll(FindStr,ReplaceStr,IsFullword,IsCapitzlization);
}

void CMainRichEditView::OnMisprintCheck()
{
	// TODO: 在此添加命令处理程序代码
	m_misprintManageDlg.OnMisprintCheck(this);
}

void CMainRichEditView::OnMisprintAddmisprint()
{
	// TODO: 在此添加命令处理程序代码
	m_misprintDlg.ShowWindow(SW_NORMAL);
	m_misprintDlg.GetDlgItem(IDC_REPLACE_EDIT)->EnableWindow(FALSE);

	CString misprintString;
	misprintString=this->GetRichEditCtrl().GetSelText();
	if(!misprintString.IsEmpty()){
		m_misprintDlg.GetDlgItem(IDC_MISPRINT_EDIT)->
				SetWindowText(misprintString);
	}
	//将真正添加的实现放到了对话框的OnOk函数中
}

BOOL CMainRichEditView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(!CRichEditView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext))
	return FALSE;

	m_nWordWrap = WrapNone;
	WrapChanged();


	//创建添加错字对话框
	m_misprintDlg.Create(IDD_ADDMISPRINT_DLG);

	//初始化m_pHtmlProperty
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	m_pPropertyManage=new CPropertyManage(
		pFrame->m_wndProperties.m_pHtmlProperty,
		pFrame->m_wndProperties.m_pPictureProperty);
	m_pPropertyManage->m_htmlFilePath=((CEBEApp*)::AfxGetApp())->m_htmlFilePath;

	//创建错误处理对话框
	m_misprintManageDlg.Create(IDD_MisprintManageDlg);

	//创建快捷键
	hAccel=::LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));  

	return TRUE;
	
}

void CMainRichEditView::OnMisprintSet()
{
	// TODO: 在此添加命令处理程序代码
	this->m_misprintManageDlg.SetMisprintSet();
	
}

void CMainRichEditView::OnOutputHtml()
{
	// TODO: 在此添加命令处理程序代码

	this->SetFocus();//更新属性面板

	//更新输出文件的路径
	m_pPropertyManage->m_htmlFilePath=((CEBEApp*)AfxGetApp())->m_htmlFilePath;
	OutputManage outputManage;
	outputManage.StartOutput(&this->GetRichEditCtrl(),OUTPUT_HTML);
}

//浏览Html文件
void CMainRichEditView::OnBrowserBtn()
{
	//先重新生成Html文件
	OnOutputHtml();

	//浏览Html文件
	//获得当前输出文件的路径  
	CString sIniFilePath;
	sIniFilePath=((CEBEApp*)AfxGetApp())->m_htmlFilePath;

	CString htmlPath;
	htmlPath.Format(sIniFilePath+_T("p-%s.html"),m_pPropertyManage->m_pHtmlProperty->GetCurPage());
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	if(PathFileExists(htmlPath))
		pFrame->m_pHtmlViewCtrl->Navigate(htmlPath);

}


//简体转繁体
void CMainRichEditView::OnGbtobig5()
{
	// TODO: 在此添加命令处理程序代码
	CGBtoBig5 GBtoBig5;
	
	CString ViewText;
	CRichEditCtrl* pRichEditCtrl=&this->GetRichEditCtrl();
	pRichEditCtrl->SetSel(0,-1);
	ViewText=pRichEditCtrl->GetSelText();
	
	CString replaceString=GBtoBig5.GBtoBig5(ViewText);
	pRichEditCtrl->ReplaceSel(replaceString);
}

//繁体转简体
void CMainRichEditView::OnBig5togb()
{
	// TODO: 在此添加命令处理程序代码
	CGBtoBig5 GBtoBig5;

	CString ViewText;
	CRichEditCtrl* pRichEditCtrl=&this->GetRichEditCtrl();
	pRichEditCtrl->SetSel(0,-1);
	ViewText=pRichEditCtrl->GetSelText();


	CString replaceString=GBtoBig5.Big5toGB(ViewText);
	pRichEditCtrl->ReplaceSel(replaceString);
/*
	//TEST
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CString str;
	pFrame->m_pHtmlViewCtrl->GetWindowText(str);
	pFrame->m_pHtmlViewCtrl->GetForegroundWindow()->GetWindowText(str);
	//pFrame->m_pHtmlViewCtrl->GetDlgItemTextW(1504,str);
	//AfxMessageBox(str);
	//1504

	IHTMLDocument2 *pDoc = NULL;
	IDispatch *pID = pFrame->m_pHtmlViewCtrl->GetHtmlDocument();

	if ( pID != NULL )
	{
		HRESULT hr3 = pID->QueryInterface(IID_IHTMLDocument2 , (void**)&pDoc);

		if( pDoc != NULL )
		{
			IOleCommandTarget *pCmdTarget;
			pDoc->QueryInterface(IID_IOleCommandTarget ,(void **)&pCmdTarget);
			//HRESULT hr = pCmdTarget->Exec(&CGID_MSHTML, IDM_SELECTALL, MSOCMDEXECOPT_DODEFAULT, NULL, NULL);
			HRESULT hr = pCmdTarget->Exec(&CGID_MSHTML, IDM_SELECTALL, MSOCMDEXECOPT_DODEFAULT, NULL, NULL);
			if(S_OK ==hr){
				AfxMessageBox(_T("OK"));
			}
		}
	}

*/
}


void CMainRichEditView::NewOpenAutoRun()
{
	//自动错误检测
	this->OnMisprintCheck();

	//自动排版
	CFormat format;
	format.DelSpaceLines(this);
	format.DelUselessSpaces(this);

	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	//format.ReplaceKeySymbol(pFrame->m_pSymbolReplaceSetDlg,this);
	//全选，然后删除行前空格
	this->GetRichEditCtrl().SetSel(0,-1);

	format.DelFrontSpaces(this);

	//自动根据替换列表进行替换
	if(this->m_repSetDlg.m_IsAutoReplace){
		this->OnReplaceListAll();
	}
}
void CMainRichEditView::OnChnengSymbolReplace()
{
	// TODO: 在此添加命令处理程序代码
	CFormat format;
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	format.ReplaceKeySymbol(pFrame->m_pSymbolReplaceSetDlg,this);
}

BOOL CMainRichEditView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
//	if(::TranslateAccelerator(GetSafeHwnd(),hAccel,pMsg))   
//        return   true;
	return CRichEditView::PreTranslateMessage(pMsg);
}
