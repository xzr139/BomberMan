#ifndef __Wall_H__
#define __Wall_H__

#include "Ogre.h"
#include "OIS.h"

using namespace Ogre;

class Wall
{
public:
	Wall(SceneManager* sm);
	virtual ~Wall(void)
	{
	};
	void setupWall();

private:
	void Surrounding();

private:
	SceneManager* _mSceneMgr;
	SceneNode* _mSn;
};

#endif
