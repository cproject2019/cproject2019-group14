#ifndef		__ZX_GMAINFRAME_H__
#define		__ZX_GMAINFRAME_H__
#include "Window.h"

//这个文件定义的整个游戏的全部窗口区域
class	GMainFrame:	public	Window{
public:
	GMainFrame();
	virtual	~GMainFrame();
public:
	virtual	bool	Create( DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hWndParent, HMENU hMenu, LPVOID lpParam );
	virtual	void	InitMessageHandler();
	virtual	WPARAM	MessageLoop();
private:
	virtual	LRESULT	OnNcPaint			(WPARAM	wParam,		LPARAM	lParam);
	virtual	LRESULT	OnSetFocus			(WPARAM	wParam,		LPARAM	lParam);
	virtual	LRESULT	OnPaint				(WPARAM	wParam,		LPARAM	lParam);
	virtual	LRESULT	OnActive			(WPARAM	wParam,		LPARAM	lParam);
	virtual	LRESULT	OnNcLButtonDown		(WPARAM	wParam,		LPARAM	lParam);
	virtual	LRESULT	OnNcLButtonUp		(WPARAM	wParam,		LPARAM	lParam);
	virtual	LRESULT	OnNcMouseMove		(WPARAM	wParam,		LPARAM	lParam);
	virtual	LRESULT	OnNCActive			(WPARAM	wParam,		LPARAM	lParam);
	virtual	LRESULT	OnWindowPosChanged	(WPARAM	wParam,		LPARAM	lParam);
	virtual	LRESULT	OnKeyDown			(WPARAM	wParam,		LPARAM	lParam);
	virtual	LRESULT	OnClose				(WPARAM	wParam,		LPARAM	lParam);
	virtual	LRESULT	OnMove				(WPARAM	wParam,		LPARAM	lParam);
	virtual	LRESULT	OnShow				(WPARAM	wParam,		LPARAM	lParam);
	virtual	LRESULT	OnMouseActive		(WPARAM	wParam,		LPARAM	lParam);
	virtual	LRESULT	OnSize				(WPARAM	wParam,		LPARAM	lParam);
	virtual	LRESULT	OnNCCalcSize		(WPARAM	wParam,		LPARAM	lParam);
private:
	bool		MouseOnSmallButton(POINT	ptMouse);
	bool		MouseOnExitButton (POINT	ptMouse);
private:
	Window*		m_lpGameCtrlArea;	//游戏区(用户实际上操作的区域)
	Window*		m_lpGameInfoArea;	//显示游戏的相关状态信息(比如生命值等等)
	bool		m_bSmallButtonDown;	//鼠标在按下最小按钮
	bool		m_bSmallButtonHover;//鼠标在最小按钮上面移动(但是,没有按下)
	bool		m_bExitButtonDown;	//鼠标按下退出按钮
	bool		m_bExitButtonHover;	//鼠标在退出按钮上移动(但是,没有按下)
	RECT		m_rtGameArea;
	RECT		m_rtGameInfo;
};


#endif