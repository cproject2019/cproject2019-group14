#include "GhostInfoQueryWindow.h"
#include "GameUserWindow.h"
#include "SelectList.h"
#include "WndClass.h"
#include "GameStatus.h"
#include "AttrByObjID.h"

//470* 320的大小,其中的列表框是450* 280
bool	IsGhost(GObjID	id);
bool	IsMapHasGhost(GMap&	MapToCheck);
void	GetAllGhostInMap(GMap&	MapToCheck, vector<GObjID>& coll);//获取一个地图中所有的怪物

GGhostInfoQueryWindow::GGhostInfoQueryWindow(GGameUserWindow*	lpCtrlWindow){
	m_lpCtrlWindow=	lpCtrlWindow;
	m_ListBox		=	new	GSelectList;
	m_uListBoxID	=	300;
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

GGhostInfoQueryWindow::~GGhostInfoQueryWindow(){
	::DeleteObject(m_bmpBackGround);
	::DeleteObject(m_hWarningFont);
	::DeleteObject(m_hTipsFont);
	delete	m_ListBox;
}

bool	GGhostInfoQueryWindow::Create(DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hOwner, HMENU hMenu, LPVOID lpParam ){
	WndClass	wndclass;
	wndclass.GetWndClass().hbrBackground	=	::CreatePatternBrush(m_bmpBackGround);
	wndclass.GetWndClass().lpszClassName	=	lpszClassName;
	wndclass.GetWndClass().hIconSm			=	NULL;
	wndclass.GetWndClass().hIcon			=	NULL;
	wndclass.Register();
	Window::Create(WS_EX_LAYERED|WS_EX_TOOLWINDOW, WS_POPUP, lpszClassName, lpszWindowName, rtWndArea, hOwner, hMenu, lpParam);
	::SetLayeredWindowAttributes(GetHwnd(), 0, 200, LWA_ALPHA);

	//450* 280的大小
	RECT	RectofList	=	{10, 20, 460, 300};
	return m_ListBox->Create(WS_EX_TOPMOST, WS_CHILD|WS_VSCROLL|WS_HSCROLL|LBS_OWNERDRAWVARIABLE, NULL, NULL, RectofList, GetHwnd(), (HMENU)m_uListBoxID, NULL);
}

void	GGhostInfoQueryWindow::InitMessageHandler(){
	m_mpMessageChain[WM_PAINT]		=	static_cast<MsgHandler>(&GGhostInfoQueryWindow::OnPaint);
	m_mpMessageChain[WM_DRAWITEM]	=	static_cast<MsgHandler>(&GGhostInfoQueryWindow::OnDrawItem);
	m_mpMessageChain[WM_MEASUREITEM]=	static_cast<MsgHandler>(&GGhostInfoQueryWindow::OnMeasureItem);
	m_mpMessageChain[WM_SHOWWINDOW]	=	static_cast<MsgHandler>(&GGhostInfoQueryWindow::OnShow);
	m_mpMessageChain[WM_KEYDOWN]	=	static_cast<MsgHandler>(&GGhostInfoQueryWindow::OnKeyDown);
	m_mpMessageChain[WM_SETFOCUS]	=	static_cast<MsgHandler>(&GGhostInfoQueryWindow::OnSetFocus);
}

void	GGhostInfoQueryWindow::LoadBackGroundBitmap(const	TString&	strFilePath){
	::DeleteObject(m_bmpBackGround);
	m_bmpBackGround=	static_cast<HBITMAP>(::LoadImage((HINSTANCE)::GetModuleHandle(NULL), strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
}

void	GGhostInfoQueryWindow::Query(unsigned	uFloorNo){//查询第uFloor层的怪物的属性
	m_uFloorNoToQuery	=	uFloorNo;
	RECT	RectOfParentWnd;
	::GetWindowRect(m_lpCtrlWindow->GetHwnd(), &RectOfParentWnd);
	::SetWindowPos(GetHwnd(), 0, RectOfParentWnd.left+ 10, RectOfParentWnd.top+ 30, 0, 0, SWP_NOSIZE);
	::ShowWindow(GetHwnd(), SW_SHOWNORMAL);
	::InvalidateRect(GetHwnd(), NULL, true);
	::SetFocus(GetHwnd());
}

LRESULT	GGhostInfoQueryWindow::OnSetFocus		(WPARAM	wParam, LPARAM	lParam){
	::SetFocus(m_ListBox->GetHwnd());
	return	0;
}

//总大小是470* 320，列表框大小是 450* 280（水平居中--距左10，垂直距上是23)
LRESULT	GGhostInfoQueryWindow::OnPaint			(WPARAM	wParam, LPARAM	lParam){
	bool	bHasGhost	=	IsMapHasGhost(vAllMaps[(uCurrentFloor- 1)]);
	PAINTSTRUCT		ps;
	::InvalidateRect(GetHwnd(), NULL, true);
	HDC		hDrawDC	=	::BeginPaint(GetHwnd(), &ps);
	RECT	ClientRect;
	::GetClientRect(GetHwnd(), &ClientRect);
	HBRUSH	hBackBrush	=	::CreatePatternBrush(m_bmpBackGround);
	HBRUSH	hPreBrush	=	(HBRUSH)::SelectObject(hDrawDC, hBackBrush);
	HPEN	hPen		=	::CreatePen(PS_INSIDEFRAME, 3, COLOR_WHITE);
	HPEN	hPrePen		=	(HPEN)::SelectObject(hDrawDC, hPen);
	::Rectangle(hDrawDC, ClientRect.left, ClientRect.top, ClientRect.right, ClientRect.bottom);
	::SelectObject(hDrawDC, hPrePen);
	::SelectObject(hDrawDC, hPreBrush);

	::SelectObject(hDrawDC, m_hWarningFont);
	::SetTextColor(hDrawDC, COLOR_WHITE);
	::SetBkMode(hDrawDC, TRANSPARENT);
	TString	strTitle	=	_T("该楼层怪物如下:");
	if(!bHasGhost){
		strTitle		=	_T("该楼层没有怪物!");
	}
	::SelectObject(hDrawDC, m_hWarningFont);
	::SetTextColor(hDrawDC, COLOR_WHITE);
	::SetBkMode(hDrawDC, TRANSPARENT);
	RECT	RectOfTitle	=	{0, 0, 470, 20};
	::DrawText(hDrawDC, strTitle.c_str(), strTitle.size(), &RectOfTitle, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	::SetTextColor(hDrawDC, RGB(255, 0,  205));
	strTitle	=	_T("[q]或[esc]关闭");
	::TextOut(hDrawDC, 5, 300, strTitle.c_str(), strTitle.size());

	::DeleteObject(hPen);
	::DeleteObject(hBackBrush);
	::EndPaint(GetHwnd(), &ps);
	return	0;
}

LRESULT	GGhostInfoQueryWindow::OnDrawItem		(WPARAM	wParam, LPARAM	lParam){
	LPDRAWITEMSTRUCT	lpDrawItem = (LPDRAWITEMSTRUCT) lParam;
	RECT	RectToDraw	=	lpDrawItem->rcItem;
	HDC		hDrawDC		=	lpDrawItem->hDC;
	GObjID	GhostID		=	lpDrawItem->itemData;
	GPOS	GhostPos	=	GetPosByObjID(GhostID);	
	HBRUSH	hBackGround	=	::CreatePatternBrush(m_bmpBackGround);
	::FillRect(hDrawDC, &RectToDraw, hBackGround);
	if(!IsGhost(GhostID)){
		::DeleteObject(hBackGround);
		return	TRUE;
	}
	HBITMAP	hObjBmp		=	static_cast<HBITMAP>(::LoadImage(NULL, _T("..\\DemoTower\\BkgrdBmp\\Objbmp\\GameObject.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	HDC		hMemDC		=	::CreateCompatibleDC(hDrawDC);
	::SelectObject(hMemDC, hObjBmp);
	//画怪物图像(位于40* 40的中央)
	unsigned	uTransparentColor	=	RGB(0, 0, 0);
	if(GhostPos.m_uRow< 2){
		uTransparentColor	=	RGB(47, 47, 47);
	}
	::TransparentBlt(hDrawDC, RectToDraw.left+ 4, RectToDraw.top+ 4, 32, 32, hMemDC, 32* GhostPos.m_uCol, 32* GhostPos.m_uRow, 32, 32, uTransparentColor);

	//画怪物的属性
	RectToDraw.left+= 40;
	unsigned	uHeight				=	RectToDraw.bottom-	RectToDraw.top;
	TString		strGhostNam		=	GetNameByObjID(GhostID);
	unsigned	uGhostAtForce		=	GetGhostAtForceByObjID(GhostID);
	unsigned	uGhostDfForce		=	GetGhostDfForceByObjID(GhostID);
	unsigned	uGhostBloodVol		=	GetGhostLifeByOdjID(GhostID);
	unsigned	uGhostMoney		=	GetGhostMoneyByObjID(GhostID);
	unsigned	uGhostExperience	=	GetGhostExprByObjID(GhostID);
	TCHAR	FirstLine[100];
	TCHAR	SecondLine[100];
	double	PerRoundGhostLost	=	uAttackCapacity*((double)uDefenceCapacity/(uDefenceCapacity+ ::GetGhostDfForceByObjID(GhostID)));
	double	PerRoundHeroLost	=	::GetGhostAtForceByObjID(GhostID)*(((double)::GetGhostDfForceByObjID(GhostID))/(uDefenceCapacity+ ::GetGhostDfForceByObjID(GhostID)));
	double	HeroTotalLost	=	uGhostBloodVol/PerRoundGhostLost* PerRoundHeroLost;	
	bool	bCanWin	=	HeroTotalLost<= lfBloodVol;
	::SelectObject(hDrawDC, m_hWarningFont);
	::SetTextColor(hDrawDC, COLOR_WHITE);
	::SetBkMode(hDrawDC, TRANSPARENT);
#ifdef	UNICODE
	wsprintf(FirstLine, L"%-6s生命:%-8d攻击:%-6d护甲:%-8d", strGhostNam.c_str(), 
		uGhostBloodVol, uGhostAtForce, uGhostDfForce);
	if(bCanWin)
		wsprintf(SecondLine, L"经验:%-8d金钱:%-8d损失:%-8.2f", uGhostExperience, uGhostMoney, HeroTotalLost);
	else
		wsprintf(SecondLine, L"经验:%-8d金钱:%-8d%s", uGhostExperience, uGhostMoney, L"无法战胜");
#else
	sprintf(FirstLine, "%-12s生命:%-8d攻击:%-6d护甲:%-8d", strGhostNam.c_str(), 
		uGhostBloodVol, uGhostAtForce, uGhostDfForce);
	if(bCanWin)
		sprintf(SecondLine, "经验:%-8d金钱:%-8d损失:%-8.2f", uGhostExperience, uGhostMoney, HeroTotalLost);
	else
		sprintf(SecondLine, "经验:%-8d金钱:%-8d%s", uGhostExperience, uGhostMoney, "无法战胜");
#endif
	uHeight/= 2;
	RectToDraw.bottom	-= uHeight;
	::DrawText(hDrawDC, FirstLine, lstrlen(FirstLine), &RectToDraw, DT_CENTER|DT_SINGLELINE|DT_VCENTER);
	RectToDraw.top		+=	uHeight;
	RectToDraw.bottom	+=	uHeight;
	::DrawText(hDrawDC, SecondLine, lstrlen(SecondLine), &RectToDraw, DT_CENTER|DT_SINGLELINE|DT_VCENTER);
	return	TRUE;
}

LRESULT	GGhostInfoQueryWindow::OnMeasureItem	(WPARAM	wParam, LPARAM	lParam){
	LPMEASUREITEMSTRUCT	lpMeasureItem = (LPMEASUREITEMSTRUCT) lParam;	
	lpMeasureItem->itemHeight	=	40;
	lpMeasureItem->itemWidth	=	450;
	return	TRUE;
}

LRESULT	GGhostInfoQueryWindow::OnShow			(WPARAM	wParam, LPARAM	lParam){
	if(!wParam){
		return	m_lpfnOldProc(GetHwnd(), WM_SHOWWINDOW, wParam, lParam);
	}
	//清除列表框里面的东西
	::SendMessage(m_ListBox->GetHwnd(), LB_RESETCONTENT, 0, 0);

	//得到整个地图上所有的怪物id
	vector<GObjID>	GhostInMap;
	GMap&	CurrentMap=	vAllMaps[uCurrentFloor- 1];
	GObjID	id;
	GetAllGhostInMap(CurrentMap, GhostInMap);
	//设置列表框的数据
	for(unsigned	i= 0; i< GhostInMap.size(); ++i){
		::SendMessage(m_ListBox->GetHwnd(), LB_ADDSTRING, 0, 0);
		::SendMessage(m_ListBox->GetHwnd(), LB_SETITEMDATA, i, (LPARAM)GhostInMap[i]);
	}
	::SendMessage(m_ListBox->GetHwnd(), LB_ADDSTRING, 0, 0);
	::SendMessage(m_ListBox->GetHwnd(), LB_SETITEMDATA, GhostInMap.size(), (LPARAM)0);
	return	0;
}

LRESULT	GGhostInfoQueryWindow::OnKeyDown			(WPARAM	wParam, LPARAM	lParam){
	if(wParam==	 81|| wParam==	VK_ESCAPE){//virtual code of q
		::ShowWindow(GetHwnd(), SW_HIDE);
		::SetFocus(m_lpCtrlWindow->GetHwnd());
	}
	return	0;
}

bool	IsMapHasGhost(GMap&	MapToCheck){
	bool	bHasGhost=	false;
	for(unsigned	uRow=	0; uRow< MAP_ROW_SCAL && !bHasGhost; ++uRow){
		for(unsigned	uCol=	0; uCol< MAP_COL_SCAL; ++uCol){
			if(IsGhost(MapToCheck.GetObjByIndex(uRow, uCol))){
				bHasGhost	=	true;
				break;
			}
		}
	}
	return	bHasGhost;
}

void	GetAllGhostInMap(GMap&	MapToCheck, vector<GObjID>& coll){
	GObjID	id;
	vector<GObjID>	vTmp;

	for(unsigned	uRow= 0; uRow< MAP_ROW_SCAL; ++uRow){
		for(unsigned	uCol= 0; uCol< MAP_COL_SCAL; ++uCol){
			id=	MapToCheck.GetObjByIndex(uRow, uCol);
			if(IsGhost(id)){
				vTmp.push_back(id);
			}
		}
	}
	//去除重复的元素
	coll.clear();
	sort(vTmp.begin(), vTmp.end());
	vector<GObjID>::iterator	itEnd=	unique(vTmp.begin(), vTmp.end());
	for(vector<GObjID>::iterator	it=	vTmp.begin(); it!= itEnd; ++it){
		coll.push_back(*it);
	}
}

