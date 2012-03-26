#include "StdAfx.h"
#include "WinTxtTranslation.h"

enum{NOTENUMTYPE_ARAB=1,NOTENUMTYPE_AIRCLE};

WinTxtTranslation::WinTxtTranslation(void)
{
}

WinTxtTranslation::~WinTxtTranslation(void)
{
}

void WinTxtTranslation::StartTranslate(CRichEditCtrl *pRichEditCtrl,CPropertyManage* propertyManage,CSymbolReplaceSetDlg* pSymbolReplaceSetDlg)
{
	this->m_pRichEditCtrl=pRichEditCtrl;
	this->m_pPropertyManage=propertyManage;
	this->m_pSymbolReplaceSetDlg=pSymbolReplaceSetDlg;

	//开始
	ReadWinTxt();
	//标识注释编号
	MarkNoteNum();
	//处理段样式标识
	HandleSectionStyle();
	//中英文字符替换
	KeyWordReplace();
	//标识符处理
	MarkHandle();
}

void WinTxtTranslation::ReadWinTxt()
{
	wchar_t wch[500];
	CString lineText;//每一行的文本
	int lineCount=m_pRichEditCtrl->GetLineCount();

	for(int i=0;i<lineCount;i++){
		memset(wch,0,500);
		m_pRichEditCtrl->GetLine(i,wch,500);
		lineText=wch;
		lineText.TrimRight(_T("\n"));
		lineText.TrimRight(_T("\r"));
		lineText.TrimRight(_T(" "));
		if(lineText.GetLength()<1)//空行不管
			continue;
		//删除多余空格
		DelExcessSpace(lineText);

		//行样式标识
		MarkLineStyle(lineText);

		//将每一行写入容器
		m_vecEachLine.push_back(lineText);
	}
}

int WinTxtTranslation::DelExcessSpace(CString& lineText)
{//删除多余空格
	int delCunt=0;
	int delpos=-1;
	delpos=lineText.FindOneOf(_T(" "));
	while(delpos>=0){
		if(delpos<=0){
			delpos=lineText.Find(_T(" "),delpos+1);
			continue;
		}
		delCunt++;
		if(!((lineText[delpos-1]<='z'&&lineText[delpos-1]>='a')||
			(lineText[delpos-1]<='Z'&&lineText[delpos-1]>='A')||
			lineText[delpos-1]==' '))
		{
			lineText.Delete(delpos,1);
			delpos--;//更新检测的起始位置
		}
		else
			delCunt--;
		delpos=lineText.Find(_T(" "),delpos+1);
	}
	return delCunt;
}

void WinTxtTranslation::KeyWordReplace()
{
	CString lineText;
	for(int i=0;i<(int)m_vecEachLine.size();i++){
		lineText=m_vecEachLine[i];
		if(m_pSymbolReplaceSetDlg->m_nSelect==1)
			//不是全文替换的话，注释文本不替换
			if(lineText.Find(_T("**注释**"))!=-1)
				break;

		//已将符号替换的操作放到了前台，这里就不需要了
//		ReplaceFromReplaceSetDlg(lineText);

		m_vecEachLine[i]=lineText;
	}
}

//判断是否为转义字符
void WinTxtTranslation::findIsESC(CString& lineText)
{
	int startPos=0;
	int symbolPos=0;
	while(startPos>=0){
		startPos=lineText.Find(_T("&"),startPos);
		if(startPos<0)
			break;
		symbolPos=lineText.Find(_T("；"),startPos);
		if(symbolPos<0)
			break;
		if(symbolPos-startPos<10){//判断转义字符长度少于10
			lineText.SetAt(symbolPos,';');
		}
	}
}

