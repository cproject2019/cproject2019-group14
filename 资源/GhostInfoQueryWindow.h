#ifndef		__ZX_GHOSTINFOQUERYWINDOW_H__
#define		__ZX_GHOSTINFOQUERYWINDOW_H__
#include "Window.h"

class	GGameUserWindow;
class	GSelectList;

//470* 320的大小,其中的列表框是450* 280
class	GGhostInfoQueryWindow:public	Window{
public:
	GGhostInfoQueryWindow(GGameUserWindow*	lpCtrlWindow);
	virtual	~GGhostInfoQueryWindow();
public:
	virtual	bool	Create(DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hOwner, HMENU hMenu, LPVOID lpParam );
public:
	void	InitMessageHandler();
public:
	void	LoadBackGroundBitmap(const	TString&	strFilePath);
public:
	void	Query(unsigned	uFloorNo);//查询第uFloor层的怪物的属性
public:
	virtual	LRESULT	OnSetFocus		(WPARAM	wParam, LPARAM	lParam);
//	virtual	LRESULT	OnCommand		(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnPaint			(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnDrawItem		(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnMeasureItem	(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnShow			(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnKeyDown			(WPARAM	wParam, LPARAM	lParam);
private:
	unsigned			m_uFloorNoToQuery;
	GSelectList*		m_ListBox;				//一个listbox用来显示商店里面出售的物品
	HBITMAP				m_bmpBackGround;		//背景
	HFONT				m_hTipsFont;			//提示用户的字体
	HFONT				m_hWarningFont;			//显示在主窗口上面的字体
	GGameUserWindow*	m_lpCtrlWindow;			
	unsigned			m_uListBoxID;			//子窗口的id号		
};

#endif		//enf of __ZX_GHOSTINFOQUERYWINDOW_H__