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
	GSelectList*		m_ListBox;				//һ��listbox������ʾ�̵�������۵���Ʒ
	HBITMAP				m_bmpBackGround;		//����
	HFONT				m_hTipsFont;			//��ʾ�û�������
	HFONT				m_hWarningFont;			//��ʾ�����������������
	vector<TString>		m_strFloorDescription;	//Ҫ���Ķ���������
	GGameUserWindow*	m_lpCtrlWindow;			
	unsigned			m_uListBoxID;			//�Ӵ��ڵ�id��		
	HWND				m_hOwner;
};



#endif	//end of __ZX_TRAVERFLOORWINDOW_H__