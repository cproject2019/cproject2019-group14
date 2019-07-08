#include "header.h"
#include "GObjID.h"

map<GObjID, TString>		ObjNameTable;	//姓名表
map<GObjID, GHOSTINFO>		GhostInfo;		//怪物的属性表
map<GObjID, GPOS>			ObjPosTable;	//在位图中的位置表

void	InitNameTalbe(){//初始化各ID对应的名字列表
	//=====================================================================
	//addpowid.h
	// ====================================================================
	ObjNameTable.clear();
	ObjNameTable[GID_OBJ_PWREDDIAMOND]			=	_T("红宝石");
	ObjNameTable[GID_OBJ_PWBLUEDIAMOND]		=	_T("蓝宝石");
	ObjNameTable[GID_OBJ_PWRHANMAOYU]			=	_T("寒毛羽");
	ObjNameTable[GID_OBJ_PWRHANYAYU]			=	_T("寒鸭羽");
	ObjNameTable[GID_OBJ_PWRIRONSWORD]			=	_T("铁剑");
	ObjNameTable[GID_OBJ_PWRCOPPERSWORD]		=	_T("铜剑");
	ObjNameTable[GID_OBJ_PWRBLUESWORD]			=	_T("碧林剑");
	ObjNameTable[GID_OBJ_PWRIRONSHIELD]		=	_T("铁盾");
	ObjNameTable[GID_OBJ_PWRGOLDSHELD]			=	_T("金盾");
	ObjNameTable[GID_OBJ_PWRPOINEERSHELD]		=	_T("先锋盾");
	ObjNameTable[GID_OBJ_PWRCORSS]				=	_T("十字架");

	//=====================================================================
	//ghostid.h
	// ====================================================================
	ObjNameTable[GID_OBJ_GHSLM]				=	_T("史莱姆");
	ObjNameTable[GID_OBJ_GHZSLM]				=	_T("中史莱姆");
	ObjNameTable[GID_OBJ_GHDSLM]				=	_T("大史莱姆");
	ObjNameTable[GID_OBJ_GHSLMW]				=	_T("史莱姆王");
	ObjNameTable[GID_OBJ_GHXBF]				=	_T("小蝙蝠");
	ObjNameTable[GID_OBJ_GHDBF]				=	_T("大蝙蝠");
	ObjNameTable[GID_OBJ_GHXXBF]				=	_T("吸血蝙蝠");
	ObjNameTable[GID_OBJ_GHKLB]				=	_T("骷髅兵");
	ObjNameTable[GID_OBJ_GHKLDZ]				=	_T("骷髅队长");
	ObjNameTable[GID_OBJ_GHKLW]				=	_T("骷髅王");
	ObjNameTable[GID_OBJ_GHKLWH]				=	_T("骷髅王后");
	ObjNameTable[GID_OBJ_GHBSR]				=	_T("半兽人");
	ObjNameTable[GID_OBJ_GHSRW]				=	_T("兽人王");
	ObjNameTable[GID_OBJ_GHLPFS]				=	_T("蓝袍法师");
	ObjNameTable[GID_OBJ_GHHPFS]				=	_T("红袍法师");
	ObjNameTable[GID_OBJ_GHQS]					=	_T("骑士");
	ObjNameTable[GID_OBJ_GHQSDZ]				=	_T("骑士队长");
	ObjNameTable[GID_OBJ_GHXHF]				=	_T("小护法");
	ObjNameTable[GID_OBJ_GHDHF]				=	_T("大护法");
	ObjNameTable[GID_OBJ_GHNTHF]				=	_T("牛头护法");
	ObjNameTable[GID_OBJ_GHSG]					=	_T("石怪");
	ObjNameTable[GID_OBJ_GHXM]					=	_T("邪魔");
	ObjNameTable[GID_OBJ_GHKJM]				=	_T("铠甲魔");
	ObjNameTable[GID_OBJ_GHXMFS]				=	_T("小魔法师");
	ObjNameTable[GID_OBJ_GHDMFS]				=	_T("大魔法师");
	ObjNameTable[GID_OBJ_GHSDGS]				=	_T("双刀鬼士");
	ObjNameTable[GID_OBJ_GHYLQS]				=	_T("幽灵骑士");
	ObjNameTable[GID_OBJ_GHYLFS]				=	_T("幽灵法师");
	ObjNameTable[GID_OBJ_GHHYMW]				=	_T("红衣魔王");
	ObjNameTable[GID_OBJ_GHPILGRIM]			=	_T("Pilgrim");
	ObjNameTable[GID_OBJ_GHFYLMW]				=	_T("幽灵魔王");//假的
	ObjNameTable[GID_OBJ_GHTYLMW]				=	_T("幽灵魔王");//真的

	//=====================================================================
	//nourid.h
	// ====================================================================
	ObjNameTable[GID_OBJ_NUREDBOTTLE]			=	_T("红瓶的钙");
	ObjNameTable[GID_OBJ_NUBLUEBOTTLE]			=	_T("蓝瓶的钙");
	ObjNameTable[GID_OBJ_NUMILK]				=	_T("千年玉露");

	//=====================================================================
	//otherid.h
	// ====================================================================
	ObjNameTable[GID_OBJ_WALL]					=	_T("墙");
	ObjNameTable[GID_OBJ_SKY]					=	_T("天空");
	ObjNameTable[GID_OBJ_PATH]					=	_T("路");
	ObjNameTable[GID_OBJ_YELKEY]				=	_T("黄钥匙");
	ObjNameTable[GID_OBJ_BLUEKEY]				=	_T("蓝钥匙");
	ObjNameTable[GID_OBJ_REDKEY]				=	_T("红钥匙");
	ObjNameTable[GID_OBJ_YELDOOR]				=	_T("黄门");
	ObjNameTable[GID_OBJ_BLUEDOOR]				=	_T("蓝门");
	ObjNameTable[GID_OBJ_REDDOOR]				=	_T("红门");
	ObjNameTable[GID_OBJ_IRONDOOR]				=	_T("铁门");
	ObjNameTable[GID_OBJ_FENCEDOOR]			=	_T("栅栏门");
	ObjNameTable[GID_OBJ_UPDOOR]				=	_T("向上的楼梯");
	ObjNameTable[GID_OBJ_DOWNDOOR]				=	_T("向下的楼梯");
	ObjNameTable[GID_OBJ_GOLDMONEY]			=	_T("金钱");

	//=====================================================================
	//personid.h
	// ====================================================================
	ObjNameTable[GID_OBJ_PERGZ]				=	_T("公主");
	ObjNameTable[GID_OBJ_PERSOG]				=	_T("小仙子");
	ObjNameTable[GID_OBJ_PERBROHERO]			=	_T("雄哥哥");
	ObjNameTable[GID_OBJ_PERWUHUN]				=	_T("无魂");
	ObjNameTable[GID_OBJ_PERWLSRNLPER]			=	_T("商人");
	ObjNameTable[GID_OBJ_PERWLNLMON]			=	_T("商人");
	ObjNameTable[GID_OBJ_PERWLNMMON]			=	_T("商人");
	ObjNameTable[GID_OBJ_PERKEYSELLER]			=	_T("商人");
	ObjNameTable[GID_OBJ_PERWLSRNMPER]			=	_T("商人");
	ObjNameTable[GID_OBJ_PERKEYBUYYER]			=	_T("商人");
	ObjNameTable[GID_OBJ_PERVICGRANPARENT]		=	_T("老爷爷");
	ObjNameTable[GID_OBJ_PERVICSELLER]			=	_T("商人");
	//=====================================================================
	//toolid.h
	// ====================================================================
	ObjNameTable[GID_OBJ_TLTRANSPORT]			=	_T("风信子");
	ObjNameTable[GID_OBJ_TLQUERYATTR]			=	_T("悟空的火眼");
	ObjNameTable[GID_OBJ_TLHAMMER]				=	_T("水晶榔头");
}

