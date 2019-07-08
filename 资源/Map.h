#ifndef		__ZX_GMAP_H__
#define		__ZX_GMAP_H__
#include "header.h"

//文件的扩展名为.dtv1(devil's tower version 1)
class	GMap{
public:
	GMap();
public:
	TString	GetMapFileName();
	TString	SetMapFileName(const	TString	strMapFileName);
	bool	LoadMap();//加载地图
	GObjID	GetObjByIndex(unsigned	uRow, unsigned	uCol);
	GObjID	SetObjByIndex(unsigned	uRow, unsigned	uCol,	GObjID	id);
private:
	TString			m_strMapFileName;
	GObjID			m_ObjID[MAP_ROW_SCAL][MAP_COL_SCAL];//地图的信息
};


//在调用GetMapFileNameByFloor之前，你要确定你调用过一次InitFileName
TString		GetMapFileNameByFloor(unsigned	uFloor);
void		InitMapFileName();		//初始化地图文件名子列表(在程序启动的时候要记得调用哦)
void		LoadAllGameMap(const	TString& strMapDirectory, vector<GMap>&	AllMap,	
						unsigned&	uTotalMaps);//从一个给定的目录下加载所有的地图

#endif
