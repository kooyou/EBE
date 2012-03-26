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

// EBE.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "EBE.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "EBEDoc.h"
#include "EBEView.h"
#include "Format.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEBEApp


BEGIN_MESSAGE_MAP(CEBEApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CEBEApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_OPENNEXTFILE_OPENBTN, &CEBEApp::OnOpenNextFile)
	ON_COMMAND(ID_HTML_SAVEAS, &CEBEApp::OnHtmlSaveas)
	ON_COMMAND(ID_NOTE_MODEL_SET, &CEBEApp::OnNoteModelSet)
END_MESSAGE_MAP()


// CEBEApp 构造

CEBEApp::CEBEApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CEBEApp 对象

CEBEApp theApp;


// CEBEApp 初始化

BOOL CEBEApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("EBE"));
	LoadStdProfileSettings(0);  // 加载标准 INI 文件选项

	InitContextMenuManager();
	InitShellManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_EBETYPE,
		RUNTIME_CLASS(CEBEDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CMainRichEditView));
	if (!pDocTemplate)
		return FALSE;
	pDocTemplate->SetContainerInfo(IDR_EBETYPE_CNTR_IP);
	AddDocTemplate(pDocTemplate);

	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 MDI 应用程序中，这应在设置 m_pMainWnd 之后立即发生


	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	if(cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew) 
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing; 
	ParseCommandLine(cmdInfo);


	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();


	//初始化输出文件路径
	//获得当前可执行文件的路径  
	CString sIniFilePath;
	CString sModFileName; 
	GetModuleFileName(NULL,sModFileName.GetBuffer(MAX_PATH),MAX_PATH);
	sModFileName.ReleaseBuffer(); 
	sModFileName.MakeReverse(); 
	sIniFilePath=sModFileName.Right(sModFileName.GetLength()-sModFileName.Find( '\\')); 
	sIniFilePath.MakeReverse();
	this->m_htmlFilePath=sIniFilePath;

	//初始化注释模板对话框
	this->m_noteModelDlg.Create(IDD_NOTE_STYLE_DLG);

	return TRUE;
}



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CEBEApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CEBEApp 自定义加载/保存方法

void CEBEApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CEBEApp::LoadCustomState()
{
}

void CEBEApp::SaveCustomState()
{
}

// CEBEApp 消息处理程序

CDocument* CEBEApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
	// TODO: 在此添加专用代码和/或调用基类

	//向文件管理添加文件
	m_fileManage.AddFile(lpszFileName);
	CDocument* pDoc=NULL;
	pDoc=CWinAppEx::OpenDocumentFile(lpszFileName);

	if(pDoc!=NULL){
		//执行自动启动的功能
		CMainRichEditView* pRichEditView=((CMainRichEditView*)(
			(CMainFrame*)GetMainWnd())->GetActiveFrame()
			->GetActiveView());
		pRichEditView->NewOpenAutoRun();
	}

	return pDoc;
}

//打开下一个文件
void CEBEApp::OnOpenNextFile()
{
	//打开下一个文件
	CString nextFile;
	nextFile=m_fileManage.GetNextRTFFile(_T(""));
	if(PathFileExists(nextFile)){
		if(NULL==OpenDocumentFile(nextFile))
			return;
	}
	else{
		return;
	}

	//更新属性
	CMainRichEditView* pMainView=((CMainRichEditView*)((CMainFrame*)GetMainWnd())->GetActiveFrame()->GetActiveView());
	//更新页码
	CString LastPageNum=pMainView->m_pPropertyManage->
		m_pHtmlProperty->GetCurPage();
	int pageNum=_wtoi(LastPageNum);
	CString CurPageNum;

	//判断是否需要保留前面的零
	CString IsZero=LastPageNum.Left(1);
	if(0==IsZero.Compare(_T("0"))){//位数不足补零
		switch(LastPageNum.GetLength()){
			case 3:
				CurPageNum.Format(_T("%03d"),pageNum+1);
				break;
			case 4:
				CurPageNum.Format(_T("%04d"),pageNum+1);
				break;
			case 5:
				CurPageNum.Format(_T("%05d"),pageNum+1);
				break;
			default:
				break;
		}
	}
	else{
		CurPageNum.Format(_T("%d"),pageNum+1);
	}
	pMainView->m_pPropertyManage->m_pHtmlProperty->SetPage(CurPageNum);

	//更新左右页
	int pageLeftRight=pMainView->m_pPropertyManage->
		m_pHtmlProperty->GetPageLeftRight();
	if(pageLeftRight==1)
		pMainView->m_pPropertyManage->
		m_pHtmlProperty->SetPageLeftRight(2);
	else
		pMainView->m_pPropertyManage->
		m_pHtmlProperty->SetPageLeftRight(1);

	//更新模板
	CMainFrame* pMainFrame=(CMainFrame*)GetMainWnd();
	if(0!=pMainFrame->m_mapModel.m_vecAutoModelOpation.size()){
		CString modelName=pMainView->m_pPropertyManage->
			m_pHtmlProperty->GetModel();
		int i=0;
		for(i=0;i<(int)pMainFrame->m_mapModel.m_vecAutoModelOpation.size();i++){
			if(modelName==pMainFrame->m_mapModel.m_vecAutoModelOpation[i])
				break;
		}
		if(i<(int)pMainFrame->m_mapModel.m_vecAutoModelOpation.size()-1){
			i++;
		}
		else{
			i=0;
		}
		pMainView->m_pPropertyManage->
			m_pHtmlProperty->SetModel(
			pMainFrame->m_mapModel.m_vecAutoModelOpation[i]);
	}


	pMainView->SetFocus();//更新属性面板
}
void CEBEApp::OnHtmlSaveas()
{
	// TODO: 在此添加命令处理程序代码
	wchar_t     buf[MAX_PATH];   
	ZeroMemory(buf,   sizeof(buf));   
	BROWSEINFO       bi;   
	bi.hwndOwner   =   NULL;   
	bi.pidlRoot   =   NULL;   
	bi.pszDisplayName   =   buf;   
	bi.lpszTitle   =   _T("请选择目录：");   
	bi.ulFlags   =   BIF_EDITBOX   ;   
	bi.lpfn   =   NULL;   
	bi.lParam   =   0;   
	bi.iImage     =   0;   
	LPITEMIDLIST     lp   =   SHBrowseForFolder(&bi);   
	if(lp   &&   SHGetPathFromIDList(lp,   buf))   
	{   
		this->m_htmlFilePath=buf;
		this->m_htmlFilePath=this->m_htmlFilePath+_T("\\");
	}
}

void CEBEApp::OnNoteModelSet()
{
	// TODO: 在此添加命令处理程序代码
	this->m_noteModelDlg.ShowWindow(SW_NORMAL);
/*	CString str=this->m_noteModelDlg.GetFirstModel(1);
	AfxMessageBox(str);*/
}