void	InitGhostInfoTable(){
	GhostInfo[GID_OBJ_GHSLM]		=	GHOSTINFO(50,	20,	1,	1,	1);
	GhostInfo[GID_OBJ_GHZSLM]		=	GHOSTINFO(70,	15,	2,	2,	1);
	GhostInfo[GID_OBJ_GHDSLM]		=	GHOSTINFO(200,	35, 10, 5,	3);
	GhostInfo[GID_OBJ_GHSLMW]		=	GHOSTINFO(700,250,125,32, 30);
	GhostInfo[GID_OBJ_GHXBF]		=	GHOSTINFO(100,	20,	5,	3,	2);
	GhostInfo[GID_OBJ_GHDBF]		=	GHOSTINFO(150,	65, 30, 10, 8);
	GhostInfo[GID_OBJ_GHXXBF]		=	GHOSTINFO(550, 160, 90, 25, 20);
	GhostInfo[GID_OBJ_GHKLB]		=	GHOSTINFO(110,	25,	5,	5,	8);
	GhostInfo[GID_OBJ_GHKLDZ]		=	GHOSTINFO(140,	40,	20,	8,	5);
	GhostInfo[GID_OBJ_GHKLW]		=	GHOSTINFO(400, 90, 50, 15, 12);
	GhostInfo[GID_OBJ_GHKLWH]		=	GHOSTINFO(3333, 1200, 1133, 126, 112);
	GhostInfo[GID_OBJ_GHBSR]		=	GHOSTINFO(300,	75,	45,	13,	10);
	GhostInfo[GID_OBJ_GHSRW]		=	GHOSTINFO(900, 450, 330, 50, 50);
	GhostInfo[GID_OBJ_GHLPFS]		=	GHOSTINFO(125,	50,	25,	10,	7);
	GhostInfo[GID_OBJ_GHHPFS]		=	GHOSTINFO(100, 200, 110, 30, 25);
	GhostInfo[GID_OBJ_GHQS]			=	GHOSTINFO(850,	350,200,45,	40);
	GhostInfo[GID_OBJ_GHQSDZ]		=	GHOSTINFO(900,	750,650,77,	70);
	GhostInfo[GID_OBJ_GHXHF]		=	GHOSTINFO(1250, 500, 400, 55, 55);
	GhostInfo[GID_OBJ_GHDHF]		=	GHOSTINFO(450, 150, 90, 22, 19);
	GhostInfo[GID_OBJ_GHNTHF]		=	GHOSTINFO(1500,560,460,60,60);
	GhostInfo[GID_OBJ_GHSG]			=	GHOSTINFO(500, 115, 65, 15, 15);
	GhostInfo[GID_OBJ_GHXM]			=	GHOSTINFO(1300, 300, 150, 40, 34);
	GhostInfo[GID_OBJ_GHXMFS]		=	GHOSTINFO(250, 120, 70, 20, 17);
	GhostInfo[GID_OBJ_GHDMFS]		=	GHOSTINFO(500, 400, 260, 47, 45);
	GhostInfo[GID_OBJ_GHSDGS]		=	GHOSTINFO(120, 620, 520, 65, 75);
	GhostInfo[GID_OBJ_GHKJM]		=	GHOSTINFO(2000, 680, 590, 70, 65);
	GhostInfo[GID_OBJ_GHYLQS]		=	GHOSTINFO(1600, 1306, 1200, 132, 112);
	GhostInfo[GID_OBJ_GHYLFS]		=	GHOSTINFO(2000, 1106, 973, 120, 105);
	GhostInfo[GID_OBJ_GHPILGRIM]	=	GHOSTINFO(3100, 1150, 1050, 92, 80);
	GhostInfo[GID_OBJ_GHHYMW]		=	GHOSTINFO(15000, 1500, 1400, 100, 100);
	GhostInfo[GID_OBJ_GHFYLMW]		=	GHOSTINFO(33333, 2000, 1600, 375, 300);
	GhostInfo[GID_OBJ_GHTYLMW]		=	GHOSTINFO(33333, 2000, 1600, 375, 300);
}


