#ifndef		__ZX_TALKINGWINDOW_H__
#define		__ZX_TALKINGWINDOW_H__
#include "Window.h"
class	GGameUserWindow;

class	GTalkingWindow:	public	Window{
public:
	GTalkingWindow(GGameUserWindow*	lpCtrlWindow);
	virtual	~GTalkingWindow();
public:
	virtual	bool	Create(DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hOwner, HMENU hMenu, LPVOID lpParam );
public:
	void	InitMessageHandler();
public:
	void	LoadBackGroundBitmap(const	TString&	strFilePath);
	void	Talking(const	vector<TString>&	strMessage, GObjID	id, unsigned	uRow, unsigned	uCol);
private:
	virtual	LRESULT	OnPaint			(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnKeyDown		(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT	OnKillFocus		(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT	OnSetFocus		(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT	OnTimer			(WPARAM wParam, LPARAM lParam);
public:
	vector<TString>		m_strMessage;
	HWND		m_hOwner;	
	unsigned	m_uMsgIndex;	//指示现在说的是第几句
	HFONT		m_hMessageFont;	//显示消息用的字体
	HBITMAP		m_bmpBackGround;
	GObjID		m_idSpeaker;
	HFONT		m_hTipsFont;
	bool		m_bFinishedTalk;
	GGameUserWindow	*	m_lpCtrlWindow;
	unsigned	m_uTimerID;
	unsigned	m_uRow;
	unsigned	m_uCol;
};
#endif	//end of __ZX_TALKINGWINDOW_H__