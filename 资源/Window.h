#ifndef		__ZX_WINDOW_H__
#define		__ZX_WINDOW_H__
#include "header.h"

static	const unsigned char g_proc_code[] =
{
	//------------parameter-----------------
	0x8B,0x44,0x24,0x10,		// mov         eax,dword ptr [esp+10h] 
	0x50,						// push        eax  
	0x8B,0x44,0x24,0x10,		// mov         eax,dword ptr [esp+10h] 
	0x50,						// push        eax  
	0x8B,0x44,0x24,0x10,	    // mov         eax,dword ptr [esp+10h] 
	0x50,						// push        eax  
	0x8B,0x44,0x24,0x10,		// mov         eax,dword ptr [esp+10h] 
	0x50,						// push        eax  

	//-----------this poiner-------------
	0xB9,0x5C,0xFF,0x12,0x00,   // mov ecx,0x12FF5C 

	//-----------call back function-------------
	0xB8,0x00,0x00,0x00,0x00,   // mov         eax,0 
	0xFF,0xD0,					// call        eax

	//return
	0xC2,0x10,0x00				// ret         10h  
};

class	Window{
public:
	typedef		LRESULT	(Window::*WndProc)(HWND	hwnd, UINT	uMsg, WPARAM	wParam, LPARAM lParam);
	typedef		LRESULT (Window::*MsgHandler)(WPARAM	wParam, LPARAM	lParam);
	typedef		map<UINT,	MsgHandler>		MsgChain;

public:
	Window();
	virtual	~Window();
public:
	virtual		WPARAM	MessageLoop();
private:
	//�������е���Ϣ
	virtual		LRESULT		MessageHandler(
		__inout HWND hwnd,
		__in	UINT uMsg,
		__in	WPARAM wParam,
		__in	LPARAM lParam);

	//��һ����Ϣ����,�����������ĳ�Ա������Ϊ��Ϣ������
	virtual		void	SetHook();
public:
	virtual		void	InitMessageHandler();	

public:
	virtual		bool	Create(
		DWORD		dwExStyle,			// extended window style
		DWORD		dwStyle,			// window style
		LPTSTR		lpszClassName,		// pointer to registered class name
		LPTSTR		lpszWindowName,		// pointer to window name
		RECT	    rtWndArea,			// window area
		HWND		hWndParent,		// handle to parent or owner window
		HMENU		hMenu,				// handle to menu, or child-window identifier
		LPVOID		lpParam				// pointer to window-creation data
		);
		HWND	GetHwnd();		//�õ���ǰ�Ĵ��ھ��
public:
	virtual	LRESULT		OnClose(WPARAM	wParam, LPARAM	lParam);

public:
	MsgChain			m_mpMessageChain;		//��Ϣ����

public:
	WNDPROC				m_lpfnOldProc;	//�ɵĹ���(�ص���ʱ����ܻ�ʹ�õ�)
private:
	HWND				m_hCurrent;		//��ǰ���ڵľ��
	unsigned	char	m_HookProc[sizeof(g_proc_code)];//���ӹ���
};

#endif		//end of __ZX_WINDOW_H__