void	InitPosTable(){
	//ghostid.h
	ObjPosTable[GID_OBJ_GHSLM]				=	GPOS(0, 0);
	ObjPosTable[GID_OBJ_GHZSLM]			=	GPOS(0, 1);
	ObjPosTable[GID_OBJ_GHDSLM]			=	GPOS(0, 2);
	ObjPosTable[GID_OBJ_GHSLMW]			=	GPOS(0, 3);
	ObjPosTable[GID_OBJ_GHXBF]				=	GPOS(0, 4);
	ObjPosTable[GID_OBJ_GHDBF]				=	GPOS(0, 5);
	ObjPosTable[GID_OBJ_GHXXBF]			=	GPOS(0, 6);
	ObjPosTable[GID_OBJ_GHFYLMW]			=	GPOS(0, 7);
	ObjPosTable[GID_OBJ_GHTYLMW]			=	GPOS(0, 7);
	ObjPosTable[GID_OBJ_GHKLB]				=	GPOS(0, 8);
	ObjPosTable[GID_OBJ_GHXMFS]			=	GPOS(0, 9);
	ObjPosTable[GID_OBJ_GHDMFS]			=	GPOS(0, 10);
	ObjPosTable[GID_OBJ_GHDHF]				=	GPOS(0, 11);
	ObjPosTable[GID_OBJ_GHKLDZ]			=	GPOS(1, 0);
	ObjPosTable[GID_OBJ_GHKLW]				=	GPOS(1, 1);
	ObjPosTable[GID_OBJ_GHKLWH]			=	GPOS(1, 2);
	ObjPosTable[GID_OBJ_GHBSR]				=	GPOS(1, 3);
	ObjPosTable[GID_OBJ_GHSRW]				=	GPOS(1, 4);
	ObjPosTable[GID_OBJ_GHSG]				=	GPOS(1, 5);
	ObjPosTable[GID_OBJ_GHPILGRIM]			=	GPOS(1, 6);
	ObjPosTable[GID_OBJ_GHLPFS]			=	GPOS(1, 7);
	ObjPosTable[GID_OBJ_GHHPFS]			=	GPOS(1, 8);
	ObjPosTable[GID_OBJ_GHXHF]				=	GPOS(1, 9);
	ObjPosTable[GID_OBJ_GHNTHF]			=	GPOS(1, 10);
	ObjPosTable[GID_OBJ_GHSDGS]			=	GPOS(1, 11);
	ObjPosTable[GID_OBJ_GHKJM]				=	GPOS(2, 0);
	ObjPosTable[GID_OBJ_GHQS]				=	GPOS(2, 1);
	ObjPosTable[GID_OBJ_GHQSDZ]			=	GPOS(2, 2);
	ObjPosTable[GID_OBJ_GHYLQS]			=	GPOS(2, 3);
	ObjPosTable[GID_OBJ_GHHYMW]			=	GPOS(2, 4);
	ObjPosTable[GID_OBJ_GHXM]				=	GPOS(2, 5);
	ObjPosTable[GID_OBJ_GHYLFS]			=	GPOS(2, 6);
	ObjPosTable[GID_OBJ_PWREDDIAMOND]		=	GPOS(4, 0);
	ObjPosTable[GID_OBJ_PWBLUEDIAMOND]		=	GPOS(4, 1);
	ObjPosTable[GID_OBJ_YELDOOR]			=	GPOS(4, 4);
	ObjPosTable[GID_OBJ_BLUEDOOR]			=	GPOS(4, 5);
	ObjPosTable[GID_OBJ_REDDOOR]			=	GPOS(4, 6);
	ObjPosTable[GID_OBJ_IRONDOOR]			=	GPOS(4, 7);
	ObjPosTable[GID_OBJ_NUREDBOTTLE]		=	GPOS(5, 0);
	ObjPosTable[GID_OBJ_NUBLUEBOTTLE]		=	GPOS(5, 1);
	ObjPosTable[GID_OBJ_REDKEY]			=	GPOS(11, 9);
	ObjPosTable[GID_OBJ_BLUEKEY]			=	GPOS(11, 10);
	ObjPosTable[GID_OBJ_YELKEY]			=	GPOS(11, 11);	
	ObjPosTable[GID_OBJ_UPDOOR]			=	GPOS(7, 0);
	ObjPosTable[GID_OBJ_DOWNDOOR]			=	GPOS(7, 1);
	ObjPosTable[GID_OBJ_WALL]				=	GPOS(12, 6);
	ObjPosTable[GID_OBJ_SKY]				=	GPOS(13, 5);
	ObjPosTable[GID_OBJ_PATH]				=	GPOS(13, 3);
	ObjPosTable[GID_OBJ_PWRHANMAOYU]		=	GPOS(5, 9);
	ObjPosTable[GID_OBJ_PWRHANYAYU]		=	GPOS(5, 10);
	ObjPosTable[GID_OBJ_PWRIRONSWORD]		=	GPOS(8, 0);
	ObjPosTable[GID_OBJ_PWRCOPPERSWORD]	=	GPOS(8, 2);
	ObjPosTable[GID_OBJ_PWRBLUESWORD]		=	GPOS(8, 3);
	ObjPosTable[GID_OBJ_PWRIRONSHIELD]		=	GPOS(10, 0);
	ObjPosTable[GID_OBJ_PWRGOLDSHELD]		=	GPOS(10, 1);
	ObjPosTable[GID_OBJ_PWRPOINEERSHELD]	=	GPOS(10, 2);
	ObjPosTable[GID_OBJ_PWRCORSS]			=	GPOS(5, 11);
	ObjPosTable[GID_OBJ_FENCEDOOR]			=	GPOS(9, 1);
	ObjPosTable[GID_OBJ_GOLDMONEY]			=	GPOS(9, 2);
	ObjPosTable[GID_OBJ_PERGZ]				=	GPOS(11, 4);
	ObjPosTable[GID_OBJ_PERSOG]			=	GPOS(3, 9);
	ObjPosTable[GID_OBJ_PERBROHERO]		=	GPOS(2, 7);
	ObjPosTable[GID_OBJ_PERWUHUN]			=	GPOS(3, 8);
	ObjPosTable[GID_OBJ_PERWLSRNLPER]		=	GPOS(3, 6);
	ObjPosTable[GID_OBJ_PERWLNLMON]		=	GPOS(11, 1);
	ObjPosTable[GID_OBJ_PERWLNMMON]		=	GPOS(11, 1);
	ObjPosTable[GID_OBJ_PERKEYSELLER]		=	GPOS(3, 6);
	ObjPosTable[GID_OBJ_PERKEYBUYYER]		=	GPOS(3, 7);
	ObjPosTable[GID_OBJ_PERVICGRANPARENT]	=	GPOS(3, 6);
	ObjPosTable[GID_OBJ_PERVICSELLER]		=	GPOS(3, 7);
	ObjPosTable[GID_OBJ_TLTRANSPORT]		=	GPOS(4, 10);
	ObjPosTable[GID_OBJ_TLQUERYATTR]		=	GPOS(6, 10);
	ObjPosTable[GID_OBJ_TLHAMMER]			=	GPOS(4, 9);
	ObjPosTable[GID_OBJ_NUMILK]			=	GPOS(7, 3);
	ObjPosTable[GID_OBJ_PERWLSRNMPER]		=	GPOS(3, 6);
}

//从一个文件里面加载字符串
void	LoadStringFromFile(const	TString&	strFilePath, vector<TString>&	strToLoad, bool		bIgnoreFirtLine){
#ifdef	UNICODE
	wfstream	in(strFilePath);
#else
	fstream		in(strFilePath);
#endif
	strToLoad.clear();
	TString	strTmp;
	if(bIgnoreFirtLine){//是否忽略第一行
		getline(in, strTmp);
	}
	while(getline(in, strTmp)&&in){
		strToLoad.push_back(strTmp);
	}
	in.close();
}