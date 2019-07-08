#include "GameUserWindow.h"
#include "WndClass.h"
#include "MessgeTips.h"
#include "TalkingWindow.h"
#include "GObjID.h"
#include "FightWindow.h"
#include "ShopWindow.h"
#include "TraverFloorWindow.h"
#include "GhostInfoQueryWindow.h"
#include "GameStatus.h"
#include "AttrByObjID.h"
#include "MsgTipsWindow.h"
#include "MsgTipsWindow.h"

GGameUserWindow::GGameUserWindow(){
	m_bmpBackGround	=	static_cast<HBITMAP>(
		::LoadImage(NULL, 
		_T("..\\DemoTower\\BkgrdBmp\\MainFrame.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	m_lpTalkingWnd	=	new	GTalkingWindow(this);
	m_lpMsgTipsWnd		=	new	GMsgTipsWindow(this);
	m_lpFightWnd	=	new	GFightWindow(this);
	m_lpShopWnd		=	new	GShopWindow(this);
	m_lpTraverWnd	=	new	GTraverFloorWindow(this);
	m_lpQueryWnd	=	new	GGhostInfoQueryWindow(this);
}

GGameUserWindow::~GGameUserWindow(){
	::DeleteObject(m_bmpBackGround);
	delete	m_lpMsgTipsWnd;
}

bool	GGameUserWindow::Create(DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hWndParent, HMENU hMenu, LPVOID lpParam ){
	//需要自己注册自己需要的窗口类哦，父类可不知道我需要什么样的窗口，所以最好自己注册一个
	WndClass	wndclass;
	wndclass.GetWndClass().hbrBackground	=	(HBRUSH)::CreatePatternBrush(m_bmpBackGround);
	wndclass.GetWndClass().lpszClassName	=	lpszClassName;
	wndclass.Register();
	Window::Create(dwExStyle, dwStyle, lpszClassName, lpszWindowName, rtWndArea, hWndParent, hMenu, NULL);
	
	RECT	MsgTipWndRect=	{0, 0, 300, 50};
	m_lpMsgTipsWnd->Create(WS_EX_WINDOWEDGE, WS_POPUP, _T("MsgTipsWindowClass"), NULL, MsgTipWndRect, ::GetParent(GetHwnd()), NULL, NULL);

	RECT	TalkWndRect=	{0, 0, TLK_WND_WIDTH, TLK_WND_HEIGHT};
	m_lpTalkingWnd->Create(WS_EX_WINDOWEDGE, WS_POPUP, _T("TalkingWindowClass"), NULL, TalkWndRect, ::GetParent(GetHwnd()), NULL, NULL);

	RECT	FitWndRect	=	{0, 0, FIT_DC_WIDTH, FIT_DC_HEIGHT};
	m_lpFightWnd->Create(WS_EX_WINDOWEDGE, WS_POPUP, _T("FightWindowClass"), NULL, FitWndRect, ::GetParent(GetHwnd()), NULL, NULL);

	RECT	ShopWndRect	=	{0, 0, 200, 200};
	m_lpShopWnd->Create(WS_EX_LAYERED, WS_POPUP, _T("ShopWindowClass"), NULL, ShopWndRect, ::GetParent(GetHwnd()), NULL, NULL);

	RECT	TraverWndRect	=	{0, 0, 200, 240};
	m_lpTraverWnd->Create(WS_EX_WINDOWEDGE, WS_POPUP, _T("TraverFloorWindowClass"), NULL, TraverWndRect, ::GetParent(GetHwnd()), NULL, NULL);

	RECT	GhostInfoRect	=	{0, 0, 470, 320};
	m_lpQueryWnd->Create(WS_EX_LAYERED, WS_POPUP, _T("GhostInfoQueryWindowClass"), NULL, GhostInfoRect, ::GetParent(GetHwnd()), NULL, NULL);

	return	true;
}

void	GGameUserWindow::InitMessageHandler(){
	Window::InitMessageHandler();
	m_mpMessageChain[WM_KEYDOWN]		=	static_cast<MsgHandler>(&GGameUserWindow::OnKeyDown);
	m_mpMessageChain[WM_SETFOCUS]		=	static_cast<MsgHandler>(&GGameUserWindow::OnSetFocus);
	m_mpMessageChain[WM_MOVE]			=	static_cast<MsgHandler>(&GGameUserWindow::OnMove);
	m_mpMessageChain[WM_PAINT]			=	static_cast<MsgHandler>(&GGameUserWindow::OnPaint);
	m_mpMessageChain[WM_SHOWWINDOW]		=	static_cast<MsgHandler>(&GGameUserWindow::OnShow);
	m_mpMessageChain[WM_ACTIVATE]		=	static_cast<MsgHandler>(&GGameUserWindow::OnActive);
	m_mpMessageChain[WM_SIZE]			=	static_cast<MsgHandler>(&GGameUserWindow::OnSize);
	m_mpMessageChain[WM_ERASEBKGND]		=	static_cast<MsgHandler>(&GGameUserWindow::OnEraseBkGnd);
}

LRESULT	GGameUserWindow::OnSetFocus		(WPARAM	wParam, LPARAM	lParam){
	if(::IsWindowVisible(m_lpTalkingWnd->GetHwnd())){
		::SetFocus(m_lpTalkingWnd->GetHwnd());
	}else	if(::IsWindowVisible(m_lpShopWnd->GetHwnd())){
		::SetFocus(m_lpShopWnd->GetHwnd());
	}else	if(::IsWindowVisible(m_lpTraverWnd->GetHwnd())){
		::SetFocus(m_lpTraverWnd->GetHwnd());
	}else	if(::IsWindowVisible(m_lpQueryWnd->GetHwnd())){
		::SetFocus(m_lpQueryWnd->GetHwnd());
	}else	if(::IsWindowVisible(m_lpFightWnd->GetHwnd())){
		::SetFocus(m_lpFightWnd->GetHwnd());
	}else	if(::IsWindowVisible(m_lpMsgTipsWnd->GetHwnd())){
		::SetFocus(m_lpMsgTipsWnd->GetHwnd());
	}
	::SendMessage(GetParent(GetHwnd()), WM_NCPAINT, 0, 0);
	return	0;
}

LRESULT	GGameUserWindow::OnActive(WPARAM wParam, LPARAM lParam){
	return	0;
}

LRESULT	GGameUserWindow::OnKeyDown		(WPARAM	wParam, LPARAM	lParam){
	//static	unsigned	uPreTickCout=	::GetTickCount();
	//unsigned	uCurrentTickCount	=	::GetTickCount();
	//if((uCurrentTickCount- uPreTickCout)< 100){
	//	cout<<"Too fast"<<endl;
	//	return	0;
	//}
	//uPreTickCout	=	uCurrentTickCount;
	::SendMessage(GetParent(GetHwnd()), WM_NCPAINT, 0, 0);
	if(wParam== 87){//W
		if(bCanCrossFloorDirectly)
			m_lpTraverWnd->Traverse();
	}else	if(wParam==	 81){//q
		if(bCanQueryGhostAttributes)
			m_lpQueryWnd->Query(uCurrentFloor);
	}else	if(wParam==	VK_LEFT){
		if(MoveLeft()){
			::InvalidateRect(GetParent(GetHwnd()), NULL, false);
		}
	}else	if(wParam==	VK_RIGHT){
		if(MoveRight()){
			::InvalidateRect(GetParent(GetHwnd()), NULL, false);
		}
	}else	if(wParam==	VK_UP){
		if(MoveUp()){
			::InvalidateRect(GetParent(GetHwnd()), NULL, false);
		}
	}else	if(wParam==	VK_DOWN){
		if(MoveDown()){
			::InvalidateRect(GetParent(GetHwnd()), NULL, false);
		}
	}
	return	m_lpfnOldProc(GetHwnd(), WM_KEYDOWN, wParam, lParam);
}

GMsgTipsWindow*	GGameUserWindow::GetMsgTpis(){
	return	m_lpMsgTipsWnd;
}

GTalkingWindow*		GGameUserWindow::GetTlkWindow(){
	return	m_lpTalkingWnd;
}

GFightWindow*		GGameUserWindow::GetFitWindow(){
	return	m_lpFightWnd;
}

LRESULT		GGameUserWindow::OnMove(WPARAM	wParam, LPARAM	lParam){
	unsigned	PosX=	LOWORD(lParam);
	unsigned	PosY=	HIWORD(lParam);
	::SetWindowPos(m_lpTalkingWnd->GetHwnd(), 0, PosX+ 95, PosY+ 120, 0, 0, SWP_NOSIZE);
	::SetWindowPos(m_lpFightWnd->GetHwnd(), 0, PosX+ 30, PosY+ 100, 0, 0, SWP_NOSIZE);
	::SetWindowPos(m_lpShopWnd->GetHwnd(), 0, PosX+ 76, PosY+ 76, 0, 0, SWP_NOSIZE);
	::SetWindowPos(m_lpTraverWnd->GetHwnd(), 0, PosX+ 150, PosY+ 60, 0, 0, SWP_NOSIZE);
	return	0;
}

LRESULT	GGameUserWindow::OnPaint			(WPARAM	wParam, LPARAM	lParam){
	PAINTSTRUCT	ps;
	HDC		hDrawDC		=	::BeginPaint(GetHwnd(), &ps);
	HDC		hMemDstDC	=	::CreateCompatibleDC(hDrawDC);
	HDC		hMemSrcDC	=	::CreateCompatibleDC(hDrawDC);
	HBITMAP	hObjBmp		=	static_cast<HBITMAP>(
		::LoadImage(NULL, 
		_T("..\\DemoTower\\BkgrdBmp\\ObjBmp\\GameObject.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	::SelectObject(hMemSrcDC, hObjBmp);
	HBITMAP	hBmpToDrawOn	=	::CreateCompatibleBitmap(hDrawDC, 32* MAP_ROW_SCAL, 32* MAP_COL_SCAL);
	::SelectObject(hMemDstDC, hBmpToDrawOn);
	GObjID	id;
	GMap&	CurrentMap=	vAllMaps[uCurrentFloor- 1];
	GPOS	ObjPos;
	unsigned	uTransparentColor=	RGB(0, 0, 0);
	GSIZE	ObjSize;
	for(unsigned	uRow= 0; uRow< MAP_ROW_SCAL; ++uRow){
		for(unsigned	uCol= 0; uCol< MAP_COL_SCAL; ++uCol){
			id=	CurrentMap.GetObjByIndex(uRow, uCol);
			if(id== GID_OBJ_ALLOCGOODS){//是大物品的点位标记
				continue;
			}	
			ObjPos	=	GetPosByObjID(id);
			ObjSize	=	GetSizeByObjID(id);
			if(ObjPos.m_uRow< 2){
				uTransparentColor	=	RGB(47, 47, 47);
			}else{
				uTransparentColor	=	RGB(0, 0, 0);
			}
			::TransparentBlt(hMemDstDC, uCol* 32, uRow* 32, 32* ObjSize.uColCount, 32* ObjSize.uRowCount, hMemSrcDC, ObjPos.m_uCol* 32, ObjPos.m_uRow* 32, 32* ObjSize.uColCount, 32* ObjSize.uRowCount, uTransparentColor);
		}
	}
	unsigned	uHeroInBmpOffset;
	if(uDirection== 0){
		uHeroInBmpOffset=	3;
	}else	if(uDirection==  1){
		uHeroInBmpOffset	=	1;
	}else	if(uDirection==	2){
		uHeroInBmpOffset	=	0;
	}else{
		uHeroInBmpOffset	=	2;
	}
	::BitBlt(hMemDstDC, MAP_OBJ_SIZE* HeroPos.m_uCol, MAP_OBJ_SIZE* HeroPos.m_uRow,
		MAP_OBJ_SIZE, MAP_OBJ_SIZE, hMemSrcDC, MAP_OBJ_SIZE* 8, MAP_OBJ_SIZE* (12+ uHeroInBmpOffset), SRCCOPY);
	::TransparentBlt(hDrawDC, 0, 0, 32* MAP_COL_SCAL, 32* MAP_ROW_SCAL, hMemDstDC, 0, 0, 32* MAP_COL_SCAL, 32* MAP_ROW_SCAL, RGB(0, 0, 0));

	::DeleteDC(hMemDstDC);
	::DeleteDC(hMemSrcDC);
	::DeleteObject(hObjBmp);
	::DeleteObject(hBmpToDrawOn);
	::EndPaint(GetHwnd(), &ps);
	return	0;
}

void	MoveTo(unsigned	uRowDst, unsigned	uColDst);

bool	GGameUserWindow::MoveLeft(){
	uDirection	=	1;
	int	iRowDst	=	HeroPos.m_uRow;
	int	iColDst	=	HeroPos.m_uCol;
	--iColDst;
	if(iColDst< 0){//到了边界
		return	true;
	}
	MoveTo(iRowDst, iColDst);
	return	true;
}

bool	GGameUserWindow::MoveRight(){
	uDirection	=	3;
	int	iRowDst	=	HeroPos.m_uRow;
	int	iColDst	=	HeroPos.m_uCol;
	++iColDst;
	if(iColDst> MAP_COL_SCAL- 1){//到了边界
		return	true;
	}
	MoveTo(iRowDst, iColDst);
	return	true;
}

bool	GGameUserWindow::MoveDown(){
	uDirection	=	2;
	int	iRowDst	=	HeroPos.m_uRow;
	int	iColDst	=	HeroPos.m_uCol;
	++iRowDst;
	if(iRowDst> MAP_ROW_SCAL- 1){//到了边界
		return	true;
	}
	MoveTo(iRowDst, iColDst);
	return	true;
}

bool	GGameUserWindow::MoveUp(){
	uDirection	=	0;
	int	iRowDst	=	HeroPos.m_uRow;
	int	iColDst	=	HeroPos.m_uCol;
	--iRowDst;
	if(iRowDst< 0){//到了边界
		return	true;
	}
	MoveTo(iRowDst, iColDst);
	return	true;
}

//为了解决闪烁，用此无耻的方法
LRESULT	GGameUserWindow::OnEraseBkGnd	(WPARAM	wParam, LPARAM	lParam){
	HDC		hDrawDC		=	(HDC)wParam;
	HDC		hMemDstDC	=	::CreateCompatibleDC(hDrawDC);
	HDC		hMemSrcDC	=	::CreateCompatibleDC(hDrawDC);
	HBITMAP	hObjBmp		=	static_cast<HBITMAP>(
		::LoadImage(NULL, 
		_T("..\\DemoTower\\BkgrdBmp\\ObjBmp\\GameObject.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	::SelectObject(hMemSrcDC, hObjBmp);
	HBITMAP	hBmpToDrawOn	=	::CreateCompatibleBitmap(hDrawDC, 32* MAP_ROW_SCAL, 32* MAP_COL_SCAL);
	::SelectObject(hMemDstDC, hBmpToDrawOn);
	GObjID	id;
	GMap&	CurrentMap=	vAllMaps[uCurrentFloor- 1];
	GPOS	ObjPos;
	unsigned	uTransparentColor=	RGB(0, 0, 0);
	GSIZE	ObjSize;
	for(unsigned	uRow= 0; uRow< MAP_ROW_SCAL; ++uRow){
		for(unsigned	uCol= 0; uCol< MAP_COL_SCAL; ++uCol){
			::TransparentBlt(hMemDstDC, uRow* MAP_OBJ_SIZE, uCol* MAP_OBJ_SIZE, MAP_OBJ_SIZE, MAP_OBJ_SIZE, 
				hMemSrcDC, 3*MAP_OBJ_SIZE, 13* MAP_OBJ_SIZE, MAP_OBJ_SIZE, MAP_OBJ_SIZE, RGB(0, 0, 0));
		}
	}
	for(unsigned	uRow= 0; uRow< MAP_ROW_SCAL; ++uRow){
		for(unsigned	uCol= 0; uCol< MAP_COL_SCAL; ++uCol){
			id=	CurrentMap.GetObjByIndex(uRow, uCol);
			if(id== GID_OBJ_ALLOCGOODS){//是大物品的点位标记
				continue;
			}	
			ObjPos	=	GetPosByObjID(id);
			ObjSize	=	GetSizeByObjID(id);
			if(ObjPos.m_uRow< 2){
				uTransparentColor	=	RGB(47, 47, 47);
			}else{
				uTransparentColor	=	RGB(0, 0, 0);
			}
			::TransparentBlt(hMemDstDC, uCol* 32, uRow* 32, 32* ObjSize.uColCount, 32* ObjSize.uRowCount, hMemSrcDC, ObjPos.m_uCol* 32, ObjPos.m_uRow* 32, 32* ObjSize.uColCount, 32* ObjSize.uRowCount, uTransparentColor);
		}
	}
	unsigned	uHeroInBmpOffset;
	if(uDirection== 0){
		uHeroInBmpOffset=	3;
	}else	if(uDirection==  1){
		uHeroInBmpOffset	=	1;
	}else	if(uDirection==	2){
		uHeroInBmpOffset	=	0;
	}else{
		uHeroInBmpOffset	=	2;
	}
	::TransparentBlt(hMemDstDC, MAP_OBJ_SIZE* HeroPos.m_uCol, MAP_OBJ_SIZE* HeroPos.m_uRow,
		MAP_OBJ_SIZE, MAP_OBJ_SIZE, hMemSrcDC, MAP_OBJ_SIZE* 8, MAP_OBJ_SIZE* (12+ uHeroInBmpOffset),MAP_OBJ_SIZE, MAP_OBJ_SIZE,  0);
	::TransparentBlt(hDrawDC, 0, 0, 32* MAP_COL_SCAL, 32* MAP_ROW_SCAL, hMemDstDC, 0, 0, 32* MAP_COL_SCAL, 32* MAP_ROW_SCAL, RGB(0, 0, 0));

	::SendMessage(GetParent(GetHwnd()), WM_NCPAINT, 0, 0);
	::DeleteDC(hMemDstDC);
	::DeleteDC(hMemSrcDC);
	::DeleteObject(hObjBmp);
	::DeleteObject(hBmpToDrawOn);
	return	0;
}

void	ChangeToCurrentFloor();
void	GGameUserWindow::MoveTo(unsigned	uRowDst, unsigned	uColDst){
	GMap&	CurrentMap=	vAllMaps[uCurrentFloor- 1];
	GObjID	id=	CurrentMap.GetObjByIndex(uRowDst, uColDst);
	if(id== GID_OBJ_ALLOCGOODS){
		id= CurrentMap.GetObjByIndex(uRowDst, uColDst-1);
	}
	if(id== GID_OBJ_ALLOCGOODS){
		id= CurrentMap.GetObjByIndex(uRowDst, uColDst-2);
	}
	if(IsGhost(id)){
		MeetWithGhost(id, uRowDst, uColDst);
	}else	if(IsHelpTool(id)){
		MeetWithHelpTool(id, uRowDst,uColDst);
	}else	if(IsNutrition(id)){
		MeetWithNourDrink(id, uRowDst, uColDst);
	}else	if(IsPerson(id)){
		MeetWithPerson(id, uRowDst, uColDst);
	}else	if(IsConstruction(id)){
		MeetWithConstruction(id, uRowDst, uColDst);
	}else	if(IsPowerTool(id)){
		MeetWithAddPowerTool(id,uRowDst,uColDst);
	}
}


//
//注意,游戏的状态不能在这里面修改
//
void	GGameUserWindow::MeetWithPerson			(GObjID	id, unsigned	uRow, unsigned	uCol){
	vector<TString>		AllTalkingContent;
	switch(id){
	case	GID_OBJ_PERGZ:
		LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\公主.txt"), AllTalkingContent, true);
		m_lpTalkingWnd->Talking(AllTalkingContent, GID_OBJ_PERGZ, uRow, uCol);
		return;

	case	GID_OBJ_PERSOG:
		if(bSOGHasGivePower){
			AllTalkingContent.push_back(_T("F希望你能尽快打败大魔王,记得没有准备好不要去见魔王."));
		}else if(bHasVisitSOG){//见过了小仙子
			if(bHasGetCross){//拿到了十字架
				LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\小仙子11.txt"), AllTalkingContent, true);
			}else{
				LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\小仙子10.txt"), AllTalkingContent, true);
			}
		}else{
			if(bHasGetCross){
				LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\小仙子01.txt"), AllTalkingContent, true);
			}else{
				LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\小仙子00.txt"), AllTalkingContent, true);
			}
		}
		m_lpTalkingWnd->Talking(AllTalkingContent, GID_OBJ_PERSOG, uRow, uCol);
		return;

	case	GID_OBJ_PERBROHERO:
		TCHAR	CurrentDirectory[MAX_PATH];
		::GetCurrentDirectory(MAX_PATH, CurrentDirectory);
		wcout<<CurrentDirectory<<endl;
		if(bHasVisitBRH){
			LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\雄哥哥1.txt"), AllTalkingContent, true);
		}else{
			bHasVisitBRH	=	true;
			LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\雄哥哥0.txt"), AllTalkingContent, true);	
		}
		m_lpTalkingWnd->Talking(AllTalkingContent, GID_OBJ_PERBROHERO, uRow, uCol);
		return;

	case	GID_OBJ_PERWUHUN:
		if(bHasVisitWH){//已经见过了
			if(bHasGetHammer){//得到了榔头
				LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\无魂11.txt"), AllTalkingContent, true);
			}else{
				LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\无魂00.txt"), AllTalkingContent, true);
			}
		}else{//没见
			bHasVisitWH	=	true;
			bIronDoorCanCross	=	true;
			if(bHasGetHammer){//有榔头
				LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\无魂01.txt"), AllTalkingContent, true);
			}else{
				LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\无魂10.txt"), AllTalkingContent, true);
			}
		}
		bHasVisitWH	=	true;
		m_lpTalkingWnd->Talking(AllTalkingContent, GID_OBJ_PERWUHUN, uRow, uCol);
		return;

	case	GID_OBJ_PERWLSRNLPER:
		m_lpShopWnd->Shop(GID_OBJ_PERWLSRNLPER);
		return;

	case	GID_OBJ_PERWLSRNMPER:
		m_lpShopWnd->Shop(GID_OBJ_PERWLSRNMPER);
		return;

	case	GID_OBJ_PERWLNLMON:
		m_lpShopWnd->Shop(GID_OBJ_PERWLNLMON);
		return;
		
	case	GID_OBJ_PERWLNMMON:
		m_lpShopWnd->Shop(GID_OBJ_PERWLNMMON);
		return;
		
	case	GID_OBJ_PERKEYSELLER:
		m_lpShopWnd->Shop(GID_OBJ_PERKEYSELLER);
		return;

	case	GID_OBJ_PERKEYBUYYER:
		m_lpShopWnd->Shop(GID_OBJ_PERKEYBUYYER);
		return;

	case	GID_OBJ_PERVICGRANPARENT:
		LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\得到护甲的商人.txt"), AllTalkingContent, true);
		m_lpTalkingWnd->Talking(AllTalkingContent, GID_OBJ_PERVICGRANPARENT, uRow,uCol);
		return;
	case	GID_OBJ_PERVICSELLER:
		LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\得到一把剑的商人.txt"), AllTalkingContent, true);
		m_lpTalkingWnd->Talking(AllTalkingContent, GID_OBJ_PERVICSELLER, uRow,uCol);
		return;
	}
}

void	GGameUserWindow::MeetWithConstruction	(GObjID	id, unsigned	uRow, unsigned	uCol){
	switch(id){
	case	GID_OBJ_WALL:
		return;

	case	GID_OBJ_SKY:
		return;

	case	GID_OBJ_PATH:
		HeroPos.m_uRow	=	uRow;
		HeroPos.m_uCol	=	uCol;
		return;

	case	GID_OBJ_YELKEY:
		++uYellowKey;
		HeroPos.m_uRow	=	uRow;
		HeroPos.m_uCol	=	uCol;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		return;

	case	GID_OBJ_BLUEKEY:
		++uBlueKey;
		HeroPos.m_uRow	=	uRow;
		HeroPos.m_uCol	=	uCol;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		return;
	case	GID_OBJ_REDKEY:
		++uRedKey;
		HeroPos.m_uRow	=	uRow;
		HeroPos.m_uCol	=	uCol;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		return;

	case	GID_OBJ_YELDOOR:
		if(uYellowKey> 0){
			--uYellowKey;
			HeroPos.m_uRow	=	uRow;
			HeroPos.m_uCol	=	uCol;
			vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
			return;
		}else{
			m_lpMsgTipsWnd->ShowMessage(_T("黄钥匙数目不够"), 500);
			return;
		}
	
	case	GID_OBJ_BLUEDOOR:
		if(uBlueKey> 0){
			--uBlueKey;
			HeroPos.m_uRow	=	uRow;
			HeroPos.m_uCol	=	uCol;
			vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
			return;
		}else{
			m_lpMsgTipsWnd->ShowMessage(_T("蓝钥匙数目不够"), 500);
			return;
		}
	case	GID_OBJ_REDDOOR:
		if(uRedKey> 0){
			--uRedKey;
			HeroPos.m_uRow	=	uRow;
			HeroPos.m_uCol	=	uCol;
			vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
			return;
		}else{
			m_lpMsgTipsWnd->ShowMessage(_T("红钥匙数目不够"), 500);
			return;
		}
		
	case	GID_OBJ_IRONDOOR:
		if(bIronDoorCanCross){
			HeroPos.m_uRow	=	uRow;
			HeroPos.m_uCol	=	uCol;
			vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
			return;
		}else{
			m_lpMsgTipsWnd->ShowMessage(_T("你需要一个特殊的东西才能打开它"), 500);
			return;
		}
		
	case	GID_OBJ_FENCEDOOR:
		HeroPos.m_uRow	=	uRow;
		HeroPos.m_uCol	=	uCol;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		return;

	case	GID_OBJ_UPDOOR:
		bUpFloor	=	true;
		++uCurrentFloor;
		if(uMaxFloorHasArrive< uCurrentFloor){
			uMaxFloorHasArrive=	uCurrentFloor;
		}
		ChangeToCurrentFloor();
		return;

	case	GID_OBJ_DOWNDOOR:
		bUpFloor	=	false;
		--uCurrentFloor;
		ChangeToCurrentFloor();
		return;

	case	GID_OBJ_GOLDMONEY:
		HeroPos.m_uRow	=	uRow;
		HeroPos.m_uCol	=	uCol;
		if(rand()%3== 0 || rand()%3==1){
			m_lpMsgTipsWnd->ShowMessage(_T("恭喜你,你中奖了,奖品是500元"), 500);
			uMoney+=	500;
		}else{
			m_lpMsgTipsWnd->ShowMessage(_T("运气真不好,一个空箱子"), 500);
		}
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		return;
	}
}

void	GGameUserWindow::MeetWithAddPowerTool	(GObjID	id, unsigned	uRow, unsigned	uCol){
	HeroPos.m_uRow	=	uRow;
	HeroPos.m_uCol	=	uCol;
	switch(id){
	case	GID_OBJ_PWREDDIAMOND:
		uAttackCapacity+=	3;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		return;

	case	GID_OBJ_PWBLUEDIAMOND:
		uDefenceCapacity+=	3;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		return;

	case	GID_OBJ_PWRHANMAOYU:
		++uLevel;
		uAttackCapacity+= 10;
		uDefenceCapacity+= 10;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		m_lpMsgTipsWnd->ShowMessage(_T("得到")+ GetNameByObjID(id)+ _T("等级+1"), 500);
		return;

	case	GID_OBJ_PWRHANYAYU:
		uLevel+=	3;
		uAttackCapacity+=	30;
		uDefenceCapacity+=	30;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		m_lpMsgTipsWnd->ShowMessage(_T("得到")+ GetNameByObjID(id)+ _T("等级+3"), 500);
		return;

	case	GID_OBJ_PWRIRONSWORD:
		uAttackCapacity+=	10;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		m_lpMsgTipsWnd->ShowMessage(_T("得到")+ GetNameByObjID(id)+ _T("攻击+ 10"), 500);
		return;

	case	GID_OBJ_PWRCOPPERSWORD:
		uAttackCapacity+=	75;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		m_lpMsgTipsWnd->ShowMessage(_T("得到")+ GetNameByObjID(id)+ _T("攻击+ 75"), 500);
		return;

	case	GID_OBJ_PWRBLUESWORD:
		uAttackCapacity+=	200;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		m_lpMsgTipsWnd->ShowMessage(_T("得到")+ GetNameByObjID(id)+ _T("攻击+ 200"), 500);
		return;

	case	GID_OBJ_PWRIRONSHIELD:
		uDefenceCapacity+=	10;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		m_lpMsgTipsWnd->ShowMessage(_T("得到")+ GetNameByObjID(id)+ _T("护甲+ 10"), 500);
		return;

	case	GID_OBJ_PWRGOLDSHELD:
		uDefenceCapacity+=	75;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		m_lpMsgTipsWnd->ShowMessage(_T("得到")+ GetNameByObjID(id)+ _T("护甲+ 75"), 500);
		return;

	case	GID_OBJ_PWRPOINEERSHELD:
		uDefenceCapacity+=	200;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		m_lpMsgTipsWnd->ShowMessage(_T("得到")+ GetNameByObjID(id)+ _T("护甲+ 200"), 500);
		return;

	case	GID_OBJ_PWRCORSS:
		bHasGetCross	=	true;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		m_lpMsgTipsWnd->ShowMessage(_T("得到")+ GetNameByObjID(id)+ _T("快去给小仙女吧"), 1000);
		return;
	}
}

void	GGameUserWindow::MeetWithNourDrink		(GObjID	id, unsigned	uRow, unsigned	uCol){
	HeroPos.m_uRow	=	uRow;
	HeroPos.m_uCol	=	uCol;
	switch(id){
	case	GID_OBJ_NUREDBOTTLE:
		lfBloodVol+=	200;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		return;
		
	case	GID_OBJ_NUBLUEBOTTLE:
		lfBloodVol+=	500;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		return;

	case	GID_OBJ_NUMILK:
		lfBloodVol*=	2;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		m_lpMsgTipsWnd->ShowMessage(_T("得到")+ GetNameByObjID(id)+ _T("血量加倍"), 500);
		return;
	}
}

void	GGameUserWindow::MeetWithGhost			(GObjID	id, unsigned	uRow, unsigned	uCol){
	if(id!=	GID_OBJ_GHHYMW && id!= GID_OBJ_GHTYLMW && id!= GID_OBJ_GHFYLMW){//只有这三个ghost会和主人公讲话
		m_lpFightWnd->Fight(id, uRow, uCol);
		return;
	}
	vector<TString>	AllTalkingContent;
	if(id==	GID_OBJ_GHHYMW){
		LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\红衣魔王.txt"), AllTalkingContent, true);
	}else	if(id==	GID_OBJ_GHTYLMW){
		LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\真魔王0.txt"), AllTalkingContent, true);
	}else	if(id==	GID_OBJ_GHFYLMW){
		LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\假魔王0.txt"), AllTalkingContent, true);
	}
	m_lpTalkingWnd->Talking(AllTalkingContent, id, uRow, uCol);
}

void	GGameUserWindow::MeetWithHelpTool		(GObjID	id, unsigned	uRow, unsigned	uCol){
	HeroPos.m_uRow	=	uRow;
	HeroPos.m_uCol	=	uCol;
	switch(id){
	case	GID_OBJ_TLTRANSPORT:
		bCanCrossFloorDirectly	=	true;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		m_lpMsgTipsWnd->ShowMessage(_T("得到")+ GetNameByObjID(id)+ _T("用W使用"), 1000);
		return;

	case	GID_OBJ_TLQUERYATTR:
		bCanQueryGhostAttributes	=	true;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		m_lpMsgTipsWnd->ShowMessage(_T("得到")+ GetNameByObjID(id)+ _T("用Q使用"), 1000);
		return;

	case	GID_OBJ_TLHAMMER:
		bHasGetHammer	=	true;
		vAllMaps[uCurrentFloor-1].SetObjByIndex(uRow, uCol, GID_OBJ_PATH);
		m_lpMsgTipsWnd->ShowMessage(_T("得到")+ GetNameByObjID(id)+ _T("好像是小偷的专业工具"), 1000);
		return;
	}
}

LRESULT	GGameUserWindow::OnShow			(WPARAM	wParam, LPARAM	lParam){
	return	0;
}

LRESULT	GGameUserWindow::OnSize			(WPARAM	wParam, LPARAM	lParam){
	return	0;
}