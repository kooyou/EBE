#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CHtmlView。"
#endif 

// CHtmlViewCtrl Html 视图

class CHtmlViewCtrl : public CHtmlView
{
	DECLARE_DYNCREATE(CHtmlViewCtrl)

public:
	CHtmlViewCtrl();           // 动态创建所使用的受保护的构造函数
	virtual ~CHtmlViewCtrl();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};


