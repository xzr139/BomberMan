#ifndef __CollisionBox_H__
#define __CollisionBox_H__

#pragma once
#include "Ogre.h"
#include "OIS.h"
#include "BtooomManager.h"
#include "Bomb.h"
#include "ParticleUniverseSystemManager.h"
#include "SoundManager.h"

using namespace Ogre;

extern AxisAlignedBox _mCharacterBox;
extern AxisAlignedBox _mEnemy1Box;
extern AxisAlignedBox _mEnemy2Box;
extern AxisAlignedBox _mEnemy3Box;
extern AxisAlignedBox _mBombChBox[5];
extern AxisAlignedBox _mBombE1Box[5];
extern AxisAlignedBox _mBombE2Box[5];
extern AxisAlignedBox _mBombE3Box[5];

extern BtooomManager* _mManagerP;

extern bool _mBCharacter;
extern bool _mBEnemy1;
extern bool _mBEnemy2;
extern bool _mBEnemy3;

extern Bomb** _mBombCh;
extern Bomb** _mBombE1;
extern Bomb** _mBombE2;
extern Bomb** _mBombE3;

extern Vector3 _mPosCh;
extern Vector3 _mPosE1;
extern Vector3 _mPosE2;
extern Vector3 _mPosE3;

extern int _mValueMap[15][15];
extern float _mValueInterest[15][15];
extern float _mValueDanger[15][15];
extern int _mNum;

extern Bomb* FindBomb(String name);
extern ParticleUniverse::ParticleSystemManager*pManager;
extern SoundManager  *soundMgr;

#endif