// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

// EBE.cpp : ����Ӧ�ó��������Ϊ��
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
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_OPENNEXTFILE_OPENBTN, &CEBEApp::OnOpenNextFile)
	ON_COMMAND(ID_HTML_SAVEAS, &CEBEApp::OnHtmlSaveas)
	ON_COMMAND(ID_NOTE_MODEL_SET, &CEBEApp::OnNoteModelSet)
END_MESSAGE_MAP()


// CEBEApp ����

CEBEApp::CEBEApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CEBEApp ����

CEBEApp theApp;


// CEBEApp ��ʼ��

BOOL CEBEApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("EBE"));
	LoadStdProfileSettings(0);  // ���ر�׼ INI �ļ�ѡ��

	InitContextMenuManager();
	InitShellManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_EBETYPE,
		RUNTIME_CLASS(CEBEDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CMainRichEditView));
	if (!pDocTemplate)
		return FALSE;
	pDocTemplate->SetContainerInfo(IDR_EBETYPE_CNTR_IP);
	AddDocTemplate(pDocTemplate);

	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������


	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	if(cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew) 
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing; 
	ParseCommandLine(cmdInfo);


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();


	//��ʼ������ļ�·��
	//��õ�ǰ��ִ���ļ���·��  
	CString sIniFilePath;
	CString sModFileName; 
	GetModuleFileName(NULL,sModFileName.GetBuffer(MAX_PATH),MAX_PATH);
	sModFileName.ReleaseBuffer(); 
	sModFileName.MakeReverse(); 
	sIniFilePath=sModFileName.Right(sModFileName.GetLength()-sModFileName.Find( '\\')); 
	sIniFilePath.MakeReverse();
	this->m_htmlFilePath=sIniFilePath;

	//��ʼ��ע��ģ��Ի���
	this->m_noteModelDlg.Create(IDD_NOTE_STYLE_DLG);

	return TRUE;
}



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// �������жԻ����Ӧ�ó�������
void CEBEApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CEBEApp �Զ������/���淽��

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

// CEBEApp ��Ϣ�������

CDocument* CEBEApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
	// TODO: �ڴ����ר�ô����/����û���

	//���ļ���������ļ�
	m_fileManage.AddFile(lpszFileName);
	CDocument* pDoc=NULL;
	pDoc=CWinAppEx::OpenDocumentFile(lpszFileName);

	if(pDoc!=NULL){
		//ִ���Զ������Ĺ���
		CMainRichEditView* pRichEditView=((CMainRichEditView*)(
			(CMainFrame*)GetMainWnd())->GetActiveFrame()
			->GetActiveView());
		pRichEditView->NewOpenAutoRun();
	}

	return pDoc;
}

//����һ���ļ�
void CEBEApp::OnOpenNextFile()
{
	//����һ���ļ�
	CString nextFile;
	nextFile=m_fileManage.GetNextRTFFile(_T(""));
	if(PathFileExists(nextFile)){
		if(NULL==OpenDocumentFile(nextFile))
			return;
	}
	else{
		return;
	}

	//��������
	CMainRichEditView* pMainView=((CMainRichEditView*)((CMainFrame*)GetMainWnd())->GetActiveFrame()->GetActiveView());
	//����ҳ��
	CString LastPageNum=pMainView->m_pPropertyManage->
		m_pHtmlProperty->GetCurPage();
	int pageNum=_wtoi(LastPageNum);
	CString CurPageNum;

	//�ж��Ƿ���Ҫ����ǰ�����
	CString IsZero=LastPageNum.Left(1);
	if(0==IsZero.Compare(_T("0"))){//λ�����㲹��
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

	//��������ҳ
	int pageLeftRight=pMainView->m_pPropertyManage->
		m_pHtmlProperty->GetPageLeftRight();
	if(pageLeftRight==1)
		pMainView->m_pPropertyManage->
		m_pHtmlProperty->SetPageLeftRight(2);
	else
		pMainView->m_pPropertyManage->
		m_pHtmlProperty->SetPageLeftRight(1);

	//����ģ��
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


	pMainView->SetFocus();//�����������
}
void CEBEApp::OnHtmlSaveas()
{
	// TODO: �ڴ���������������
	wchar_t     buf[MAX_PATH];   
	ZeroMemory(buf,   sizeof(buf));   
	BROWSEINFO       bi;   
	bi.hwndOwner   =   NULL;   
	bi.pidlRoot   =   NULL;   
	bi.pszDisplayName   =   buf;   
	bi.lpszTitle   =   _T("��ѡ��Ŀ¼��");   
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
	// TODO: �ڴ���������������
	this->m_noteModelDlg.ShowWindow(SW_NORMAL);
/*	CString str=this->m_noteModelDlg.GetFirstModel(1);
	AfxMessageBox(str);*/
}
