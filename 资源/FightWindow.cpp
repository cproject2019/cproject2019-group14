#include "FightWindow.h"
#include "GameUserWindow.h"
#include "AttrByObjID.h"
#include "GameStatus.h"
#include "GameUserWindow.h"
#include "WndClass.h"
#include "MsgTipsWindow.h"
#include "GObjID.h"
#include "TalkingWindow.h"

//430* 120的尺寸
GFightWindow::GFightWindow(GGameUserWindow*	lpCtrlWindow){
	m_lpCtrlWindow		=	lpCtrlWindow;
	m_hOwner			=	NULL;
	m_bFinishedFight	=	false;	//刚开始不需要
	LOGFONT	font;
	::RtlZeroMemory(&font, sizeof(font));
	font.lfCharSet	=	GB2312_CHARSET;
	StrCpy(font.lfFaceName, _T("隶书\0"));
	font.lfHeight	=	20;
	font.lfWidth	=	10;
	font.lfWeight	=	1;
	m_hObjAttrFont	=	::CreateFontIndirect(&font);

	//画对战双方名字的字体
	font.lfCharSet	=	GB2312_CHARSET;
	StrCpy(font.lfFaceName, _T("楷体\0"));
	font.lfHeight		=	24;
	font.lfWidth		=	12;
	font.lfWeight		=	1;
	m_hObjNameFont	=	::CreateFontIndirect(&font);

	//画VS用的字体
	StrCpy(font.lfFaceName, _T("华康少女文字W5\0"));
	font.lfHeight		=	70;
	font.lfWidth		=	35;
	font.lfWeight		=	1;
	m_hVSFont		=	::CreateFontIndirect(&font);
	m_bmpGObject	=	static_cast<HBITMAP>(::LoadImage(NULL, _T("..\\DemoTower\\BkgrdBmp\\Objbmp\\GameObject.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	LoadBackGroundBitmap(_T("..\\DemoTower\\BkgrdBmp\\MainFrame.bmp"));
	m_uTimerID	=	1000;
}

GFightWindow::~GFightWindow(){
	::DeleteObject(m_bmpBackGround);
	::DeleteObject(m_hObjAttrFont);
	::DeleteObject(m_hVSFont);
	::DeleteObject(m_hObjNameFont);
	::DeleteObject(m_bmpGObject);
	::KillTimer(GetHwnd(), m_uTimerID);
}

void	GFightWindow::LoadBackGroundBitmap(const	TString&	strFilePath){
	m_bmpBackGround	=	static_cast<HBITMAP>(::LoadImage(NULL, strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
}

bool	GFightWindow::Create(DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hOwner, HMENU hMenu, LPVOID lpParam ){
	m_hOwner		=	hOwner;
	WndClass	wndclass;
	wndclass.GetWndClass().lpszClassName	=	lpszClassName;
	wndclass.GetWndClass().hbrBackground	=	::CreatePatternBrush(m_bmpBackGround);
	wndclass.GetWndClass().hIcon			=	NULL;
	wndclass.GetWndClass().hIconSm			=	NULL;
	wndclass.Register();
	Window::Create(WS_EX_TOOLWINDOW|WS_EX_LAYERED, WS_POPUP|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, lpszClassName, NULL, rtWndArea, hOwner, NULL, NULL);
	::SetLayeredWindowAttributes(GetHwnd(), 0, 255, LWA_ALPHA);//设置成半透明的
	return	true;
}

void	GFightWindow::InitMessageHandler(){
	m_mpMessageChain[WM_PAINT]		=	static_cast<MsgHandler>(&GFightWindow::OnPaint);
	m_mpMessageChain[WM_KILLFOCUS]	=	static_cast<MsgHandler>(&GFightWindow::OnKillFocus);
	m_mpMessageChain[WM_SETFOCUS]	=	static_cast<MsgHandler>(&GFightWindow::OnSetFocus);
	m_mpMessageChain[WM_TIMER]		=	static_cast<MsgHandler>(&GFightWindow::OnTimer);
}

void	GFightWindow::Fight(GObjID	id, unsigned	uRow, unsigned	uCol){
	m_idFightWith			=	id;
	m_uRow		=	uRow;
	m_uCol		=	uCol;
	m_lfGhostBloodVol		=	::GetGhostLifeByOdjID(id);
	unsigned	uGhostAtForce	=	::GetGhostAtForceByObjID(id);
	unsigned	uGhostDfForce	=	::GetGhostDfForceByObjID(id);
	m_lpPerRoundGhostLost	=	uAttackCapacity*((double)uDefenceCapacity/(uDefenceCapacity+ ::GetGhostDfForceByObjID(id)));
	m_lfPerRoundHeroLost	=	::GetGhostAtForceByObjID(id)*(((double)::GetGhostDfForceByObjID(id))/(uDefenceCapacity+ ::GetGhostDfForceByObjID(id)));
	if(ceil(m_lfGhostBloodVol/m_lpPerRoundGhostLost)* m_lfPerRoundHeroLost>	lfBloodVol){
		m_lpCtrlWindow->GetMsgTpis()->ShowMessage(_T("打不过,过会再来吧,亲!"), 1000);
		return;
	}
	RECT	RectOfParent;
	::InvalidateRect(GetHwnd(), NULL, false);
	::GetWindowRect(m_hOwner, &RectOfParent);
	::SetWindowPos(GetHwnd(), 0, RectOfParent.left+ 30, RectOfParent.top+ 100, 0, 0, SWP_NOSIZE);
	::ShowWindow(GetHwnd(), SW_SHOWNORMAL);
	m_bFinishedFight		=	false;
	::SetTimer(GetHwnd(), m_uTimerID, 300, NULL);
}

TString	IntToString(int 	iValue); 
LRESULT	GFightWindow::OnPaint			(WPARAM	wParam, LPARAM	lParam){
	PAINTSTRUCT	ps;
	HDC	hDrawDC	=	::BeginPaint(GetHwnd(), &ps);
	HDC	hMemSrcDC	=	::CreateCompatibleDC(hDrawDC);
	HDC	hMemDstDC	=	::CreateCompatibleDC(hDrawDC);
	HBRUSH	hPatternBrush	=	::CreatePatternBrush(m_bmpBackGround);
	HBITMAP	hBmpToDrawOn	=	::CreateCompatibleBitmap(hDrawDC, FIT_DC_WIDTH, FIT_DC_HEIGHT);
	::SelectObject(hMemDstDC, hBmpToDrawOn);
	RECT	ClientRect;
	::GetClientRect(GetHwnd(), &ClientRect);
	//HPEN	hPrePen		=	(HPEN)::SelectObject(hMemDstDC, ::CreatePen(PS_SOLID, 3, COLOR_WHITE));
	//HBRUSH	hPreBrush	=	(HBRUSH)::SelectObject(hMemDstDC, hPatternBrush);
	HDC		hParentDC	=	::GetWindowDC(m_hOwner);
	RECT	RectOfParentWnd;
	RECT	RectOfCurrentWnd;
	::GetWindowRect(m_hOwner, &RectOfParentWnd);
	::GetWindowRect(GetHwnd(), &RectOfCurrentWnd);
	RECT	RectOfCurrentClient	=	{0, 0, FIT_DC_WIDTH, FIT_DC_HEIGHT};
	::FillRect(hMemDstDC, &RectOfCurrentClient, hPatternBrush);
	BLENDFUNCTION	BlendFunc;
	BlendFunc.BlendFlags			=	0;
	BlendFunc.BlendOp				=	AC_SRC_OVER;
	BlendFunc.SourceConstantAlpha	=	150;
	BlendFunc.AlphaFormat			=	0;
	//::AlphaBlend(hDrawDC, DrawRt.left, DrawRt.top, 300, 50, hMemDstDC, 0, 0, 300, 50, BlendFunc);
	::AlphaBlend(hMemDstDC, 0, 0, FIT_DC_WIDTH, FIT_DC_HEIGHT, hParentDC, RectOfCurrentWnd.left- RectOfParentWnd.left,
		RectOfCurrentWnd.top- RectOfParentWnd.top, FIT_DC_WIDTH, FIT_DC_HEIGHT, BlendFunc);
	HBRUSH	hHollowBrush	=	(HBRUSH)::GetStockObject(NULL_BRUSH);
	HPEN	hPen	=	::CreatePen(PS_INSIDEFRAME, 3, RGB(255, 255, 0));
	::SelectObject(hMemDstDC, hHollowBrush);
	::SelectObject(hMemDstDC, hPen);
	//::BitBlt(hMemDstDC, 0, 0, RectOfCurrentWnd.right-RectOfCurrentWnd.left,
	//	RectOfCurrentWnd.bottom-RectOfCurrentWnd.top, hParentDC, 
	//	RectOfCurrentWnd.left- RectOfParentWnd.left, RectOfCurrentWnd.top- RectOfParentWnd.top, SRCCOPY);
	////整个窗口的边框
	::Rectangle(hMemDstDC, ClientRect.left, ClientRect.top, ClientRect.right, ClientRect.bottom);
	//对战双方的图像框
	::Rectangle(hMemDstDC, ClientRect.left+ 10, ClientRect.top+ 10, ClientRect.left+ 60, ClientRect.top+ 60);
	::Rectangle(hMemDstDC, ClientRect.right- 60, ClientRect.bottom- 60, ClientRect.right- 10, ClientRect.bottom- 10);
	//显示对战双方图像
	::SelectObject(hMemSrcDC, m_bmpGObject);
	::TransparentBlt(hMemDstDC, ClientRect.right- 51, ClientRect.bottom- 51, 32, 32, hMemSrcDC, 32* 8, 32* 12, 32, 32, RGB(0, 0, 0));
	unsigned	uTransparentColor	=	RGB(0, 0, 0);
	GPOS	pos=	::GetPosByObjID(m_idFightWith);
	if(pos.m_uRow< 2){
		uTransparentColor	=	RGB(47, 47, 47);
	}
	::TransparentBlt(hMemDstDC, ClientRect.left+ 19, ClientRect.top+ 19, 32, 32, hMemSrcDC, 32* pos.m_uCol, 32* pos.m_uRow,32, 32, uTransparentColor);
	//::DeleteObject(::SelectObject(hMemDstDC, hPrePen));

	//画对战双方的属性
	TString	strShow;
	unsigned	uPaintPosX, uPaintPosY;
	::SelectObject(hMemDstDC, m_hObjAttrFont);
	strShow=	_T("血量:")+ IntToString(m_lfGhostBloodVol);
	::SetTextColor(hMemDstDC, COLOR_WHITE);
	::SetBkMode(hMemDstDC, TRANSPARENT);
	uPaintPosX	=	60;
	uPaintPosY	=	3;
	::TextOut(hMemDstDC, uPaintPosX, uPaintPosY, strShow.c_str(), strShow.size());
	TEXTMETRIC	tm;
	::GetTextMetrics(hMemDstDC, &tm);
	uPaintPosY=	uPaintPosY+ tm.tmHeight;
	strShow=	_T("武力:")+ IntToString(::GetGhostAtForceByObjID(m_idFightWith));
	::TextOut(hMemDstDC, uPaintPosX, uPaintPosY, strShow.c_str(), strShow.size());
	uPaintPosY=	uPaintPosY+ tm.tmHeight;
	strShow=	_T("护甲:")+ IntToString(::GetGhostDfForceByObjID(m_idFightWith));
	::TextOut(hMemDstDC, uPaintPosX, uPaintPosY, strShow.c_str(), strShow.size());

	SIZE	size;
	strShow=	IntToString(lfBloodVol)+ _T(":量血");
	::GetTextExtentPoint32(hMemDstDC, strShow.c_str(), strShow.size(), &size);
	uPaintPosY	=	ClientRect.bottom- 10- tm.tmHeight* 3+ 5;
	uPaintPosX	=	ClientRect.right- 60- size.cx;
	::TextOut(hMemDstDC, uPaintPosX, uPaintPosY, strShow.c_str(), strShow.size());

	uPaintPosY	=	uPaintPosY+ tm.tmHeight;
	strShow= IntToString(uAttackCapacity)+ _T(":力武");
	::GetTextExtentPoint32(hMemDstDC, strShow.c_str(), strShow.size(), &size);
	uPaintPosX	=	ClientRect.right- 60- size.cx;
	::TextOut(hMemDstDC, uPaintPosX, uPaintPosY, strShow.c_str(), strShow.size());

	uPaintPosY	=	uPaintPosY+ tm.tmHeight;
	strShow= IntToString(uDefenceCapacity)+ _T(":甲护");
	::GetTextExtentPoint32(hMemDstDC, strShow.c_str(), strShow.size(), &size);
	uPaintPosX	=	ClientRect.right- 60- size.cx;
	::TextOut(hMemDstDC, uPaintPosX, uPaintPosY, strShow.c_str(), strShow.size());

	::SelectObject(hMemDstDC, m_hObjNameFont);
	strShow=	::GetNameByObjID(m_idFightWith);
	uPaintPosX=	5;
	uPaintPosY	=	60;
	::TextOut(hMemDstDC, uPaintPosX, uPaintPosY, strShow.c_str(), strShow.size());

	strShow	=	_T("勇士");
	::GetTextExtentPoint32(hMemDstDC, strShow.c_str(),strShow.size(), &size);
	uPaintPosX=	ClientRect.right-10- size.cx;
	uPaintPosY=	ClientRect.bottom- 60- size.cy;
	::TextOut(hMemDstDC, uPaintPosX, uPaintPosY, strShow.c_str(), strShow.size());

	::SelectObject(hMemDstDC, m_hVSFont);
	strShow	=	_T("VS");
	::GetTextExtentPoint32(hMemDstDC, strShow.c_str(),strShow.size(), &size);
	uPaintPosX	=	(ClientRect.right+ ClientRect.left- size.cx)/2;
	uPaintPosY	=	(ClientRect.top+ ClientRect.bottom- size.cy)/2;
	::TextOut(hMemDstDC, uPaintPosX, uPaintPosY, strShow.c_str(), strShow.size());

	::BitBlt(hDrawDC, 0, 0, FIT_DC_WIDTH, FIT_DC_HEIGHT, hMemDstDC, 0, 0, SRCCOPY);

	::ReleaseDC(m_hOwner, hParentDC);
	::DeleteObject(hPatternBrush);
	::DeleteDC(hMemDstDC);
	::DeleteObject(hBmpToDrawOn);
	::EndPaint(GetHwnd(), &ps);
	::DeleteDC(hMemSrcDC);
	::DeleteObject(hPen);
	return	0;
}

LRESULT	GFightWindow::OnTimer			(WPARAM wParam, LPARAM lParam){
	::SendMessage(m_hOwner, WM_NCPAINT, wParam, lParam);
	if(wParam!=m_uTimerID){//不是我们设置的timer
		return	m_lpfnOldProc(GetHwnd(), WM_TIMER, wParam, lParam);
	}
	if(!m_bFinishedFight){
		m_lfGhostBloodVol	-=	m_lpPerRoundGhostLost;
		lfBloodVol			-=	m_lfPerRoundHeroLost;
		::InvalidateRect(GetHwnd(), NULL, false);
		::UpdateWindow(GetHwnd());
	}
	if(m_lfGhostBloodVol<= 0){
		::KillTimer(GetHwnd(), m_uTimerID);
		m_bFinishedFight	=	true;
		::ShowWindow(GetHwnd(), SW_HIDE);
		::SetFocus(m_hOwner);
			vector<TString>	AllTalkingContent;
	::ShowWindow(GetHwnd(), SW_HIDE);
	if(m_idFightWith!= GID_OBJ_GHFYLMW&& m_idFightWith!=	GID_OBJ_GHTYLMW){
		m_bFinishedFight	= false;
		unsigned	uGhostExpr		=	::GetGhostExprByObjID(m_idFightWith);
		unsigned	uGhostMoney	=	::GetGhostMoneyByObjID(m_idFightWith);
		uMoney		+=	uGhostMoney;
		uExperience	+=	uGhostExpr;
		TString	strMessge	=	_T("经验+ ")+ IntToString(uGhostExpr)+ _T(" 金钱+ ")+ IntToString(uGhostMoney);
		m_lpCtrlWindow->GetMsgTpis()->ShowMessage(strMessge, 500);
		vAllMaps[uCurrentFloor-1].SetObjByIndex(m_uRow, m_uCol, GID_OBJ_PATH);
		HeroPos.m_uRow	=	m_uRow;
		HeroPos.m_uCol	=	m_uCol;
		::InvalidateRect(m_hOwner, NULL, false);
	}
	else	if(m_idFightWith==	GID_OBJ_GHFYLMW){
		bHasSeeFakeDevil	=	true;
		LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\假魔王1.txt"), AllTalkingContent, true);
		m_lpCtrlWindow->GetTlkWindow()->Talking(AllTalkingContent, GID_OBJ_GHFYLMW, m_uRow, m_uCol);
	}else	if(m_idFightWith==	GID_OBJ_GHTYLMW){
		bHasSeeTrueDevil	=	true;
		LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\Talking\\真魔王1.txt"), AllTalkingContent, true);
		m_lpCtrlWindow->GetTlkWindow()->Talking(AllTalkingContent, GID_OBJ_GHTYLMW, m_uRow, m_uCol);
	}
	return	0;
	}
	return	0;
}

LRESULT	GFightWindow::OnKillFocus		(WPARAM wParam, LPARAM lParam){
	if(!m_bFinishedFight){
		return	0;
	}
}

LRESULT	GFightWindow::OnSetFocus		(WPARAM wParam, LPARAM lParam){
	::SendMessage(m_hOwner, WM_NCPAINT, 0, 0);
	return	0;
}

TString	IntToString(int 	iValue){
	TString		strInt;	//存放int的值
	while(iValue){
		strInt.push_back(wchar_t(iValue%10+ '0'));
		iValue/=	10;
	}
	reverse(strInt.begin(), strInt.end());
	return	strInt;
}