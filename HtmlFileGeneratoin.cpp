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
	//��ʼ����Ա����
	this->m_pPropertyManage=pPropertyManage;
	this->m_iterVecEachLine=vecEachLine.begin();
	this->m_iterVecEachLineEnd=vecEachLine.end();
	this->m_iterVecSectionStyle=vecSectionStyle.begin();
	
	//��ȡҳ�ţ�����ҳ��ǰ�����ȥ��
	this->m_pageNum=m_pPropertyManage->m_pHtmlProperty->GetCurPage();
	m_pageNum.TrimLeft(_T("0"));

	//�����趨
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//�趨

	//��ʼ���ļ�
	if(!InitFiles())
		return;

	//����������
	TraverseVector(vecEachLine,vecSectionStyle);

	//���Html�ļ�
	OutputHtmlFile();

	//�رմ򿪵��ļ�
	CloseFiles();

	//�ָ������趨
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//��ԭ�����趨
}

bool HtmlFileGeneration::InitFiles()
{
	//��õ�ǰ��ִ���ļ���·��  
	CString   sModFileName; 
	GetModuleFileName(NULL,sModFileName.GetBuffer(MAX_PATH),MAX_PATH);
	sModFileName.ReleaseBuffer(); 
	sModFileName.MakeReverse(); 
	m_sIniFilePath=sModFileName.Right(sModFileName.GetLength()-sModFileName.Find( '\\')); 
	m_sIniFilePath.MakeReverse();


	CString fPath;
	CString errMsg=_T("���ļ�ʧ�ܣ�");
	try{
		//��ҳͼƬ������ʼ���ļ�·��
		fPath=m_sIniFilePath+_T("system\\pic_left_start.txt");
		if(!m_fPicLeftStr.Open(fPath,CFile::modeRead)){
			errMsg=errMsg+fPath;
			AfxMessageBox(errMsg);
			return false;
		}
		//��ҳͼƬ�����ҿ�ʼ���ļ�·��
		fPath=m_sIniFilePath+_T("system\\pic_right_start.txt");
		if(!m_fPicRightStr.Open(fPath,CFile::modeRead)){
			errMsg=errMsg+fPath;
			AfxMessageBox(errMsg);
			return false;
		}
		//��ҳͼƬ������������ļ�·��
		fPath=m_sIniFilePath+_T("system\\pic_left_end.txt");
		if(!m_fPicLeftEnd.Open(fPath,CFile::modeRead)){
			errMsg=errMsg+fPath;
			AfxMessageBox(errMsg);
			return false;
		}
		//��ҳͼƬ�����ҽ������ļ�·��
		fPath=m_sIniFilePath+_T("system\\pic_right_end.txt");
		if(!m_fPicRightEnd.Open(fPath,CFile::modeRead)){
			errMsg=errMsg+fPath;
			AfxMessageBox(errMsg);
			return false;
		}
		//��ҳͼƬ�����п�ʼ���ļ�·��
		fPath=m_sIniFilePath+_T("system\\pic_center_start.txt");
		if(!m_fPicCenter.Open(fPath,CFile::modeRead)){
			errMsg=errMsg+fPath;
			AfxMessageBox(errMsg);
			return false;
		}

		//����ģ��m_fHtmlWithModel(�����ļ�)
		CString sIniFilePath=m_pPropertyManage->m_htmlFilePath;
		fPath.Format(sIniFilePath+_T("p-%s.html"),m_pageNum);
		if(!m_fHtmlWithModel.Open(fPath,CFile::modeReadWrite|CFile::modeCreate)){
			errMsg=errMsg+fPath;
			AfxMessageBox(errMsg);
			return false;
		}
	}
	catch(CFileException fe){
		AfxMessageBox(_T("����Html�ļ��Ǵ��ļ�ʧ��!"));
	}
	m_htmlFileName=fPath;//��¼��ǰд���html�ļ�������
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
	int normalTextLineNum=0;//�����ı��������к�Ϊ�����css��ʽ

	for(std::vector<CString>::iterator iter=vecEachLine.begin();iter!=vecEachLine.end();++iter)
	{
		lineText=*iter;
		
		if(lineText.IsEmpty())
			continue;

		normalTextLineNum++;//ÿ��һ����Ч�ı�������CSS��ʶ������1

		//����ͼƬ��ʶ
		if(TRUE==HandlePictureMark(iter))
			continue;

		//�������ʶ
		std::vector<CString>::iterator iterOld=iter;
		iter=HandleTableMark(iter);
		if(iterOld!=iter){
			normalTextLineNum=normalTextLineNum+(iter-iterOld);
			continue;
		}

		//��ǰ��������
		m_lineNum++;

		if(m_IsNote){//�ж������Ƿ�д��ע���ı�
			WriteNote(lineText);
			continue;
		}
		switch(lineText[0])
		{
		case '#':
			m_IsNote=true;
			m_lineNum--;
			break;//��ʼע��
		case ' ':
			if(lineText[1]==' ')
				WriteSectionStyle(lineText,normalTextLineNum-1,vecSectionStyle);
			//д�������ʽ���ı�
			break;
		default://����д��
			WriteEachLine(lineText);
		}  
	}

	//�ж�Div�Ƿ�պ�
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
	//�ж��Ƿ��Ǳ���ʶ��
	if(lineText.Compare(_T("table#start"))!=0)
		return iter;

	//���ʼ
	WriteDiv();//�Ƿ�д��</div>
	WriteTableStart();

	iter++; //������ʶ��

	while(true){
		if(iter==m_iterVecEachLineEnd)
			return --iter;
		lineText=*iter;
		if(lineText.Compare(_T("table#end"))==0){
			//������
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
	int TabWidth=0;//�����滻
	CString widthStr;
	for(int i=0;i<(int)m_tableManage.m_vecTableStr.size();i++){
		AddHtmlVector(tr);
		TabWidth=100;//�����滻
		for(int j=0;j<(int)m_tableManage.m_vecTableStr[i].size();j++){
			tabStr=m_tableManage.m_vecTableStr[i].at(j);
			td=_T("                    <td>####</td>\n");//����Ҫtd1
			widthStr.Format(_T("%d"),TabWidth++);//�����滻
			td.Replace(_T("##width##"),widthStr);
			td.Replace(_T("####"),tabStr);

			HandleNoteNum(td);//����ע�ͷ�

			AddHtmlVector(td);
		}
		AddHtmlVector(trEnd);
	}
}
BOOL HtmlFileGeneration::HandlePictureMark(std::vector<CString>::iterator iter)
{
	CString lineText=*iter;
	//�ж��Ƿ���ͼƬ��ʶ��
		if(lineText.Compare(_T("pic#start"))==0){
			//ͼƬ��ʼ
			WritePicStart();
			return TRUE;
		}
		if(lineText.Compare(_T("pic#end"))==0){
			//ͼƬ����
			WritePicEnd();
			return TRUE;
		}
		return FALSE;
}

void HtmlFileGeneration::WritePicStart()
{//д��ͼƬ��ʼ��ʶ
	if(m_IsDiv){//�Ƿ���Ҫд��</div>������ǩ
		AddHtmlVector(_T("            	</div>\n"));
		m_IsDiv=false;
	}
	CString lineText;
	switch(m_pPropertyManage->m_pPictureProperty->GetPictureAlign()){
		case PICTURE_ALIGN_CENTER://����
			while(m_fPicCenter.ReadString(lineText)){
				lineText.Replace(_T("$$$$"),this->m_pageNum);
				lineText.Replace(_T("@@@@"),m_pPropertyManage->m_pPictureProperty->GetPictureName());//ͼƬ����
				CString pro;
				pro.Format(_T("%s"),m_pPropertyManage->m_pPictureProperty->GetPictureWidth());//ͼƬ���
				lineText.Replace(_T("####"),pro);
				pro.Format(_T("%s"),m_pPropertyManage->m_pPictureProperty->GetPictureHight());//ͼƬ�߶�
				lineText.Replace(_T("&&&&"),pro);
				AddHtmlVector(lineText);//���ֿ��
				AddHtmlVector(_T("\n"));
			}
			break;
		case PICTURE_ALIGN_LEFT://����
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
		case PICTURE_ALIGN_RIGHT://����
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

	//�Ƿ���Ҫд��</div>������ǩ
	WriteDiv();

	CString lineText;
	switch(m_pPropertyManage->m_pPictureProperty->GetPictureAlign()){
		case PICTURE_ALIGN_CENTER://����
			break;
		case PICTURE_ALIGN_LEFT://����
			while(m_fPicLeftEnd.ReadString(lineText)){
				AddHtmlVector(lineText);
				AddHtmlVector(_T("\n"));
			}
			break;
		case PICTURE_ALIGN_RIGHT://����
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
	WriteDiv();//д��</div>

	if(expText.IsEmpty())
		return;

	CEBEApp *app=(CEBEApp*)AfxGetApp();

	CString lineStyle=HandleLineStyleMark(expText);//�����б�ʶ��

	//�״�д��ע���ı�ʱд���ʶ��Ϣ
	if(m_IsFirstWriteExp){
		m_IsFirstWriteExp=false;
		AddHtmlVector(_T("<!--explain_text_start-->\n"));
	}

	//�ж��Ƿ�Ҫ��ע������
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
	//��ȡע�ͱ��

	expText.TrimLeft(_T(" "));//ɾ���ո�
	CString strExpNum=_T("");
	CString expMark;

	switch(m_pPropertyManage->m_pHtmlProperty->GetExpStyle())
	{
	case 1:
		if(expText.GetLength()>=3){
			for(int i=0;i<3;i++){//ֻ���ǰ��3���ַ�
				if(expText[i]<='9'&&expText[i]>='0')
					strExpNum=strExpNum+expText[i];
			}
		}
		if(strExpNum.GetLength()>0){
			if(m_IsBr){
				AddHtmlVector(_T("<br/>\n"));
				//�ڲ�ͬ��ע�ͼ���ӻ��з�<br/>
				m_IsBr=true;
			}
			expText.Delete(0,strExpNum.GetLength());//ɾ��ע�ͺ�
			AddHtmlVector(
				_T("                    <span class=\"super\">"));
			AddHtmlVector(strExpNum);
			AddHtmlVector(_T("</span>"));
		//	CString expMark=_T("<a ")+expName+_T(" style=\"letter-spacing:2px;\">&nbsp;");
			CString expMark=_T("<a ")+expName+_T(">");
			//����Ҫ�Զ���<letter-spacing>����
			AddHtmlVector(expMark);
			m_IsBr=true;
		}
		else{
			AddHtmlVector(_T("\n"));//ֱ�ӻ���
			expText.TrimLeft(_T(" "));
			//CString expMark=_T("                    <a ")+expName+_T(" style=\"letter-spacing:2px;\">&nbsp;&nbsp;");
			CString expMark=_T("                    <a ")+expName+_T(">");
			//����Ҫ�Զ���<letter-spacing>����
			AddHtmlVector(expMark);
			m_IsBr=true;//�������<br/>��ʶΪ��
		}
		break;
	case 2:
		for(int i=0;i<expText.GetLength();i++){
			CString str;
			if(expText[i]<=9322 && expText[i]>=9312){//9312Ϊ�ٵı���
				strExpNum=strExpNum+expText[i];
			}
		}
		if(strExpNum.GetLength()>0)
		{
			if(m_IsBr){
				AddHtmlVector(_T("<br/>\n"));
				//�ڲ�ͬ��ע�ͼ���ӻ��з�<br/>
				m_IsBr=true;
			}
			expMark=app->m_noteModelDlg.GetNoteFirstLineModel();
			expMark.Replace(_T("name=\"p-xxx-xx\""),expName);//�滻����
			expMark.Replace(_T("#number#"),strExpNum);//�滻ע�ͺ�
			expText.TrimLeft(_T(' '));
			expText.TrimRight(_T(' '));
			expText.Replace(strExpNum,_T(""));
			expMark.Replace(_T("#noteText#"),expText);//�滻ע���ı�
			expMark=_T("                    ")+expMark;
			m_IsBr=true;
		}
		else
		{
			AddHtmlVector(_T("\n"));//ֱ�ӻ���
			expMark=app->m_noteModelDlg.GetNoteSecondLineModel();
			expMark.Replace(_T("name=\"p-xxx-xx\""),expName);//�滻����
			expText.TrimLeft(_T(' '));
			expText.TrimRight(_T(' '));
			expMark.Replace(_T("#noteText#"),expText);//�滻ע���ı�
			expMark=_T("                    ")+expMark;
			m_IsBr=true;//�������<br/>��ʶΪ��
		}
		//����Ƿ�letter-spacing��ͻ
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
	//�����ĵ�ÿһ�н���ע���ж��봦��
	HandleNoteNum(lineText);

	//��nobr��letter-spacing�ȱ�ǩ�����ж�
	CString styleStr=HandleLineStyleMark(lineText);//��ȡstyle��ʽ

	CString EachLineText=_T("                    <a name=\"p-");
	CString str;//д�����룬ҳ��
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
	lineText.TrimLeft(_T(" "));//ɾ���ո�
	WriteEachLine(lineText);
}

void HtmlFileGeneration::HandleNoteNum(CString& lineText)
{
	bool IsFirst=true;
	int cstrIndex=0;
	CString expModel=m_pPropertyManage->m_pHtmlProperty->GetExpModel();
	CString strExpNum=_T("");
	int len=lineText.GetLength();//�õ���һ�е��ַ������������ֽ���
	int iSubStart=0;
	int iSubEnd=0;
	//����ע�ͷ���ʶ���ж��Ƿ�Ϊע��
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

	//���nobr
	pos=lineText.Find(_T("##nobr##"));
	if(pos!=-1){
		lineText.Insert(0,_T("<nobr>"));
		lineText.Replace(_T("##nobr##"),_T("</nobr>"));
	}

	//���letter-spacing
	pos=lineText.Find(_T("##LS="));
	if(pos!=-1){
		styleStr=styleStr+_T("letter-spacing:");
		lineText.Replace(_T("##LS="),_T(""));
		CString letNum=lineText.Right(lineText.GetLength()-pos);
		int LSpos=letNum.Find(_T("##"));
		if(LSpos!=-1){
			letNum=letNum.Left(LSpos);
			letNum.Replace(_T("��"),_T("-"));
			styleStr=styleStr+letNum+_T("px;");
			lineText.Delete(pos,letNum.GetLength()+2);//ɾ����ʶ
		}
	}

	styleStr=styleStr+_T("\"");

	if(styleStr.Compare(_T("style=\"\""))==0)
		return _T("");
	return styleStr;
}

//����������ģ�������д�뵽��Ӧ��ģ���ļ�
void HtmlFileGeneration::OutputHtmlFile()
{
	//����Html�ļ��ַ���
	CString m_html;

	//ģ���ļ�
	CStdioFile modelFile;
	if(!modelFile.Open(m_pPropertyManage->getModelFileName(),CFile::modeRead)){
		AfxMessageBox(_T("ģ���ļ���ʧ�ܣ���ģ���ļ������Ѿ������ڣ���"));
		return;
	}
	m_html.Empty();//���ǰ�����ɵ�html�ı�

	CString readStr;
	//��ģ���ļ��е�����ȫ��ȡ��������CString
	while(modelFile.ReadString(readStr)){
		m_html=m_html+readStr+_T("\n");
	}
	modelFile.Close();

	std::vector<CString> m_vecHtmlText;
	m_vecHtmlText.clear();//�����ǰ��html�ı�
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

	//�����ɵ�������ģ�����ϣ�д�뵽�����ļ�
	m_html.Replace(_T("<!--main_text-->"),htmlText);//д��ȫ������
	//д��ע���ı�
	m_html.Replace(_T("<!--explain_text-->"),htmlExp);
	//д��ҳ��
	m_html.Replace(_T("<!--page_number-->"),m_pageNum);


	//��unicodeתΪutf-8����д��utf-8�ļ�
	 int u8Len = ::WideCharToMultiByte(CP_UTF8, NULL, m_html, wcslen(m_html), NULL, 0, NULL, NULL);
    //ͬ�ϣ�����ռ�Ҫ��'\0'�����ռ�
    //UTF8��Ȼ��Unicode��ѹ����ʽ����Ҳ�Ƕ��ֽ��ַ��������Կ�����char����ʽ����
    char* szU8 = new char[u8Len + 1];
    //ת��
    //unicode���Ӧ��strlen��wcslen
    ::WideCharToMultiByte(CP_UTF8, NULL, m_html, wcslen(m_html), szU8, u8Len, NULL, NULL);
    //������'\0'
    szU8[u8Len] = '\0';
	//����ΪUTF-8�ļ�
	 m_fHtmlWithModel.Write("\xef\xbb\xbf", 3);
	 m_fHtmlWithModel.Write(szU8,u8Len);
}

void HtmlFileGeneration::WriteDiv()
{
	//�ж�Div�Ƿ�պ�
	if(this->m_IsDiv){
		AddHtmlVector(_T("            	</div>\n"));
		m_IsDiv=false;
	}
}