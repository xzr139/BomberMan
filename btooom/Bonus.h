#ifndef __Bonus_H__
#define __Bonus_H__

#include "Ogre.h"

using namespace Ogre;

class Bonus
{
public:
	Bonus(SceneManager* sm,String ID):_mSceneMgr(sm),_mID(ID)
	{
		if(!_mSceneMgr->hasSceneNode("Bonus"+_mID))
			_mSn = _mSceneMgr->getRootSceneNode()->createChildSceneNode("Bonus"+_mID);
		else
			_mSn = _mSceneMgr->getSceneNode("Bonus"+_mID);
		_mPowerID = 0;
		_mSpeedID = 0;
		_mBombNumID = 0;
		_mRandnum = clock();
	}
	~Bonus(void)
	{
		delete _mSn;
	}
	void CreatBonus(Vector3 pos);
	void IncreasePower(Vector3 pos);
	void IncreaseSpeed(Vector3 pos);
	void IncreaseBombNum(Vector3 pos);
	void updateValueInt(Vector3 pos,int value);

private:
	SceneManager* _mSceneMgr;
	SceneNode* _mSn;

	String _mID;

	int _mPowerID;
	int _mSpeedID;
	int _mBombNumID;

	float _mRandnum;
};

#endif
