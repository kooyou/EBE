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

#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "EBE.h"
#include <locale>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar ��Ϣ�������

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);

	m_wndObjectCombo.GetWindowRect(&rectCombo);

	int cyCmb = rectCombo.Size().cy;
	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb + cyTlb, rectClient.Width(), rectClient.Height() -(cyCmb+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// �������:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("δ�ܴ���������� \n");
		return -1;      // δ�ܴ���
	}

//	m_wndObjectCombo.AddString(_T("Ӧ�ó���"));
	m_wndObjectCombo.AddString(_T("ҳ������"));
	m_wndObjectCombo.SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));
	m_wndObjectCombo.SetCurSel(0);

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("δ�ܴ�����������\n");
		return -1;      // δ�ܴ���
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* ������*/);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* ����*/);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* pCmdUI)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: �ڴ˴���������������
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: �ڴ˴����������� UI ����������
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: �ڴ˴���������������
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: �ڴ˴����������� UI ����������
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	//ҳ������
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("ҳ��"));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("����"), _T("���ű���ʷ"), _T("��ǰ�༭������")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("ҳ��"), _T("000"), _T("��ǰ�༭��ҳ��")));
	
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("����ҳ��"), _T("��"), _T("����֮һ: ��ҳ����ҳ"));
	pProp->AddOption(_T("��"));
	pProp->AddOption(_T("��"));
	pProp->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp);

	CMFCPropertyGridProperty* pProp1 = new CMFCPropertyGridProperty(_T("ע������"), _T("ԲȦ"), _T("����֮һ: ԲȦ������������"));
	pProp1->AddOption(_T("ԲȦ"));
	pProp1->AddOption(_T("����������"));
	pProp1->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp1);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("ע����ʽ"), _T("<span class=\"super\">#number#</span>"), _T("ע�͵�css��ʽ��#number#Ϊע�ͺţ�")));

	CMFCPropertyGridProperty* pProp_1 = new CMFCPropertyGridProperty(_T("ģ��"),_T("ѡ��ģ��"), _T("����֮һ"));
	CStdioFile modelFile;

	//�����趨
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//�趨

	//��õ�ǰ��ִ���ļ���·��  
	CString sModFileName; 
	GetModuleFileName(NULL,sModFileName.GetBuffer(MAX_PATH),MAX_PATH);
	sModFileName.ReleaseBuffer(); 
	sModFileName.MakeReverse(); 
	CString sIniFilePath;
	sIniFilePath=sModFileName.Right(sModFileName.GetLength()-sModFileName.Find( '\\')); 
	sIniFilePath.MakeReverse();

	CString fPath;
	fPath.Format(_T("%s//modelList.txt"),sIniFilePath);

	//���ļ���ȡ��Ϣ
	modelFile.Open(fPath,CFile::modeRead);
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CString optionStr;//ģ������
	CString filename;//ģ���Ӧ���ļ���ַ
	while(modelFile.ReadString(optionStr)){
		if(modelFile.ReadString(filename)){
			pProp_1->AddOption(optionStr);
			//pFrame->m_mapModel[optionStr]=filename;//��ģ���Ӧ���ļ���ַд��map
		}
	}
	modelFile.Close();
	pProp_1->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp_1);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("������ʽ"), _T("t1"), _T("���ĵ�CSS��ʽ")));

	m_wndPropList.AddProperty(pGroup1);

		//�ָ������趨
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//��ԭ�����趨


	//ͼƬ����
	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("ͼƬ"));

	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("����"), _T("ͼƬ��"), _T("��ǰҳ��ͼƬ��")));

	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("��(xp)"), _T("180"), _T("ͼƬ�߶ȣ���λ���أ�")));
	
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("��(xp)"), _T("250"), _T("ͼƬ��ȣ���λ���أ�")));
	
	CMFCPropertyGridProperty* pProp2 = new CMFCPropertyGridProperty(_T("λ��"), _T("��"), _T("����֮һ: ���ҡ�����"));
	pProp2->AddOption(_T("��"));
	pProp2->AddOption(_T("��"));
	pProp2->AddOption(_T("����"));
	pProp2->AllowEdit(FALSE);

	pGroup2->AddSubItem(pProp2);
	m_wndPropList.AddProperty(pGroup2);

	//��ʼ��m_pHtmlProperty
	m_pHtmlProperty=static_cast<CHtmlProperty*>(this->m_wndPropList.GetProperty(0));

	//��ʼ��m_pPictureProperty
	m_pPictureProperty=static_cast<CPictureProperty*>(this->m_wndPropList.GetProperty(1));
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
}

//���Կռ䷢���޸���Ϣ��Ӧ����
LRESULT CPropertiesWnd::OnPropertyChanged(__in WPARAM wparam, __in LPARAM lparam)
{
	CMFCPropertyGridProperty * pProperty = ( CMFCPropertyGridProperty * ) lparam;
	CString proName=pProperty->GetName();//��ȡ�޸ĵ�������
	if(proName.Compare(_T("ģ��"))==0){
		CString modelName;
		COleVariant _var;
		_var=pProperty->GetValue();
		modelName=_var.bstrVal;
		CString ModelFilePath;
		//��ȡ��ģ����ļ�·��
		ModelFilePath=((CMainFrame*)this->GetParent())->
			m_mapModel.getModelFilePath(modelName);
		if(ModelFilePath.IsEmpty())
			return 0;
		//����CCSSListCtrl��ĳ�Ա�����޸���ʽ�б������
		CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		pFrame->m_cssListCtrl.ChangeDataFromModelTxt(ModelFilePath);
	}
	return 0;
}

void CPropertiesWnd::AddModelOpation(CString modelName)
{
	m_pHtmlProperty->AddModelOpatoin(modelName);
}