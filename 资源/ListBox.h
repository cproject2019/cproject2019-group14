#ifndef		__ZX_LISTBOX_H__
#define		__ZX_LISTBOX_H__

#include "Window.h"
class	GListBox:	public	Window{
public:
	GListBox();
	virtual	~GListBox();
public:
	virtual	bool	Create( DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hWndParent, HMENU hMenu, LPVOID lpParam );
public:
	void	LoadBackGroundBitmap(const	TString&	strFilePath);
public:
	HWND			m_hParent;			//�����
	unsigned		m_uCtrlID;			//ID��
	HBITMAP			m_bmpBackGround;	//����ͼ
};

#endif