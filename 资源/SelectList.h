#ifndef		__ZX_SELECTLIST_H__
#define		__ZX_SELECTLIST_H__

#include "ListBox.h"

class	GSelectList:	public	GListBox{
public:
	GSelectList();
	virtual	~GSelectList();
public:
	virtual	void	InitMessageHandler();
private://��Ϣ����
	virtual	LRESULT	OnKeyDown			(WPARAM	wParam,	LPARAM	lParam);//�û�ѡ����ʲô
	virtual	LRESULT	OnLButtonDBLCLK		(WPARAM	wParam,	LPARAM	lParam);//�ü������ѡ����ʲô
	virtual	LRESULT	OnEraseGkGnd		(WPARAM	wParam,	LPARAM	lParam);
};

#endif		//end of __ZX_SELECTLIST_H__
