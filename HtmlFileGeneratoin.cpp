#include "StdAfx.h"
#include "HtmlFileGeneration.h"
#include "EBE.h"
#include <locale>

HtmlFileGeneration::HtmlFileGeneration(void)
{
	m_IsNote=false;
	m_IsDiv=false;
	m_IsFirstWriteExp=true;
	m_IsBr=false;
	m_lineNum=0;
}

HtmlFileGeneration::~HtmlFileGeneration(void)
{
}

void HtmlFileGeneration::StartGenerate(CPropertyManage* pPropertyManage,std::vector<CString>& vecEachLine,std::vector<std::vector<CString>>& vecSectionStyle)
{
	//初始化成员变量
	this->m_pPropertyManage=pPropertyManage;
	this->m_iterVecEachLine=vecEachLine.begin();
	this->m_iterVecEachLineEnd=vecEachLine.end();
	this->m_iterVecSectionStyle=vecSectionStyle.begin();
	
	//获取页号，并将页号前面的零去掉
	this->m_pageNum=m_pPropertyManage->m_pHtmlProperty->GetCurPage();
	m_pageNum.TrimLeft(_T("0"));

	//区域设定
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//设定

	//初始化文件
	if(!InitFiles())
		return;

	//遍历并处理
	TraverseVector(vecEachLine,vecSectionStyle);

	//输出Html文件
	OutputHtmlFile();

	//关闭打开的文件
	CloseFiles();

	//恢复区域设定
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定
}

bool HtmlFileGeneration::InitFiles()
{
	//获得当前可执行文件的路径  
	CString   sModFileName; 
	GetModuleFileName(NULL,sModFileName.GetBuffer(MAX_PATH),MAX_PATH);
	sModFileName.ReleaseBuffer(); 
	sModFileName.MakeReverse(); 
	m_sIniFilePath=sModFileName.Right(sModFileName.GetLength()-sModFileName.Find( '\\')); 
	m_sIniFilePath.MakeReverse();


	CString fPath;
	CString errMsg=_T("打开文件失败：");
	try{
		//网页图片（靠左开始）文件路径
		fPath=m_sIniFilePath+_T("system\\pic_left_start.txt");
		if(!m_fPicLeftStr.Open(fPath,CFile::modeRead)){
			errMsg=errMsg+fPath;
			AfxMessageBox(errMsg);
			return false;
		}
		//网页图片（靠右开始）文件路径
		fPath=m_sIniFilePath+_T("system\\pic_right_start.txt");
		if(!m_fPicRightStr.Open(fPath,CFile::modeRead)){
			errMsg=errMsg+fPath;
			AfxMessageBox(errMsg);
			return false;
		}
		//网页图片（靠左结束）文件路径
		fPath=m_sIniFilePath+_T("system\\pic_left_end.txt");
		if(!m_fPicLeftEnd.Open(fPath,CFile::modeRead)){
			errMsg=errMsg+fPath;
			AfxMessageBox(errMsg);
			return false;
		}
		//网页图片（靠右结束）文件路径
		fPath=m_sIniFilePath+_T("system\\pic_right_end.txt");
		if(!m_fPicRightEnd.Open(fPath,CFile::modeRead)){
			errMsg=errMsg+fPath;
			AfxMessageBox(errMsg);
			return false;
		}
		//网页图片（靠中开始）文件路径
		fPath=m_sIniFilePath+_T("system\\pic_center_start.txt");
		if(!m_fPicCenter.Open(fPath,CFile::modeRead)){
			errMsg=errMsg+fPath;
			AfxMessageBox(errMsg);
			return false;
		}

		//包括模板m_fHtmlWithModel(最终文件)
		CString sIniFilePath=m_pPropertyManage->m_htmlFilePath;
		fPath.Format(sIniFilePath+_T("p-%s.html"),m_pageNum);
		if(!m_fHtmlWithModel.Open(fPath,CFile::modeReadWrite|CFile::modeCreate)){
			errMsg=errMsg+fPath;
			AfxMessageBox(errMsg);
			return false;
		}
	}
	catch(CFileException fe){
		AfxMessageBox(_T("生成Html文件是打开文件失败!"));
	}
	m_htmlFileName=fPath;//记录当前写入的html文件的名字
	return true;
}