void WinTxtTranslation::ReplaceFromReplaceSetDlg(CString& lineTextToReplace)
{
	//标点符号替换
	m_pSymbolReplaceSetDlg->UpdateData(true);//刷新数据

	if(m_pSymbolReplaceSetDlg->m_Symbol1)//逗号
	{
		if(m_pSymbolReplaceSetDlg->m_editString1.IsEmpty())
			lineTextToReplace.Replace(_T(","),_T("，"));
		else{
			lineTextToReplace.Replace(_T(","),
				m_pSymbolReplaceSetDlg->m_editString1);
		}
	}

	if(m_pSymbolReplaceSetDlg->m_Symbol2)//句号
	{
		if(m_pSymbolReplaceSetDlg->m_editString2.IsEmpty())
			lineTextToReplace.Replace(_T("."),_T("。"));
		else{
			lineTextToReplace.Replace(_T("."),
				m_pSymbolReplaceSetDlg->m_editString2);
		}
	}

	if(m_pSymbolReplaceSetDlg->m_Symbol3)//分号
	{
		if(m_pSymbolReplaceSetDlg->m_editString3.IsEmpty())
		{
			lineTextToReplace.Replace(_T(";"),_T("；"));
			findIsESC(lineTextToReplace);//判断是否为转义字符
		}
		else{
			lineTextToReplace.Replace(_T(";"),
				m_pSymbolReplaceSetDlg->m_editString3);
		}
	}

	if(m_pSymbolReplaceSetDlg->m_Symbol4)//冒号
	{
		if(m_pSymbolReplaceSetDlg->m_editString4.IsEmpty())
			lineTextToReplace.Replace(_T(":"),_T("："));
		else{
			lineTextToReplace.Replace(_T(":"),
				m_pSymbolReplaceSetDlg->m_editString4);
		}
	}

	if(m_pSymbolReplaceSetDlg->m_Symbol5)//波浪号
	{	
		if(m_pSymbolReplaceSetDlg->m_editString5.IsEmpty())
			lineTextToReplace.Replace(_T("~"),_T("～"));
		else{
			lineTextToReplace.Replace(_T("~"),
				m_pSymbolReplaceSetDlg->m_editString5);
		}
	}

	if(m_pSymbolReplaceSetDlg->m_Symbol6)//破折号
	{
		if(m_pSymbolReplaceSetDlg->m_editString6.IsEmpty())
			lineTextToReplace.Replace(_T("--"),_T("—"));
		else{
			lineTextToReplace.Replace(_T("--"),
				m_pSymbolReplaceSetDlg->m_editString6);
		}
	}

	if(m_pSymbolReplaceSetDlg->m_Symbol7)//括号
	{
		lineTextToReplace.Replace(_T("("),_T("（"));
		lineTextToReplace.Replace(_T(")"),_T("）"));
	}

	if(m_pSymbolReplaceSetDlg->m_Symbol8)//单破折号
	{
		if(m_pSymbolReplaceSetDlg->m_editString8.IsEmpty())
			lineTextToReplace.Replace(_T("-"),_T("—"));
		else{
			lineTextToReplace.Replace(_T("-"),
				m_pSymbolReplaceSetDlg->m_editString8);
		}
	}

	if(m_pSymbolReplaceSetDlg->m_IsDoubleDash)//双破折号替换
	{
		CString replaceStr;
		m_pSymbolReplaceSetDlg->m_doubleDashEdit.GetWindowTextW(replaceStr);
		lineTextToReplace.Replace(_T("——"),replaceStr);
	}
}
//这里暂时没用到
void WinTxtTranslation::EngChnRep(CString& lineText)
{
	int pos=0;
	while(pos!=-1){
		pos=lineText.Find(_T("，"),pos);
		if(pos>0){
		if((lineText[pos-1]>='a'&&lineText[pos-1]<='z')||
			(lineText[pos-1]>='A'&&lineText[pos-1]<='Z')||
			(lineText[pos-1]>='0'&&lineText[pos-1]<='9'))
			if(lineText.GetLength()!=pos+1){
				if((lineText[pos+1]>='a'&&lineText[pos+1]<='z')||
			(lineText[pos+1]>='A'&&lineText[pos+1]<='Z')||
			(lineText[pos+1]>='0'&&lineText[pos+1]<='9')){
					lineText.SetAt(pos,',');
				}
			}
			else
			{
				lineText.SetAt(pos,',');
			}
			
		if(lineText.GetLength()==pos)
			break;
		pos++;
		}
	}

	pos=0;
	while(pos!=-1){
		pos=lineText.Find(_T("．"),pos);
		if(pos>0){
		if((lineText[pos-1]>='a'&&lineText[pos-1]<='z')||
			(lineText[pos-1]>='A'&&lineText[pos-1]<='Z')||
			(lineText[pos-1]>='0'&&lineText[pos-1]<='9'))
			if(lineText.GetLength()!=pos+1){
				if((lineText[pos+1]>='a'&&lineText[pos+1]<='z')||
			(lineText[pos+1]>='A'&&lineText[pos+1]<='Z')||
			(lineText[pos+1]>='0'&&lineText[pos+1]<='9')){
					lineText.SetAt(pos,'.');
				}
			}
			else
			{
				lineText.SetAt(pos,'.');
			}
			
		if(lineText.GetLength()==pos)
			break;
		pos++;
		}
	}

	pos=0;
	while(pos!=-1){
		pos=lineText.Find(_T("；"),pos);
		if(pos>0){
		if((lineText[pos-1]>='a'&&lineText[pos-1]<='z')||
			(lineText[pos-1]>='A'&&lineText[pos-1]<='Z')||
			(lineText[pos-1]>='0'&&lineText[pos-1]<='9'))
			if(lineText.GetLength()!=pos+1){
				if((lineText[pos+1]>='a'&&lineText[pos+1]<='z')||
			(lineText[pos+1]>='A'&&lineText[pos+1]<='Z')||
			(lineText[pos+1]>='0'&&lineText[pos+1]<='9')){
					lineText.SetAt(pos,';');
				}
			}
			else
			{
				lineText.SetAt(pos,';');
			}
			
		if(lineText.GetLength()==pos)
			break;
		pos++;
		}
	}
}

