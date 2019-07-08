#include "AttrByObjID.h"
#include "GObjID.h"
extern map<GObjID, TString>			ObjNameTable;		//姓名表
extern map<GObjID, GHOSTINFO>		GhostInfo;			//怪物的属性表
extern map<GObjID, GPOS>			ObjPosTable;		//位置表

GPOS		GetPosByObjID			(GObjID id){
	return	ObjPosTable[id];
}

TString		GetNameByObjID			(GObjID	id){		//取得名字
	return		ObjNameTable[id];
}

GSIZE		GetSizeByObjID			(GObjID	id){		//取得占位大小
	//仅仅只有两个点位比较大的商店需要3*1的位置，其它的都是1*1
	GSIZE	size;
	size.uColCount	=	size.uRowCount	=	1;
	if((id!=	GID_OBJ_PERWLNLMON) && (id!= GID_OBJ_PERWLNMMON))
		return	size;
	size.uColCount	=	3;
	size.uRowCount	=	1;
	return	size;
}


unsigned	GetGhostAtForceByObjID	(GObjID	id){		//取得攻击力
	return		GhostInfo[id].m_uAtForce;
}

unsigned	GetGhostDfForceByObjID	(GObjID	id){		//取得防御力
	return		GhostInfo[id].m_uDfForce;
}

unsigned	GetGhostExprByObjID		(GObjID	id){		//杀死怪物得到的经验
	return		GhostInfo[id].m_uExpr;
}

unsigned	GetGhostMoneyByObjID	(GObjID	id){		//杀光死怪物得到的钱
	return		GhostInfo[id].m_uMoney;
}

unsigned	GetGhostLifeByOdjID		(GObjID	id){		//得到怪物的生命值
	return		GhostInfo[id].m_uLife;
}

bool	IsGhost(GObjID	id){
	return	(id<= GID_OBJ_GHEND && id>= GID_OBJ_GHBEGIN);
}

bool	IsPowerTool(GObjID id){
	return	(id<=GID_OBJ_POWREND && id>= GID_OBJ_POWRBEGIN);
}

bool	IsConstruction(GObjID	id){
	return	(id<= GID_OBJ_OTHEREND && id>= GID_OBJ_OTHERBEGIN);
}

bool	IsNutrition(GObjID	id){
	return	(id<=GID_OBJ_NUEND && id>= GID_OBJ_NUBEGIN);
}

bool	IsPerson(GObjID	id){
	return	(id<= GID_OBJ_PEREND && id>= GID_OBJ_PERBEGIN);
}

bool	IsHelpTool(GObjID	id){
	return	(id<=GID_OBJ_TLEND && id>= GID_OBJ_TLBEGIN);
}
