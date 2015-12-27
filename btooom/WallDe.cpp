#include "WallDe.h"
#include "CollisionsBox.h"

WallDe::WallDe(SceneManager* sm):_mSceneMgr(sm)
{
	_mSn = _mSceneMgr->getRootSceneNode()->createChildSceneNode("DesWall",Vector3(0,0,0));

}


void WallDe::setupWallDe()
{
	for(int i =0;i<15;i++)
		for(int j =0;j<15;j++)
			if(_mValueMap[i][j]>0)
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
				if(_mValueMap[i][j] ==1)
				{
					if(!_mSceneMgr->hasEntity("WallDes"+x+y))
						ent = _mSceneMgr->createEntity("WallDes"+x+y,"brick.mesh");
				}
				else
				{
					if(!_mSceneMgr->hasEntity("WallDes"+x+y))
						ent = _mSceneMgr->createEntity("WallDes"+x+y,"wood.mesh");	
				}
				if(!_mSceneMgr->hasSceneNode("WallDes"+x+y))
				{
					SceneNode* temp;
					temp = _mSn->createChildSceneNode("WallDes"+x+y,Vector3(-525+75*j,0,-525+75*i));
					temp->attachObject(ent);
					temp->scale(1.5,1.5,1.5);
				}
				_mValueInterest[i+1][j]+=0.5;
				_mValueInterest[i-1][j]+=0.5;
				_mValueInterest[i][j+1]+=0.5;
				_mValueInterest[i][j-1]+=0.5;				
			}
}