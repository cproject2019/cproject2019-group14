#include "MainFrame.h"
#include "GameUserWindow.h"
#include "GameInfoWindow.h"
#include "WndClass.h"
#include "GameStatus.h"

void 	InitGameUseData();
//这个文件定义的整个游戏的全部窗口区域
GMainFrame::GMainFrame(){
	InitGameUseData();
	m_lpGameCtrlArea	=	new	GGameUserWindow;
	m_lpGameInfoArea	=	new	GGameInfoWindow;
	//游戏控制区(玩家能操作的区域)
	m_rtGameArea.left	=	m_rtGameArea.top	=	0;
	m_rtGameArea.right	=	m_rtGameArea.bottom	=	MAP_OBJ_SIZE* MAP_ROW_SCAL; 

	//游戏信息区(显示游戏状态的区域)
	m_rtGameInfo.left	=	MAP_OBJ_SIZE* MAP_ROW_SCAL;
	m_rtGameInfo.top	=	0;
	m_rtGameInfo.right	=	MAINFRAME_WIDTH-	2*MAINFRAME_BORDER_WIDTH;
	m_rtGameInfo.bottom	=	MAP_OBJ_SIZE*	MAP_ROW_SCAL;
	srand(time(NULL));
}

GMainFrame::~GMainFrame(){
	delete		m_lpGameInfoArea;
	delete		m_lpGameCtrlArea;
	m_lpGameCtrlArea	=	NULL;
	m_lpGameInfoArea	=	NULL;
}

bool	GMainFrame::Create( DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hWndParent, HMENU hMenu, LPVOID lpParam ){
	m_bExitButtonDown	=	false;
	m_bExitButtonHover	=	false;
	m_bSmallButtonDown	=	false;
	m_bSmallButtonHover	=	false;
	WndClass	wndclass;
	wndclass.GetWndClass().lpszClassName	=	lpszClassName;
	wndclass.GetWndClass().hIcon			=	NULL;
	wndclass.GetWndClass().hIconSm			=	wndclass.GetWndClass().hIcon;
	wndclass.Register();
	if(!Window::Create(dwExStyle|WS_EX_LAYERED, dwStyle, lpszClassName, lpszWindowName, rtWndArea, hWndParent, hMenu, lpParam))
		return	false;
	::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	//创建两个子窗口
	m_lpGameCtrlArea->Create(WS_EX_WINDOWEDGE, WS_CHILD|WS_VISIBLE, _T("GameAeraClass"), NULL, m_rtGameArea, GetHwnd(), NULL, NULL);
	::SetFocus(m_lpGameCtrlArea->GetHwnd());
	m_lpGameInfoArea->Create(WS_EX_WINDOWEDGE, WS_CHILD|WS_VISIBLE, _T("GameInfoClass"), NULL, m_rtGameInfo, GetHwnd(), NULL, NULL);
	::SetLayeredWindowAttributes(GetHwnd(), 0, 255, LWA_ALPHA);
	return	true;
}

void	GMainFrame::InitMessageHandler(){
	Window::InitMessageHandler();
	m_mpMessageChain[WM_NCPAINT]		=	static_cast<MsgHandler>(&GMainFrame::OnNcPaint);
	m_mpMessageChain[WM_SETFOCUS]		=	static_cast<MsgHandler>(&GMainFrame::OnSetFocus);
	m_mpMessageChain[WM_PAINT]			=	static_cast<MsgHandler>(&GMainFrame::OnPaint);
	m_mpMessageChain[WM_ACTIVATE]		=	static_cast<MsgHandler>(&GMainFrame::OnActive);
	m_mpMessageChain[WM_NCLBUTTONDOWN]	=	static_cast<MsgHandler>(&GMainFrame::OnNcLButtonDown);
	m_mpMessageChain[WM_NCLBUTTONUP	]	=	static_cast<MsgHandler>(&GMainFrame::OnNcLButtonUp);
	m_mpMessageChain[WM_NCMOUSEMOVE]	=	static_cast<MsgHandler>(&GMainFrame::OnNcMouseMove);
	m_mpMessageChain[WM_WINDOWPOSCHANGED]=	static_cast<MsgHandler>(&GMainFrame::OnWindowPosChanged);
	m_mpMessageChain[WM_KEYDOWN]		=	static_cast<MsgHandler>(&GMainFrame::OnKeyDown);
	m_mpMessageChain[WM_MOVE]			=	static_cast<MsgHandler>(&GMainFrame::OnMove);
	m_mpMessageChain[WM_SHOWWINDOW]		=	static_cast<MsgHandler>(&GMainFrame::OnShow);
	m_mpMessageChain[WM_MOUSEACTIVATE]	=	static_cast<MsgHandler>(&GMainFrame::OnMouseActive);
	m_mpMessageChain[WM_SIZE]			=	static_cast<MsgHandler>(&GMainFrame::OnSize);
	m_mpMessageChain[WM_NCACTIVATE ]	=	static_cast<MsgHandler>(&GMainFrame::OnNCActive);
	m_mpMessageChain[WM_NCCALCSIZE]		=	static_cast<MsgHandler>(&GMainFrame::OnNCCalcSize);
}

