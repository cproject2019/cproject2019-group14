#ifndef		__ZX_MSGTIPSWINDOW_H__
#define		__ZX_MSGTIPSWINDOW_H__
#include "Window.h"
class	GGameUserWindow;

class	GMsgTipsWindow:	public	Window{
public:
	GMsgTipsWindow(GGameUserWindow*	lpCtrlWindow);
	virtual	~GMsgTipsWindow();
public:
	virtual	bool	Create( DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hWndParent, HMENU hMenu, LPVOID lpParam );
public:
	virtual	void	ShowMessage(const	TString&	strMessage,	
		unsigned	uMilSecondsToWait);
private:
	virtual	void	InitMessageHandler();
private:
	virtual	LRESULT	OnPaint			(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnKillFocus		(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnKeyDown		(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT	OnTimer			(WPARAM wParam, LPARAM lParam);
private:
	HFONT				m_hMessageFont;		//��Ϣ�õ�������
	HBITMAP				m_bmpBackGround;	//��Ϣ��ı���ͼ��
	GGameUserWindow*	m_lpCtrlWindow;		//�����ƴ���
	HWND				m_hOwner;
	TString				m_strMessage;
	unsigned			m_uTimerID;
};


#endif