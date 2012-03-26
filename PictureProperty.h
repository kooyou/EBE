#pragma once

enum{PICTURE_ALIGN_LEFT=1,PICTURE_ALIGN_RIGHT,PICTURE_ALIGN_CENTER};

// CPictureProperty ÃüÁîÄ¿±ê

class CPictureProperty : public CMFCPropertyGridProperty
{
public:
	CPictureProperty();
	virtual ~CPictureProperty();

public:
	CString strGroupName;

public:
	int GetPictureAlign();
	CString GetPictureName();
	CString GetPictureHight();
	CString GetPictureWidth();
	void SetPictureWidth(CString pictureWidth);
	void SetPictureHight(CString pictureHight);
	void SetPictureName(CString pictureName);
	void SetPictureAlign(int align);

};


