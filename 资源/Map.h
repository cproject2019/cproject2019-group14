#ifndef		__ZX_GMAP_H__
#define		__ZX_GMAP_H__
#include "header.h"

//�ļ�����չ��Ϊ.dtv1(devil's tower version 1)
class	GMap{
public:
	GMap();
public:
	TString	GetMapFileName();
	TString	SetMapFileName(const	TString	strMapFileName);
	bool	LoadMap();//���ص�ͼ
	GObjID	GetObjByIndex(unsigned	uRow, unsigned	uCol);
	GObjID	SetObjByIndex(unsigned	uRow, unsigned	uCol,	GObjID	id);
private:
	TString			m_strMapFileName;
	GObjID			m_ObjID[MAP_ROW_SCAL][MAP_COL_SCAL];//��ͼ����Ϣ
};


//�ڵ���GetMapFileNameByFloor֮ǰ����Ҫȷ������ù�һ��InitFileName
TString		GetMapFileNameByFloor(unsigned	uFloor);
void		InitMapFileName();		//��ʼ����ͼ�ļ������б�(�ڳ���������ʱ��Ҫ�ǵõ���Ŷ)
void		LoadAllGameMap(const	TString& strMapDirectory, vector<GMap>&	AllMap,	
						unsigned&	uTotalMaps);//��һ��������Ŀ¼�¼������еĵ�ͼ

#endif
