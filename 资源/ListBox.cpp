#include "ListBox.h"

GListBox::GListBox(){
	m_hParent			=	NULL;
	m_bmpBackGround		=	NULL;
	LoadBackGroundBitmap(_T("..\\DemoTower\\BkgrdBmp\\MainFrame.bmp"));
}

GListBox::~GListBox(){
	::DeleteObject(m_bmpBackGround);
}

bool	GListBox::Create( DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hWndParent, HMENU hMenu, LPVOID lpParam ){
	m_uCtrlID		=	(unsigned)hMenu;//id号
	m_hParent		=	hWndParent;	//parent window
	//注意，listbox我们得用系统的实现哦(系统为我们做了太多的事情)，亲(当然，我会 将其subclass滴)
	//因为我们想接收消息，我们一定要将其风格设置为LBS_NOTIFY,并且，不需要名字的哦，故而lpszWindowName= null
	return	Window::Create(WS_EX_TOPMOST, WS_VISIBLE|WS_CHILD|dwStyle|LBS_NOTIFY , _T("listbox"), NULL, rtWndArea, m_hParent, hMenu, lpParam);
}

void	GListBox::LoadBackGroundBitmap(const	TString&	strFilePath){
	::DeleteObject(m_bmpBackGround);//clear the previous bmp
	m_bmpBackGround	=	static_cast<HBITMAP>(::LoadImage(NULL, strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
}
