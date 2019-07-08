#include "ListBox.h"

GListBox::GListBox(){
	m_hParent			=	NULL;
	m_bmpBackGround		=	NULL;
	LoadBackGroundBitmap(_T("..\\DemoTower\\BkgrdBmp\\MainFrame.bmp"));
}

GListBox::~GListBox(){
	::DeleteObject(m_bmpBackGround);
}

bool	GListBox::Create( DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hWndParent, HMENU hMenu, LPVOID lpParam ){
	m_uCtrlID		=	(unsigned)hMenu;//id��
	m_hParent		=	hWndParent;	//parent window
	//ע�⣬listbox���ǵ���ϵͳ��ʵ��Ŷ(ϵͳΪ��������̫�������)����(��Ȼ���һ� ����subclass��)
	//��Ϊ�����������Ϣ������һ��Ҫ����������ΪLBS_NOTIFY,���ң�����Ҫ���ֵ�Ŷ���ʶ�lpszWindowName= null
	return	Window::Create(WS_EX_TOPMOST, WS_VISIBLE|WS_CHILD|dwStyle|LBS_NOTIFY , _T("listbox"), NULL, rtWndArea, m_hParent, hMenu, lpParam);
}

void	GListBox::LoadBackGroundBitmap(const	TString&	strFilePath){
	::DeleteObject(m_bmpBackGround);//clear the previous bmp
	m_bmpBackGround	=	static_cast<HBITMAP>(::LoadImage(NULL, strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
}
