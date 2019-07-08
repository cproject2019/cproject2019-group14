#ifndef		__ZX_GHOSTINFOQUERYWINDOW_H__
#define		__ZX_GHOSTINFOQUERYWINDOW_H__
#include "Window.h"

class	GGameUserWindow;
class	GSelectList;

//470* 320�Ĵ�С,���е��б����450* 280
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
	void	Query(unsigned	uFloorNo);//��ѯ��uFloor��Ĺ��������
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
	GSelectList*		m_ListBox;				//һ��listbox������ʾ�̵�������۵���Ʒ
	HBITMAP				m_bmpBackGround;		//����
	HFONT				m_hTipsFont;			//��ʾ�û�������
	HFONT				m_hWarningFont;			//��ʾ�����������������
	GGameUserWindow*	m_lpCtrlWindow;			
	unsigned			m_uListBoxID;			//�Ӵ��ڵ�id��		
};

#endif		//enf of __ZX_GHOSTINFOQUERYWINDOW_H__