void HtmlFileGeneration::CloseFiles()
{
	this->m_fHtmlWithModel.Close();
	this->m_fPicCenter.Close();
	this->m_fPicLeftEnd.Close();
	this->m_fPicLeftStr.Close();
	this->m_fPicRightEnd.Close();
	this->m_fPicRightStr.Close();
}

void HtmlFileGeneration::TraverseVector(std::vector<CString>& vecEachLine,std::vector<std::vector<CString>>& vecSectionStyle)
{
	CString lineText;
	int normalTextLineNum=0;//正常文本，根据行号为段添加css样式

	for(std::vector<CString>::iterator iter=vecEachLine.begin();iter!=vecEachLine.end();++iter)
	{
		lineText=*iter;
		
		if(lineText.IsEmpty())
			continue;

		normalTextLineNum++;//每读一行有效文本，段落CSS标识行增加1

		//处理图片标识
		if(TRUE==HandlePictureMark(iter))
			continue;

		//处理表格标识
		std::vector<CString>::iterator iterOld=iter;
		iter=HandleTableMark(iter);
		if(iterOld!=iter){
			normalTextLineNum=normalTextLineNum+(iter-iterOld);
			continue;
		}

		//当前增加行数
		m_lineNum++;

		if(m_IsNote){//判断现在是否写入注释文本
			WriteNote(lineText);
			continue;
		}
		switch(lineText[0])
		{
		case '#':
			m_IsNote=true;
			m_lineNum--;
			break;//开始注释
		case ' ':
			if(lineText[1]==' ')
				WriteSectionStyle(lineText,normalTextLineNum-1,vecSectionStyle);
			//写入基本格式的文本
			break;
		default://正常写入
			WriteEachLine(lineText);
		}  
	}

	//判断Div是否闭合
	WriteDiv();
}
void HtmlFileGeneration::AddHtmlVector(CString lineText)
{
	this->m_vecHtml.push_back(lineText);
}

std::vector<CString>::iterator HtmlFileGeneration::HandleTableMark(
		std::vector<CString>::iterator iter)
{
	CString lineText=*iter;
	//判断是否是表格标识行
	if(lineText.Compare(_T("table#start"))!=0)
		return iter;

	//表格开始
	WriteDiv();//是否写入</div>
	WriteTableStart();

	iter++; //丢弃标识行

	while(true){
		if(iter==m_iterVecEachLineEnd)
			return --iter;
		lineText=*iter;
		if(lineText.Compare(_T("table#end"))==0){
			//表格结束
			WriteTableText();
			WriteTableEnd();

			break;
		}
		m_tableManage.SplitTableText(lineText);

		iter++;
	}
	return iter;
}
void HtmlFileGeneration::WriteTableText()
{
	CString tabStr;
	CString tr=_T("                    <tr>\n");
	CString trEnd=_T("                    </tr>\n");
	CString td;
	int TabWidth=0;//方便替换
	CString widthStr;
	for(int i=0;i<(int)m_tableManage.m_vecTableStr.size();i++){
		AddHtmlVector(tr);
		TabWidth=100;//方便替换
		for(int j=0;j<(int)m_tableManage.m_vecTableStr[i].size();j++){
			tabStr=m_tableManage.m_vecTableStr[i].at(j);
			td=_T("                    <td>####</td>\n");//不需要td1
			widthStr.Format(_T("%d"),TabWidth++);//方便替换
			td.Replace(_T("##width##"),widthStr);
			td.Replace(_T("####"),tabStr);

			HandleNoteNum(td);//处理注释符

			AddHtmlVector(td);
		}
		AddHtmlVector(trEnd);
	}
}
BOOL HtmlFileGeneration::HandlePictureMark(std::vector<CString>::iterator iter)
{
	CString lineText=*iter;
	//判断是否是图片标识行
		if(lineText.Compare(_T("pic#start"))==0){
			//图片开始
			WritePicStart();
			return TRUE;
		}
		if(lineText.Compare(_T("pic#end"))==0){
			//图片结束
			WritePicEnd();
			return TRUE;
		}
		return FALSE;
}

