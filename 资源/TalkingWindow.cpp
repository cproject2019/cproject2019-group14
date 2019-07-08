#include "TalkingWindow.h"
#include "WndClass.h"
#include "AttrByObjID.h"
#include "GameUserWindow.h"
#include "MsgTipsWindow.h"
#include "GObjID.h"
#include "GameStatus.h"
#include "FightWindow.h"

GTalkingWindow::GTalkingWindow(GGameUserWindow*	lpCtrlWindow){
	m_lpCtrlWindow	=	lpCtrlWindow;
	m_bmpBackGround	=	NULL;
	m_hMessageFont	=	NULL;
	LOGFONT	font;
	::RtlZeroMemory(&font, sizeof(font));
	font.lfCharSet	=	GB2312_CHARSET;
	StrCpy(font.lfFaceName, _T("����\0"));
	font.lfHeight	=	16;
	font.lfWidth	=	8;
	font.lfWeight	=	1;
	m_hMessageFont	=	::CreateFontIndirect(&font);
	font.lfCharSet	=	GB2312_CHARSET;
	StrCpy(font.lfFaceName, _T("����\0"));
	font.lfHeight	=	14;
	font.lfWidth	=	7;
	font.lfWeight	=	1;
	m_hTipsFont		=	::CreateFontIndirect(&font);
	m_uTimerID		=	2000;
	//���ڱ���ͼƬ
	LoadBackGroundBitmap(_T("..\\DemoTower\\BkgrdBmp\\MainFrame.bmp"));
}

GTalkingWindow::~GTalkingWindow(){
	::DeleteObject(m_hMessageFont);
	::DeleteObject(m_bmpBackGround);
	::DeleteObject(m_hTipsFont);
}

//���ڵĳߴ���300*75
bool	GTalkingWindow::Create(DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hOwner, HMENU hMenu, LPVOID lpParam ){
	m_hOwner	=	hOwner;
	WndClass	wndclass;
	wndclass.GetWndClass().lpszClassName	=	lpszClassName;
	wndclass.GetWndClass().hIcon			=	NULL;
	wndclass.GetWndClass().hbrBackground	=	(HBRUSH)::CreatePatternBrush(m_bmpBackGround);
	wndclass.GetWndClass().hIconSm			=	NULL;
	wndclass.Register();
	//���������һ�������Ĵ��ڣ����ǣ������������������������ʾ�����ʶ�����ΪWS_EX_TOOLWINDOW
	Window::Create(WS_EX_TOOLWINDOW|WS_EX_LAYERED, WS_POPUP|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, lpszClassName, NULL, rtWndArea, hOwner, NULL, NULL);
	::SetLayeredWindowAttributes(GetHwnd(), 0, 255, LWA_ALPHA);//���óɰ�͸����
	return	true;
}

void	GTalkingWindow::InitMessageHandler(){
	m_mpMessageChain[WM_PAINT]		=	static_cast<MsgHandler>(&GTalkingWindow::OnPaint);
	m_mpMessageChain[WM_KEYDOWN]	=	static_cast<MsgHandler>(&GTalkingWindow::OnKeyDown);
	m_mpMessageChain[WM_KILLFOCUS]	=	static_cast<MsgHandler>(&GTalkingWindow::OnKillFocus);
	m_mpMessageChain[WM_SETFOCUS]	=	static_cast<MsgHandler>(&GTalkingWindow::OnSetFocus);
	m_mpMessageChain[WM_TIMER]		=	static_cast<MsgHandler>(&GTalkingWindow::OnTimer);
}

void	GTalkingWindow::Talking(const	vector<TString>&	strMessage, GObjID	id, unsigned	uRow, unsigned	uCol){
	m_bFinishedTalk	=	false;
	m_strMessage	=	strMessage;
	m_idSpeaker		=	id;
	m_uRow			=	uRow;
	m_uCol			=	uCol;
	if(strMessage.empty()){
		return;
	}
	RECT	RecTOfOwner;
	::GetWindowRect(m_hOwner, &RecTOfOwner);
	::SetWindowPos(GetHwnd(), 0, RecTOfOwner.left+ 95, RecTOfOwner.top+ 120, 0, 0, SWP_NOSIZE);
	m_uMsgIndex	=	0;
	::InvalidateRect(GetHwnd(), NULL, false);
	::ShowWindow(GetHwnd(), SW_SHOWNORMAL);
	::SetTimer(GetHwnd(), m_uTimerID, 2000, NULL);
}

