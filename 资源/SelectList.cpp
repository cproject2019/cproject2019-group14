#include "SelectList.h"

GSelectList::GSelectList():GListBox(){}

GSelectList::~GSelectList(){}

void	GSelectList::InitMessageHandler(){
	m_mpMessageChain[WM_KEYDOWN]			=	static_cast<MsgHandler>(&GSelectList::OnKeyDown);
	m_mpMessageChain[WM_LBUTTONDBLCLK]		=	static_cast<MsgHandler>(&GSelectList::OnLButtonDBLCLK);
	m_mpMessageChain[WM_ERASEBKGND]			=	static_cast<MsgHandler>(&GSelectList::OnEraseGkGnd);
}

LRESULT	GSelectList::OnKeyDown			(WPARAM	wParam,	LPARAM	lParam){//�û�ѡ����ʲô
	if(wParam==	VK_SPACE||wParam==VK_RETURN){//�û�ѡ����ȷ��,�����㴰�ڷ����û�ȷ�ϵ���Ϣ
		return	::SendMessage(m_hParent, WM_COMMAND, MAKEWPARAM(m_uCtrlID, LBN_DBLCLK), (LPARAM)GetHwnd());
	}else{
		::SendMessage(m_hParent, WM_KEYDOWN, wParam, lParam);
		return	m_lpfnOldProc(GetHwnd(), WM_KEYDOWN, wParam, lParam);
	}
}

LRESULT	GSelectList::OnLButtonDBLCLK	(WPARAM	wParam,	LPARAM	lParam){//�ü������ѡ����ʲô
	return	m_lpfnOldProc(GetHwnd(), WM_LBUTTONDBLCLK, wParam, lParam);
}

LRESULT	GSelectList::OnEraseGkGnd		(WPARAM	wParam,	LPARAM	lParam){
	HDC	hDrawDC	=	(HDC)wParam;
	RECT	ClientRect;
	::GetClientRect(GetHwnd(), &ClientRect);
	HBRUSH	hBackBrush	=	::CreatePatternBrush(m_bmpBackGround);
	::FillRect(hDrawDC, &ClientRect, hBackBrush);
	::DeleteObject(hBackBrush);
	return	TRUE;
}