void HtmlFileGeneration::WritePicStart()
{//写入图片开始标识
	if(m_IsDiv){//是否需要写入</div>结束标签
		AddHtmlVector(_T("            	</div>\n"));
		m_IsDiv=false;
	}
	CString lineText;
	switch(m_pPropertyManage->m_pPictureProperty->GetPictureAlign()){
		case PICTURE_ALIGN_CENTER://居中
			while(m_fPicCenter.ReadString(lineText)){
				lineText.Replace(_T("$$$$"),this->m_pageNum);
				lineText.Replace(_T("@@@@"),m_pPropertyManage->m_pPictureProperty->GetPictureName());//图片名字
				CString pro;
				pro.Format(_T("%s"),m_pPropertyManage->m_pPictureProperty->GetPictureWidth());//图片宽度
				lineText.Replace(_T("####"),pro);
				pro.Format(_T("%s"),m_pPropertyManage->m_pPictureProperty->GetPictureHight());//图片高度
				lineText.Replace(_T("&&&&"),pro);
				AddHtmlVector(lineText);//文字宽度
				AddHtmlVector(_T("\n"));
			}
			break;
		case PICTURE_ALIGN_LEFT://靠左
			while(m_fPicLeftStr.ReadString(lineText)){
				lineText.Replace(_T("$$$$"),this->m_pageNum);
				lineText.Replace(_T("@@@@"),m_pPropertyManage->m_pPictureProperty->GetPictureName());
				CString pro;
				pro.Format(_T("%s"),m_pPropertyManage->m_pPictureProperty->GetPictureWidth());
				lineText.Replace(_T("####"),pro);
				pro.Format(_T("%s"),m_pPropertyManage->m_pPictureProperty->GetPictureHight());
				lineText.Replace(_T("&&&&"),pro);
				pro.Format(_T("%d"),580-10-_wtoi(m_pPropertyManage->m_pPictureProperty->GetPictureWidth()));
				lineText.Replace(_T("##text##"),pro);
				AddHtmlVector(lineText);
				AddHtmlVector(_T("\n"));
			}
			break;
		case PICTURE_ALIGN_RIGHT://靠右
			while(m_fPicRightEnd.ReadString(lineText)){
				lineText.Replace(_T("$$$$"),this->m_pageNum);
				lineText.Replace(_T("@@@@"),m_pPropertyManage->m_pPictureProperty->GetPictureName());
				CString pro;
				pro.Format(_T("%s"),m_pPropertyManage->m_pPictureProperty->GetPictureWidth());
				lineText.Replace(_T("####"),pro);
				pro.Format(_T("%s"),m_pPropertyManage->m_pPictureProperty->GetPictureHight());
				lineText.Replace(_T("&&&&"),pro);
				pro.Format(_T("%d"),580-10-_wtoi(m_pPropertyManage->m_pPictureProperty->GetPictureWidth()));
				lineText.Replace(_T("##text##"),pro);
				AddHtmlVector(lineText);
				AddHtmlVector(_T("\n"));
			}
			break;
		default:
			break;
	}
}

