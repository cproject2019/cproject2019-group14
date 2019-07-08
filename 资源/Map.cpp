#include "Map.h"

//把整数转换需要使用的字符串(string)，仅仅在这里面用到
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

bool	GMap::LoadMap(){//加载地图
	fstream		in(m_strMapFileName);
	if(!in)	//加载失败
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


vector<TString>		strMapFileName;//一个全局的变量供程序使用

TString		GetMapFileNameByFloor(unsigned	uFloor){
	return	strMapFileName[uFloor];
}

void		InitMapFileName(){		//初始化地图文件名子列表
	strMapFileName.push_back(_T("序章"));
	for(unsigned	uFloor=		1; uFloor	<	MAX_MAP_COUNT; ++uFloor){
		strMapFileName.push_back(IntToSTLString(uFloor));
	}
}

//把整数转换需要使用的字符串(string)，仅仅在这里面用到
TString		IntToSTLString(unsigned		uValue){
	TString		strResult;
	TString		strTmp;
	while(uValue){
		strTmp.push_back(uValue%10+ TCHAR('0'));
		uValue/=	10;
	}
	reverse(strTmp.begin(), strTmp.end());
	strResult.append(_T("第"));
	strResult+=	strTmp;
	strResult.append(_T("层"));
	return	strResult;
}

unsigned	GetSubFileCount(const	TString&	strFileDirectory);
void		LoadAllGameMap(const	TString& strMapDirectory, vector<GMap>&	AllMap,	unsigned&	uTotalMaps){//从一个给定的目录下加载所有的地图
	uTotalMaps	=	GetSubFileCount(strMapDirectory);
	//依次读取地图文件
	TString		strFilePath;
	GMap	MapTmp;
	for(unsigned	uMapIndex	=	0; uMapIndex< uTotalMaps; ++uMapIndex){
		strFilePath=	strMapDirectory+ _T("\\")+ GetMapFileNameByFloor(uMapIndex)+ _T(".dtv1");
		MapTmp.SetMapFileName(strFilePath);
		MapTmp.LoadMap();
		AllMap.push_back(MapTmp);
	}
}

unsigned	GetSubFileCount(const	TString&	strFileDirectory){//获取一个目录里面的文件数目
	//这个只能用windows api了
	HANDLE	hFile;
	WIN32_FIND_DATA	FileFindData;
	TString		FileSearchPattern	=	strFileDirectory+ _T("\\*");
	unsigned	uTotalFile=	0;
	//获取地图文件的数目(在uTotalMaps里面记录着)
	do{
		hFile=	::FindFirstFile(FileSearchPattern.c_str(), &FileFindData);
		if(hFile==	INVALID_HANDLE_VALUE){
			uTotalFile=	0;
			break;
		}
		++uTotalFile;
		while(::FindNextFile(hFile, &FileFindData))
			++uTotalFile;
	}while(false);	//这里面使用do-while(0)语句更简单
	::FindClose(hFile);
	return	uTotalFile? uTotalFile-2: uTotalFile;
}