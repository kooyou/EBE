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
	//��������Big5�ַ�������Gb�����ַ� 
	//---------------------------- 
	char* pszGbs=NULL; //Gb����ļ����ַ� 
	int iLen=0; //��Ҫת�����ַ��� 
	CString sGb; //���ص��ַ��� 
	//����ת�����ַ��� 
	iLen = ::WideCharToMultiByte(936, NULL, BigString, 2*wcslen(BigString), NULL, 0, NULL, NULL);
	//��pszGbs�����ڴ� 
	pszGbs=new char[2*iLen+1];
	memset(pszGbs,0,2*iLen+1);
	//ת��Gb�뷱�嵽Gb����壬ʹ��API����LCMapString 
	LCMapString(0x0804,LCMAP_SIMPLIFIED_CHINESE, BigString, -1,(LPWSTR)pszGbs, 2*iLen); 
	//����Gb������ַ� 
	sGb=(LPCTSTR)pszGbs; 
	//�ͷ��ڴ�
	delete [] pszGbs; //�h�����e����֪��ʲ��ԭ��
	return sGb;
}
CString CGBtoBig5::GBtoBig5(CString GBString)
{
	//---------------------------- 
	//��������GB�����ַ�������Big5�����ַ� 
	//---------------------------- 
	char* pszBig5=NULL; //Gb����ļ����ַ� 
	int iLen=0; //��Ҫת�����ַ��� 
	CString sBig5; //���ص��ַ��� 
	//����ת�����ַ��� 
	iLen = ::WideCharToMultiByte(936, NULL, GBString, 2*wcslen(GBString), NULL, 0, NULL, NULL);
	//��pszGbs�����ڴ� 
	pszBig5=new char[2*iLen+1];
	memset(pszBig5,0,2*iLen+1);
	//ת��Gb�뷱�嵽Gb����壬ʹ��API����LCMapString 
	LCMapString(0x0804,LCMAP_TRADITIONAL_CHINESE, GBString, -1,(LPWSTR)pszBig5, 2*iLen); 
	//����Gb������ַ� 
	sBig5=(LPCTSTR)pszBig5;
	//�ͷ��ڴ�
	delete [] pszBig5; //�h�����e����֪��ʲ��ԭ��
	return sBig5;
}