void WinTxtTranslation::MarkLineStyle(CString& lineText)
{
	int findIndex=-1;
	//检测nobr
	if(lineText.Find(_T("<nobr>"))!=-1){
		lineText.Replace(_T("<nobr>"),_T("##nobr##"));
	}

	//检测letter-spaing
	findIndex=lineText.Find(_T("<LS="));
	if(findIndex!=-1){
		lineText.Replace(_T("<LS="),_T("##LS="));
		findIndex=lineText.Find(_T(">"),findIndex+1);
		if(findIndex!=-1){
			lineText.Delete(findIndex,1);
			lineText.Insert(findIndex,_T("##"));
		}
	}

	//检测<em>
	//<em>不需要检测
}

void WinTxtTranslation::MarkNoteNum()
{
	bool IsFirst=true;
	int cstrIndex=0;
	CString expStart=_T("^^^");//包住注释编号的标识符
	CString expEnd=_T("^^^");
	CString strExpNum=_T("");

	CString lineText;//每行的内容

	//确定注释样式
	int noteNumType=m_pPropertyManage->m_pHtmlProperty->GetExpStyle();

	for(int index=0;index<(int)m_vecEachLine.size();index++){
		lineText=m_vecEachLine[index];
		CString lenstr(lineText);//转为CSringW格式，获取字符数
		int len=lineText.GetLength();//得到这一行的字符数，而不是字节数
		int i=0;

		//判断是否到注释文本
		if(lineText.Find(_T("**注释**"))!=-1){
			lineText=_T("##**注释**");//增加"#"来标识注释开始
			m_vecEachLine[index]=lineText;
			return;
		}

		switch(noteNumType)//注释样式
		{
		case NOTENUMTYPE_ARAB://阿拉伯数字样式
			if(-1==lineText.Find(_T("<**")))
				break;
			lineText.Replace(_T("<**"),expStart);
			lineText.Replace(_T("**>"),expEnd);
			break;
		case NOTENUMTYPE_AIRCLE://圆圈样式
			for(i=0;i<len;i++){
				if(lenstr[i]>=9312&&lenstr[i]<=9322){//查找圆圈型注释字符
			/*		//前三个很可能进入了注释文本，注释文本不需要添加<span>
					if(i<=2)
						break;*/
					CString strExpNum(lenstr[i]);
					lineText.Replace(strExpNum,expStart+strExpNum+expEnd);
				}
			}
			break;
		default:
			break;
		}

		//保存修改后的文本
		m_vecEachLine[index]=lineText;
	}
}
void WinTxtTranslation::HandleSectionStyle()
{
	//初始化CssStyle容器
	for(std::vector<CString>::iterator iter=m_vecEachLine.begin();iter!=m_vecEachLine.end();iter++){
		std::vector<CString> vecStr;
		vecStr.push_back(_T(""));
		vecStr.push_back(_T(""));
		vecStr.push_back(_T(""));
		m_vecSectionStyle.push_back(vecStr);
	}

	int originTextLine=0;
	CString lineText;
	//遍历vector容器
	for(std::vector<CString>::iterator iter=m_vecEachLine.begin();iter!=m_vecEachLine.end();){
		lineText=*iter;
		lineText.TrimRight(_T("\n"));
		lineText.TrimRight(_T("\r"));
		lineText.TrimRight(_T(" "));

		//正式文本行递增
		originTextLine++;

		//检测是否是cssStyle样式标识行
		if(lineText.Find(_T("$class="))!=-1){
			RecordSectionStyle(lineText,originTextLine-1);
			originTextLine--;
			iter=m_vecEachLine.erase(iter);//因为erase之后的iterator会无效
		}
		else{
			++iter;//因为erase会使iterator无效
		}
		/////////////////////////////////////
	}

}

