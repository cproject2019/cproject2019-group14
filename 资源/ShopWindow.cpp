#include "GameUserWindow.h"
#include "ShopWindow.h"
#include "SelectList.h"
#include "WndClass.h"
#include "GameStatus.h"
#include "GObjID.h"
#include "MsgTipsWindow.h"

TString	IntToString(int 	iValue); 
GShopWindow::GShopWindow(GGameUserWindow*	lpCtrlWindow):m_lpCtrlWindow(lpCtrlWindow){
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

GShopWindow::~GShopWindow(){
	::DeleteObject(m_bmpBackGround);
	::DeleteObject(m_hTipsFont);
	::DeleteObject(m_hWarningFont);
	delete	m_ListBox;
}

bool	GShopWindow::Create(DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hOwner, HMENU hMenu, LPVOID lpParam ){
	WndClass	wndclass;
	wndclass.GetWndClass().hbrBackground	=	::CreatePatternBrush(m_bmpBackGround);
	wndclass.GetWndClass().lpszClassName	=	lpszClassName;
	wndclass.GetWndClass().hIcon			=	NULL;
	wndclass.GetWndClass().hIconSm			=	NULL;
	wndclass.Register();
	Window::Create(WS_EX_LAYERED|WS_EX_TOOLWINDOW, WS_POPUP|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, lpszClassName, NULL, rtWndArea, hOwner, hMenu, lpParam);
	::SetLayeredWindowAttributes(GetHwnd(), 0, 200, LWA_ALPHA);
	//列表框的大小是150* 100(设置风格是自绘)
	RECT	RectofList	=	{25, 55, 175, 155};
	return	m_ListBox->Create(WS_EX_TOPMOST, WS_CHILD|WS_VISIBLE|LBS_OWNERDRAWVARIABLE, NULL, NULL, RectofList, GetHwnd(), (HMENU)m_uListBoxID, NULL);
}

void	GShopWindow::InitMessageHandler(){
	m_mpMessageChain[WM_SETFOCUS]		=	static_cast<MsgHandler>(&GShopWindow::OnSetFocus);
	m_mpMessageChain[WM_COMMAND]		=	static_cast<MsgHandler>(&GShopWindow::OnCommand);
	m_mpMessageChain[WM_PAINT]			=	static_cast<MsgHandler>(&GShopWindow::OnPaint);
	m_mpMessageChain[WM_DRAWITEM]		=	static_cast<MsgHandler>(&GShopWindow::OnDrawItem);
	m_mpMessageChain[WM_MEASUREITEM]	=	static_cast<MsgHandler>(&GShopWindow::OnMeasureItem);
	m_mpMessageChain[WM_SHOWWINDOW]		=	static_cast<MsgHandler>(&GShopWindow::OnShow);
	m_mpMessageChain[WM_KEYDOWN]			=	static_cast<MsgHandler>(&GShopWindow::OnKeyDown);
}

void	GShopWindow::LoadBackGroundBitmap(const	TString&	strFilePath){
	::DeleteObject(m_bmpBackGround);
	m_bmpBackGround=	static_cast<HBITMAP>(::LoadImage((HINSTANCE)::GetModuleHandle(NULL), strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
}

void	GShopWindow::Shop(GObjID	id){
	m_ShopID	=	id;
	//加载商店的描述字符串
	LoadStringFromFile(_T("..\\DemoTower\\BkgrdBmp\\ShopDescription\\Shop")+ IntToString(m_ShopID)+ _T(".txt"), m_strSoldDescription, true);
	RECT	ParentPos;
	::GetWindowRect(m_lpCtrlWindow->GetHwnd(), &ParentPos);
	::SetWindowPos(GetHwnd(),0,  ParentPos.left+ 76, ParentPos.top+ 76, 0, 0, SWP_NOSIZE);
	::ShowWindow(GetHwnd(), SW_SHOWNORMAL);
	::InvalidateRect(GetHwnd(), NULL, true);
}

LRESULT	GShopWindow::OnSetFocus		(WPARAM	wParam, LPARAM	lParam){
	::SendMessage(m_ListBox->GetHwnd(), LB_SETCURSEL, 0, 0);
	::SetFocus(m_ListBox->GetHwnd());
	return	0;
}

LRESULT	GShopWindow::OnCommand		(WPARAM	wParam, LPARAM	lParam){
	if((lParam!=	(LPARAM)m_ListBox->GetHwnd())||(LOWORD(wParam)!= m_uListBoxID)||(HIWORD(wParam)!= LBN_DBLCLK)){//不是我们要的控件消息
		return	m_lpfnOldProc(GetHwnd(), WM_COMMAND, wParam, lParam);
	}
	unsigned	uChoosed	=	::SendMessage(m_ListBox->GetHwnd(), LB_GETCURSEL, 0, 0);
	if(uChoosed==	m_strSoldDescription.size()- 1){//选择了最后一个(退出)
		::ShowWindow(GetHwnd(), SW_HIDE);
		::SetFocus(m_lpCtrlWindow->GetHwnd());
		return	0;
	}
	switch(m_ShopID){
	case	GID_OBJ_PERWLSRNLPER:	//卖武力的商人(需要较少经验)--204u
		switch(uChoosed){
		case	0:	//提升一级/100点
			if(uExperience<	100){//not enough
				UnableToBuy(_T("经验不够,一会再来吧!"));
				return	0;
			}
			uExperience	-=	100;
			AddPower(1, 0, 0, 0);
			break;

		case	1://增加4点攻击/30点
			if(uExperience< 30){
				UnableToBuy(_T("经验不够,一会再来吧!"));
				return	0;
			}
			uExperience	-= 30;
			AddPower(0, 4, 0, 0);
			break;

		case	2://增加4点防御/30点
			if(uExperience< 30){
				UnableToBuy(_T("经验不够,一会再来吧!"));
				return	0;
			}
			uExperience			-=	30;
			AddPower(0, 0, 4, 0);
			break;

		default:
			return	0;
		}
		break;
	case	GID_OBJ_PERWLSRNMPER://卖武力的商人(需要较多经验)--205u
		switch(uChoosed){
		case	0:
			if(uExperience< 270){
				UnableToBuy(_T("经验不够,一会再来吧!"));
				return	0;
			}
			uExperience	-=	270;
			AddPower(3, 0, 0, 0);
			break;
			
		case	1://增加17点攻击/95点
			if(uExperience< 95){
				UnableToBuy(_T("经验不够,一会再来吧!"));
				return	0;
			}
			uExperience-=	95;
			AddPower(0, 17, 0, 0);
			break;

		case	2://增加17点防御/95点
			if(uExperience< 95){
				UnableToBuy(_T("经验不够,一会再来吧!"));
				return	0;
			}
			uExperience-=	95;
			AddPower(0, 0, 17, 0);
			break;
			
		default:
			return	0;
		}
		break;
	case	GID_OBJ_PERWLNLMON://卖血和武力的（需要较少金钱，占位比较大的商店)--206u
		if(uMoney< 25){
			UnableToBuy(_T("金钱不够,一会再来吧!"));
			return	0;
		}
		uMoney-=	25;
		switch(uChoosed){
		case	0://增加800点生命/$25
			AddPower(0, 0, 0, 800);
			break;
			
		case	1://增加4点攻击/$25
			AddPower(0, 4, 0, 0);
			break;

		case	2://增加4点防御/$25
			AddPower(0, 0, 4, 0);
			break;

		default:
			return	0;
		}
		break;
	case	GID_OBJ_PERWLNMMON://卖血和武力的（需要较多金钱，占位比较大的商店)--207u
		if(uMoney< 100){
			UnableToBuy(_T("金钱不够,一会再来吧!"));
			return	0;
		}
		uMoney-=	100;
		switch(uChoosed){
		case	0://增加4000点生命/$100
			AddPower(0, 0, 0, 4000);
			break;

		case	1://增加20点攻击/$100
			AddPower(0, 20, 0, 0);
			break;

		case	2://增加20点防御/$100
			AddPower(0, 0, 20, 0);
			break;

		default:
			return	0;
		}
		break;
	case	GID_OBJ_PERKEYSELLER://卖钥匙的
		switch(uChoosed){
		case	0://买一把黄钥匙/$10
			if(uMoney< 10){
				UnableToBuy(_T("金钱不够,一会再来吧!"));
				return	0;
			}
			uMoney-=	10;
			++uYellowKey;
			InvalidateRect(m_lpCtrlWindow->GetHwnd(), NULL, false);
			break;

		case	1://买一把蓝钥匙/$50
			if(uMoney< 50){
				UnableToBuy(_T("金钱不够,一会再来吧!"));
				return	0;
			}
			uMoney-=	50;
			++uBlueKey;
			InvalidateRect(m_lpCtrlWindow->GetHwnd(), NULL, false);
			break;

		case	2://买一把红钥匙/$100
			if(uMoney< 100){
				UnableToBuy(_T("金钱不够,一会再来吧!"));
				return	0;
			}
			uMoney-=	100;
			++uRedKey;
			InvalidateRect(m_lpCtrlWindow->GetHwnd(), NULL, false);
			break;

		default:
			return	0;
		}
		break;
	case	GID_OBJ_PERKEYBUYYER://收钥匙的
		switch(uChoosed){
		case	0://卖一把黄钥匙/$7
			if(uYellowKey== 0){
				UnableToBuy(_T("黄钥匙数目不够,一会再来吧!"));
				return	0;
			}
			--uYellowKey;
			uMoney		+=	7;
			InvalidateRect(m_lpCtrlWindow->GetHwnd(), NULL, false);
			break;
			
		case	1://卖一把蓝钥匙/$35
			if(uBlueKey==	0){
				UnableToBuy(_T("蓝钥匙数目不够,一会再来吧!"));
				return	0;
			}
			--uBlueKey;
			uMoney+=	35;
			InvalidateRect(m_lpCtrlWindow->GetHwnd(), NULL, false);
			break;

		case	2://卖一把红钥匙/$70
			if(uRedKey== 0){
				UnableToBuy(_T("红钥匙数目不够,一会再来吧!"));
				return	0;
			}
			--uRedKey;
			uMoney	+=	70;
			InvalidateRect(m_lpCtrlWindow->GetHwnd(), NULL, false);
			break;
		}
	default:
		return	0;
	}
	::InvalidateRect(::GetParent(m_lpCtrlWindow->GetHwnd()), NULL, false);
}

//窗口的大小是200* 200
LRESULT	GShopWindow::OnPaint			(WPARAM	wParam, LPARAM	lParam){
	::InvalidateRect(GetHwnd(), NULL, false);
	PAINTSTRUCT	ps;
	HDC		hDrawDC=	::BeginPaint(GetHwnd(), &ps);
	RECT	ClientRect;
	::GetClientRect(GetHwnd(), &ClientRect);
	//画边框
	HPEN	hPen		=	(HPEN)::CreatePen(PS_SOLID, 3, COLOR_WHITE);
	HPEN	hPrePen		=	(HPEN)::SelectObject(hDrawDC, hPen);
	HBRUSH	hPreBrush	=	(HBRUSH)::SelectObject(hDrawDC, ::GetStockObject(NULL_BRUSH));
	::Rectangle(hDrawDC, ClientRect.left+ 1, ClientRect.top+ 1, ClientRect.right- 1, ClientRect.bottom- 1);

	//画欢迎的提示
	::SelectObject(hDrawDC, hPrePen);
	::SelectObject(hDrawDC, hPreBrush);
	::DeleteObject(hPen);
	::SelectObject(hDrawDC, m_hWarningFont);
	::SetTextColor(hDrawDC, COLOR_WHITE);
	::SetBkMode(hDrawDC, TRANSPARENT);
	SIZE	size;
	TString	strToShow	=	_T("你好勇士");
	unsigned	uPaintCorX	=	10;
	unsigned	uPaintCorY	=	8;
	::GetTextExtentPoint32(hDrawDC, strToShow.c_str(), strToShow.size(), &size);
	::TextOut(hDrawDC, uPaintCorX, uPaintCorY, strToShow.c_str(), strToShow.size());
	strToShow	=	_T("请选择要购买的东西:");
	uPaintCorY=	uPaintCorY+ size.cy+ 5;
	TextOut(hDrawDC, uPaintCorX, uPaintCorY, strToShow.c_str(), strToShow.size());

	//画操作提示
	::SelectObject(hDrawDC, m_hTipsFont);
	::SetTextColor(hDrawDC, RGB(255, 0, 255));
	uPaintCorX	=	6;
	uPaintCorY	=	156;
	strToShow	=	_T("↑");
	TextOut(hDrawDC, uPaintCorX, uPaintCorY, strToShow.c_str(), strToShow.size());
	uPaintCorY	=	168;
	strToShow	=	_T("↓");
	TextOut(hDrawDC, uPaintCorX, uPaintCorY, strToShow.c_str(), strToShow.size());
	uPaintCorY	=	162;
	uPaintCorX	=	20;
	strToShow	=	_T("移动光标");
	TextOut(hDrawDC, uPaintCorX, uPaintCorY, strToShow.c_str(), strToShow.size());

	uPaintCorX	=	6;
	uPaintCorY	=	180;
	strToShow	=	_T("[空格]确定");
	TextOut(hDrawDC, uPaintCorX, uPaintCorY, strToShow.c_str(), strToShow.size());

	uPaintCorX	=	100;
	uPaintCorY	=	170;
	::SetTextColor(hDrawDC, COLOR_WHITE);
	::SelectObject(hDrawDC, m_hWarningFont);
	if(m_ShopID	==	GID_OBJ_PERKEYBUYYER){
		strToShow	=	_T("--得到金钱");
	}else	if(m_ShopID==	GID_OBJ_PERWLSRNLPER|| m_ShopID==	GID_OBJ_PERWLSRNMPER){
		strToShow	=	_T("--需要经验");		
	}else{
		strToShow	=	_T("--需要金钱");
	}
	TextOut(hDrawDC, uPaintCorX, uPaintCorY, strToShow.c_str(), strToShow.size());

	::EndPaint(GetHwnd(), &ps);
	return	0;
}

LRESULT	GShopWindow::OnDrawItem		(WPARAM	wParam, LPARAM	lParam){//要注意写，这里面有问题哦，亲爱的
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

LRESULT	GShopWindow::OnShow			(WPARAM	wParam, LPARAM	lParam){
	if(!wParam){
		return	m_lpfnOldProc(GetHwnd(), WM_SHOWWINDOW, wParam, lParam);
	}
	::SendMessage(m_ListBox->GetHwnd(), LB_RESETCONTENT, 0, 0);
	for(unsigned	i=	0; i< m_strSoldDescription.size(); ++i){
		::SendMessage(m_ListBox->GetHwnd(), LB_ADDSTRING, 0, 0);
		::SendMessage(m_ListBox->GetHwnd(), LB_SETITEMDATA, i, (LPARAM)m_strSoldDescription[i].c_str());
	}
	return	0;
}

LRESULT	GShopWindow::OnMeasureItem	(WPARAM	wParam, LPARAM	lParam){
	LPMEASUREITEMSTRUCT	lpdis=	(LPMEASUREITEMSTRUCT)lParam;
	lpdis->itemHeight	=	25;
	lpdis->itemWidth	=	140;
	return	TRUE;
}

LRESULT	GShopWindow::OnKeyDown			(WPARAM	wParam, LPARAM	lParam){
	if(wParam==	VK_ESCAPE){//退出
		::ShowWindow(GetHwnd(), SW_HIDE);
		::SetFocus(m_lpCtrlWindow->GetHwnd());
		return	0;
	}
	return	m_lpfnOldProc(GetHwnd(), WM_KEYUP, wParam, lParam);
}

void	GShopWindow::UnableToBuy(const	TString&	strFailedDescription){
	::ShowWindow(GetHwnd(), SW_HIDE);
	::SetFocus(m_lpCtrlWindow->GetHwnd());
	m_lpCtrlWindow->GetMsgTpis()->ShowMessage(strFailedDescription, 1000);
}

void	GShopWindow::AddPower(unsigned	uLevelToAdd, unsigned uAtForceToAdd, unsigned	uDfForceToAdd, unsigned	uLifeToAdd){
	uLevel				+=	uLevelToAdd;
	uAttackCapacity		=	uAttackCapacity + uLevelToAdd* 10+ uAtForceToAdd;
	uDefenceCapacity	=	uDefenceCapacity+ uLevelToAdd* 10+ uDfForceToAdd;
	lfBloodVol			+=	uLifeToAdd;
	::InvalidateRect(m_lpCtrlWindow->GetHwnd(), NULL, false);
}