#include "GameInfoWindow.h"
#include "WndClass.h"
#include "GameStatus.h"
#include "AttrByObjID.h"
#include "GObjID.h"

GGameInfoWindow::GGameInfoWindow(){
	m_bmpBackGround	=	static_cast<HBITMAP>(
		::LoadImage(NULL, 
		_T("..\\DemoTower\\BkgrdBmp\\MainFrame.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	m_PlayerStatusFrame.left	=	m_AuthorInfoFrame.left	=	m_KeyFrame.left	=	7;
	m_PlayerStatusFrame.right	=	m_AuthorInfoFrame.right	=	m_KeyFrame.right=	127;
	m_PlayerStatusFrame.top		=	6;
	m_PlayerStatusFrame.bottom	=	146;//120* 140
	m_KeyFrame.top			=	156;
	m_KeyFrame.bottom		=	276;
	m_AuthorInfoFrame.top	=	286;
	m_AuthorInfoFrame.bottom=	346;

	LOGFONT	font;
	::RtlZeroMemory(&font, sizeof(font));
	font.lfCharSet	=	GB2312_CHARSET;
	StrCpy(font.lfFaceName, _T("楷体\0"));
	font.lfHeight	=	18;
	font.lfWidth	=	9;
	font.lfWeight	=	700;
	m_hDrawFont	=	::CreateFontIndirect(&font);

	m_hObjBmp	=	static_cast<HBITMAP>(::LoadImage(NULL, 
		_T("..\\DemoTower\\BkgrdBmp\\ObjBmp\\GameObject.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
}

GGameInfoWindow::~GGameInfoWindow(){
	::DeleteObject(m_bmpBackGround);
	::DeleteObject(m_hDrawFont);
	::DeleteObject(m_hObjBmp);
}

bool	GGameInfoWindow::Create( DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hWndParent, HMENU hMenu, LPVOID lpParam ){
	//需要自己注册自己需要的窗口类哦
	WndClass	wndclass;
	wndclass.GetWndClass().hbrBackground	=	(HBRUSH)::CreatePatternBrush(m_bmpBackGround);
	wndclass.GetWndClass().lpszClassName	=	lpszClassName;
	wndclass.Register();
	return	Window::Create(dwExStyle, dwStyle, lpszClassName, lpszWindowName, rtWndArea, hWndParent, hMenu, NULL);
}

void	GGameInfoWindow::InitMessageHandler(){
	m_mpMessageChain[WM_PAINT]		=	static_cast<MsgHandler>(&GGameInfoWindow::OnPaint);
	m_mpMessageChain[WM_ERASEBKGND]	=	static_cast<MsgHandler>(&GGameInfoWindow::OnEraseBkGnd);
}

LRESULT	GGameInfoWindow::OnPaint		(WPARAM	wParam, LPARAM	lParam){
	PAINTSTRUCT	ps;
	HDC	hDrawDC		=	::BeginPaint(GetHwnd(), &ps);
	HDC	hMemSrcDC		=	::CreateCompatibleDC(hDrawDC);
	HDC	hMemDstDC	=	::CreateCompatibleDC(hDrawDC);
	RECT	RectOfClient;
	::GetClientRect(GetHwnd(), &RectOfClient);
	HBITMAP	hBmpToDrawOn	=	::CreateCompatibleBitmap(hDrawDC, RectOfClient.right, RectOfClient.bottom);
	::SelectObject(hMemDstDC, hBmpToDrawOn);
	HBITMAP	hParentBackGround	=	(HBITMAP)::LoadImage(NULL, 
		_T("..\\DemoTower\\BkgrdBmp\\GameInfoBackGround.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HBRUSH	hParentBackBrush	=	::CreatePatternBrush(hParentBackGround);
	::FillRect(hMemDstDC, &RectOfClient, hParentBackBrush);
	HBITMAP	hBackGround	=	static_cast<HBITMAP>(
		::LoadImage(NULL, 
		_T("..\\DemoTower\\BkgrdBmp\\MainFrame.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	HBRUSH	hBackBrush		=	::CreatePatternBrush(hBackGround);
	::FillRect(hMemDstDC, &m_PlayerStatusFrame, hBackBrush);
	::FillRect(hMemDstDC, &m_AuthorInfoFrame, hBackBrush);
	::FillRect(hMemDstDC, &m_KeyFrame, hBackBrush);

	::SelectObject(hMemSrcDC, m_hObjBmp);
	::TransparentBlt(hMemDstDC, m_PlayerStatusFrame.left+ 4, m_PlayerStatusFrame.top+ 4, 32, 32, hMemSrcDC, 8*32, 12* 32, 32, 32, RGB(0, 0, 0));
	RECT	RectOfLevel	=	{m_PlayerStatusFrame.left+ 40, m_PlayerStatusFrame.top, m_PlayerStatusFrame.left+ 120, m_PlayerStatusFrame.top+ 40};
	TCHAR	Buffer[100];
	wsprintf(Buffer, _T("%-5d级"), uLevel);
	::SetTextColor(hMemDstDC, COLOR_WHITE);
	::SetBkMode(hMemDstDC, TRANSPARENT);
	::SelectObject(hMemDstDC, m_hDrawFont);
	::DrawText(hMemDstDC, Buffer, lstrlen(Buffer), &RectOfLevel, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	RECT	RectOfBlood	=	{m_PlayerStatusFrame.left+ 4, m_PlayerStatusFrame.top+ 40, m_PlayerStatusFrame.right, m_PlayerStatusFrame.top+ 60};
	wsprintf(Buffer, _T("生命 %-7d"), (int)lfBloodVol);
	::DrawText(hMemDstDC, Buffer, lstrlen(Buffer), &RectOfBlood, DT_SINGLELINE|DT_VCENTER);

	RECT	RectOfAtForce	=	{m_PlayerStatusFrame.left+ 4, RectOfBlood.top+ 20, m_PlayerStatusFrame.right, RectOfBlood.top+ 40};
	wsprintf(Buffer, _T("武力 %-7d"), uAttackCapacity);
	::DrawText(hMemDstDC, Buffer, lstrlen(Buffer), &RectOfAtForce, DT_SINGLELINE|DT_VCENTER);

	RECT	RectOfDfForce	=	{m_PlayerStatusFrame.left+ 4, RectOfAtForce.top+ 20, m_PlayerStatusFrame.right, RectOfAtForce.top+ 40};
	wsprintf(Buffer, _T("护甲 %-7d"), uDefenceCapacity);
	::DrawText(hMemDstDC, Buffer, lstrlen(Buffer), &RectOfDfForce, DT_SINGLELINE|DT_VCENTER);

	RECT	RectOfMoney	=	{m_PlayerStatusFrame.left+ 4, RectOfDfForce.top+ 20, m_PlayerStatusFrame.right, RectOfDfForce.top+ 40};
	wsprintf(Buffer, _T("金钱 %-7d"), uMoney);
	::DrawText(hMemDstDC, Buffer, lstrlen(Buffer), &RectOfMoney, DT_SINGLELINE|DT_VCENTER);

	RECT	RectOfExpr	=	{m_PlayerStatusFrame.left+ 4, RectOfMoney.top+ 20, m_PlayerStatusFrame.right, RectOfMoney.top+ 40};
	wsprintf(Buffer, _T("经验 %-7d"), uExperience);
	::DrawText(hMemDstDC, Buffer, lstrlen(Buffer), &RectOfExpr, DT_SINGLELINE|DT_VCENTER);

	GPOS	KeyPos	=	GetPosByObjID(GID_OBJ_YELKEY);
	::TransparentBlt(hMemDstDC, m_KeyFrame.left+ 4, m_KeyFrame.top+ 4, 32, 32, hMemSrcDC, KeyPos.m_uCol*32, KeyPos.m_uRow*32, 32, 32, RGB(0, 0, 0));
	wsprintf(Buffer, _T("%6d"), uYellowKey);
	RECT	RectOfYelKeyCount=	{m_KeyFrame.left+ 40, m_KeyFrame.top, m_KeyFrame.right, m_KeyFrame.top+ 40};
	::DrawText(hMemDstDC, Buffer, lstrlen(Buffer), &RectOfYelKeyCount, DT_VCENTER|DT_SINGLELINE);

	KeyPos	=	GetPosByObjID(GID_OBJ_BLUEKEY);
	::TransparentBlt(hMemDstDC, m_KeyFrame.left+ 4, m_KeyFrame.top+ 44, 32, 32, hMemSrcDC, KeyPos.m_uCol*32, KeyPos.m_uRow*32, 32, 32, RGB(0, 0, 0));
	wsprintf(Buffer, _T("%6d"), uBlueKey);
	RECT	RectOfBlueKeyCount=	{m_KeyFrame.left+ 40, m_KeyFrame.top+ 40, m_KeyFrame.right, m_KeyFrame.top+ 80};
	::DrawText(hMemDstDC, Buffer, lstrlen(Buffer), &RectOfBlueKeyCount, DT_VCENTER|DT_SINGLELINE);

	KeyPos	=	GetPosByObjID(GID_OBJ_REDKEY);
	::TransparentBlt(hMemDstDC, m_KeyFrame.left+ 4, m_KeyFrame.top+ 84, 32, 32, hMemSrcDC, KeyPos.m_uCol*32, KeyPos.m_uRow*32, 32, 32, RGB(0, 0, 0));
	wsprintf(Buffer, _T("%6d"), uRedKey);
	RECT	RectOfRedKeyCount=	{m_KeyFrame.left+ 40, m_KeyFrame.top+ 80, m_KeyFrame.right, m_KeyFrame.top+ 120};
	::DrawText(hMemDstDC, Buffer, lstrlen(Buffer), &RectOfRedKeyCount, DT_VCENTER|DT_SINGLELINE);

	TString	strCurrentFloor	=	GetMapFileNameByFloor(uCurrentFloor- 1);
	RECT	RectOfCurrentFloor	=	{m_AuthorInfoFrame.left, m_AuthorInfoFrame.top, m_AuthorInfoFrame.right, m_AuthorInfoFrame.top+ 30};
	::DrawText(hMemDstDC, strCurrentFloor.c_str(), strCurrentFloor.size(), &RectOfCurrentFloor, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	RECT	RectOfAuthorQQ		=	{m_AuthorInfoFrame.left, m_AuthorInfoFrame.top+ 30, m_AuthorInfoFrame.right, m_AuthorInfoFrame.bottom};
	wsprintf(Buffer, _T("Q:1025679612"));
	::DrawText(hMemDstDC, Buffer, lstrlen(Buffer), &RectOfAuthorQQ, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	::BitBlt(hDrawDC, 0, 0, RectOfClient.right, RectOfClient.bottom, hMemDstDC, 0, 0, SRCCOPY);

	::DeleteObject(hParentBackBrush);
	::DeleteObject(hParentBackGround);
	::DeleteDC(hMemDstDC);
	::DeleteObject(hBmpToDrawOn);
	::EndPaint(GetHwnd(), &ps);
	::DeleteDC(hMemSrcDC);
	::DeleteObject(hBackBrush);
	::DeleteObject(hBackGround);
	return	0;
}

LRESULT	GGameInfoWindow::OnEraseBkGnd(WPARAM wParam, LPARAM lParam){
	return	TRUE;
}