void WinTxtTranslation::RecordSectionStyle(CString lineText, int lineIndex)
{
	if(m_vecSectionStyle.empty())
		return;
	CString cssStr;
	CString styleStr;
	//删除多余的标识符号
	lineText.Replace(_T("$"),_T(""));

	int pos;
	//获取class
	pos=lineText.Find(_T("style"));
	cssStr=lineText.Left(pos);
	cssStr.TrimRight(_T(" "));
	cssStr.TrimRight(_T("\""));
	cssStr.TrimLeft(_T(" "));
	cssStr.Replace(_T("<class=\""),_T(""));

	//获取style
	styleStr=lineText.Right(lineText.GetLength()-pos);
	styleStr.TrimRight(_T(" "));
	styleStr.TrimRight(_T(">"));


	//标记每行的cssStyle
	m_vecSectionStyle[lineIndex][0]=_T("##paraStart##");
	m_vecSectionStyle[lineIndex][1]=cssStr;
	m_vecSectionStyle[lineIndex][2]=styleStr;
}

void WinTxtTranslation::MarkHandle()
{
	CString lineText;
	for(std::vector<CString>::iterator iter=m_vecEachLine.begin();iter!=m_vecEachLine.end();iter++){
		lineText=*iter;
		//判断是否是图片标识行
		if(lineText.Compare(_T("**Pic_Start**"))==0){
			//写入图片开始标识符
			lineText=_T("pic#start");
		}

		if(lineText.Compare(_T("**Pic_End**"))==0){
			//写入图片结束标识符
			lineText=_T("pic#start");
		}
		//判断是否是表格标识行
		if(lineText.Find(_T("**Table_Start**"))!=-1){
			//表格开始
			lineText=_T("table#start");
		}
		if(lineText.Find(_T("**Table_End**"))!=-1){
			//表格结束
			lineText=_T("table#end");
		}
		
		//更新修改的文本
		*iter=lineText;
	}
}