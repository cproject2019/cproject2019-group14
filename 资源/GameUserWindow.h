#ifndef		__ZX_GAMEUSERWINDOW_H__
#define		__ZX_GAMEUSERWINDOW_H__
#include "Window.h"
class	GMsgTipsWindow;
class	GTalkingWindow;
class	GFightWindow;
class	GShopWindow;
class	GTraverFloorWindow;
class	GGhostInfoQueryWindow;
//����������Ϸ������
class	GGameUserWindow:	public	Window{
public:
	GGameUserWindow();
	virtual	~GGameUserWindow();
public:
	virtual	bool	Create( DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hWndParent, HMENU hMenu, LPVOID lpParam );
	virtual	void	InitMessageHandler();
public:
	GMsgTipsWindow*		GetMsgTpis();
	GTalkingWindow*		GetTlkWindow();
	GFightWindow*		GetFitWindow();
private:
	virtual	LRESULT	OnKeyDown		(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnSetFocus		(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnMove			(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnPaint			(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnShow			(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnActive		(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnSize			(WPARAM	wParam, LPARAM	lParam);
	virtual	LRESULT	OnEraseBkGnd	(WPARAM	wParam, LPARAM	lParam);
private:
	bool	MoveLeft();
	bool	MoveRight();
	bool	MoveDown();
	bool	MoveUp();
	void	MoveTo(unsigned	uRowDst, unsigned	uColDst);
private:
	void	MeetWithPerson			(GObjID	id, unsigned	uRow, unsigned	uCol);
	void	MeetWithConstruction	(GObjID	id, unsigned	uRow, unsigned	uCol);
	void	MeetWithAddPowerTool	(GObjID	id, unsigned	uRow, unsigned	uCol);
	void	MeetWithNourDrink		(GObjID	id, unsigned	uRow, unsigned	uCol);
	void	MeetWithGhost			(GObjID	id, unsigned	uRow, unsigned	uCol);
	void	MeetWithHelpTool		(GObjID	id, unsigned	uRow, unsigned	uCol);
private:
	HBITMAP					m_bmpBackGround;	//����ˢ
	GTalkingWindow*			m_lpTalkingWnd;
	GFightWindow*			m_lpFightWnd;		//��ʾfight����
	GShopWindow*			m_lpShopWnd;		//�̵�Ĵ���
	GTraverFloorWindow*		m_lpTraverWnd;		//�л�¥��Ĵ���
	GMsgTipsWindow*			m_lpMsgTipsWnd;		//��ʾ��Ϣ��
	GGhostInfoQueryWindow*	m_lpQueryWnd;		//�������Բ鿴�б�
};

#endif		//end of __ZX_GAMEUSERWINDOW_H__