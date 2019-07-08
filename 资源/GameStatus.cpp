#include "GameStatus.h"

//血量
double				lfBloodVol=	1000;					

//经验
unsigned			uExperience=	0;					
	
//金钱
unsigned			uMoney=	0;						

//等级
unsigned			uLevel=	1;						

//攻击
unsigned			uAttackCapacity	=	20;			

//防御
unsigned			uDefenceCapacity=	10;	

//红钥匙
unsigned			uRedKey=	0;			

//黄钥匙
unsigned			uYellowKey=	0;				

//蓝钥匙
unsigned			uBlueKey=	0;				

//楼层数目
unsigned			uFloorCount=	0;			

//当前楼层
unsigned			uCurrentFloor=	1;

//到达的最大楼层
unsigned			uMaxFloorHasArrive=	1;		

//存放所有的地图
vector<GMap>		vAllMaps;					

//是否得到十字架
bool				bHasGetCross		=	false;			

//是否已经见过小仙子
bool				bHasVisitSOG		=	false;		

//是否已经把能量给了武士
bool				bSOGHasGivePower	=	false;

//是否见过雄哥哥
bool				bHasVisitBRH=	false;			

//是否见过无魂
bool				bHasVisitWH=	false;			

//是否得到榔头
bool				bHasGetHammer=	false;			

//是否可以直接穿越楼层
bool				bCanCrossFloorDirectly=	false;

//是否可以查看怪物属性
bool				bCanQueryGhostAttributes=	false;		

//是否可以见魔王
bool				bCanSeeDevil			=	false;	

//是否见过真的魔王
bool				bHasSeeTrueDevil		=	false;

//是否见过红衣魔王
bool				bHasSeeRedClothDevil	=	false;

//是否见过假的魔王
bool				bHasSeeFakeDevil		=	false;

//第二关的铁门是否可以通过
bool				bIronDoorCanCross		=	false;

GPOS				HeroPos(9, 5);//主角的地点

bool				bWin=	false;
//0向上 1向左 2向下 3向右
unsigned			uDirection;				

//往上走
bool				bUpFloor=	true; //

void		InitNameTalbe();
void		InitGhostInfoTable();
void		InitPosTable();
void		InitMapFileName();
void		LoadAllGameMap(const	TString& strMapDirectory, vector<GMap>&	AllMap,	
	unsigned&	uTotalMaps);

void	InitGameUseData(){
	InitMapFileName();
	InitNameTalbe();
	InitGhostInfoTable();
	InitPosTable();
	LoadAllGameMap(_T("..\\DemoTower\\BkgrdBmp\\maps"),vAllMaps, uFloorCount);
}

