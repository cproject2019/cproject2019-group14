#include <typeinfo>
#include "MainFrame.h"
#include "GObjID.h"

unsigned	GetGhostAtForceByObjID(GObjID id);
int main(){
	FreeConsole();
	Window*	mainframe=	new	GMainFrame;
	RECT	MainFrameRt	=	{300, 200, MAINFRAME_WIDTH+ 300, MAINFRAME_HEIGHT+ 200};
	mainframe->Create(WS_EX_WINDOWEDGE, WS_VISIBLE|WS_TILED&(~WS_SYSMENU)&(~WS_SIZEBOX), _T("MainFramwClass"), NULL, MainFrameRt, NULL, NULL, NULL);
	mainframe->MessageLoop();
	delete	mainframe;
} 
