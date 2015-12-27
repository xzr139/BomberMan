#ifndef __WallDe_H__
#define __WallDe_H__

#include "Ogre.h"
#include "OIS.h"
//#include "CollisionsBox.h"

using namespace Ogre;

class WallDe
{
public:
	WallDe(SceneManager* sm);
	~WallDe(void)
	{
	}
	void setupWallDe();
private:
	SceneManager* _mSceneMgr;
	SceneNode* _mSn;
};

#endif
