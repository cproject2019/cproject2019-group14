#ifndef		__ZX_GMAINFRAME_H__
#define		__ZX_GMAINFRAME_H__
#include "Window.h"

//����ļ������������Ϸ��ȫ����������
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
	Window*		m_lpGameCtrlArea;	//��Ϸ��(�û�ʵ���ϲ���������)
	Window*		m_lpGameInfoArea;	//��ʾ��Ϸ�����״̬��Ϣ(��������ֵ�ȵ�)
	bool		m_bSmallButtonDown;	//����ڰ�����С��ť
	bool		m_bSmallButtonHover;//�������С��ť�����ƶ�(����,û�а���)
	bool		m_bExitButtonDown;	//��갴���˳���ť
	bool		m_bExitButtonHover;	//������˳���ť���ƶ�(����,û�а���)
	RECT		m_rtGameArea;
	RECT		m_rtGameInfo;
};


#endif