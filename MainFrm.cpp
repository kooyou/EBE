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

// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "EBE.h"

#include "MainFrm.h"
//#include "FileManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(IDS_ADDMODEL, &CMainFrame::OnAddModel)
	ON_COMMAND(ID_MODELFILE_MANAGE, &CMainFrame::OnModelFileManage)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);

	m_pModelManageDlg=NULL;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // ����������ʽ...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // ����Ϊ FALSE �Ὣ�رհ�ť������ѡ�������Ҳ�
	mdiTabParams.m_bTabIcons = FALSE;    // ����Ϊ TRUE ���� MDI ѡ��������ĵ�ͼ��
	mdiTabParams.m_bAutoColor = TRUE;    // ����Ϊ FALSE ������ MDI ѡ����Զ���ɫ
	mdiTabParams.m_bDocumentMenu = TRUE; // ��ѡ�������ұ�Ե�����ĵ��˵�
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	m_wndRibbonBar.Create(this);
	InitializeRibbon();

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// �������񽫴�������࣬��˽���ʱ��������ͣ��:
	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	// ���������á�Outlook��������:
	if (!CreateOutlookBar(m_wndNavigationBar, ID_VIEW_NAVIGATION, m_wndTree, m_wndCalendar, 250))
	{
		TRACE0("δ�ܴ�����������\n");
		return -1;      // δ�ܴ���
	}

	// �Ѵ��� Outlook ����Ӧ���������ͣ����
	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);

	// ����ͣ������
	if (!CreateDockingWindows())
	{
		TRACE0("δ�ܴ���ͣ������\n");
		return -1;
	}

	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);


	// ������ǿ�Ĵ��ڹ���Ի���
	EnableWindowsDialog(ID_WINDOW_MANAGER, IDS_WINDOWS_MANAGER, TRUE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

void CMainFrame::InitializeRibbon()
{
	BOOL bNameValid;

	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_RIBBON_FILE);
	ASSERT(bNameValid);

	// �������ͼ��:
	m_PanelImages.SetImageSize(CSize(16, 16));
	m_PanelImages.Load(IDB_BUTTONS);

	// ��ʼ����ť:
	//m_MainButton.SetImage(IDB_EBE);
	m_MainButton.SetImage(IDB_MAIN);
	m_MainButton.SetText(_T("\nf"));
	m_MainButton.SetToolTipText(strTemp);

	m_wndRibbonBar.SetApplicationButton(&m_MainButton, CSize (45, 45));
	CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(strTemp, IDB_FILESMALL, IDB_FILELARGE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_NEW);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_NEW, strTemp, 0, 0));
	bNameValid = strTemp.LoadString(IDS_RIBBON_OPEN);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_OPEN, strTemp, 1, 1));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE, strTemp, 2, 2));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVEAS);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE_AS, strTemp, 3, 3));

	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnPrint = new CMFCRibbonButton(ID_FILE_PRINT, strTemp, 6, 6);
	pBtnPrint->SetKeys(_T("p"), _T("w"));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_LABEL);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonLabel(strTemp));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_QUICK);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_DIRECT, strTemp, 7, 7, TRUE));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_PREVIEW);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_PREVIEW, strTemp, 8, 8, TRUE));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_SETUP);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_SETUP, strTemp, 11, 11, TRUE));
	pMainPanel->Add(pBtnPrint);
	pMainPanel->Add(new CMFCRibbonSeparator(TRUE));

	bNameValid = strTemp.LoadString(IDS_RIBBON_CLOSE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_CLOSE, strTemp, 9, 9));

	bNameValid = strTemp.LoadString(IDS_RIBBON_RECENT_DOCS);
	ASSERT(bNameValid);
	pMainPanel->AddRecentFilesList(strTemp);

	bNameValid = strTemp.LoadString(IDS_RIBBON_EXIT);
	ASSERT(bNameValid);
	pMainPanel->AddToBottom(new CMFCRibbonMainPanelButton(ID_APP_EXIT, strTemp, 15));

	// Ϊ�������塱�����ӡ��������:
	bNameValid = strTemp.LoadString(IDS_RIBBON_HOME);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pCategoryHome = m_wndRibbonBar.AddCategory(strTemp, IDB_WRITESMALL, IDB_WRITELARGE);

	// �����������塱���:
	bNameValid = strTemp.LoadString(IDS_RIBBON_CLIPBOARD);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelClipboard = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));

	bNameValid = strTemp.LoadString(IDS_RIBBON_PASTE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnPaste = new CMFCRibbonButton(ID_EDIT_PASTE, strTemp, 0, 0);
	pBtnPaste->SetMenu(IDR_PASTE_MENU, TRUE);
	pPanelClipboard->Add(pBtnPaste);

	bNameValid = strTemp.LoadString(IDS_RIBBON_CUT);
	ASSERT(bNameValid);
	pPanelClipboard->Add(new CMFCRibbonButton(ID_EDIT_CUT, strTemp, 1));
	bNameValid = strTemp.LoadString(IDS_RIBBON_COPY);
	ASSERT(bNameValid);
	pPanelClipboard->Add(new CMFCRibbonButton(ID_EDIT_COPY, strTemp, 2));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SELECTALL);
	ASSERT(bNameValid);
	pPanelClipboard->Add(new CMFCRibbonButton(ID_EDIT_SELECT_ALL, strTemp, -1));

	bNameValid = strTemp.LoadString(IDS_RIBBON_INSERT_OBJECT);
	ASSERT(bNameValid);
	pPanelClipboard->Add(new CMFCRibbonButton(ID_OLE_INSERT_NEW, strTemp, -1));

	// ��������ӡ�����/�滻�����:
	bNameValid = strTemp.LoadString(IDS_RIBBON_FINDREPLACE);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelFindReplace = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));

	bNameValid = strTemp.LoadString(IDS_RIBBON_FIND);
	ASSERT(bNameValid);
	pPanelFindReplace->Add(new CMFCRibbonButton(ID_EDIT_FIND, strTemp, -1));
	bNameValid = strTemp.LoadString(IDS_RIBBON_FINDNEXT);
	ASSERT(bNameValid);
	pPanelFindReplace->Add(new CMFCRibbonButton(ID_EDIT_REPEAT, strTemp, -1));
	bNameValid = strTemp.LoadString(IDS_RIBBON_REPLACE);
	ASSERT(bNameValid);
	pPanelFindReplace->Add(new CMFCRibbonButton(ID_EDIT_REPLACE, strTemp, -1));

	// ��������ӡ���ͼ�����:
	bNameValid = strTemp.LoadString(IDS_RIBBON_VIEW);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelView = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon (7));

	bNameValid = strTemp.LoadString(IDS_RIBBON_STATUSBAR);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnStatusBar = new CMFCRibbonCheckBox(ID_VIEW_STATUS_BAR, strTemp);
	pPanelView->Add(pBtnStatusBar);

	// ��������ӡ����ڡ����:
	bNameValid = strTemp.LoadString(IDS_RIBBON_WINDOW);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelWindow = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon (7));

	bNameValid = strTemp.LoadString(IDS_RIBBON_WINDOWS);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnWindows = new CMFCRibbonButton(ID_WINDOW_MANAGER, strTemp, -1, 1);
	pBtnWindows->SetMenu(IDR_WINDOWS_MENU, TRUE);
	pPanelWindow->Add(pBtnWindows);

	//��ӡ�����һ��������
	bNameValid = strTemp.LoadStringW(IDS_OPENNEXTFILE);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pOpenNextPanel= pCategoryHome->AddPanel(strTemp,m_PanelImages.ExtractIcon(7));
	bNameValid= strTemp.LoadStringW(IDS_OPENNEXTFILE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pOpenNextBtn = new CMFCRibbonButton(ID_OPENNEXTFILE_OPENBTN,strTemp,-1,2);
	pOpenNextPanel->Add(pOpenNextBtn);

	//��ӡ��滻ˢ�¡�����
	bNameValid =strTemp.LoadStringW(IDS_REPLACERIBBONBUTTON_REFRESH);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pReplace = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon (30));
	bNameValid =strTemp.LoadStringW(IDS_REPLACERIBBONBUTTON_SET);
	ASSERT(bNameValid);
	CMFCRibbonButton* pReplaceBtn = new CMFCRibbonButton(ID_REPLACE_LIST, strTemp, -1, 3);
	pReplaceBtn->SetMenu(IDR_REPLACELIST, TRUE);
	pReplace->Add(pReplaceBtn);

	//��ӡ��Ű桱����
	bNameValid =strTemp.LoadStringW(IDS_FORMAT);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pForamtPanelWindow = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon (30));
	CMFCRibbonButton* pFormatBtnWindows = new CMFCRibbonButton(IDS_FORMAT, strTemp, -1, 4);
	pFormatBtnWindows->SetMenu(IDR_FORMAT,TRUE);
	pForamtPanelWindow->Add(pFormatBtnWindows);

	//��ӡ�����������
	bNameValid=strTemp.LoadStringW(IDS_MISPRINTMANAGE);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pMisprintPanelWindow = pCategoryHome->AddPanel(strTemp,
		m_PanelImages.ExtractIcon(30));
	CMFCRibbonButton* pMisprintBtnWindows=new CMFCRibbonButton(
			IDS_MISPRINTMANAGE,strTemp,-1,5);
	pMisprintBtnWindows->SetMenu(IDR_MISPRINTMANAGE,TRUE);
	pMisprintPanelWindow->Add(pMisprintBtnWindows);

	//��ӡ����������
	bNameValid=strTemp.LoadString(IDS_OUTPUT);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pOutputPanel= pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon (30));
	bNameValid=strTemp.LoadStringW(IDS_OUTPUT_HTML);
	ASSERT(bNameValid);
	CMFCRibbonButton* pOutputBtn = new CMFCRibbonButton(IDS_OUTPUT_HTML,strTemp, -1, 6);
	pOutputBtn->SetMenu(IDR_OUTPUT,TRUE);
	pOutputPanel->Add(pOutputBtn);

	//��ӡ����������
	bNameValid=strTemp.LoadString(IDS_HTML_BROWSER);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pBrowserPanel= pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon (30));
	bNameValid=strTemp.LoadStringW(IDS_HTML_BROWSER);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBrowserBtn = new CMFCRibbonButton(IDS_HTML_BROWSER_BTN,strTemp, -1, 7);
	pBrowserPanel->Add(pBrowserBtn);

	//��ӡ����ģ�塱����
	bNameValid=strTemp.LoadString(IDS_ADDMODEL);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pAddModelPanelWindow = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon (30));
	CMFCRibbonButton* pAddModelBtnWindows = new CMFCRibbonButton(IDS_ADDMODEL, strTemp, -1, 8);
	pAddModelBtnWindows->SetMenu(IDR_MODEL_MANAGE,TRUE);
	pAddModelPanelWindow->Add(pAddModelBtnWindows);
	





	// ��Ԫ����ӵ�ѡ��Ҳ�:
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pVisualStyleButton = new CMFCRibbonButton(-1, strTemp, -1, -1);

	pVisualStyleButton->SetMenu(IDR_THEME_MENU, FALSE /* ��Ĭ������*/, TRUE /* �Ҷ���*/);

	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_TIP);
	ASSERT(bNameValid);
	pVisualStyleButton->SetToolTipText(strTemp);
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_DESC);
	ASSERT(bNameValid);
	pVisualStyleButton->SetDescription(strTemp);
	m_wndRibbonBar.AddToTabs(pVisualStyleButton);

	// ��ӿ��ٷ��ʹ���������:
	CList<UINT, UINT> lstQATCmds;

	lstQATCmds.AddTail(ID_FILE_NEW);
	lstQATCmds.AddTail(ID_FILE_OPEN);
	lstQATCmds.AddTail(ID_FILE_SAVE);
	lstQATCmds.AddTail(ID_FILE_PRINT_DIRECT);

	m_wndRibbonBar.SetQuickAccessCommands(lstQATCmds);

	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_APP_ABOUT, _T("\na"), m_PanelImages.ExtractIcon (0)));
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;
	// �������Դ���
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ��������ԡ�����\n");
		return FALSE; // δ�ܴ���
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

	UpdateMDITabbedBarsIcons();
}

