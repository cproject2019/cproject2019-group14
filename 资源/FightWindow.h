//���ͷ�ļ���������ս���Ĵ���
#ifndef		__ZX_FIGHTWINDOW_H__
#define		__ZX_FIGHTWINDOW_H__
#include "Window.h"

class	GGameUserWindow;

//��С��430* 120
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
	HFONT		m_hObjNameFont;		//��ʾ���������õ�����
	HFONT		m_hObjAttrFont;		//��ʾ���������õ�����
	HFONT		m_hVSFont;			//��ʾVS�õ�font
	HBITMAP		m_bmpBackGround;
	GObjID		m_idFightWith;
	bool		m_bFinishedFight;
	GGameUserWindow	*	m_lpCtrlWindow;
	unsigned	m_uTimerID;
	double		m_lfGhostBloodVol;		//ghostʣ�µ�Ѫ��	
	double		m_lfPerRoundHeroLost;	//һ���غ�heroʧȥ��Ѫ��
	double		m_lpPerRoundGhostLost;	//һ���غ�ghostʧȥ��Ѫ��
	HBITMAP		m_bmpGObject;
	unsigned	m_uRow;
	unsigned	m_uCol;
};
#endif	//end of __ZX_FIGHTWINDOW_H__