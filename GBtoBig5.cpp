#include "StdAfx.h"
#include "GBtoBig5.h"

CGBtoBig5::CGBtoBig5(void)
{
}

CGBtoBig5::~CGBtoBig5(void)
{
}

CString CGBtoBig5::Big5toGB(CString BigString)
{
	//---------------------------- 
	//函数输入Big5字符，返回Gb简体字符 
	//---------------------------- 
	char* pszGbs=NULL; //Gb编码的简体字符 
	int iLen=0; //需要转换的字符数 
	CString sGb; //返回的字符串 
	//计算转换的字符数 
	iLen = ::WideCharToMultiByte(936, NULL, BigString, 2*wcslen(BigString), NULL, 0, NULL, NULL);
	//给pszGbs分配内存 
	pszGbs=new char[2*iLen+1];
	memset(pszGbs,0,2*iLen+1);
	//转换Gb码繁体到Gb码简体，使用API函数LCMapString 
	LCMapString(0x0804,LCMAP_SIMPLIFIED_CHINESE, BigString, -1,(LPWSTR)pszGbs, 2*iLen); 
	//返回Gb码简体字符 
	sGb=(LPCTSTR)pszGbs; 
	//释放内存
	delete [] pszGbs; //刪除出錯，不知道什麽原因
	return sGb;
}
CString CGBtoBig5::GBtoBig5(CString GBString)
{
	//---------------------------- 
	//函数输入GB简体字符，返回Big5繁体字符 
	//---------------------------- 
	char* pszBig5=NULL; //Gb编码的简体字符 
	int iLen=0; //需要转换的字符数 
	CString sBig5; //返回的字符串 
	//计算转换的字符数 
	iLen = ::WideCharToMultiByte(936, NULL, GBString, 2*wcslen(GBString), NULL, 0, NULL, NULL);
	//给pszGbs分配内存 
	pszBig5=new char[2*iLen+1];
	memset(pszBig5,0,2*iLen+1);
	//转换Gb码繁体到Gb码简体，使用API函数LCMapString 
	LCMapString(0x0804,LCMAP_TRADITIONAL_CHINESE, GBString, -1,(LPWSTR)pszBig5, 2*iLen); 
	//返回Gb码简体字符 
	sBig5=(LPCTSTR)pszBig5;
	//释放内存
	delete [] pszBig5; //刪除出錯，不知道什麽原因
	return sBig5;
}
