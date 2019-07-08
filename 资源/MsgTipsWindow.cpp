#include "MsgTipsWindow.h"
#include "GameUserWindow.h"
#include "WndClass.h"

GMsgTipsWindow::GMsgTipsWindow(GGameUserWindow*	lpCtrlWindow){
	m_bmpBackGround	=	(HBITMAP)LoadImage(NULL, _T("..\\DemoTower\\BkgrdBmp\\MainFrame.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_hMessageFont	=	NULL;
	LOGFONT	font;
	::RtlZeroMemory(&font, sizeof(font));
	font.lfCharSet	=	GB2312_CHARSET;
	StrCpy(font.lfFaceName, _T("楷体\0"));
	font.lfHeight	=	20;
	font.lfWidth	=	10;
	font.lfWeight	=	1;
	m_hMessageFont	=	::CreateFontIndirect(&font);
	m_uTimerID		=	100;
	m_lpCtrlWindow	=	lpCtrlWindow;
}

GMsgTipsWindow::~GMsgTipsWindow(){
	::DeleteObject(m_hMessageFont);
	::DeleteObject(m_bmpBackGround);
}

bool	GMsgTipsWindow::Create( DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hWndParent, HMENU hMenu, LPVOID lpParam ){
	WndClass	wndclass;
	wndclass.GetWndClass().lpszClassName	=	lpszClassName;
	wndclass.Register();
	m_hOwner		=	hWndParent;
	Window::Create(WS_EX_TOOLWINDOW|WS_EX_LAYERED, WS_POPUP|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, lpszClassName, NULL, rtWndArea, NULL, NULL, NULL);
	::SetLayeredWindowAttributes(GetHwnd(), 0, 255, LWA_ALPHA);//设置成半透明的
	return	0;
}

void	GMsgTipsWindow::InitMessageHandler(){
	m_mpMessageChain[WM_PAINT]		=	static_cast<MsgHandler>(&GMsgTipsWindow::OnPaint);
	m_mpMessageChain[WM_KILLFOCUS]	=	static_cast<MsgHandler>(&GMsgTipsWindow::OnKillFocus);
	m_mpMessageChain[WM_KEYDOWN]	=	static_cast<MsgHandler>(&GMsgTipsWindow::OnKeyDown);
	m_mpMessageChain[WM_TIMER]		=	static_cast<MsgHandler>(&GMsgTipsWindow::OnTimer);
}

void	GMsgTipsWindow::ShowMessage(const TString& strMessage, unsigned uMilSecondsToWait){
	//当用户按下任何键或者定时器到时的时候就会关闭
	m_strMessage	=	strMessage;
	RECT	RecTOfOwner;
	::GetWindowRect(m_hOwner, &RecTOfOwner);
	::SetWindowPos(GetHwnd(), 0, RecTOfOwner.left+ 92, RecTOfOwner.top+ 120, 0, 0, SWP_NOSIZE);
	::InvalidateRect(GetHwnd(), NULL, false);
	::ShowWindow(GetHwnd(), SW_SHOWNORMAL);
	::SetTimer(GetHwnd(), m_uTimerID, uMilSecondsToWait, NULL);
}

LRESULT	GMsgTipsWindow::OnPaint(WPARAM	wParam, LPARAM	lParam){
	::InvalidateRect(GetHwnd(), NULL, false);
	PAINTSTRUCT	ps;
	HDC			hDrawDC			=	::BeginPaint(GetHwnd(), &ps);
	HDC			hMemDC			=	::CreateCompatibleDC(hDrawDC);
	HBITMAP		hBmpToDrawOn	=	::CreateCompatibleBitmap(hDrawDC, TLK_WND_WIDTH, TLK_WND_HEIGHT);
	HBRUSH		hPatternBrush	=	::CreatePatternBrush(m_bmpBackGround);
	::SelectObject(hMemDC, hBmpToDrawOn);
	::SelectObject(hMemDC, hPatternBrush);
	unsigned	uLindWidth	=	3;
	HPEN	hPrePen	=	(HPEN)::SelectObject(hMemDC, ::CreatePen(PS_SOLID, 3, COLOR_VIOLET));
	RECT	RectOfClient;
	::GetClientRect(GetHwnd(), &RectOfClient);
	::FillRect(hMemDC, &RectOfClient, hPatternBrush);
	HDC	hParentDC	=	::GetWindowDC(m_hOwner);
	BLENDFUNCTION	BlendFunc;
	BlendFunc.BlendFlags			=	0;
	BlendFunc.BlendOp				=	AC_SRC_OVER;
	BlendFunc.SourceConstantAlpha	=	150;
	BlendFunc.AlphaFormat			=	0;
	RECT	RectOfCurrentWnd;
	RECT	RectOfParentWnd;
	::GetWindowRect(m_hOwner, &RectOfParentWnd);
	::GetWindowRect(GetHwnd(), &RectOfCurrentWnd);
	::AlphaBlend(hMemDC, 0, 0, RectOfClient.right, RectOfClient.bottom, hParentDC, RectOfCurrentWnd.left- RectOfParentWnd.left,
		RectOfCurrentWnd.top- RectOfParentWnd.top, RectOfClient.right, RectOfClient.bottom, BlendFunc);
	HPEN	hPen	=	::CreatePen(PS_INSIDEFRAME, 3, RGB(255, 255, 0));
	HBRUSH	hHollowBrush	=	(HBRUSH)::GetStockObject(NULL_BRUSH);
	::SelectObject(hMemDC, hPen);
	::SelectObject(hMemDC, hHollowBrush);
	::Rectangle(hMemDC, 0, 0, RectOfClient.right, RectOfClient.bottom);
	::SelectObject(hMemDC, m_hMessageFont);
	::SetTextColor(hMemDC, COLOR_WHITE);
	::SetBkMode(hMemDC, TRANSPARENT);
	::DrawText(hMemDC,m_strMessage.c_str(), m_strMessage.size(), &RectOfClient,  DT_CENTER|DT_SINGLELINE|DT_VCENTER);
	::BitBlt(hDrawDC, 0, 0, RectOfClient.right, RectOfClient.bottom, hMemDC, 0, 0, SRCCOPY);

	::DeleteObject(hBmpToDrawOn);
	::DeleteDC(hMemDC);
	::EndPaint(GetHwnd(), &ps);
	::DeleteObject(hPatternBrush);
	::ReleaseDC(m_hOwner, hParentDC);
	return	0;
}

LRESULT	GMsgTipsWindow::OnKillFocus		(WPARAM	wParam, LPARAM	lParam){
	::KillTimer(GetHwnd(), m_uTimerID);
	return	0;
}

LRESULT	GMsgTipsWindow::OnKeyDown		(WPARAM wParam, LPARAM lParam){
	//::SendMessage(GetHwnd(), WM_TIMER, m_uTimerID, NULL);
	return	0;
}

LRESULT	GMsgTipsWindow::OnTimer			(WPARAM wParam, LPARAM lParam){
	::ShowWindow(GetHwnd(), SW_HIDE);
	::SetFocus(m_hOwner);
	return	0;
}