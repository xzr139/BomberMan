#include "Wall.h"
#include "CollisionsBox.h"

Wall::Wall(SceneManager* sm):_mSceneMgr(sm)
{
	_mSn = _mSceneMgr->getRootSceneNode()->createChildSceneNode("UndesWall",Vector3(0,0,0));
	Surrounding();
};

void Wall::setupWall()
{
	for(int i =0;i<15;i++)
		for(int j =0;j<15;j++)
			if(_mValueMap[i][j]<0)
			{
				String x,y;
				if(i<10)
					x= "0"+ StringConverter::toString(i);
				else
					x= StringConverter::toString(i);
				if(j<10)
					y= "0"+ StringConverter::toString(j);
				else
					y= StringConverter::toString(j);
				Entity* ent;
				if(!_mSceneMgr->hasEntity("Wall"+x+y))
					ent = _mSceneMgr->createEntity("Wall"+x+y,"wall.mesh");			
				if(!_mSceneMgr->hasSceneNode("Wall"+x+y))
				{
					SceneNode* temp;
					temp = _mSn->createChildSceneNode("Wall"+x+y,Vector3(-525+75*j,0,-525+75*i));
					temp->attachObject(ent);
					temp->scale(1.5,1.5,1.5);
				}
			}
}

void Wall::Surrounding()
{
		for(int i = 0;i<17;i++)
	{
		Entity* ent = _mSceneMgr->createEntity("Walll"+StringConverter::toString(i),"wall.mesh");
		SceneNode* temp = _mSn->createChildSceneNode("Walll"+StringConverter::toString(i),Vector3(-600,0,-600+75*i));
		temp->attachObject(ent);
		temp->scale(1.5,1.5,1.5);
	}
	for(int i = 0;i<15;i++)
	{
		Entity* ent = _mSceneMgr->createEntity("Wallf"+StringConverter::toString(i),"wall.mesh");
		SceneNode* temp = _mSn->createChildSceneNode("Wallf"+StringConverter::toString(i),Vector3(-600+75*(i+1),0,600));
		temp->attachObject(ent);
		temp->scale(1.5,1.5,1.5);
	}
	for(int i = 0;i<17;i++)
	{
		Entity* ent = _mSceneMgr->createEntity("Wallr"+StringConverter::toString(i),"wall.mesh");
		SceneNode* temp = _mSn->createChildSceneNode("Wallr"+StringConverter::toString(i),Vector3(600,0,-600+75*i));
		temp->attachObject(ent);
		temp->scale(1.5,1.5,1.5);
	}
	for(int i = 0;i<15;i++)
	{
		Entity* ent = _mSceneMgr->createEntity("Wallb"+StringConverter::toString(i),"wall.mesh");
		SceneNode* temp = _mSn->createChildSceneNode("Wallb"+StringConverter::toString(i),Vector3(-600+75*(i+1),0,-600));
		temp->attachObject(ent);
		temp->scale(1.5,1.5,1.5);
	}
}

