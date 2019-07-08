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
	HFONT		m_hMessageFont;		//消息用到的字体
	HBITMAP		m_bmpBackGround;	//消息框的背景图标
	HWND		m_hOwner;
};