#include "header.h"

class	GMessageTips{
public:
	GMessageTips(HWND	hOwner);
	virtual	~GMessageTips();
public:
	virtual	void	ShowMessage(const	TString&	strMessage,	
			unsigned	uMilSecondsToWait);
public:
	void			LoadBackGroundBitmap(const	TString&	strFilePath);
private:;		
	HFONT		m_hMessageFont;		//��Ϣ�õ�������
	HBITMAP		m_bmpBackGround;	//��Ϣ��ı���ͼ��
	HWND		m_hOwner;
};