//���ر���ͼƬ
void	GTalkingWindow::LoadBackGroundBitmap(const TString& strFilePath){
	m_bmpBackGround	=	static_cast<HBITMAP>(::LoadImage(NULL, strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
}

LRESULT	GTalkingWindow::OnPaint(WPARAM	wParam, LPARAM	lParam){
	if(m_strMessage.empty()){
		return	m_lpfnOldProc(GetHwnd(), WM_PAINT, wParam, lParam);
	}
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

	//һ�仰�Ŀ�ͷ��F��ʾ�⻰�ǵ�һ���˽��ģ�����ͷ����F��ʾ�����ǽ���
	TEXTMETRIC	tm;
	::GetTextMetrics(hMemDC, &tm);
	unsigned	uCharHeight	=	tm.tmHeight;
	TString		strSpeakerName;
	SIZE		SizeOfSpeakerName;
	unsigned	uXPrint, uYPrint;
	uXPrint	=	uYPrint	=	5;//���ʱ���X��Y����
	unsigned	uLineExternal=	2;	//��֮��ļ�϶
	if(m_strMessage[m_uMsgIndex][0]==	wchar_t('F')||m_strMessage[m_uMsgIndex][0]==	wchar_t('f')){
		strSpeakerName	=	GetNameByObjID(m_idSpeaker);
	}else{
		strSpeakerName	=	_T("��ʿ");
	}
	//draw speaker name
	TString		strMessage=	m_strMessage[m_uMsgIndex].c_str()+ 1;//����Ҫ��ʾ����Ϣ
	strSpeakerName+= _T(":");
	::GetTextExtentPoint32(hMemDC, strSpeakerName.c_str(), strSpeakerName.size(), &SizeOfSpeakerName);
	TextOut(hMemDC, uXPrint, uYPrint, strSpeakerName.c_str(), strSpeakerName.size());
	uYPrint=	uYPrint+ uCharHeight+ uLineExternal;
	uXPrint+=	SizeOfSpeakerName.cx-	tm.tmAveCharWidth;
	unsigned	uCharHasWrite	=		0;	//�Ѿ�д�˶��ٸ��ַ�
	unsigned	uTotalChar		=		strMessage.size();	//���е�Ҫд���ַ�����
	int	uHSpaceLeft	=	TLK_WND_WIDTH-	uXPrint;//ˮƽ��ʣ�µĴ�С
	int	uCharCanWrite;				//��һ�п���д���ַ�����
	SIZE		CharPatialSize;	//���ռ�õĴ�С
	//draw talking content
	while(uCharHasWrite< uTotalChar){
		::GetTextExtentExPoint(hMemDC, strMessage.c_str(), strMessage.size(), uHSpaceLeft, &uCharCanWrite, NULL, &CharPatialSize);
		::TextOut(hMemDC, uXPrint, uYPrint, strMessage.c_str()+ uCharHasWrite, 
			(uCharHasWrite+ uCharCanWrite>= uTotalChar)?	uTotalChar-uCharHasWrite: uCharCanWrite);
		uCharHasWrite+=	uCharCanWrite;
		uYPrint+=	uCharHeight;
	}
	//draw tips text
	TString		strTips=	_T("[�ո�]��[�س�]");
	SIZE		SizeOfTips;
	::SelectObject(hMemDC, m_hTipsFont);
	::GetTextExtentPoint32(hMemDC, strTips.c_str(), strTips.size(), &SizeOfTips);
	RECT		RectOfTips=	RectOfClient;
	RectOfTips.bottom-= uLindWidth;
	RectOfTips.right-=uLindWidth;
	RectOfTips.left	=	RectOfTips.right- SizeOfTips.cx;
	RectOfTips.top		=	RectOfTips.bottom- SizeOfTips.cy;
	::SetTextColor(hMemDC, RGB(255, 0, 255));
	::DrawText(hMemDC, strTips.c_str(), strTips.size(), &RectOfTips, DT_SINGLELINE);
	::DeleteObject(::SelectObject(hMemDC, hPrePen));
	::BitBlt(hDrawDC, 0, 0, TLK_WND_WIDTH, TLK_WND_HEIGHT, hMemDC, 0, 0, SRCCOPY);

	::DeleteDC(hMemDC);
	::DeleteObject(hBmpToDrawOn);
	::DeleteObject(hPatternBrush);
	::ReleaseDC(GetHwnd(), hMemDC);
	::EndPaint(GetHwnd(), &ps);
	::DeleteObject(hPen);
	::ReleaseDC(m_hOwner, hParentDC);
	return	0;
}

LRESULT	GTalkingWindow::OnKeyDown(WPARAM wParam, LPARAM lParam){
	if(wParam!= VK_RETURN && wParam!= VK_SPACE)
		return	m_lpfnOldProc(GetHwnd(), WM_KEYDOWN, wParam, lParam);
	if(m_uMsgIndex< m_strMessage.size()- 1){
		++m_uMsgIndex;
		::InvalidateRect(GetHwnd(), NULL, false);
		return	0;
	}
	m_bFinishedTalk	=	true;
	::SetFocus(m_hOwner);
	return	0;
}

LRESULT	GTalkingWindow::OnSetFocus(WPARAM wParam, LPARAM lParam){
	//::EnableWindow(m_hOwner, false);
	return	0;
}

LRESULT	GTalkingWindow::OnKillFocus(WPARAM wParam, LPARAM lParam){
	if(!m_bFinishedTalk){
		return	0;
	}
	::ShowWindow(GetHwnd(), SW_HIDE);
	if(m_idSpeaker==	GID_OBJ_PERSOG){//С���ӸոնԻ����
		if(!bHasVisitSOG){//���֮ǰû�м���
			m_lpCtrlWindow->GetMsgTpis()->ShowMessage(_T("�õ�����Կ�׸�һ��"), 500);
			++uRedKey;
			++uBlueKey;
			++uYellowKey;
			vAllMaps[uCurrentFloor-1].SetObjByIndex(m_uRow, m_uCol, GID_OBJ_PATH);
			vAllMaps[uCurrentFloor-1].SetObjByIndex(m_uRow, m_uCol-1, GID_OBJ_PERSOG);
			bHasVisitSOG	=	true;//����Ϊ����С������
		}
		if(bHasGetCross&&!bSOGHasGivePower){//��û�а���������С����Ŷ
			bSOGHasGivePower	=	true;
			uAttackCapacity		+=	200;
			uDefenceCapacity	+=	200;
			m_lpCtrlWindow->GetMsgTpis()->ShowMessage(_T("����+200,����+200"), 500);
		}
		::InvalidateRect(::GetParent(m_lpCtrlWindow->GetHwnd()), NULL, false);
	}else	if(m_idSpeaker==	GID_OBJ_GHHYMW){
		m_lpCtrlWindow->GetFitWindow()->Fight(GID_OBJ_GHHYMW, m_uRow, m_uCol);
	}else	if(m_idSpeaker==	GID_OBJ_GHFYLMW){
		if(!bHasSeeFakeDevil){//��û�д����
			m_lpCtrlWindow->GetFitWindow()->Fight(GID_OBJ_GHFYLMW, m_uRow, m_uCol);
			bHasSeeFakeDevil		=	true;
		}else{
			HeroPos.m_uRow	=	m_uRow;
			HeroPos.m_uCol	=	m_uCol;
			vAllMaps[uCurrentFloor-1].SetObjByIndex(m_uRow, m_uCol, GID_OBJ_PATH);
			::InvalidateRect(m_hOwner, NULL, false);
		}
	}else	if(m_idSpeaker==	GID_OBJ_GHTYLMW){
		if(!bHasSeeTrueDevil){//û�д����
			m_lpCtrlWindow->GetFitWindow()->Fight(GID_OBJ_GHTYLMW, m_uRow, m_uCol);
			bHasSeeTrueDevil		=	true;
		}else{
			HeroPos.m_uRow	=	m_uRow;
			HeroPos.m_uCol	=	m_uCol;
			vAllMaps[uCurrentFloor-1].SetObjByIndex(m_uRow, m_uCol, GID_OBJ_PATH);
			::InvalidateRect(m_hOwner, NULL, false);
		}
	}else	if(m_idSpeaker==	GID_OBJ_PERWUHUN){
		if(bHasVisitWH&&bHasGetHammer){
			vAllMaps[uCurrentFloor-1].SetObjByIndex(m_uRow, m_uCol, GID_OBJ_PATH);
			::InvalidateRect(m_hOwner, NULL, false);
		}
	}else	if(m_idSpeaker==	GID_OBJ_PERVICSELLER){
		vAllMaps[uCurrentFloor-1].SetObjByIndex(m_uRow, m_uCol, GID_OBJ_PATH);
		uAttackCapacity+=	70;
		::InvalidateRect(m_hOwner, NULL, false);
	}else	if(m_idSpeaker==	GID_OBJ_PERVICGRANPARENT){
		vAllMaps[uCurrentFloor-1].SetObjByIndex(m_uRow, m_uCol, GID_OBJ_PATH);
		uDefenceCapacity+=	70;
		::InvalidateRect(m_hOwner, NULL, false);
	}else	if(m_idSpeaker	==	GID_OBJ_PERGZ){
		vAllMaps[uCurrentFloor-1].SetObjByIndex(m_uRow, m_uCol, GID_OBJ_PATH);
		vAllMaps[uCurrentFloor-1].SetObjByIndex(10, 10, GID_OBJ_UPDOOR);
		::InvalidateRect(m_hOwner, NULL, false);
	}
	return	0;
}

LRESULT	GTalkingWindow::OnTimer(WPARAM wParam, LPARAM lParam){
	if(wParam==	m_uTimerID){
		return	0;
	}
	return	m_lpfnOldProc(GetHwnd(), WM_TIMER, wParam, lParam);
}