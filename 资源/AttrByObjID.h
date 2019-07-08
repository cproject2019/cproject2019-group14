#ifndef		__ZX_ATTRBYOBJID_H__
#define		__ZX_ATTRBYOBJID_H__
#include "header.h"

//����GetNameByOdjID֮ǰ��ȷ��������InitNameTalbe
TString		GetNameByObjID			(GObjID	id);		//ȡ������

//�����������Ĵ�С��1*1���������������ʵ�ֱȽϼ�
GSIZE		GetSizeByObjID			(GObjID	id);		//ȡ��ռλ��С

//�������º���֮ǰ��ȷ��������InitPosTable
GPOS		GetPosByObjID			(GObjID	id);		//��λͼ�е�λ��

//�������º���֮ǰ��ȷ��������InitGhostInfoTable
unsigned	GetGhostAtForceByObjID	(GObjID	id);//ȡ�ù�����
unsigned	GetGhostDfForceByObjID	(GObjID	id);//ȡ�÷�����
unsigned	GetGhostExprByObjID		(GObjID	id);//ɱ������õ��ľ���
unsigned	GetGhostMoneyByObjID	(GObjID	id);//ɱ��������õ���Ǯ
unsigned	GetGhostLifeByOdjID		(GObjID	id);//�õ����������ֵ


bool		NeedTransparentBlt(GObjID	id);//�Ƿ񱳾���Ҫ͸����ʾ

bool	IsGhost(GObjID id);
bool	IsPowerTool(GObjID id);
bool	IsConstruction(GObjID	id);
bool	IsNutrition(GObjID	id);
bool	IsPerson(GObjID	id);
bool	IsHelpTool(GObjID	id);
#endif		//end of __ZX_ATTRBYOBJID_H__