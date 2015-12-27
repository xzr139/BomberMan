#ifndef __BtooomManager_H__
#define __BtooomManager_H__

#include "Ogre.h"
#include "OIS.h"
#include "Character.h"
#include "Enemy.h"
#include "WallManager.h"
#include "BombManager.h"

class BtooomManager
{
public:
	BtooomManager(SceneManager* sm,bool ch,bool e1,bool e2,bool e3):_mSceneMgr(sm)
	{
		Plane planeGround(Vector3::UNIT_Y, 0);
		MeshManager::getSingleton().createPlane("ground",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeGround,
			1125,1125,20,20,true,1,2.5,2.5,Vector3::UNIT_Z);

		Entity* ent = _mSceneMgr->createEntity("GroundEntity", "ground");
		_mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
		ent->setMaterialName("Examples/MRAMOR6X6");
		ent->setCastShadows(false);

		if(ch)
			_mCharacter = new Character(_mSceneMgr);
		else
			_mCharacter = NULL;
		if(e1)
			_mEnemy1 =new Enemy(_mSceneMgr, "E1");
		else
			_mEnemy1 = NULL;
		if(e2)
			_mEnemy2 =new Enemy(_mSceneMgr, "E2");
		else
			_mEnemy2 = NULL;
		if(e3)
			_mEnemy3 =new Enemy(_mSceneMgr,"E3");
		else
			_mEnemy3 = NULL;
		_mWallMgr = new WallManager(_mSceneMgr);
	}
	~BtooomManager(void)
	{
	}

	int update(float interval);
	void update_KeyUp(const OIS::KeyEvent& evt);
	void update_KeyDown(const OIS::KeyEvent& evt);

public:
	Ogre::SceneManager* _mSceneMgr;
	Character* _mCharacter;
	WallManager* _mWallMgr;
	Enemy* _mEnemy1;
	Enemy* _mEnemy2;
	Enemy* _mEnemy3;
};

#endif