void HtmlFileGeneration::WritePicEnd()
{

	//是否需要写入</div>结束标签
	WriteDiv();

	CString lineText;
	switch(m_pPropertyManage->m_pPictureProperty->GetPictureAlign()){
		case PICTURE_ALIGN_CENTER://居中
			break;
		case PICTURE_ALIGN_LEFT://靠左
			while(m_fPicLeftEnd.ReadString(lineText)){
				AddHtmlVector(lineText);
				AddHtmlVector(_T("\n"));
			}
			break;
		case PICTURE_ALIGN_RIGHT://靠右
			break;
		default:
			break;
	}
}
void HtmlFileGeneration::WriteTableStart()
{
	AddHtmlVector(_T("            	<div align=\"center\">"));
	AddHtmlVector(_T("\n"));
	AddHtmlVector(_T("                  <table border=\"0\" cellspacing=\"0\" cellpadding=\"0\">"));
	AddHtmlVector(_T("\n"));
}
void HtmlFileGeneration::WriteTableEnd()
{
	AddHtmlVector(_T("                   </table>"));
	AddHtmlVector(_T("\n"));
	AddHtmlVector(_T("               </div>"));
	AddHtmlVector(_T("\n"));
}
void HtmlFileGeneration::WriteNote(CString &expText)
{
	WriteDiv();//写入</div>

	if(expText.IsEmpty())
		return;

	CEBEApp *app=(CEBEApp*)AfxGetApp();

	CString lineStyle=HandleLineStyleMark(expText);//处理行标识符

	//首次写入注释文本时写入标识信息
	if(m_IsFirstWriteExp){
		m_IsFirstWriteExp=false;
		AddHtmlVector(_T("<!--explain_text_start-->\n"));
	}

	//判断是否要将注释命名
	CString expName=_T("");
	if(true){
		if(true){
			expName.Format(_T("name=\"p-%s-%d\""),
				m_pageNum,this->m_lineNum);
		}
		/*else{
			expName.Format(_T("name=\"p-%s-%d\" %s"),
				m_pPropertyManage->m_pHtmlProperty->GetCurPage(),
				this->m_lineNum,lineStyle);
		}*/
	}
	//获取注释编号

	expText.TrimLeft(_T(" "));//删除空格
	CString strExpNum=_T("");
	CString expMark;

	switch(m_pPropertyManage->m_pHtmlProperty->GetExpStyle())
	{
	case 1:
		if(expText.GetLength()>=3){
			for(int i=0;i<3;i++){//只检查前面3个字符
				if(expText[i]<='9'&&expText[i]>='0')
					strExpNum=strExpNum+expText[i];
			}
		}
		if(strExpNum.GetLength()>0){
			if(m_IsBr){
				AddHtmlVector(_T("<br/>\n"));
				//在不同的注释间添加换行符<br/>
				m_IsBr=true;
			}
			expText.Delete(0,strExpNum.GetLength());//删除注释号
			AddHtmlVector(
				_T("                    <span class=\"super\">"));
			AddHtmlVector(strExpNum);
			AddHtmlVector(_T("</span>"));
		//	CString expMark=_T("<a ")+expName+_T(" style=\"letter-spacing:2px;\">&nbsp;");
			CString expMark=_T("<a ")+expName+_T(">");
			//不需要自动加<letter-spacing>属性
			AddHtmlVector(expMark);
			m_IsBr=true;
		}
		else{
			AddHtmlVector(_T("\n"));//直接换行
			expText.TrimLeft(_T(" "));
			//CString expMark=_T("                    <a ")+expName+_T(" style=\"letter-spacing:2px;\">&nbsp;&nbsp;");
			CString expMark=_T("                    <a ")+expName+_T(">");
			//不需要自动加<letter-spacing>属性
			AddHtmlVector(expMark);
			m_IsBr=true;//设置添加<br/>标识为真
		}
		break;
	case 2:
		for(int i=0;i<expText.GetLength();i++){
			CString str;
			if(expText[i]<=9322 && expText[i]>=9312){//9312为①的编码
				strExpNum=strExpNum+expText[i];
			}
		}
		if(strExpNum.GetLength()>0)
		{
			if(m_IsBr){
				AddHtmlVector(_T("<br/>\n"));
				//在不同的注释间添加换行符<br/>
				m_IsBr=true;
			}
			expMark=app->m_noteModelDlg.GetNoteFirstLineModel();
			expMark.Replace(_T("name=\"p-xxx-xx\""),expName);//替换行数
			expMark.Replace(_T("#number#"),strExpNum);//替换注释号
			expText.TrimLeft(_T(' '));
			expText.TrimRight(_T(' '));
			expText.Replace(strExpNum,_T(""));
			expMark.Replace(_T("#noteText#"),expText);//替换注释文本
			expMark=_T("                    ")+expMark;
			m_IsBr=true;
		}
		else
		{
			AddHtmlVector(_T("\n"));//直接换行
			expMark=app->m_noteModelDlg.GetNoteSecondLineModel();
			expMark.Replace(_T("name=\"p-xxx-xx\""),expName);//替换行数
			expText.TrimLeft(_T(' '));
			expText.TrimRight(_T(' '));
			expMark.Replace(_T("#noteText#"),expText);//替换注释文本
			expMark=_T("                    ")+expMark;
			m_IsBr=true;//设置添加<br/>标识为真
		}
		//检测是否letter-spacing冲突
		if(!lineStyle.IsEmpty()){
			int lettPos=expMark.Find(_T("letter-spacing:"));
			if(lettPos>=0){
				int endPos=expMark.Find(_T("px"),lettPos);
				if(endPos>=0){
					expMark.Delete(lettPos,endPos-lettPos+2);
					lineStyle.Replace(_T("style=\""),_T(""));
					lineStyle.Replace(_T(";\""),_T(""));
					expMark.Insert(lettPos,lineStyle);
				}
			}
			else{
				CString NameStyle=expName+_T(" ")+lineStyle;
				expMark.Replace(expName,NameStyle);
			}
		}
		AddHtmlVector(expMark);
		break;
	default:
		break;
	}
	/*
	AddHtmlVector(expText);
	AddHtmlVector(_T("</a>"));*/
}

