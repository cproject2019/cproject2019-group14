#ifndef		__ZX_GAMESTATUS_H__
#define		__ZX_GAMESTATUS_H__
#include "header.h"
#include "Map.h"

//这个文件用来存储主角的属性
extern	double				lfBloodVol;					//血量

extern	unsigned			uExperience;				//经验

extern	unsigned			uMoney;						//金钱

extern	unsigned			uLevel;						//等级

extern	unsigned			uAttackCapacity;			//攻击

extern	unsigned			uDefenceCapacity;			//防御

extern	unsigned			uRedKey;					//红钥匙

extern	unsigned			uYellowKey;					//黄钥匙

extern	unsigned			uBlueKey;					//蓝钥匙

extern	unsigned			uFloorCount;				//楼层数目

extern	unsigned			uCurrentFloor;				//当前楼层

extern	unsigned			uMaxFloorHasArrive;			//到达的最大楼层

extern	vector<GMap>		vAllMaps;					//存放所有的地图

extern	bool				bHasGetCross;				//是否得到十字架

extern	bool				bHasVisitSOG;				//是否已经见过小仙子

extern	bool				bSOGHasGivePower;			//是否已经把能量给了武士

extern	bool				bHasVisitBRH;				//是否见过雄哥哥

extern	bool				bHasVisitWH;				//是否见过无魂

extern	bool				bHasGetHammer;				//是否得到榔头

extern	bool				bCanCrossFloorDirectly;		//是否可以直接穿越楼层

extern	bool				bCanQueryGhostAttributes;	//是否可以查看怪物属性	

extern	bool				bCanSeeDevil;				//是否可以见魔王

extern	bool				bIronDoorCanCross;			//第二关的铁门是否打开

extern	bool				bHasSeeTrueDevil;			//是否见过真的魔王

extern	bool				bHasSeeFakeDevil;			//是否见过假的魔王

extern	bool				bHasSeeRedClothDevil;		//是否见过红衣魔王

extern GPOS					HeroPos;					//主角在的地方

extern unsigned				uDirection;					//主角的方向

//往上走
extern bool					bUpFloor; //

extern	bool				bWin;
#endif