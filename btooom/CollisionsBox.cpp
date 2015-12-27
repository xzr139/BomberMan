#include "CollisionsBox.h"

AxisAlignedBox _mCharacterBox;  //包围盒们
AxisAlignedBox _mEnemy1Box;
AxisAlignedBox _mEnemy2Box;
AxisAlignedBox _mEnemy3Box;
AxisAlignedBox _mBombChBox[5]; 
AxisAlignedBox _mBombE1Box[5];
AxisAlignedBox _mBombE2Box[5];
AxisAlignedBox _mBombE3Box[5];

BtooomManager* _mManagerP;

bool _mBCharacter;
bool _mBEnemy1;                  //是否设定了敌人一号
bool _mBEnemy2;                  //是否设定了敌人二号
bool _mBEnemy3;                  //同了个上

Bomb** _mBombCh;                 //炸弹门
Bomb** _mBombE1;
Bomb** _mBombE2;
Bomb** _mBombE3;

Vector3 _mPosCh;                 //位置
Vector3 _mPosE1;
Vector3 _mPosE2;
Vector3 _mPosE3;

int _mValueMap[15][15];          //墙和炸弹的情况，墙为1,2-1，炸弹为-2
float _mValueInterest[15][15];   //感兴趣的地方
float _mValueDanger[15][15];     //危险的地方
int _mNum;                       //find次数，用于避免重复

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
