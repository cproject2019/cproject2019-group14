#include "TraverFloorWindow.h"
#include "SelectList.h"
#include "GameUserWindow.h"
#include "WndClass.h"
#include "GameStatus.h"
#include "Map.h"
#include "MsgTipsWindow.h"
#include "GObjID.h"

void	ChangeToCurrentFloor();
GTraverFloorWindow::GTraverFloorWindow(GGameUserWindow*	lpCtrlWindow):m_lpCtrlWindow(lpCtrlWindow){
	m_ListBox			=	NULL;
	m_bmpBackGround		=	NULL;
	m_hTipsFont			=	NULL;
	m_hWarningFont		=	NULL;
	m_uListBoxID		=	100;
	m_ListBox			=	new	GSelectList;
	LoadBackGroundBitmap(_T("..\\DemoTower\\BkgrdBmp\\MainFrame.bmp"));
	LOGFONT	font;
	::RtlZeroMemory(&font, sizeof(font));
	font.lfCharSet	=	GB2312_CHARSET;
	StrCpy(font.lfFaceName, _T("楷体\0"));
	font.lfHeight	=	12;
	font.lfWidth	=	6;
	font.lfWeight	=	1;
	m_hTipsFont		=	::CreateFontIndirect(&font);

	font.lfHeight	=	16;
	font.lfWidth	=	8;
	m_hWarningFont	=	::CreateFontIndirect(&font);
}

GTraverFloorWindow::~GTraverFloorWindow(){
	delete	m_ListBox;
	::DeleteObject(m_hWarningFont);
	::DeleteObject(m_hTipsFont);
	::DeleteObject(m_bmpBackGround);
}

bool	GTraverFloorWindow::Create(DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hOwner, HMENU hMenu, LPVOID lpParam ){
	WndClass	wndclass;
	m_hOwner	=	hOwner;
	wndclass.GetWndClass().hbrBackground	=	::CreatePatternBrush(m_bmpBackGround);
	wndclass.GetWndClass().lpszClassName	=	lpszClassName;
	wndclass.GetWndClass().hIconSm			=	NULL;
	wndclass.GetWndClass().hIcon			=	NULL;
	wndclass.Register();
	Window::Create(WS_EX_TOPMOST|WS_EX_LAYERED|WS_EX_TOOLWINDOW, WS_POPUP|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, lpszClassName, NULL, rtWndArea, hOwner, hMenu, lpParam);
	::SetLayeredWindowAttributes(GetHwnd(), 0, 255, LWA_ALPHA);
	//列表框的大小是150* 100(设置风格是自绘)
	RECT	RectofList	=	{10, 30, 190, 210};
	return	m_ListBox->Create(WS_EX_WINDOWEDGE, WS_CHILD|WS_VSCROLL|WS_HSCROLL|LBS_OWNERDRAWVARIABLE, NULL, NULL, RectofList, GetHwnd(), (HMENU)m_uListBoxID, NULL);
}

void	GTraverFloorWindow::InitMessageHandler(){
	m_mpMessageChain[WM_SETFOCUS]		=	static_cast<MsgHandler>(&GTraverFloorWindow::OnSetFocus);
	m_mpMessageChain[WM_COMMAND]		=	static_cast<MsgHandler>(&GTraverFloorWindow::OnCommand);
	m_mpMessageChain[WM_PAINT]			=	static_cast<MsgHandler>(&GTraverFloorWindow::OnPaint);
	m_mpMessageChain[WM_DRAWITEM]		=	static_cast<MsgHandler>(&GTraverFloorWindow::OnDrawItem);
	m_mpMessageChain[WM_MEASUREITEM]	=	static_cast<MsgHandler>(&GTraverFloorWindow::OnMeasureItem);
	m_mpMessageChain[WM_SHOWWINDOW]		=	static_cast<MsgHandler>(&GTraverFloorWindow::OnShow);
	m_mpMessageChain[WM_KEYDOWN]		=	static_cast<MsgHandler>(&GTraverFloorWindow::OnKeyDown);
}

