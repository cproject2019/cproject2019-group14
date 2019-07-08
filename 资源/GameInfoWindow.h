#ifndef		__ZX_GAMEINFOWINDOW_H__
#define		__ZX_GAMEINFOWINDOW_H__
#include "Window.h"
class	GGameInfoWindow:	public	Window{
public:
	GGameInfoWindow();
	virtual	~GGameInfoWindow();
public:
	virtual	bool	Create( DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hWndParent, HMENU hMenu, LPVOID lpParam );
	virtual	void	InitMessageHandler();
private:
	virtual	LRESULT	OnPaint		(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnEraseBkGnd(WPARAM	wParam, LPARAM	lParam);
private:
	HBITMAP		m_bmpBackGround;	//±³¾°Ë¢
	RECT		m_PlayerStatusFrame;
	RECT		m_KeyFrame;
	RECT		m_AuthorInfoFrame;
	HFONT		m_hDrawFont;
	HBITMAP		m_hObjBmp;
};

#endif		//end	of	__ZX_GAMEINFOWINDOW_H__