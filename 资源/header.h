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
	unsigned			m_uAtForce;			//������
	unsigned			m_uDfForce;			//������
	unsigned			m_uMoney;			//��ɱ�������ǵõ���Ǯ
	unsigned			m_uExpr;			//��ɱ�������ǵõ��ľ���
};

//һ�������λ�Ĵ�С
struct	GSIZE{
	unsigned		uRowCount;
	unsigned		uColCount;
};

//�������е�λ��
struct	GPOS{
public:
	GPOS(){}
	GPOS(unsigned	uRow, unsigned	uCol):m_uRow(uRow), m_uCol(uCol){}
public:
	unsigned		m_uRow;
	unsigned		m_uCol;
};

//��ͼ�ĳߴ���11*11
#define		MAP_ROW_SCAL		11
#define		MAP_COL_SCAL		11
#define		MAP_OBJ_SIZE		32

//���ĵ�ͼ����(ʵ�����ǲ���������ô��¥��ģ�Ҫ�Ǹ���ô���ͼ�����꣬������������
//�õ�ͼ�༭���ǿ��Կ����ģ����ǣ������۵�Ҫ�����������ð���
#define		MAX_MAP_COUNT		100


//������Ϸ����Ĵ�С
#define		MAINFRAME_WIDTH		490
#define		MAINFRAME_HEIGHT	380


//���ڱ߿�ĺ��
#define		MAINFRAME_BORDER_WIDTH	3
#define		MAINFRAME_CAPTION_WIDTH	25

//�����ڵ�λͼ��ť�ĳߴ�
#define		MAINFRAME_BITMAPBUTTON_HEIGHT			19
#define		MAINFRAME_BITMAPBUTTON_SMALL_WIDTH		24
#define		MAINFRAME_BITMAPBUTTON_EXIT_WIDTH		34


//�Ի����ڵĳߴ�
#define TLK_WND_WIDTH		300
#define	TLK_WND_HEIGHT		75

//fight�ĳߴ�(�����öԻ���ʵ��)
#define	FIT_DC_WIDTH		430
#define	FIT_DC_HEIGHT		120

//�߿����ɫ
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