#include "StdAfx.h"
#include "PropertyManage.h"
#include "MainFrm.h"

CPropertyManage::CPropertyManage(void)
{
}

CPropertyManage::~CPropertyManage(void)
{
}

CString CPropertyManage::getModelFileName()
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetApp()->GetMainWnd();
	return pMainFrame->m_mapModel.m_mapModel[this->m_pHtmlProperty->GetModel()];
}

CPropertyManage::CPropertyManage(CHtmlProperty* pHtmlProperty,CPictureProperty* pPictureProperty)
{
	this->m_pHtmlProperty=pHtmlProperty;
	this->m_pPictureProperty=pPictureProperty;

	this->UpdataData(true);
	
}

void CPropertyManage::UpdataData(bool IsDownLoad)
{
	if(IsDownLoad){
		this->m_bookName=this->m_pHtmlProperty->GetBookName();
		this->m_LeftRightPage=this->m_pHtmlProperty->GetPageLeftRight();
		this->m_modelFileName=this->m_pHtmlProperty->GetModel();
		this->m_NoteNumType=this->m_pHtmlProperty->GetExpStyle();
		this->m_NoteType=this->m_pHtmlProperty->GetExpModel();
		this->m_PageNum=this->m_pHtmlProperty->GetCurPage();
		this->m_textStyle=this->m_pHtmlProperty->GetTextCss();

		this->m_pictureName=this->m_pPictureProperty->GetPictureName();
		this->m_pictureHeight=this->m_pPictureProperty->GetPictureHight();
		this->m_pictureWidth=this->m_pPictureProperty->GetPictureWidth();
		this->m_picturePos=this->m_pPictureProperty->GetPictureAlign();
	}
	else{
		this->m_pHtmlProperty->SetPage(this->m_PageNum);
		this->m_pHtmlProperty->SetPageLeftRight(this->m_LeftRightPage);
		this->m_pHtmlProperty->SetBookName(this->m_bookName);
		this->m_pHtmlProperty->SetModel(this->m_modelFileName);
		this->m_pHtmlProperty->SetExpStyle(this->m_NoteNumType);
		this->m_pHtmlProperty->SetExpModel(this->m_NoteType);
		this->m_pHtmlProperty->SetTextCss(this->m_textStyle);

		this->m_pPictureProperty->SetPictureName(this->m_pictureName);
		this->m_pPictureProperty->SetPictureHight(this->m_pictureHeight);
		this->m_pPictureProperty->SetPictureWidth(this->m_pictureWidth);
		this->m_pPictureProperty->SetPictureAlign(this->m_picturePos);
	}
	
}