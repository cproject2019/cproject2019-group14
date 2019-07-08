#include "AttrByObjID.h"
#include "GObjID.h"
extern map<GObjID, TString>			ObjNameTable;		//������
extern map<GObjID, GHOSTINFO>		GhostInfo;			//��������Ա�
extern map<GObjID, GPOS>			ObjPosTable;		//λ�ñ�

GPOS		GetPosByObjID			(GObjID id){
	return	ObjPosTable[id];
}

TString		GetNameByObjID			(GObjID	id){		//ȡ������
	return		ObjNameTable[id];
}

GSIZE		GetSizeByObjID			(GObjID	id){		//ȡ��ռλ��С
	//����ֻ��������λ�Ƚϴ���̵���Ҫ3*1��λ�ã������Ķ���1*1
	GSIZE	size;
	size.uColCount	=	size.uRowCount	=	1;
	if((id!=	GID_OBJ_PERWLNLMON) && (id!= GID_OBJ_PERWLNMMON))
		return	size;
	size.uColCount	=	3;
	size.uRowCount	=	1;
	return	size;
}


unsigned	GetGhostAtForceByObjID	(GObjID	id){		//ȡ�ù�����
	return		GhostInfo[id].m_uAtForce;
}

unsigned	GetGhostDfForceByObjID	(GObjID	id){		//ȡ�÷�����
	return		GhostInfo[id].m_uDfForce;
}

unsigned	GetGhostExprByObjID		(GObjID	id){		//ɱ������õ��ľ���
	return		GhostInfo[id].m_uExpr;
}

unsigned	GetGhostMoneyByObjID	(GObjID	id){		//ɱ��������õ���Ǯ
	return		GhostInfo[id].m_uMoney;
}

unsigned	GetGhostLifeByOdjID		(GObjID	id){		//�õ����������ֵ
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
