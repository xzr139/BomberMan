#include "CollisionsBox.h"

AxisAlignedBox _mCharacterBox;  //��Χ����
AxisAlignedBox _mEnemy1Box;
AxisAlignedBox _mEnemy2Box;
AxisAlignedBox _mEnemy3Box;
AxisAlignedBox _mBombChBox[5]; 
AxisAlignedBox _mBombE1Box[5];
AxisAlignedBox _mBombE2Box[5];
AxisAlignedBox _mBombE3Box[5];

BtooomManager* _mManagerP;

bool _mBCharacter;
bool _mBEnemy1;                  //�Ƿ��趨�˵���һ��
bool _mBEnemy2;                  //�Ƿ��趨�˵��˶���
bool _mBEnemy3;                  //ͬ�˸���

Bomb** _mBombCh;                 //ը����
Bomb** _mBombE1;
Bomb** _mBombE2;
Bomb** _mBombE3;

Vector3 _mPosCh;                 //λ��
Vector3 _mPosE1;
Vector3 _mPosE2;
Vector3 _mPosE3;

int _mValueMap[15][15];          //ǽ��ը���������ǽΪ1,2-1��ը��Ϊ-2
float _mValueInterest[15][15];   //����Ȥ�ĵط�
float _mValueDanger[15][15];     //Σ�յĵط�
int _mNum;                       //find���������ڱ����ظ�

SoundManager  *soundMgr;
ParticleUniverse::ParticleSystemManager*pManager; 

Bomb* FindBomb(String name)
{
	String subname = name.substr(4,2);
	Bomb *b = NULL;
	if(subname == "Ch")
	{
		subname = name.substr(6,1);
		for(int i = 0;i<3;i++)
			if(subname == Ogre::StringConverter::toString(i))
			{
				b = _mBombCh[i];
				break;
			}
	}
	else if(subname == "E1")
	{
		subname = name.substr(6,1);
		for(int i = 0;i<3;i++)
			if(subname == Ogre::StringConverter::toString(i))
			{
				b = _mBombE1[i];
				break;
			}
	}
	else if(subname == "E2")
	{
		subname = name.substr(6,1);
		for(int i = 0;i<3;i++)
			if(subname == Ogre::StringConverter::toString(i))
			{
				b = _mBombE2[i];
				break;
			}
	}
	else if(subname == "E3")
	{
		subname = name.substr(6,1);
		for(int i = 0;i<3;i++)
			if(subname == Ogre::StringConverter::toString(i))
			{
				b = _mBombE3[i];
				break;
			}
	}
	return b;
}
