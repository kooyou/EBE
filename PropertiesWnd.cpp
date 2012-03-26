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
// CResourceViewBar 消息处理程序

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

	// 创建组合:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("未能创建属性组合 \n");
		return -1;      // 未能创建
	}

//	m_wndObjectCombo.AddString(_T("应用程序"));
	m_wndObjectCombo.AddString(_T("页面属性"));
	m_wndObjectCombo.SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));
	m_wndObjectCombo.SetCurSel(0);

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* 已锁定*/);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* 锁定*/);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由:
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
	// TODO: 在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: 在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	//页面属性
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("页面"));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("书名"), _T("澳门编年史"), _T("当前编辑的书名")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("页码"), _T("000"), _T("当前编辑的页码")));
	
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("左右页面"), _T("左"), _T("其中之一: 左页、右页"));
	pProp->AddOption(_T("左"));
	pProp->AddOption(_T("右"));
	pProp->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp);

	CMFCPropertyGridProperty* pProp1 = new CMFCPropertyGridProperty(_T("注释类型"), _T("圆圈"), _T("其中之一: 圆圈、阿拉伯数字"));
	pProp1->AddOption(_T("圆圈"));
	pProp1->AddOption(_T("阿拉伯数字"));
	pProp1->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp1);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("注释样式"), _T("<span class=\"super\">#number#</span>"), _T("注释的css样式（#number#为注释号）")));

	CMFCPropertyGridProperty* pProp_1 = new CMFCPropertyGridProperty(_T("模板"),_T("选择模板"), _T("其中之一"));
	CStdioFile modelFile;

	//区域设定
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

	CString fPath;
	fPath.Format(_T("%s//modelList.txt"),sIniFilePath);

	//从文件读取信息
	modelFile.Open(fPath,CFile::modeRead);
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CString optionStr;//模板名称
	CString filename;//模板对应的文件地址
	while(modelFile.ReadString(optionStr)){
		if(modelFile.ReadString(filename)){
			pProp_1->AddOption(optionStr);
			//pFrame->m_mapModel[optionStr]=filename;//将模板对应的文件地址写入map
		}
	}
	modelFile.Close();
	pProp_1->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp_1);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("正文样式"), _T("t1"), _T("正文的CSS样式")));

	m_wndPropList.AddProperty(pGroup1);

		//恢复区域设定
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定


	//图片属性
	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("图片"));

	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("名字"), _T("图片名"), _T("当前页的图片名")));

	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("高(xp)"), _T("180"), _T("图片高度（单位像素）")));
	
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("宽(xp)"), _T("250"), _T("图片宽度（单位像素）")));
	
	CMFCPropertyGridProperty* pProp2 = new CMFCPropertyGridProperty(_T("位置"), _T("左"), _T("其中之一: 左、右、居中"));
	pProp2->AddOption(_T("左"));
	pProp2->AddOption(_T("右"));
	pProp2->AddOption(_T("居中"));
	pProp2->AllowEdit(FALSE);

	pGroup2->AddSubItem(pProp2);
	m_wndPropList.AddProperty(pGroup2);

	//初始化m_pHtmlProperty
	m_pHtmlProperty=static_cast<CHtmlProperty*>(this->m_wndPropList.GetProperty(0));

	//初始化m_pPictureProperty
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

//属性空间发生修改消息响应函数
LRESULT CPropertiesWnd::OnPropertyChanged(__in WPARAM wparam, __in LPARAM lparam)
{
	CMFCPropertyGridProperty * pProperty = ( CMFCPropertyGridProperty * ) lparam;
	CString proName=pProperty->GetName();//获取修改的属性名
	if(proName.Compare(_T("模板"))==0){
		CString modelName;
		COleVariant _var;
		_var=pProperty->GetValue();
		modelName=_var.bstrVal;
		CString ModelFilePath;
		//获取该模板的文件路径
		ModelFilePath=((CMainFrame*)this->GetParent())->
			m_mapModel.getModelFilePath(modelName);
		if(ModelFilePath.IsEmpty())
			return 0;
		//调用CCSSListCtrl类的成员函数修改样式列表的内容
		CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		pFrame->m_cssListCtrl.ChangeDataFromModelTxt(ModelFilePath);
	}
	return 0;
}

void CPropertiesWnd::AddModelOpation(CString modelName)
{
	m_pHtmlProperty->AddModelOpatoin(modelName);
}