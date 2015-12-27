#ifndef __WallManager_H__
#define __WallManager_H__

#include "Ogre.h"
#include "OIS.h"
#include "Wall.h"
#include "WallDe.h"

using namespace Ogre;

class WallManager
{
public:
	WallManager(SceneManager* sm):_mSceneMgr(sm)
	{
		_mWallDe = new WallDe(_mSceneMgr);
		_mWall = new Wall(_mSceneMgr);
	}
	~WallManager(void)
	{
	}
	void setupWall();
private:
	SceneManager* _mSceneMgr;
	SceneNode* _mSn;

	WallDe* _mWallDe;
	Wall* _mWall;
};

#endif