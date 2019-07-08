//这个头文件定义主角战斗的处理
#ifndef		__ZX_FIGHTWINDOW_H__
#define		__ZX_FIGHTWINDOW_H__
#include "Window.h"

class	GGameUserWindow;

//大小是430* 120
class	GFightWindow:	public	Window{
public:
	GFightWindow(GGameUserWindow*	lpCtrlWindow);
	virtual	~GFightWindow();
public:
	virtual	bool	Create(DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hOwner, HMENU hMenu, LPVOID lpParam );
public:
	void	InitMessageHandler();
public:
	void	LoadBackGroundBitmap(const	TString&	strFilePath);
	void	Fight(GObjID	id, unsigned	uRow, unsigned	uCol);
private:
	virtual	LRESULT	OnPaint			(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnKillFocus		(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT	OnSetFocus		(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT	OnTimer			(WPARAM wParam, LPARAM lParam);
public:
	HWND		m_hOwner;	
	HFONT		m_hObjNameFont;		//显示对象名字用的字体
	HFONT		m_hObjAttrFont;		//显示对象属性用的字体
	HFONT		m_hVSFont;			//显示VS用的font
	HBITMAP		m_bmpBackGround;
	GObjID		m_idFightWith;
	bool		m_bFinishedFight;
	GGameUserWindow	*	m_lpCtrlWindow;
	unsigned	m_uTimerID;
	double		m_lfGhostBloodVol;		//ghost剩下的血量	
	double		m_lfPerRoundHeroLost;	//一个回合hero失去的血量
	double		m_lpPerRoundGhostLost;	//一个回合ghost失去的血量
	HBITMAP		m_bmpGObject;
	unsigned	m_uRow;
	unsigned	m_uCol;
};
#endif	//end of __ZX_FIGHTWINDOW_H__