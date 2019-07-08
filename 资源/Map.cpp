#include "Map.h"

//������ת����Ҫʹ�õ��ַ���(string)���������������õ�
TString		IntToSTLString(unsigned		uValue);

GMap::GMap(){}

TString	GMap::GetMapFileName(){
	return		this->m_strMapFileName;
}

TString	GMap::SetMapFileName(const	TString	strMapFileName){
	TString	tmp=	this->m_strMapFileName;
	this->m_strMapFileName	=	strMapFileName;
	return	tmp;
}

bool	GMap::LoadMap(){//���ص�ͼ
	fstream		in(m_strMapFileName);
	if(!in)	//����ʧ��
		return	false;
	for(unsigned	uRow=	0; uRow< MAP_ROW_SCAL; ++uRow){
		for(unsigned	uCol=	0; uCol	< MAP_COL_SCAL; ++uCol){
			in>>this->m_ObjID[uRow][uCol];
		}
	}
	in.close();
	return	true;
}

GObjID	GMap::GetObjByIndex(unsigned	uRow, unsigned	uCol){
	return	m_ObjID[uRow][uCol];
}

GObjID	GMap::SetObjByIndex(unsigned	uRow, unsigned	uCol,	GObjID	id){
	GObjID	tmp=	this->m_ObjID[uRow][uCol];
	this->m_ObjID[uRow][uCol]	=	id;
	return	tmp;
}


vector<TString>		strMapFileName;//һ��ȫ�ֵı���������ʹ��

TString		GetMapFileNameByFloor(unsigned	uFloor){
	return	strMapFileName[uFloor];
}

void		InitMapFileName(){		//��ʼ����ͼ�ļ������б�
	strMapFileName.push_back(_T("����"));
	for(unsigned	uFloor=		1; uFloor	<	MAX_MAP_COUNT; ++uFloor){
		strMapFileName.push_back(IntToSTLString(uFloor));
	}
}

//������ת����Ҫʹ�õ��ַ���(string)���������������õ�
TString		IntToSTLString(unsigned		uValue){
	TString		strResult;
	TString		strTmp;
	while(uValue){
		strTmp.push_back(uValue%10+ TCHAR('0'));
		uValue/=	10;
	}
	reverse(strTmp.begin(), strTmp.end());
	strResult.append(_T("��"));
	strResult+=	strTmp;
	strResult.append(_T("��"));
	return	strResult;
}

unsigned	GetSubFileCount(const	TString&	strFileDirectory);
void		LoadAllGameMap(const	TString& strMapDirectory, vector<GMap>&	AllMap,	unsigned&	uTotalMaps){//��һ��������Ŀ¼�¼������еĵ�ͼ
	uTotalMaps	=	GetSubFileCount(strMapDirectory);
	//���ζ�ȡ��ͼ�ļ�
	TString		strFilePath;
	GMap	MapTmp;
	for(unsigned	uMapIndex	=	0; uMapIndex< uTotalMaps; ++uMapIndex){
		strFilePath=	strMapDirectory+ _T("\\")+ GetMapFileNameByFloor(uMapIndex)+ _T(".dtv1");
		MapTmp.SetMapFileName(strFilePath);
		MapTmp.LoadMap();
		AllMap.push_back(MapTmp);
	}
}

unsigned	GetSubFileCount(const	TString&	strFileDirectory){//��ȡһ��Ŀ¼������ļ���Ŀ
	//���ֻ����windows api��
	HANDLE	hFile;
	WIN32_FIND_DATA	FileFindData;
	TString		FileSearchPattern	=	strFileDirectory+ _T("\\*");
	unsigned	uTotalFile=	0;
	//��ȡ��ͼ�ļ�����Ŀ(��uTotalMaps�����¼��)
	do{
		hFile=	::FindFirstFile(FileSearchPattern.c_str(), &FileFindData);
		if(hFile==	INVALID_HANDLE_VALUE){
			uTotalFile=	0;
			break;
		}
		++uTotalFile;
		while(::FindNextFile(hFile, &FileFindData))
			++uTotalFile;
	}while(false);	//������ʹ��do-while(0)������
	::FindClose(hFile);
	return	uTotalFile? uTotalFile-2: uTotalFile;
}