BOOL CMainFrame::CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, CMFCShellTreeCtrl& tree, CCalendarBar& calendar, int nInitialWidth)
{
	CWindowDC dc(NULL);

	bar.SetMode2003();

	BOOL bNameValid;
	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_SHORTCUTS);
	ASSERT(bNameValid);
	if (!bar.Create(strTemp, this, CRect(0, 0, nInitialWidth, 32000), uiID, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		return FALSE; // δ�ܴ���
	}

	CMFCOutlookBarTabCtrl* pOutlookBar = (CMFCOutlookBarTabCtrl*)bar.GetUnderlyingWindow();

	if (pOutlookBar == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	pOutlookBar->EnableInPlaceEdit(TRUE);

	static UINT uiPageID = 1;

	DWORD dwPaneStyle = AFX_DEFAULT_TOOLBAR_STYLE | CBRS_FLOAT_MULTI;

	
	// �ɸ��������Զ����أ��ɵ�����С�������ܹر�
	DWORD dwStyle = AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE;

	CRect rectDummy(0, 0, 0, 0);

	//�����滻�б�
	const DWORD dwReplaceListStyle=WS_CHILD|WS_VISIBLE;
	m_replaceListCtrl.Create(dwReplaceListStyle,rectDummy,&bar,1500);
	bNameValid=strTemp.LoadString(IDS_REPLACELIST);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(&m_replaceListCtrl, strTemp, 0, TRUE, dwStyle);

	//����CSS��ʽ�б�
	const DWORD dwCSSListStyle=WS_CHILD|WS_VISIBLE;
	m_cssListCtrl.Create(dwCSSListStyle,rectDummy,&bar,1501);
	bNameValid=strTemp.LoadString(IDS_CSSLISTCTRL);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(&m_cssListCtrl,strTemp,1,TRUE,dwStyle);

	//���ó����ַ����б�
	const DWORD dwUsefulStringListStyle=WS_CHILD|WS_VISIBLE;
	m_usefulStringList.Create(dwUsefulStringListStyle,rectDummy,&bar,1502);
	bNameValid=strTemp.LoadString(IDS_USEFULSTRINGLIST);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(&m_usefulStringList,strTemp,2,TRUE,dwStyle);

	//�滻�����ŶԻ���
	m_pSymbolReplaceSetDlg=new CSymbolReplaceSetDlg();
	m_pSymbolReplaceSetDlg->Create(IDD_SYMBOL_REPLACE_SET,this);
	m_pSymbolReplaceSetDlg->ShowWindow(SW_SHOW);
	bNameValid=strTemp.LoadString(IDS_SYMBOLREPLACE_SET_DLG);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(m_pSymbolReplaceSetDlg, strTemp, 3, TRUE, dwStyle);

	//Html���
	const DWORD dwHtmlEditCtrl = WS_CHILD | WS_VISIBLE ;
	m_pHtmlViewCtrl=new CHtmlViewCtrl();
	m_pHtmlViewCtrl->Create(NULL,_T("HtmlEdit"),dwHtmlEditCtrl, rectDummy, &bar, 1504);
	strTemp=_T("Html���");
	bNameValid=true;
	pOutlookBar->AddControl(m_pHtmlViewCtrl, strTemp, 4, TRUE, dwStyle);





	bar.SetPaneStyle(bar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	pOutlookBar->SetImageList(theApp.m_bHiColorIcons ? IDB_PAGES_HC : IDB_PAGES, 24);
	pOutlookBar->SetToolbarImageList(theApp.m_bHiColorIcons ? IDB_PAGES_SMALL_HC : IDB_PAGES_SMALL, 16);
	pOutlookBar->RecalcLayout();

	BOOL bAnimation = theApp.GetInt(_T("OutlookAnimation"), TRUE);
	CMFCOutlookBarTabCtrl::EnableAnimation(bAnimation);

	bar.SetButtonsFont(&afxGlobalData.fontBold);

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnAddModel()
{
	CFileDialog m_findDlg(TRUE);
	m_findDlg.m_ofn.lpstrFilter = _T("html Documents (*.*)\0*.*\0\0");
	if (IDOK == m_findDlg.DoModal())
	{
		CString modelName;
		modelName=m_findDlg.GetFileName();
		modelName.Replace(_T(".html"),_T(""));
		modelName.Replace(_T(".HTML"),_T(""));
		modelName.Replace(_T(".txt"),_T("")); 
		//�����������뵱ǰ�򿪵�ģ��
		this->m_wndProperties.AddModelOpation(modelName);
		//����ģ���¼
		if(m_findDlg.GetPathName()==_T("")){
			return;
			AfxMessageBox(_T("ģ���ʧ�ܣ�"));
		}
		this->m_mapModel.AddModel(modelName,m_findDlg.GetPathName());
	}
}

//ģ���ļ�����
void CMainFrame::OnModelFileManage()
{
	//��ȡ��������е�ģ���б�����
	CMFCPropertyGridProperty* pModelPro=m_wndProperties.m_pHtmlProperty->GetSubItem(5);
	int opationCount=pModelPro->GetOptionCount();
	m_mapModel.m_vecModelOpation.clear();
	for(int i=0;i<opationCount;i++){
		m_mapModel.m_vecModelOpation.push_back(pModelPro->GetOption(i));
	}

	//��һ�ε��þͳ�ʼ���Ի���
	if(m_pModelManageDlg==NULL){
		m_pModelManageDlg=new CModelManageDlg();
		m_pModelManageDlg->Create(IDD_MODEL_MANAGE);

		//��ʼ���Ի����е�ģ���б�
		m_pModelManageDlg->m_modelListCtrl.SetCheck(0);
		m_pModelManageDlg->m_modelListCtrl.ModifyStyle(0,LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL);
		m_pModelManageDlg->m_modelListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP| LVS_EX_CHECKBOXES);
		m_pModelManageDlg->m_modelListCtrl.InsertColumn(0,_T("�Զ�ѡ��"),LVCFMT_CENTER,50);
		m_pModelManageDlg->m_modelListCtrl.InsertColumn(1,_T("ģ����"),LVCFMT_LEFT,200);
	}

	//������е�item
	m_pModelManageDlg->m_modelListCtrl.DeleteAllItems();

	//���б��������
	for(int i=0;i<(int)m_mapModel.m_vecModelOpation.size();i++){
		int iItem=m_pModelManageDlg->m_modelListCtrl.InsertItem(0,_T(""));
		m_pModelManageDlg->m_modelListCtrl.SetItemText(iItem,1,m_mapModel.m_vecModelOpation[i]);
	}
	m_pModelManageDlg->ShowWindow(SW_NORMAL);
}


void CMainFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	this->m_replaceListCtrl.OnClose();

	this->m_usefulStringList.OnClose();


	if(m_pSymbolReplaceSetDlg!=NULL){
		m_pSymbolReplaceSetDlg->DestroyWindow();
		delete m_pSymbolReplaceSetDlg;
	}
	if(m_pHtmlViewCtrl!=NULL){
		//m_pHtmlViewCtrl->DestroyWindow();
		//delete m_pHtmlViewCtrl; //�д���
	}
	if(m_pModelManageDlg!=NULL){
		m_pModelManageDlg->DestroyWindow();
		delete m_pModelManageDlg;
	}
	CMDIFrameWndEx::OnClose();
}

//����ģ���б��û�ʹ��ģ������Ҫ������Ӧ������
void CMainFrame::RefreshModelProList()
{
	//����ģ���б�
	this->m_mapModel.m_vecModelOpation.clear();
	int itemCount=m_pModelManageDlg->m_modelListCtrl.GetItemCount();
	for(int i=0;i<itemCount;i++){
		this->m_mapModel.m_vecModelOpation.push_back(
			m_pModelManageDlg->m_modelListCtrl.GetItemText(i,1));
	}

	//����ģ�����Ե�ѡ��
	this->m_wndProperties.m_pHtmlProperty->RemoveModelAllOpation();
	for(int i=0;i<(int)m_mapModel.m_vecModelOpation.size();i++){
		m_wndProperties.m_pHtmlProperty->AddModelOpatoin(
			m_mapModel.m_vecModelOpation[i]);
	}

	//�����Զ�ѡ����б�
	m_mapModel.m_vecAutoModelOpation.clear();
	for(int i=0;i<itemCount;i++){
		if(m_pModelManageDlg->m_modelListCtrl.GetCheck(i)){
			m_mapModel.m_vecAutoModelOpation.push_back(
				m_mapModel.m_vecModelOpation[i]);
		}
	}
}