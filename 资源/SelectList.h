#ifndef		__ZX_SELECTLIST_H__
#define		__ZX_SELECTLIST_H__

#include "ListBox.h"

class	GSelectList:	public	GListBox{
public:
	GSelectList();
	virtual	~GSelectList();
public:
	virtual	void	InitMessageHandler();
private://消息处理
	virtual	LRESULT	OnKeyDown			(WPARAM	wParam,	LPARAM	lParam);//用户选择了什么
	virtual	LRESULT	OnLButtonDBLCLK		(WPARAM	wParam,	LPARAM	lParam);//用记用鼠标选择了什么
	virtual	LRESULT	OnEraseGkGnd		(WPARAM	wParam,	LPARAM	lParam);
};

#endif		//end of __ZX_SELECTLIST_H__
