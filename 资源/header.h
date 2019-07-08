#ifndef		__ZX_HEADER_H__
#define		__ZX_HEADER_H__

#include <shlwapi.h>
#include <windows.h>
#define		_T(queto)	TEXT(queto)


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

#ifndef		UNICODE
#define		TString		string
#define		TFstream	fstream
#else
#define		TString		wstring
#define		TFstream	wfstream
#endif

typedef		unsigned		GObjID;

class	GHOSTINFO{
public:
	GHOSTINFO(){}
	GHOSTINFO(unsigned	uLife, unsigned	uAtForce, unsigned uDfForce, unsigned uMoney, unsigned uExpr):
		m_uLife(uLife),m_uAtForce(uAtForce), m_uDfForce(uDfForce), m_uExpr(uExpr), m_uMoney(uMoney){}
public:
	unsigned			m_uLife;
	unsigned			m_uAtForce;			//攻击力
	unsigned			m_uDfForce;			//防御力
	unsigned			m_uMoney;			//被杀死后主角得到的钱
	unsigned			m_uExpr;			//被杀死后主角得到的经验
};

//一个物体点位的大小
struct	GSIZE{
	unsigned		uRowCount;
	unsigned		uColCount;
};

//物体所有的位置
struct	GPOS{
public:
	GPOS(){}
	GPOS(unsigned	uRow, unsigned	uCol):m_uRow(uRow), m_uCol(uCol){}
public:
	unsigned		m_uRow;
	unsigned		m_uCol;
};

//地图的尺寸是11*11
#define		MAP_ROW_SCAL		11
#define		MAP_COL_SCAL		11
#define		MAP_OBJ_SIZE		32

//最多的地图数量(实际上是不可能有这么多楼层的，要是搞这么多地图，尼玛，老子累死啊，
//用地图编辑器是可以开发的，但是，老子累得要死，开发你妹啊。
#define		MAX_MAP_COUNT		100


//整个游戏区域的大小
#define		MAINFRAME_WIDTH		490
#define		MAINFRAME_HEIGHT	380


//窗口边框的厚度
#define		MAINFRAME_BORDER_WIDTH	3
#define		MAINFRAME_CAPTION_WIDTH	25

//主窗口的位图按钮的尺寸
#define		MAINFRAME_BITMAPBUTTON_HEIGHT			19
#define		MAINFRAME_BITMAPBUTTON_SMALL_WIDTH		24
#define		MAINFRAME_BITMAPBUTTON_EXIT_WIDTH		34


//对话窗口的尺寸
#define TLK_WND_WIDTH		300
#define	TLK_WND_HEIGHT		75

//fight的尺寸(不是用对话框实现)
#define	FIT_DC_WIDTH		430
#define	FIT_DC_HEIGHT		120

//边框的颜色
#define	COLOR_VIOLET	RGB(200, 200, 255)
#define	COLOR_GOLDEN	RGB(255, 255, 0)
#define COLOR_WHITE		RGB(255, 255, 255)

#pragma comment(lib, "Msimg32")
#pragma comment(lib, "user32")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "kernel32")
#pragma comment(lib, "shlwapi")

void	LoadStringFromFile(const	TString&	strFilePath, vector<TString>&	strToLoad, bool		bIgnoreFirtLine=	false);
TString	IntToString(int 	iValue); 
#endif