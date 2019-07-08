#ifndef		__ZX_TRAVERFLOORWINDOW_H__
#define		__ZX_TRAVERFLOORWINDOW_H__
#include "Window.h"

class	GGameUserWindow;
class	GSelectList;

class	GTraverFloorWindow:public	Window{
public:
	GTraverFloorWindow(GGameUserWindow*	lpCtrlWindow);
	virtual	~GTraverFloorWindow();
public:
	virtual	bool	Create(DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hOwner, HMENU hMenu, LPVOID lpParam );
public:
	void	InitMessageHandler();
public:
	void	LoadBackGroundBitmap(const	TString&	strFilePath);
public:
	void	Traverse();
private:
	virtual	LRESULT	OnSetFocus		(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnCommand		(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnPaint			(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnDrawItem		(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnMeasureItem	(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnShow			(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnKeyDown		(WPARAM	wParam, LPARAM	lParam);
private:
	GSelectList*		m_ListBox;				//一个listbox用来显示商店里面出售的物品
	HBITMAP				m_bmpBackGround;		//背景
	HFONT				m_hTipsFont;			//提示用户的字体
	HFONT				m_hWarningFont;			//显示在主窗口上面的字体
	vector<TString>		m_strFloorDescription;	//要卖的东西的描述
	GGameUserWindow*	m_lpCtrlWindow;			
	unsigned			m_uListBoxID;			//子窗口的id号		
	HWND				m_hOwner;
};



#endif	//end of __ZX_TRAVERFLOORWINDOW_H__