void HtmlFileGeneration::WriteEachLine(CString& lineText)
{
	//对正文的每一行进行注释判定与处理
	HandleNoteNum(lineText);

	//对nobr、letter-spacing等标签进行判断
	CString styleStr=HandleLineStyleMark(lineText);//获取style样式

	CString EachLineText=_T("                    <a name=\"p-");
	CString str;//写入行码，页码
	if(styleStr.IsEmpty()){
		str.Format(_T("%s-%d\">"),m_pageNum,m_lineNum);
	}
	else{
		str.Format(_T("%s-%d\" %s>"),m_pageNum,m_lineNum,styleStr);
	}
	EachLineText=EachLineText+str;
	EachLineText=EachLineText+lineText+_T("</a>\n");

	AddHtmlVector(EachLineText);
/*	AddHtmlVector(lineText);
	AddHtmlVector(_T("</a>\n"));*/
}
void HtmlFileGeneration::WriteSectionStyle(CString& lineText,int lineIndex,std::vector<std::vector<CString>>& vecSectionStyle)
{
	CString textCssStr=_T("");
	if(m_IsDiv)
	{
		textCssStr=_T("            	</div>\n");
		m_IsDiv=false;
	}
	CString cssStr=_T("");
	CString styleStr=_T("");
	if((0==vecSectionStyle.size())||lineIndex>(int)vecSectionStyle.size()||lineIndex<0){
		cssStr=m_pPropertyManage->m_pHtmlProperty->GetTextCss();
		styleStr=_T("");
	}
	else{
		if(vecSectionStyle[lineIndex][0].Compare(
			_T("##paraStart##"))==0){
			cssStr=vecSectionStyle[lineIndex][1];
			if(vecSectionStyle[lineIndex][2].Compare(
				_T("style=\"\""))!=0){
				styleStr=vecSectionStyle[lineIndex][2];
			}
		}
		else{
			cssStr=m_pPropertyManage->m_pHtmlProperty->GetTextCss();
			styleStr=_T("");
		}
	}
	textCssStr=textCssStr+_T("            	<div class=\"")+
		cssStr+_T("\" ")+styleStr+_T(">\n");
	AddHtmlVector(textCssStr);
	m_IsDiv=true;
	lineText.TrimLeft(_T(" "));//删除空格
	WriteEachLine(lineText);
}

void HtmlFileGeneration::HandleNoteNum(CString& lineText)
{
	bool IsFirst=true;
	int cstrIndex=0;
	CString expModel=m_pPropertyManage->m_pHtmlProperty->GetExpModel();
	CString strExpNum=_T("");
	int len=lineText.GetLength();//得到这一行的字符数，而不是字节数
	int iSubStart=0;
	int iSubEnd=0;
	//根据注释符标识来判定是否为注释
	while(iSubEnd!=-1){
		iSubStart=lineText.Find(_T("^^^"),iSubEnd);
		iSubEnd=lineText.Find(_T("^^^"),iSubStart+3);
		if(iSubEnd!=-1){
			CString expNum;
			expNum=lineText.Left(iSubEnd);
			expNum=expNum.Right(iSubEnd-iSubStart-3);
			expModel.Replace(_T("#number#"),expNum);
			CString expStr=_T("^^^")+expNum+_T("^^^");
			lineText.Replace(expStr,expModel);
		}
	}
}

