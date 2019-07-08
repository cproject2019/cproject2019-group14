#include "MessgeTips.h"

GMessageTips::GMessageTips(HWND	hOwner){
	m_bmpBackGround	=	NULL;
	m_hMessageFont	=	NULL;
	LOGFONT	font;
	::RtlZeroMemory(&font, sizeof(font));
	font.lfCharSet	=	GB2312_CHARSET;
	StrCpy(font.lfFaceName, _T("����\0"));
	font.lfHeight	=	20;
	font.lfWidth	=	10;
	font.lfWeight	=	1;
	m_hMessageFont	=	::CreateFontIndirect(&font);
	LoadBackGroundBitmap(_T("..\\DemoTower\\BkgrdBmp\\MainFrame.bmp"));//���ر���ͼƬ
	m_hOwner	=	hOwner;
}

GMessageTips::~GMessageTips(){
	::DeleteObject(m_hMessageFont);
	::DeleteObject(m_bmpBackGround);
}

void	GMessageTips::ShowMessage(const	TString&	strMessage,	unsigned	uMilSecondsToWait){
	RECT	DrawRt=	{92, 120, 392, 172};//�ı����ڵľ��ο�(ˮƽ���У���ֱ����ƫ��)
	HDC	hDrawDC				=		::GetDC(m_hOwner);
	HDC	hMemDstDC			=		::CreateCompatibleDC(hDrawDC);
	HDC	hMemSrcDC			=		::CreateCompatibleDC(hDrawDC);
	HBITMAP	hDrawBmp		=		::CreateCompatibleBitmap(hDrawDC,300,50);//�ڴ�λͼ������draw������
	::SelectObject(hMemDstDC, hDrawBmp);
	::SelectObject(hMemSrcDC, m_bmpBackGround);//ѡ������Ҫ���л���

	//��λͼ����hMemDstDC����
	BITMAP	bmp;
	::GetObject(m_bmpBackGround,sizeof(bmp),  &bmp);
	for(unsigned	i= 0; i< 300; i+= bmp.bmWidth){
		for(unsigned	j= 0; j< 50; j+= bmp.bmHeight){
			::BitBlt(hMemDstDC, i, j, bmp.bmWidth, bmp.bmHeight, hMemSrcDC, 0, 0, SRCCOPY);
		}
	}
	//��ʾ���Ľ��
	BLENDFUNCTION	BlendFunc;
	BlendFunc.BlendFlags			=	0;
	BlendFunc.BlendOp				=	AC_SRC_OVER;
	BlendFunc.SourceConstantAlpha	=	150;
	BlendFunc.AlphaFormat			=	0;
	::AlphaBlend(hDrawDC, DrawRt.left, DrawRt.top, 300, 50, hMemDstDC, 0, 0, 300, 50, BlendFunc);

	//��ʾ����
	::SetTextColor(hDrawDC, RGB(255, 255, 0));
	::SetBkMode(hDrawDC, TRANSPARENT);
	HFONT	hPreFont	=	(HFONT)::SelectObject(hDrawDC, m_hMessageFont);
	::DrawText(hDrawDC, strMessage.c_str(), -1,&DrawRt,  DT_CENTER|DT_SINGLELINE|DT_VCENTER);

	//���߿�
	HPEN	hPrePen	=	(HPEN)::SelectObject(hDrawDC, ::CreatePen(PS_SOLID, 3, RGB(255, 255, 0)));
	::MoveToEx(hDrawDC, DrawRt.left, DrawRt.top, NULL);
	::LineTo(hDrawDC, DrawRt.right-2, DrawRt.top);
	::LineTo(hDrawDC, DrawRt.right-2, DrawRt.bottom-2);
	::LineTo(hDrawDC, DrawRt.left, DrawRt.bottom-2);
	::LineTo(hDrawDC, DrawRt.left, DrawRt.top);

	//�ͷž��
	::SelectObject(hDrawDC, hPreFont);
	::DeleteObject(::SelectObject(hDrawDC, hPrePen));
	::DeleteObject(hDrawBmp);
	::DeleteDC(hMemDstDC);
	::DeleteDC(hMemSrcDC);
	::ReleaseDC(m_hOwner, hDrawDC);
	::Sleep(uMilSecondsToWait);

	//�粻���µĻ�����ʾЧ���᲻����
	::InvalidateRect(m_hOwner, NULL, false);
	::UpdateWindow(m_hOwner);
}

void			GMessageTips::LoadBackGroundBitmap(const	TString&	strFilePath){
	::DeleteObject(m_bmpBackGround);
	m_bmpBackGround	=	static_cast<HBITMAP>(::LoadImage(NULL, strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
}