void	GTraverFloorWindow::LoadBackGroundBitmap(const	TString&	strFilePath){
	::DeleteObject(m_bmpBackGround);
	m_bmpBackGround=	static_cast<HBITMAP>(::LoadImage((HINSTANCE)::GetModuleHandle(NULL), strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
}

void	GTraverFloorWindow::Traverse(){
	m_strFloorDescription.clear();
	for(unsigned	i= 0; i< uMaxFloorHasArrive; ++i){
		m_strFloorDescription.push_back(GetMapFileNameByFloor(i));
	}
	RECT	ParentPos;
	::GetWindowRect(m_lpCtrlWindow->GetHwnd(), &ParentPos);
	::SetWindowPos(GetHwnd(),0,  ParentPos.left+ 150, ParentPos.top+ 60, 0, 0, SWP_NOSIZE);
	::ShowWindow(GetHwnd(), SW_SHOWNORMAL);
	::InvalidateRect(GetHwnd(), NULL, false);
	::SetFocus(GetHwnd());
}

LRESULT	GTraverFloorWindow::OnSetFocus		(WPARAM	wParam, LPARAM	lParam){
	::SendMessage(m_ListBox->GetHwnd(), LB_SETCURSEL, 0, 0);
	::SetFocus(m_ListBox->GetHwnd());
	return	0;
}

LRESULT	GTraverFloorWindow::OnCommand		(WPARAM	wParam, LPARAM	lParam){
	if((lParam!=	(LPARAM)m_ListBox->GetHwnd())||(LOWORD(wParam)!= m_uListBoxID)||(HIWORD(wParam)!= LBN_DBLCLK)){//不是我们要的控件消息
		return	m_lpfnOldProc(GetHwnd(), WM_COMMAND, wParam, lParam);
	}
	unsigned	uChoosed	=	::SendMessage(m_ListBox->GetHwnd(), LB_GETCURSEL, 0, 0);
	if(uChoosed< m_strFloorDescription.size()){//用户进行了选择
		//uCurrentFloor	=	uChoosed+ 1;
		if(uCurrentFloor< uChoosed+ 1){//向下走
			bUpFloor	=	true;
		}else{
			bUpFloor	=	false;
		}
		uCurrentFloor=	uChoosed+ 1;
		ChangeToCurrentFloor();
		::InvalidateRect(GetParent(m_lpCtrlWindow->GetHwnd()),NULL, false);
		::UpdateWindow(m_lpCtrlWindow->GetHwnd());
		::ShowWindow(GetHwnd(), SW_HIDE);
		TString	strMessage	=	_T("进入")+ GetMapFileNameByFloor(uCurrentFloor- 1)+ _T("…………");
		::SetFocus(m_lpCtrlWindow->GetHwnd());
		m_lpCtrlWindow->GetMsgTpis()->ShowMessage(strMessage, 800);
	}else	if(uChoosed==	m_strFloorDescription.size()){//选择了取消
		::ShowWindow(GetHwnd(), SW_HIDE);
		::SetFocus(m_lpCtrlWindow->GetHwnd());
	}
	return	0;
}

LRESULT	GTraverFloorWindow::OnPaint			(WPARAM	wParam, LPARAM	lParam){
	PAINTSTRUCT		ps;
	::InvalidateRect(GetHwnd(), NULL, false);
	RECT	RectOfCurrentWnd;
	RECT	RectOfParentWnd;
	RECT	ClientRect;
	::GetClientRect(GetHwnd(), &ClientRect);
	::GetWindowRect(m_hOwner, &RectOfParentWnd);
	::GetWindowRect(GetHwnd(), &RectOfCurrentWnd);
	HDC		hDrawDC		=	::BeginPaint(GetHwnd(), &ps);
	HDC		hParentDC	=	::GetDC(m_hOwner);
	HDC		hMemDC		=	::CreateCompatibleDC(hDrawDC);
	HBITMAP	hBmpToDrawOn	=	::CreateCompatibleBitmap(hDrawDC, ClientRect.right, ClientRect.bottom);
	::SelectObject(hMemDC, hBmpToDrawOn);
	HBRUSH	hBackBrush	=	::CreatePatternBrush(m_bmpBackGround);
	::FillRect(hMemDC, &ClientRect, hBackBrush);
	BLENDFUNCTION	BlendFunc;
	BlendFunc.BlendFlags			=	0;
	BlendFunc.BlendOp				=	AC_SRC_OVER;
	BlendFunc.SourceConstantAlpha	=	150;
	BlendFunc.AlphaFormat			=	0;
	::AlphaBlend(hMemDC, 0, 0, ClientRect.right, ClientRect.bottom, hParentDC, 
		RectOfCurrentWnd.left- RectOfParentWnd.left,  RectOfCurrentWnd.top- RectOfParentWnd.top, 
		ClientRect.right, ClientRect.bottom, BlendFunc);
	HPEN	hPen			=	::CreatePen(PS_INSIDEFRAME, 3, RGB(255, 255, 0));
	HBRUSH	hHollowBrush	=	(HBRUSH)::GetStockObject(NULL_BRUSH);
	::SelectObject(hMemDC, hPen);
	::SelectObject(hMemDC, hHollowBrush);
	::Rectangle(hMemDC, ClientRect.left, ClientRect.top, ClientRect.right, ClientRect.bottom);
	::DeleteObject(hPen);
	hPen	=	CreatePen(PS_INSIDEFRAME, 3, RGB(150, 150, 150));
	::SelectObject(hMemDC, hPen);
	::Rectangle(hMemDC, ClientRect.left+ 7, ClientRect.top+ 27, ClientRect.left+ 193, ClientRect.top+ 213);


	::SelectObject(hMemDC, m_hWarningFont);
	::SetTextColor(hMemDC, COLOR_WHITE);
	::SetBkMode(hMemDC, TRANSPARENT);
	TString	strToShow=	_T("请选择要到达的楼层:");
	::TextOut(hMemDC, 5, 7, strToShow.c_str(), strToShow.size());
	
	::SetTextColor(hMemDC, RGB(255, 0, 200));
	::SelectObject(hMemDC, m_hTipsFont);
	strToShow	=	_T("[方向键]移动 [空格]确定");
	::TextOut(hMemDC, 5, 220, strToShow.c_str(), strToShow.size());

	::BitBlt(hDrawDC, 0, 0, ClientRect.right, ClientRect.bottom, hMemDC, 0, 0, SRCCOPY);
	::DeleteObject(hBackBrush);
	::DeleteObject(hPen);
	::EndPaint(GetHwnd(), &ps);
	return	0;
}

LRESULT	GTraverFloorWindow::OnDrawItem		(WPARAM	wParam, LPARAM	lParam){
	LPDRAWITEMSTRUCT	lpdis	=	(LPDRAWITEMSTRUCT)lParam;
	RECT		RectToDraw	=	lpdis->rcItem;
	unsigned	uItemState	=	lpdis->itemState;
	HDC			hDrawDC		=	lpdis->hDC;
	HBRUSH		hBackBrush;
	HPEN		hFramePen;
	HRGN		hRgn;
	::SelectObject(hDrawDC, m_hWarningFont);
	::SetTextColor(hDrawDC, COLOR_WHITE);
	::SetBkMode(hDrawDC, TRANSPARENT);
	if(uItemState&ODS_SELECTED){
		hBackBrush	=	::CreateSolidBrush(RGB(200, 200, 0));
		hFramePen	=	::CreatePen(PS_SOLID, 1, RGB(200, 200, 0));
		hRgn		=	::CreateEllipticRgn(RectToDraw.left, RectToDraw.top, RectToDraw.right, RectToDraw.bottom);
	}else{
		hBackBrush	=	::CreatePatternBrush(m_bmpBackGround);
		hFramePen	=	::CreatePen(PS_SOLID, 0, NULL_PEN);
		hRgn		=	::CreateRectRgn(RectToDraw.left, RectToDraw.top, RectToDraw.right, RectToDraw.bottom);
	}
	::FillRgn(hDrawDC, hRgn,hBackBrush);
	::DrawText(hDrawDC, (LPCTSTR)lpdis->itemData, lstrlen((LPCTSTR)lpdis->itemData), &RectToDraw, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	::DeleteObject(hFramePen);
	::DeleteObject(hBackBrush);
	::DeleteObject(hRgn);
	return	TRUE;
}

LRESULT	GTraverFloorWindow::OnMeasureItem	(WPARAM	wParam, LPARAM	lParam){
	LPMEASUREITEMSTRUCT	lpdis=	(LPMEASUREITEMSTRUCT)lParam;
	lpdis->itemHeight	=	25;
	lpdis->itemWidth	=	140;
	return	TRUE;
}

LRESULT	GTraverFloorWindow::OnShow			(WPARAM	wParam, LPARAM	lParam){
	if(!wParam){
		return	m_lpfnOldProc(GetHwnd(), WM_SHOWWINDOW, wParam, lParam);
	}
	::SendMessage(m_ListBox->GetHwnd(), LB_RESETCONTENT, 0, 0);
	for(unsigned	i=	0; i< m_strFloorDescription.size(); ++i){
		::SendMessage(m_ListBox->GetHwnd(), LB_ADDSTRING, 0, 0);
		::SendMessage(m_ListBox->GetHwnd(), LB_SETITEMDATA, i, (LPARAM)m_strFloorDescription[i].c_str());
	}
	::SendMessage(m_ListBox->GetHwnd(), LB_ADDSTRING, 0, 0);
	::SendMessage(m_ListBox->GetHwnd(), LB_SETITEMDATA, m_strFloorDescription.size(), (LPARAM)_T("取消"));
	return	0;
}

LRESULT	GTraverFloorWindow::OnKeyDown		(WPARAM	wParam, LPARAM	lParam){
	if(wParam==	VK_ESCAPE){//退出
		::ShowWindow(GetHwnd(), SW_HIDE);
		return	0;
	}else{
		::InvalidateRect(m_ListBox->GetHwnd(), NULL, false);
	}
	return	m_lpfnOldProc(GetHwnd(), WM_KEYUP, wParam, lParam);
}

//向下的楼梯
#define	SEARCH_DOWN_FLOOR	0
//向上的楼梯
#define	SEARCH_UP_FLOOR		1
GPOS	GetFloorPos(unsigned	uFloorNo, unsigned	uFloorType){
	GPOS	UpFloorPos, DownFloorPos;
	GMap&	map=	vAllMaps[uFloorNo- 1];	
	for(unsigned	uRow= 0; uRow< MAP_ROW_SCAL; ++uRow){
		for(unsigned	uCol= 0; uCol< MAP_COL_SCAL; ++uCol){
			if(map.GetObjByIndex(uRow, uCol)== GID_OBJ_UPDOOR){
				UpFloorPos.m_uRow	=	uRow;
				UpFloorPos.m_uCol	=	uCol;
			}else	if(map.GetObjByIndex(uRow, uCol)== GID_OBJ_DOWNDOOR){
				DownFloorPos.m_uRow	=	uRow;
				DownFloorPos.m_uCol	=	uCol;
			}
		}
	}
	if(uFloorType	== SEARCH_DOWN_FLOOR){
		return	DownFloorPos;
	}else{
		return	UpFloorPos;
	}
}

void	SetHeroPosAndDirection(GPOS	FloorPos, unsigned	uFloorNo){
	GMap&	MapTest	=	vAllMaps[uFloorNo- 1];
	unsigned	uRow=	FloorPos.m_uRow;
	unsigned	uCol=	FloorPos.m_uCol;
	if(bUpFloor){
		if(uFloorNo== 1){//是序章
			HeroPos.m_uRow= 9;
			HeroPos.m_uCol=	5;
			uDirection	=	0;
			return	;
		}
	}
	if(uRow> 0){
		if(MapTest.GetObjByIndex(uRow- 1, uCol)== GID_OBJ_PATH){
			uDirection= 0;
			HeroPos.m_uCol=	uCol;
			HeroPos.m_uRow=	uRow- 1;
			return;
		}
	}
	if(uRow< MAP_ROW_SCAL- 1){
		if(MapTest.GetObjByIndex(uRow+ 1, uCol)== GID_OBJ_PATH){
			uDirection= 2;
			HeroPos.m_uCol=	uCol;
			HeroPos.m_uRow=	uRow+ 1;
			return;
		}
	}
	if(uCol> 0){
		if(MapTest.GetObjByIndex(uRow, uCol- 1)== GID_OBJ_PATH){
			uDirection= 1;
			HeroPos.m_uCol=	uCol- 1;
			HeroPos.m_uRow=	uRow;
			return;
		}
	}
	if(uCol< MAP_COL_SCAL- 1){
		if(MapTest.GetObjByIndex(uRow, uCol+ 1)== GID_OBJ_PATH){
			uDirection= 3;
			HeroPos.m_uCol=	uCol+ 1;
			HeroPos.m_uRow=	uRow;
			return;
		}
	}
}

void	ChangeToCurrentFloor(){
	GPOS	FloorPos;
	if(bUpFloor){
		FloorPos	=	GetFloorPos(uCurrentFloor, SEARCH_DOWN_FLOOR);
	}else{
		FloorPos	=	GetFloorPos(uCurrentFloor, SEARCH_UP_FLOOR);
	}
	SetHeroPosAndDirection(FloorPos, uCurrentFloor);
}