CString HtmlFileGeneration::HandleLineStyleMark(CString& lineText)
{
	CString styleStr=_T("style=\"");
	int pos=-1;

	//检测nobr
	pos=lineText.Find(_T("##nobr##"));
	if(pos!=-1){
		lineText.Insert(0,_T("<nobr>"));
		lineText.Replace(_T("##nobr##"),_T("</nobr>"));
	}

	//检测letter-spacing
	pos=lineText.Find(_T("##LS="));
	if(pos!=-1){
		styleStr=styleStr+_T("letter-spacing:");
		lineText.Replace(_T("##LS="),_T(""));
		CString letNum=lineText.Right(lineText.GetLength()-pos);
		int LSpos=letNum.Find(_T("##"));
		if(LSpos!=-1){
			letNum=letNum.Left(LSpos);
			letNum.Replace(_T("—"),_T("-"));
			styleStr=styleStr+letNum+_T("px;");
			lineText.Delete(pos,letNum.GetLength()+2);//删除标识
		}
	}

	styleStr=styleStr+_T("\"");

	if(styleStr.Compare(_T("style=\"\""))==0)
		return _T("");
	return styleStr;
}

//将生产的无模板的内容写入到相应的模板文件
void HtmlFileGeneration::OutputHtmlFile()
{
	//最终Html文件字符串
	CString m_html;

	//模板文件
	CStdioFile modelFile;
	if(!modelFile.Open(m_pPropertyManage->getModelFileName(),CFile::modeRead)){
		AfxMessageBox(_T("模板文件打开失败！（模板文件可能已经不存在！）"));
		return;
	}
	m_html.Empty();//清空前面生成的html文本

	CString readStr;
	//将模板文件中的内容全部取出，放在CString
	while(modelFile.ReadString(readStr)){
		m_html=m_html+readStr+_T("\n");
	}
	modelFile.Close();

	std::vector<CString> m_vecHtmlText;
	m_vecHtmlText.clear();//清除以前的html文本
	for(int i=0;i<(int)m_vecHtml.size();i++){
		m_vecHtmlText.push_back(m_vecHtml[i]);
	}
	CString htmlText;
	CString htmlExp;
	bool Isexplaining=false;
	for(int i=0;i<(int)m_vecHtmlText.size();i++){
		if(m_vecHtmlText[i].Find(_T("<!--explain_text_start-->"))!=-1){
			Isexplaining=true;
			continue;
		}
		if(!Isexplaining)
			htmlText=htmlText+m_vecHtmlText[i];
		else{
			htmlExp=htmlExp+m_vecHtmlText[i];
		}
	}

	//将生成的内容与模板相结合，写入到最终文件
	m_html.Replace(_T("<!--main_text-->"),htmlText);//写入全体内容
	//写入注释文本
	m_html.Replace(_T("<!--explain_text-->"),htmlExp);
	//写入页码
	m_html.Replace(_T("<!--page_number-->"),m_pageNum);


	//将unicode转为utf-8，并写入utf-8文件
	 int u8Len = ::WideCharToMultiByte(CP_UTF8, NULL, m_html, wcslen(m_html), NULL, 0, NULL, NULL);
    //同上，分配空间要给'\0'留个空间
    //UTF8虽然是Unicode的压缩形式，但也是多字节字符串，所以可以以char的形式保存
    char* szU8 = new char[u8Len + 1];
    //转换
    //unicode版对应的strlen是wcslen
    ::WideCharToMultiByte(CP_UTF8, NULL, m_html, wcslen(m_html), szU8, u8Len, NULL, NULL);
    //最后加上'\0'
    szU8[u8Len] = '\0';
	//保存为UTF-8文件
	 m_fHtmlWithModel.Write("\xef\xbb\xbf", 3);
	 m_fHtmlWithModel.Write(szU8,u8Len);
}

void HtmlFileGeneration::WriteDiv()
{
	//判断Div是否闭合
	if(this->m_IsDiv){
		AddHtmlVector(_T("            	</div>\n"));
		m_IsDiv=false;
	}
}