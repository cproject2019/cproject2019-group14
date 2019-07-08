#ifndef		__ZX_SHOPWINDOW_H__
#define		__ZX_SHOPWINDOW_H__
#include "Window.h"

class	GGameUserWindow;
class	GSelectList;

class	GShopWindow:public	Window{
public:
	GShopWindow(GGameUserWindow*	lpCtrlWindow);
	virtual	~GShopWindow();
public:
	virtual	bool	Create(DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hOwner, HMENU hMenu, LPVOID lpParam );
public:
	void	InitMessageHandler();
public:
	void	LoadBackGroundBitmap(const	TString&	strFilePath);
public:
	void	Shop(GObjID	id);
public:
	virtual	LRESULT	OnSetFocus		(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnCommand		(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnPaint			(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnDrawItem		(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnMeasureItem	(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnShow			(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnKeyDown			(WPARAM	wParam, LPARAM	lParam);
private:
	void	UnableToBuy(const	TString&	strFailedDescription);
	void	AddPower(unsigned	uLevelToAdd, unsigned uAtForceToAdd, unsigned	uDfForceToAdd, unsigned	uLifeToAdd);
private:
	GObjID				m_ShopID;				//确定是哪一个shop
	GSelectList*		m_ListBox;				//一个listbox用来显示商店里面出售的物品
	HBITMAP				m_bmpBackGround;		//背景
	HFONT				m_hTipsFont;			//提示用户的字体
	HFONT				m_hWarningFont;			//显示在主窗口上面的字体
	vector<TString>		m_strSoldDescription;	//要卖的东西的描述
	GGameUserWindow*	m_lpCtrlWindow;			
	unsigned			m_uListBoxID;			//子窗口的id号		
};

#endif