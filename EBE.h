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

// EBE.h : EBE Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#include "FileManage.h"
#include "NoteModelDlg.h"

// CEBEApp:
// �йش����ʵ�֣������ EBE.cpp
//

class CEBEApp : public CWinAppEx
{
public:
	CEBEApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	afx_msg void OnOpenNextFile();
	DECLARE_MESSAGE_MAP()
protected:
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);

public:
	CFileManage m_fileManage;
	CString m_htmlFilePath;
	CNoteModelDlg m_noteModelDlg;
	afx_msg void OnHtmlSaveas();
	afx_msg void OnNoteModelSet();
};

extern CEBEApp theApp;
