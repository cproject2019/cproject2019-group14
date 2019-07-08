#include "Window.h"

Window::Window(){}

Window::~Window(){}

//�������е���Ϣ
LRESULT		Window::MessageHandler(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
	map<UINT, MsgHandler>::iterator it= m_mpMessageChain.find(uMsg);
	if(it!= m_mpMessageChain.end()){
		return (this->*(*it).second)(wParam, lParam);
	}
	return m_lpfnOldProc(hwnd, uMsg, wParam, lParam);
}

void		Window::SetHook(){
	::RtlCopyMemory(m_HookProc,g_proc_code,sizeof(g_proc_code));
	unsigned int i_this = (unsigned int)this;
	WndProc	proc	=	&Window::MessageHandler;  
	unsigned int i_proc = 0;
	__asm
	{
		mov eax,proc;
		mov i_proc,eax;
	}
	unsigned char *p = m_HookProc;
	*((unsigned int *)(p + 21)) = i_this;
	*((unsigned int *)(p + 26)) = i_proc;	
	m_lpfnOldProc=	(WNDPROC)SetWindowLong(m_hCurrent,GWL_WNDPROC,(LONG)m_HookProc);
}

WPARAM		Window::MessageLoop(){
	MSG message;
	while(::GetMessage(&message, NULL, 0, 0))
	{
		::TranslateMessage(&message);
		::DispatchMessage(&message);
	}
	return(message.wParam);
}

void		Window::InitMessageHandler(){
	m_mpMessageChain[WM_CLOSE]		=	static_cast<MsgHandler>(&Window::OnClose);
}

bool	Window::Create(
	DWORD		dwExStyle,			// extended window style
	DWORD		dwStyle,			// window style
	LPTSTR		lpszClassName,		// pointer to registered class name
	LPTSTR		lpszWindowName,	// pointer to window name
	RECT	    rtWndArea,			// window area
	HWND		hWndParent,		// handle to parent or owner window
	HMENU		hMenu,				// handle to menu, or child-window identifier
	LPVOID		lpParam				// pointer to window-creation data
	){
	m_hCurrent	=	::CreateWindowEx(dwExStyle, lpszClassName, lpszWindowName,
		dwStyle, rtWndArea.left, rtWndArea.top, rtWndArea.right-	rtWndArea.left, 
		rtWndArea.bottom-	rtWndArea.top, hWndParent, hMenu, (HINSTANCE)GetModuleHandle(NULL),lpParam);
	if(m_hCurrent==	NULL)
		return	false;
	InitMessageHandler();	//��ʼ����Ϣ��������
	SetHook();				//��ת����ĳ�Ա��������
	return	true;
}

LRESULT		Window::OnClose(WPARAM	wParam, LPARAM	lParam){
	::PostQuitMessage(0);
	return	0;
}

HWND	Window::GetHwnd(){		//�õ���ǰ�Ĵ��ھ��
	return	m_hCurrent;
}
