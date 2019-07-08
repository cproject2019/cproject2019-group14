#ifndef		__ZX_ATTRBYOBJID_H__
#define		__ZX_ATTRBYOBJID_H__
#include "header.h"

//调用GetNameByOdjID之前请确保调用了InitNameTalbe
TString		GetNameByObjID			(GObjID	id);		//取得名字

//大多数的物体的大小是1*1，所以这个函数的实现比较简单
GSIZE		GetSizeByObjID			(GObjID	id);		//取得占位大小

//调用以下函数之前请确保调用了InitPosTable
GPOS		GetPosByObjID			(GObjID	id);		//在位图中的位置

//调用以下函数之前请确保调用了InitGhostInfoTable
unsigned	GetGhostAtForceByObjID	(GObjID	id);//取得攻击力
unsigned	GetGhostDfForceByObjID	(GObjID	id);//取得防御力
unsigned	GetGhostExprByObjID		(GObjID	id);//杀死怪物得到的经验
unsigned	GetGhostMoneyByObjID	(GObjID	id);//杀光死怪物得到的钱
unsigned	GetGhostLifeByOdjID		(GObjID	id);//得到怪物的生命值


bool		NeedTransparentBlt(GObjID	id);//是否背景需要透明显示

bool	IsGhost(GObjID id);
bool	IsPowerTool(GObjID id);
bool	IsConstruction(GObjID	id);
bool	IsNutrition(GObjID	id);
bool	IsPerson(GObjID	id);
bool	IsHelpTool(GObjID	id);
#endif		//end of __ZX_ATTRBYOBJID_H__