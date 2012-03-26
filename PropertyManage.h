#pragma once
#include "htmlproperty.h"
#include "PictureProperty.h"

class CPropertyManage
{
public:
	CPropertyManage(CHtmlProperty* pHtmlProperty,CPictureProperty* pPictureProperty);
	virtual ~CPropertyManage(void);
	CPropertyManage(void);

public:
	CString getModelFileName();
	void UpdataData(bool IsDownLoad);

public:
	//Ò³Ãæ
	CString m_bookName;
	CString m_PageNum;
	int m_LeftRightPage;
	int m_NoteNumType;
	CString m_NoteType;
	CString m_modelFileName;
	CString m_textStyle;

	//Í¼Æ¬
	CString m_pictureName;
	CString m_pictureHeight;
	CString m_pictureWidth;
	int m_picturePos;
public:
	CHtmlProperty* m_pHtmlProperty;
	CPictureProperty* m_pPictureProperty;

	CString m_htmlFilePath;
};
