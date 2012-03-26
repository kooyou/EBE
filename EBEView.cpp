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

// EBEView.cpp : CMainRichEditView ���ʵ��
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
	// ��׼��ӡ����
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

// CMainRichEditView ����/����

CMainRichEditView::CMainRichEditView()
{
	// TODO: �ڴ˴���ӹ������

}

CMainRichEditView::~CMainRichEditView()
{
	m_pPropertyManage=NULL;
}

BOOL CMainRichEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CRichEditView::PreCreateWindow(cs);
}

void CMainRichEditView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// ���ô�ӡ�߾�(720 � = 1/2 Ӣ��)
	SetMargins(CRect(720, 720, 720, 720));
}


// CMainRichEditView ��ӡ


void CMainRichEditView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CMainRichEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}


void CMainRichEditView::OnDestroy()
{
	// ����ʱͣ�ô������
	// ʹ�ò����ͼʱ�ǳ���Ҫ 
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }

   if(m_pPropertyManage!=NULL)
	   delete m_pPropertyManage;//��������

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


// CMainRichEditView ���

#ifdef _DEBUG
void CMainRichEditView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CMainRichEditView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CEBEDoc* CMainRichEditView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEBEDoc)));
	return (CEBEDoc*)m_pDocument;
}
#endif //_DEBUG


// CMainRichEditView ��Ϣ�������


void CMainRichEditView::OnReplaceListAll()
{
	MisprintManage misprintManage;
	misprintManage.replaceListAll(this);
}

void CMainRichEditView::OnReplacelistSet()
{
	// TODO: �ڴ���������������
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
		_T("����")));                 // lpszFacename
//	format.UnionFontSize(this,&font);
	format.ChangeLineAuto(this);
}

void CMainRichEditView::OnFormatDelspacelines()
{
	// TODO: �ڴ���������������
	CFormat format;
	format.DelSpaceLines(this);
}

void CMainRichEditView::OnDeluselessspaces()
{
	// TODO: �ڴ���������������
	CFormat format;
	format.DelUselessSpaces(this);
}

void CMainRichEditView::OnUnionfontsize()
{
	// TODO: �ڴ���������������
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
		_T("����")));                 // lpszFacename
	format.UnionFontSize(this,&font);
}

void CMainRichEditView::OnChangelinesauto()
{
	// TODO: �ڴ���������������
	CFormat format;
	format.ChangeLineAuto(this);
}

void CMainRichEditView::OnDelfrontspaces()
{
	// TODO: �ڴ���������������
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
//�����ݼ�
void CMainRichEditView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//�ж��Ƿ���Ctrl+X��ϼ���
	//���������Ӧ�ĳ����ַ��б���ı���Ƶ���ͼ��
	if(::GetKeyState(VK_CONTROL)<0){
		CString usefulListItemText;
		switch(nChar){
			case '1':
				//��ȡ�����ַ����б�����Ӧ���ı�
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
	// TODO: �ڴ���������������
	LineStyleManage lineStyleManage;//����ʽ
	NoteNumStyleManage noteNumStyleManage;//ע�ͺ�
	NoteManage noteManage;//ע��
	TableStyleManage tableStyleManage;//���
	PictureStyleManage pictureStyleManage;//ͼƬ

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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���������������
	m_misprintManageDlg.OnMisprintCheck(this);
}

void CMainRichEditView::OnMisprintAddmisprint()
{
	// TODO: �ڴ���������������
	m_misprintDlg.ShowWindow(SW_NORMAL);
	m_misprintDlg.GetDlgItem(IDC_REPLACE_EDIT)->EnableWindow(FALSE);

	CString misprintString;
	misprintString=this->GetRichEditCtrl().GetSelText();
	if(!misprintString.IsEmpty()){
		m_misprintDlg.GetDlgItem(IDC_MISPRINT_EDIT)->
				SetWindowText(misprintString);
	}
	//��������ӵ�ʵ�ַŵ��˶Ի����OnOk������
}

BOOL CMainRichEditView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(!CRichEditView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext))
	return FALSE;

	m_nWordWrap = WrapNone;
	WrapChanged();


	//������Ӵ��ֶԻ���
	m_misprintDlg.Create(IDD_ADDMISPRINT_DLG);

	//��ʼ��m_pHtmlProperty
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	m_pPropertyManage=new CPropertyManage(
		pFrame->m_wndProperties.m_pHtmlProperty,
		pFrame->m_wndProperties.m_pPictureProperty);
	m_pPropertyManage->m_htmlFilePath=((CEBEApp*)::AfxGetApp())->m_htmlFilePath;

	//����������Ի���
	m_misprintManageDlg.Create(IDD_MisprintManageDlg);

	//������ݼ�
	hAccel=::LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));  

	return TRUE;
	
}

void CMainRichEditView::OnMisprintSet()
{
	// TODO: �ڴ���������������
	this->m_misprintManageDlg.SetMisprintSet();
	
}

void CMainRichEditView::OnOutputHtml()
{
	// TODO: �ڴ���������������

	this->SetFocus();//�����������

	//��������ļ���·��
	m_pPropertyManage->m_htmlFilePath=((CEBEApp*)AfxGetApp())->m_htmlFilePath;
	OutputManage outputManage;
	outputManage.StartOutput(&this->GetRichEditCtrl(),OUTPUT_HTML);
}

//���Html�ļ�
void CMainRichEditView::OnBrowserBtn()
{
	//����������Html�ļ�
	OnOutputHtml();

	//���Html�ļ�
	//��õ�ǰ����ļ���·��  
	CString sIniFilePath;
	sIniFilePath=((CEBEApp*)AfxGetApp())->m_htmlFilePath;

	CString htmlPath;
	htmlPath.Format(sIniFilePath+_T("p-%s.html"),m_pPropertyManage->m_pHtmlProperty->GetCurPage());
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	if(PathFileExists(htmlPath))
		pFrame->m_pHtmlViewCtrl->Navigate(htmlPath);

}


//����ת����
void CMainRichEditView::OnGbtobig5()
{
	// TODO: �ڴ���������������
	CGBtoBig5 GBtoBig5;
	
	CString ViewText;
	CRichEditCtrl* pRichEditCtrl=&this->GetRichEditCtrl();
	pRichEditCtrl->SetSel(0,-1);
	ViewText=pRichEditCtrl->GetSelText();
	
	CString replaceString=GBtoBig5.GBtoBig5(ViewText);
	pRichEditCtrl->ReplaceSel(replaceString);
}

//����ת����
void CMainRichEditView::OnBig5togb()
{
	// TODO: �ڴ���������������
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
	//�Զ�������
	this->OnMisprintCheck();

	//�Զ��Ű�
	CFormat format;
	format.DelSpaceLines(this);
	format.DelUselessSpaces(this);

	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	//format.ReplaceKeySymbol(pFrame->m_pSymbolReplaceSetDlg,this);
	//ȫѡ��Ȼ��ɾ����ǰ�ո�
	this->GetRichEditCtrl().SetSel(0,-1);

	format.DelFrontSpaces(this);

	//�Զ������滻�б�����滻
	if(this->m_repSetDlg.m_IsAutoReplace){
		this->OnReplaceListAll();
	}
}
void CMainRichEditView::OnChnengSymbolReplace()
{
	// TODO: �ڴ���������������
	CFormat format;
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	format.ReplaceKeySymbol(pFrame->m_pSymbolReplaceSetDlg,this);
}

BOOL CMainRichEditView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
//	if(::TranslateAccelerator(GetSafeHwnd(),hAccel,pMsg))   
//        return   true;
	return CRichEditView::PreTranslateMessage(pMsg);
}
