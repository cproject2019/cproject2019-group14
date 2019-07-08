#ifndef		__ZX_GAMESTATUS_H__
#define		__ZX_GAMESTATUS_H__
#include "header.h"
#include "Map.h"

//����ļ������洢���ǵ�����
extern	double				lfBloodVol;					//Ѫ��

extern	unsigned			uExperience;				//����

extern	unsigned			uMoney;						//��Ǯ

extern	unsigned			uLevel;						//�ȼ�

extern	unsigned			uAttackCapacity;			//����

extern	unsigned			uDefenceCapacity;			//����

extern	unsigned			uRedKey;					//��Կ��

extern	unsigned			uYellowKey;					//��Կ��

extern	unsigned			uBlueKey;					//��Կ��

extern	unsigned			uFloorCount;				//¥����Ŀ

extern	unsigned			uCurrentFloor;				//��ǰ¥��

extern	unsigned			uMaxFloorHasArrive;			//��������¥��

extern	vector<GMap>		vAllMaps;					//������еĵ�ͼ

extern	bool				bHasGetCross;				//�Ƿ�õ�ʮ�ּ�

extern	bool				bHasVisitSOG;				//�Ƿ��Ѿ�����С����

extern	bool				bSOGHasGivePower;			//�Ƿ��Ѿ�������������ʿ

extern	bool				bHasVisitBRH;				//�Ƿ�����۸��

extern	bool				bHasVisitWH;				//�Ƿ�����޻�

extern	bool				bHasGetHammer;				//�Ƿ�õ���ͷ

extern	bool				bCanCrossFloorDirectly;		//�Ƿ����ֱ�Ӵ�Խ¥��

extern	bool				bCanQueryGhostAttributes;	//�Ƿ���Բ鿴��������	

extern	bool				bCanSeeDevil;				//�Ƿ���Լ�ħ��

extern	bool				bIronDoorCanCross;			//�ڶ��ص������Ƿ��

extern	bool				bHasSeeTrueDevil;			//�Ƿ�������ħ��

extern	bool				bHasSeeFakeDevil;			//�Ƿ�����ٵ�ħ��

extern	bool				bHasSeeRedClothDevil;		//�Ƿ��������ħ��

extern GPOS					HeroPos;					//�����ڵĵط�

extern unsigned				uDirection;					//���ǵķ���

//������
extern bool					bUpFloor; //

extern	bool				bWin;
#endif