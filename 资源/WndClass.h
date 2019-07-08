#ifndef		__ZX_WNDCLASS_H__
#define		__ZX_WNDCLASS_H__
#include "header.h"
class	WndClass{
public:
	WndClass(LPTSTR	lpszClassName=	_T("MyApplication"));
	~WndClass();
public:
	WNDCLASSEX&	GetWndClass();
	ATOM		Register();
public:
	WNDCLASSEX	m_wndclass;
};


#endif