//整个位图按钮位于captin的中间(离上下各3相素)，离右边框距离为10相素
LRESULT	GMainFrame::OnNcPaint(WPARAM	wParam, LPARAM	lParam){
	//在边框上面需要画几次，为了避免闪烁，用了memory dc
	HBITMAP	hBack= static_cast<HBITMAP>(
		::LoadImage(NULL, 
		_T("..\\DemoTower\\BkgrdBmp\\MainFrame.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	HBRUSH	hBackGrd	=	::CreatePatternBrush(hBack);
	HDC		hWindowDC	=	::GetWindowDC(GetHwnd());
	::SelectObject(hWindowDC, hBackGrd);
	HDC			hMemDstDC		=	::CreateCompatibleDC(hWindowDC);
	HBITMAP		hBmpToDrawOn	=	::CreateCompatibleBitmap(hWindowDC, MAINFRAME_WIDTH, MAINFRAME_CAPTION_WIDTH);
	::SelectObject(hMemDstDC, hBmpToDrawOn);
	//画周围的四个边框
	::SelectObject(hMemDstDC, hBackGrd);
	::Rectangle(hMemDstDC, 0, 0, MAINFRAME_WIDTH, MAINFRAME_CAPTION_WIDTH);
	::Rectangle(hWindowDC, 0, MAINFRAME_CAPTION_WIDTH, MAINFRAME_BORDER_WIDTH, MAINFRAME_HEIGHT);
	::Rectangle(hWindowDC, MAINFRAME_WIDTH-	MAINFRAME_BORDER_WIDTH, MAINFRAME_CAPTION_WIDTH, MAINFRAME_WIDTH, MAINFRAME_HEIGHT);
	::Rectangle(hWindowDC, 0, MAINFRAME_HEIGHT-	MAINFRAME_BORDER_WIDTH, MAINFRAME_WIDTH, MAINFRAME_HEIGHT);
	//画位图按钮
	HBITMAP	hButton= static_cast<HBITMAP>(
		::LoadImage(NULL, 
		_T("..\\DemoTower\\BkgrdBmp\\Button.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	HDC	hMemSrcDC	=	::CreateCompatibleDC(hWindowDC);
	::SelectObject(hMemSrcDC, hButton);
	unsigned	uBeginPaintX	=	MAINFRAME_WIDTH	-	10	-	MAINFRAME_BITMAPBUTTON_EXIT_WIDTH-	
		MAINFRAME_BITMAPBUTTON_SMALL_WIDTH;
	unsigned	uBeginPaintY	=	3;
	::BitBlt(hMemDstDC, uBeginPaintX, uBeginPaintY, MAINFRAME_BITMAPBUTTON_SMALL_WIDTH, 
		MAINFRAME_BITMAPBUTTON_HEIGHT, hMemSrcDC, 24*(m_bSmallButtonDown+ m_bSmallButtonHover),
		0, SRCCOPY);
	::BitBlt(hMemDstDC, uBeginPaintX+ MAINFRAME_BITMAPBUTTON_SMALL_WIDTH, uBeginPaintY,
		MAINFRAME_BITMAPBUTTON_EXIT_WIDTH, MAINFRAME_BITMAPBUTTON_HEIGHT, hMemSrcDC, 24* 3+ 34* (m_bExitButtonDown+ m_bExitButtonHover),
		0, SRCCOPY);
	::BitBlt(hWindowDC, 0, 0, MAINFRAME_WIDTH, MAINFRAME_CAPTION_WIDTH, hMemDstDC, 0, 0, SRCCOPY);

	//释放句柄
	::DeleteObject(hBack);
	::DeleteObject(hBackGrd);
	::DeleteDC(hMemSrcDC);
	::DeleteDC(hMemDstDC);
	::DeleteObject(hBmpToDrawOn);
	::DeleteObject(hButton);
	::ReleaseDC(GetHwnd(), hWindowDC);
	return	0;
}

LRESULT	GMainFrame::OnSetFocus(WPARAM	wParam, LPARAM	lParam){
	::SendMessage(GetHwnd(), WM_NCPAINT, 0, 0);
	if(!bWin){
		cout<<"un end"<<endl;
		::SetFocus(m_lpGameCtrlArea->GetHwnd());
	}else	{
		cout<<"Game end"<<endl;
	}
	return	0;
}


LRESULT	GMainFrame::OnPaint(WPARAM	wParam, LPARAM	lParam){
	::SendMessage(GetHwnd(), WM_NCPAINT, 0, 0);
	::InvalidateRect(m_lpGameCtrlArea->GetHwnd(), NULL, false);
	::InvalidateRect(m_lpGameInfoArea->GetHwnd(), NULL, false);
	return	m_lpfnOldProc(GetHwnd(), WM_PAINT, wParam, lParam);
}

LRESULT	GMainFrame::OnActive(WPARAM	wParam, LPARAM	lParam){
	::SendMessage(GetHwnd(), WM_NCPAINT, 0, 0);
	::SetFocus(GetHwnd());
	::SendMessage(m_lpGameCtrlArea->GetHwnd(), WM_ACTIVATE, wParam, lParam);
	return	m_lpfnOldProc(GetHwnd(), WM_ACTIVATE, wParam, lParam);
}

LRESULT	GMainFrame::OnNcLButtonDown	(WPARAM	wParam,		LPARAM	lParam){
	POINT	ptMouse;
	::GetCursorPos(&ptMouse);
	bool	bOnSmallButton	=	MouseOnSmallButton	(ptMouse);
	bool	bOnExitButton	=	MouseOnExitButton	(ptMouse);
	if(bOnSmallButton){
		m_bSmallButtonDown	=	true;
		m_bSmallButtonHover	=	true;
	}else	if(bOnExitButton){
		m_bExitButtonDown	=	true;
		m_bExitButtonHover	=	true;
	}
	::SendMessage(GetHwnd(), WM_NCPAINT, 0, 0);
	if(bOnExitButton||bOnSmallButton)
		return	0;
	return	m_lpfnOldProc(GetHwnd(), WM_NCLBUTTONDOWN, wParam, lParam);
}

LRESULT	GMainFrame::OnNcLButtonUp	(WPARAM	wParam,		LPARAM	lParam){
	POINT	ptMouse;
	::GetCursorPos(&ptMouse);
	bool	bOnSmallButton	=	MouseOnSmallButton(ptMouse);
	bool	bOnExitButton	=	MouseOnExitButton(ptMouse);
	if(bOnSmallButton&&m_bSmallButtonDown){//点击最小化
		::ShowWindow(GetHwnd(), SW_MINIMIZE);
	}else	if(bOnExitButton&&m_bExitButtonDown){//点击关闭
		::SendMessage(GetHwnd(), WM_CLOSE, 0, 0);
	}
	m_bExitButtonDown	=	false;
	m_bExitButtonHover	=	false;
	m_bSmallButtonDown	=	false;
	m_bSmallButtonHover	=	false;
	::SendMessage(GetHwnd(), WM_NCPAINT, 0, 0);
	if(bOnExitButton||bOnSmallButton)
		return	0;
	return	m_lpfnOldProc(GetHwnd(), WM_NCLBUTTONUP, wParam, lParam);
}

LRESULT	GMainFrame::OnNcMouseMove	(WPARAM	wParam,		LPARAM	lParam){
	POINT	ptMouse;
	::GetCursorPos(&ptMouse);
	bool	bOnSmallButton	=	MouseOnSmallButton(ptMouse);
	bool	bOnExitButton	=	MouseOnExitButton(ptMouse);
	bool	bShouldChangeState=	false;
	if(bOnExitButton&&	!m_bExitButtonHover){//当前在关闭按钮上移动（以前不在)
		m_bExitButtonHover		=	true;
		bShouldChangeState		=	true;
	}	
	if(bOnSmallButton&&!m_bSmallButtonHover){//当前在最小化按钮上移动（以前不在)
		m_bSmallButtonHover		=	true;
		bShouldChangeState		=	true;
	}
	if(m_bExitButtonHover && !bOnExitButton){//当前不关闭按钮上移动（以前在)
		m_bExitButtonHover		=	false;
		m_bExitButtonDown		=	false;
		bShouldChangeState		=	true;
	}
	if(m_bSmallButtonHover && !bOnSmallButton){//当前不在最小化按钮上移动（以前在)
		m_bSmallButtonHover		=	false;
		m_bSmallButtonDown		=	false;
		bShouldChangeState		=	true;
	}
	if(bShouldChangeState){
		::SendMessage(GetHwnd(), WM_NCPAINT, 0, 0);
	}
	if(bOnExitButton||bOnSmallButton)
		return	0;
	if(m_bExitButtonDown){
		::SendMessage(GetHwnd(), WM_NCPAINT, 0, 0);
		return	0;
	}
	return	m_lpfnOldProc(GetHwnd(), WM_NCMOUSEMOVE, wParam, lParam);
}

LRESULT	GMainFrame::OnWindowPosChanged	(WPARAM	wParam,		LPARAM	lParam){
	::SendMessage(GetHwnd(), WM_NCPAINT, 0, 0);
	return	m_lpfnOldProc(GetHwnd(), WM_WINDOWPOSCHANGED, wParam, lParam);
}

LRESULT	GMainFrame::OnKeyDown			(WPARAM	wParam,		LPARAM	lParam){
	::SendMessage(GetHwnd(), WM_NCPAINT, 0, 0);
	return	m_lpfnOldProc(GetHwnd(), WM_KEYDOWN, wParam, lParam);
}

LRESULT	GMainFrame::OnClose				(WPARAM	wParam,		LPARAM	lParam){
	::PostQuitMessage(0);
	return	0;
}

//整个位图按钮位于captin的中间(离上下各3相素)，离右边框距离为10相素
bool		GMainFrame::MouseOnSmallButton(POINT	ptMouse){
	RECT		WindowRect;
	::GetWindowRect(GetHwnd(), &WindowRect);
	return	(WindowRect.right- 10- MAINFRAME_BITMAPBUTTON_EXIT_WIDTH > ptMouse.x)&&
			(WindowRect.right- 10-	MAINFRAME_BITMAPBUTTON_EXIT_WIDTH- MAINFRAME_BITMAPBUTTON_SMALL_WIDTH< ptMouse.x)&&
			(WindowRect.top+ 3< ptMouse.y)&&(WindowRect.top+ 22> ptMouse.y);
}

bool		GMainFrame::MouseOnExitButton (POINT	ptMouse){
	RECT	WindowRect;
	::GetWindowRect(GetHwnd(), &WindowRect);
	return	(WindowRect.right-	10> ptMouse.x)&&
			(WindowRect.right-	10-	MAINFRAME_BITMAPBUTTON_EXIT_WIDTH< ptMouse.x)&&
			(WindowRect.top+ 3< ptMouse.y)&& (WindowRect.top+ 22> ptMouse.y);
}

LRESULT	GMainFrame::OnMove(WPARAM wParam, LPARAM lParam){
	::SendMessage(m_lpGameCtrlArea->GetHwnd(),WM_MOVE, wParam, lParam);
	::SetFocus(GetHwnd());
	return	0;
}

LRESULT	GMainFrame::OnShow				(WPARAM	wParam,		LPARAM	lParam){
	::SendMessage(m_lpGameCtrlArea->GetHwnd(), WM_SHOWWINDOW, wParam, lParam);
	return	0;
}

LRESULT	GMainFrame::OnMouseActive		(WPARAM	wParam,		LPARAM	lParam){
	::SendMessage(GetHwnd(), WM_NCPAINT, 0, 0);
	return	0;
}

LRESULT	GMainFrame::OnSize				(WPARAM	wParam,		LPARAM	lParam){
	::SendMessage(m_lpGameCtrlArea->GetHwnd(), WM_SIZE, wParam, lParam);
	return	0;
}

LRESULT	GMainFrame::OnNCActive(WPARAM wParam, LPARAM lParam){
	::SendMessage(GetHwnd(), WM_NCPAINT, wParam, lParam);
	return	m_lpfnOldProc(GetHwnd(), WM_NCACTIVATE, wParam, lParam);
}

LRESULT	GMainFrame::OnNCCalcSize(WPARAM wParam, LPARAM lParam){
	::SendMessage(GetHwnd(), WM_NCPAINT, wParam, lParam);
	return	m_lpfnOldProc(GetHwnd(), WM_NCCALCSIZE, wParam, lParam);
}

WPARAM	GMainFrame::MessageLoop(){
	MSG	message;
	while(true){
		if(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)){
			if(message.message==WM_QUIT){
				break;
			}
			::TranslateMessage(&message);
			::DispatchMessage(&message);
		}else{
			::Sleep(1);
			::SendMessage(GetHwnd(), WM_NCPAINT, 0, 0);
		}
	}
	return	message.message;
}