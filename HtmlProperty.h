#pragma once

class CHtmlProperty: public CMFCPropertyGridProperty
{
public:
	CHtmlProperty();
	virtual ~CHtmlProperty();

	void AddModelOpatoin(CString modelName);
	CString GetBookName();
	CString GetCurPage();
	int GetPageLeftRight();//×óÒ³·µ»Ø1£¬ÓÒÒ³·µ»Ø2
	int GetExpStyle();//°¢À­²®Êý×Ö·µ»Ø1£¬Ô²È¦·µ»Ø2
//	void GetPicProperty(CPicProperty* picPro);
	CString SetPage(CString pageNum);
	int SetPageLeftRight(int pageLeftRight);//×óÒ³·µ»Ø1£¬ÓÒÒ³·µ»Ø2
	CString GetModel();
	CString GetExpModel();
	CString GetTextCss();
	void SetTextCss(CString textCss);
	void SetBookName(CString bookName);
	void SetModel(CString model);
	void SetExpModel(CString expModel);
	void SetExpStyle(int expStyle);
	void RemoveModelAllOpation();
public:
	CString strGroupName;
};
