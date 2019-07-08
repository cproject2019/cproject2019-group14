#include "GameStatus.h"

//Ѫ��
double				lfBloodVol=	1000;					

//����
unsigned			uExperience=	0;					
	
//��Ǯ
unsigned			uMoney=	0;						

//�ȼ�
unsigned			uLevel=	1;						

//����
unsigned			uAttackCapacity	=	20;			

//����
unsigned			uDefenceCapacity=	10;	

//��Կ��
unsigned			uRedKey=	0;			

//��Կ��
unsigned			uYellowKey=	0;				

//��Կ��
unsigned			uBlueKey=	0;				

//¥����Ŀ
unsigned			uFloorCount=	0;			

//��ǰ¥��
unsigned			uCurrentFloor=	1;

//��������¥��
unsigned			uMaxFloorHasArrive=	1;		

//������еĵ�ͼ
vector<GMap>		vAllMaps;					

//�Ƿ�õ�ʮ�ּ�
bool				bHasGetCross		=	false;			

//�Ƿ��Ѿ�����С����
bool				bHasVisitSOG		=	false;		

//�Ƿ��Ѿ�������������ʿ
bool				bSOGHasGivePower	=	false;

//�Ƿ�����۸��
bool				bHasVisitBRH=	false;			

//�Ƿ�����޻�
bool				bHasVisitWH=	false;			

//�Ƿ�õ���ͷ
bool				bHasGetHammer=	false;			

//�Ƿ����ֱ�Ӵ�Խ¥��
bool				bCanCrossFloorDirectly=	false;

//�Ƿ���Բ鿴��������
bool				bCanQueryGhostAttributes=	false;		

//�Ƿ���Լ�ħ��
bool				bCanSeeDevil			=	false;	

//�Ƿ�������ħ��
bool				bHasSeeTrueDevil		=	false;

//�Ƿ��������ħ��
bool				bHasSeeRedClothDevil	=	false;

//�Ƿ�����ٵ�ħ��
bool				bHasSeeFakeDevil		=	false;

//�ڶ��ص������Ƿ����ͨ��
bool				bIronDoorCanCross		=	false;

GPOS				HeroPos(9, 5);//���ǵĵص�

bool				bWin=	false;
//0���� 1���� 2���� 3����
unsigned			uDirection;				

//������
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

