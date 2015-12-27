#include "BombManager.h"
#include "CollisionsBox.h"
#include "ParticleUniverseSystemManager.h"

bool BombManager::update(float interval)
{
	for(int i=0;i<3;i++)
		if(_mBomb[i]->_mState==_mBomb[i]->Alive)
		{
			if(!_mBomb[i]->update(interval))
			{
				_mBomb[i]->Explode(_mPower);			
				if(_mID == "Ch")
					_mBombChBox[i].setNull();
				else if(_mID == "E1")
					_mBombE1Box[i].setNull();
				else if(_mID == "E2")
					_mBombE2Box[i].setNull();
				else if(_mID == "E3")
					_mBombE3Box[i].setNull();
				return false;
			}
		}
		else
		{
			if(_mBomb[i]->_mIsFade)
			{
				_mBomb[i]->_mFadeTime-=interval;								
				if(_mBomb[i]->_mFadeTime<=0)
				{
					Vector3 temp = _mBomb[i]->_mSn->getPosition();
					int x = temp.x/75+7;
					int y = temp.z/75+7;
					_mValueDanger[y][x] = 0;
					for(int j = 0; j<_mBomb[i]->_mPower;j++)
					{	
						int t = y-1-j;
						if(t>=0)
							_mValueDanger[t][x] = 0;//
						t=x-1-j;
						if(t>=0)
							_mValueDanger[y][t] = 0;//
						t=y+1+j;
						if(t<15)
							_mValueDanger[t][x] = 0;//
						t=x+1+j;
						if(i<15)
							_mValueDanger[y][t] = 0;//
					}	
					_mBomb[i]->_mIsFade = false;
					_mBomb[i]->_mFadeTime = 0;
					_mSceneMgr->destroySceneNode(_mBomb[i]->_mSn);//
					_mBomb[i]->_mSn = NULL;
					for(;!_mBomb[i]->_mStack.empty();)
					{
						String temp = _mBomb[i]->_mStack.top();
						_mBomb[i]->_mStack.pop();
						_mSceneMgr->destroySceneNode(temp);
						pManager->destroyParticleSystem(temp,_mSceneMgr);
					}
				}
			}
		}
	return true;
}

bool BombManager::setBomb(Vector3 pos)
{
	int i,j;
	if(pos.x<0)
		i=(pos.x-37.5)/75;
	else
		i=(pos.x+37.5)/75;
	if(pos.z<0)
		j=(pos.z-37.5)/75;
	else
		j=(pos.z+37.5)/75;
	Vector3 _pos(i*75,5,j*75);

	for(int i=0;i<3;i++)
	{
		if((_mBomb[i]->_mState == _mBomb[i]->Dead)&&!(_mSceneMgr->hasSceneNode("Bomb"+_mID+Ogre::StringConverter::toString(i))))
		{
			if(Check(_pos))
			{
				_mBomb[i]->Start(_mSceneMgr->getRootSceneNode()->createChildSceneNode("Bomb"+_mID+Ogre::StringConverter::toString(i),_pos));
				_mValueMap[int((_pos.z+525)/75)][int((_pos.x+525)/75)] = -2;
				if(_mID == "Ch")
				{
					_mBombChBox[i] = _mBomb[i]->_mSn->_getWorldAABB();
					_mBombChBox[i].setExtents(Vector3(_pos.x-37.5,_pos.y,_pos.z-37.5),Vector3(37.5+_pos.x,50+_pos.y,37.5+_pos.z));
				}
				else if(_mID == "E1")
				{
					_mBombE1Box[i] = _mBomb[i]->_mSn->_getWorldAABB();
					_mBombE1Box[i].setExtents(Vector3(_pos.x-37.5,_pos.y,_pos.z-37.5),Vector3(37.5+_pos.x,50+_pos.y,37.5+_pos.z));
				}
				else if(_mID == "E2")
				{
					_mBombE2Box[i] = _mBomb[i]->_mSn->_getWorldAABB();
					_mBombE2Box[i].setExtents(Vector3(_pos.x-37.5,_pos.y,_pos.z-37.5),Vector3(37.5+_pos.x,50+_pos.y,37.5+_pos.z));
				}
				else if(_mID == "E3")
				{
					_mBombE3Box[i] = _mBomb[i]->_mSn->_getWorldAABB();
					_mBombE3Box[i].setExtents(Vector3(_pos.x-37.5,_pos.y,_pos.z-37.5),Vector3(37.5+_pos.x,50+_pos.y,37.5+_pos.z));
				}				
			}
			else
				return false;
			i=3;
		}
	}
	return true;
}

bool BombManager::Check(Vector3 pos)
{
	for(int j=0;j<3;j++)
	{
		if(_mBombCh&&_mBombCh[j]->_mState==_mBombCh[j]->Alive&&_mBombCh[j]->_mSn->getPosition()==pos)
			return false;
		if(_mBombE1&&_mBombE1[j]->_mState==_mBombE1[j]->Alive&&_mBombE1[j]->_mSn->getPosition()==pos)
			return false;
		if(_mBombE2&&_mBombE2[j]->_mState==_mBombE2[j]->Alive&&_mBombE2[j]->_mSn->getPosition()==pos)
			return false;
		if(_mBombE3&&_mBombE3[j]->_mState==_mBombE3[j]->Alive&&_mBombE3[j]->_mSn->getPosition()==pos)
			return false;
	}
			
	return true;
}

void BombManager::addPower()
{
	_mPower++;
	for(int i = 0;i<3;i++)
		_mBomb[i]->_mPower++;
}