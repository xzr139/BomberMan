#ifndef __BombManager_H__
#define __BombManager_H__

#include "Bonus.h"
#include "Bomb.h"
#include "Ogre.h"
#include "OIS.h"

using namespace Ogre;

class BombManager
{

public:
	BombManager(SceneManager* sm, String ID):_mSceneMgr(sm),_mID(ID)
	{
		_mBonus = new Bonus(sm,ID);
		for(int i=0;i<3;i++)
		{
			_mBomb[i]=new Bomb(sm,_mBonus,i,_mID);
		}
		_mPower = 1;
	}
	~BombManager(void)
	{
	}

	bool update(float interval);
	bool setBomb(Vector3 pos);
	void addPower();
	int _mPower;
	Bomb* _mBomb[3];

private:
	bool Check(Vector3 pos);

private:
	SceneManager* _mSceneMgr;
	Bonus* _mBonus;
	String _mID;
};

#endif