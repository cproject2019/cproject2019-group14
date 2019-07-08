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
	GObjID				m_ShopID;				//ȷ������һ��shop
	GSelectList*		m_ListBox;				//һ��listbox������ʾ�̵�������۵���Ʒ
	HBITMAP				m_bmpBackGround;		//����
	HFONT				m_hTipsFont;			//��ʾ�û�������
	HFONT				m_hWarningFont;			//��ʾ�����������������
	vector<TString>		m_strSoldDescription;	//Ҫ���Ķ���������
	GGameUserWindow*	m_lpCtrlWindow;			
	unsigned			m_uListBoxID;			//�Ӵ��ڵ�id��		
};

#endif