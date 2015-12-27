#include "Enemy.h"
#include "CollisionsBox.h"

void Enemy::updateEnemy(float interval) 
{
	if(_mAlive)
	{
		if(_mStopTime<=0)
		{
			checkcollision();
			updateBody(interval);		
		}
		else
			updateTime(interval);
		updateAnimations(interval);
		updateBomb(interval);
	}
	else
		updateBomb(interval);
	
}

void Enemy::setupBody(SceneManager* sceneMgr)
{
	_mSceneMgr = sceneMgr;
//	pos.y +=CHAR_HEIGHT;
	if(_mID == "E1")
	{
		if(!_mSceneMgr->hasSceneNode("Enemy1"))
			_mSn = _mSceneMgr->getRootSceneNode()->createChildSceneNode("Enemy1");
		_mEnt = _mSceneMgr->createEntity("EnemyBody1", "mario.mesh");
		_mEnemy1Box = _mSn->_getWorldAABB();
//		_mEnemy1Box.setExtents(Vector3(-37.5+pos.x,0,-37.5+pos.z),Vector3(37.5+pos.x,CHAR_HEIGHT,37.5+pos.z));
	}
	else if(_mID == "E2")
	{
		if(!_mSceneMgr->hasSceneNode("Enemy2"))
			_mSn = _mSceneMgr->getRootSceneNode()->createChildSceneNode("Enemy2");
		_mEnt = _mSceneMgr->createEntity("EnemyBody2", "mario.mesh");
		_mEnemy2Box = _mSn->_getWorldAABB();
//		_mEnemy2Box.setExtents(Vector3(-37.5+pos.x,0,-37.5+pos.z),Vector3(37.5+pos.x,CHAR_HEIGHT,37.5+pos.z));
	}
	else if(_mID == "E3")
	{
		if(!_mSceneMgr->hasSceneNode("Enemy3"))
			_mSn = _mSceneMgr->getRootSceneNode()->createChildSceneNode("Enemy3");
		_mEnt = _mSceneMgr->createEntity("EnemyBody3", "mario.mesh");
		_mEnemy3Box = _mSn->_getWorldAABB();
//		_mEnemy3Box.setExtents(Vector3(-37.5+pos.x,0,-37.5+pos.z),Vector3(37.5+pos.x,CHAR_HEIGHT,37.5+pos.z));
	}
//	_mCurPos2D = To2D(pos);
	_mSn->attachObject(_mEnt);
	_mSn->scale(12,12,12);
	_mLastdir = Vector3(1,0,0);
	_mDirPos = Vector3();
	_mTempNum = 0;
	_mIsColliside = false;
	_mAlive = true;
	}

void Enemy::setupParticle()
{
	if(_mID == "E1")
	{
		pSysbomb =  pManager->createParticleSystem("E1Bomb","blackHole",_mSceneMgr);
		pSysspeed = pManager->createParticleSystem("E1Speed","flareShield",_mSceneMgr);
		pSysnum = pManager->createParticleSystem("E1Num","atomicity",_mSceneMgr);
	}
	else if(_mID == "E2")
	{
		pSysbomb =  pManager->createParticleSystem("E2Bomb","blackHole",_mSceneMgr);
		pSysspeed = pManager->createParticleSystem("E2Speed","flareShield",_mSceneMgr);
		pSysnum = pManager->createParticleSystem("E2Num","atomicity",_mSceneMgr);
	}
	else if(_mID =="E3")
	{
		pSysbomb =  pManager->createParticleSystem("E3Bomb","blackHole",_mSceneMgr);
		pSysspeed = pManager->createParticleSystem("E3Speed","flareShield",_mSceneMgr);
		pSysnum = pManager->createParticleSystem("E3Num","atomicity",_mSceneMgr);
	}
	pSysbomb->setScale(Vector3(8,8,8));
	pSysspeed->setScale(Vector3(8,8,8));
	pSysnum->setScale(Vector3(8,8,8));
	_mSn->attachObject(pSysbomb);
	_mSn->attachObject(pSysspeed);
	_mSn->attachObject(pSysnum);
}

void Enemy::setupAnimations()
{
	_mEnt->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

	String animNames[] ={"idle", "walk"};

	for (int i = 0; i < NUM_ANIMS; i++)
	{
		if(i==0) 
			_mAnimationState[i] = _mEnt->getAnimationState("idle");
		else 
			_mAnimationState[i] = _mEnt->getAnimationState(animNames[i]);
		_mAnimationState[i]->setLoop(true);
		_mFadingIn[i] = false;
		_mFadingOut[i] = false;
	}
	setupBaseAnimation(Idle);
}

void Enemy::setupBomb(SceneManager* sceneMgr)
{
	_mBombList = new BombManager(sceneMgr, _mID);
	_mBombCurNumber=0;
	_mBombNumber = 1;
	if(_mID == "E1")
		_mBombE1 = _mBombList->_mBomb;
	else
		if(_mID == "E2")
			_mBombE2 = _mBombList->_mBomb;
		else
			if(_mID == "E3")
				_mBombE3 = _mBombList->_mBomb;
}

void Enemy::setupSpeed()
{
	_mWalkSpeed=112.5f;
	_mMeterPerS=75.0f/_mWalkSpeed;
}

void Enemy::setupTime()
{
	_mIsFinish = true;
	_mIsStop = true;
	_mLastTime = 0;
	_mStopTime = 0;
}

void Enemy::setupMap()
{
	for(int i =0;i<15;i++)
		for(int j = 0;j<15;j++)
			_mFootValue[i][j] = 0;
}

void Enemy::setupBaseAnimation(StateID id, bool reset)
{

	if(_mState !=id)
	{
		if (_mState >= 0 && _mState < NUM_ANIMS)
		{
			_mFadingIn[_mState] = false;
			_mFadingOut[_mState] = true;
		}

		_mState = id;
		_mAnimationState[id]->setEnabled(true);
		_mAnimationState[id]->setWeight(0);
		_mFadingOut[id] = false;
		_mFadingIn[id] = true;
		if (reset) 
			_mAnimationState[id]->setTimePosition(0);
	}
}

void Enemy::setupPosition(Vector3 pos)
{
	pos.y +=CHAR_HEIGHT;
	if(_mID == "E1")
		_mEnemy1Box.setExtents(Vector3(-37.5+pos.x,0,-37.5+pos.z),Vector3(37.5+pos.x,CHAR_HEIGHT,37.5+pos.z));
	else if(_mID == "E2")
		_mEnemy2Box.setExtents(Vector3(-37.5+pos.x,0,-37.5+pos.z),Vector3(37.5+pos.x,CHAR_HEIGHT,37.5+pos.z));
	else if(_mID == "E3")
		_mEnemy3Box.setExtents(Vector3(-37.5+pos.x,0,-37.5+pos.z),Vector3(37.5+pos.x,CHAR_HEIGHT,37.5+pos.z));
	_mSn->setPosition(pos);
	_mCurPos2D = To2D(pos);
	_mDirPos = Vector3(0,0,0);
	Vector3 temp(1,0,0);
	Radian i=Math::ATan2(_mLastdir.x,_mLastdir.z);
	Radian j=Math::ATan2(temp.x,temp.z);
	_mSn->yaw(i-j);
	_mLastdir=temp;
	_mTempNum = 0;
	_mIsColliside = false;
	_mAlive = true;
	setupBaseAnimation(Idle);
	setupMap();
	setupTime();
	setupSpeed();
	setupBomb(_mSceneMgr);
	Deceide();
}

void Enemy::updateBody(float interval)
{
	if(_mIsFinish)//完成一步
	{
		if(_mFootWay.empty())//决定新路
			if(!Deceide())
			{
				Stop(1);			
				return;
			}
		if(_mIsStop)//之前站着
		{
			if(_mState == Idle)
				setupBaseAnimation(Walk);
			_mIsStop = false;
			PutBomb();
		}
		WalkStateID temp = _mFootWay.front();
		Turn(temp);
		float safetime = IsSafe();
		if(safetime)
		{
			if(safetime >0)
			{
				_mLastTime = 0;
				_mIsFinish=true;
				if(safetime>=0.05&&safetime<=0.051)
					safetime = 0.25;
				Stop(safetime);
				return;
			}
			else
			{
				if(safetime ==-1)
				{
					if(_mState ==Walk)
					{
						_mIsStop = true;
						setupBaseAnimation(Idle);
					}
					_mFootWay.pop();
					return;
				}
				if(safetime == -2)
				{
					return;
				}
			}
		}
		_mFootWay.pop();
		if(_mTempNum >0)
			_mTempNum--;
		_mIsFinish = false;
		_mLastTime = _mMeterPerS;

	}
	if(1/*!_mIsColliside*/)
	{
		if(_mLastTime <= 0)
		{
			_mLastTime = 0;
			_mIsFinish=true;
			if(_mLastdir.x ==1)
				_mCurPos2D.x++;
			else if(_mLastdir.x ==-1)
				_mCurPos2D.x--;
			else if(_mLastdir.z ==1)
				_mCurPos2D.y++;
			else if(_mLastdir.z ==-1)
				_mCurPos2D.y--;
			if(_mFootWay.empty())
			{
				if(_mValueDanger[int(_mCurPos2D.x)][int(_mCurPos2D.y)]==0)
					Stop(1);
				updatePosition();
			}
		}
		else
		{
			_mLastTime-=interval;
			_mIsFinish=false;
			_mSn->translate(0, 0, interval * _mWalkSpeed,Node::TS_LOCAL);
		}
		Vector3 temp = _mSn->getPosition();
		if(_mID == "E1")
			_mEnemy1Box.setExtents(Vector3(temp.x-37.5,0,temp.z-37.5),Vector3(temp.x+37.5,CHAR_HEIGHT,temp.z+37.5));
		else if(_mID == "E2")
			_mEnemy2Box.setExtents(Vector3(temp.x-37.5,0,temp.z-37.5),Vector3(temp.x+37.5,CHAR_HEIGHT,temp.z+37.5));
		else if(_mID == "E3")
			_mEnemy3Box.setExtents(Vector3(temp.x-37.5,0,temp.z-37.5),Vector3(temp.x+37.5,CHAR_HEIGHT,temp.z+37.5));
	}
	else
	{
		_mIsFinish = true;
		_mLastTime = 0;
		updatePosition();
		_mCurPos2D = To2D(_mSn->getPosition());
		ClearStackQueue();
	}

}

void Enemy::Turn(WalkStateID dir) //转向
{
	updatePosition();
	Vector3 temp(0,0,0);
	if(dir == Left)
		temp.z = -1;
	else if(dir == Right)
		temp.z = 1;
	else if(dir == Up)
		temp.x = -1;
	else if(dir == Down)
		temp.x = 1;

	if(temp!=_mLastdir&&temp !=Vector3::ZERO)
	{
		Radian i=Math::ATan2(_mLastdir.x,_mLastdir.z);
		Radian j=Math::ATan2(temp.x,temp.z);
		_mSn->yaw(i-j);
		_mLastdir=temp;
	}
}

void Enemy::Stop(float time)
{
	_mStopTime = time;
	_mIsStop = true;
	if(_mState == Walk)
		setupBaseAnimation(Idle);
}

void Enemy::PutBomb()
{
	int w=0,x=0,y=0,z=0;
	bool put = true;
	if(_mValueMap[int(_mCurPos2D.x-1)][int(_mCurPos2D.y)]>0)
		w=1;
	if(_mValueMap[int(_mCurPos2D.x+1)][int(_mCurPos2D.y)]>0)
		x=1;
	if(_mValueMap[int(_mCurPos2D.x)][int(_mCurPos2D.y-1)]>0)
		y=1;
	if(_mValueMap[int(_mCurPos2D.x)][int(_mCurPos2D.y+1)]>0)
		z=1;
	if(w||x||y||z)
		put = false;
	else 
		put=rand()%3;

	if(_mValueDanger[int(_mCurPos2D.x)][int(_mCurPos2D.y)]>0||_mValueDanger[int(_mCurPos2D.x-1)][int(_mCurPos2D.y)]>0||_mValueDanger[int(_mCurPos2D.x+1)][int(_mCurPos2D.y)]>0||_mValueDanger[int(_mCurPos2D.x)][int(_mCurPos2D.y-1)]>0||_mValueDanger[int(_mCurPos2D.x)][int(_mCurPos2D.y+1)]>0)
		put = true;
	if(!put)
		if(_mBombCurNumber<_mBombNumber)
			if(_mBombList->setBomb(_mSn->getPosition()))
				_mBombCurNumber++;
}

void Enemy::updateTime(float interval)
{
	_mStopTime -=interval;
}

void Enemy::updateBomb(float interval)
{
	if(!_mBombList->update(interval))
		_mBombCurNumber--;
}

void Enemy::updateAnimations(float interval)
{
	Real baseAnimSpeed = 3;

	if (_mState != Idle) 
		_mAnimationState[_mState]->addTime(interval * baseAnimSpeed);
	fadeAnimations(interval);
}

void Enemy::fadeAnimations(Real deltaTime)
{
	for (int i = 0; i < NUM_ANIMS; i++)
	{
		if (_mFadingIn[i])
		{
			Real newWeight = _mAnimationState[i]->getWeight() + deltaTime * ANIM_FADE_SPEED;
			_mAnimationState[i]->setWeight(Math::Clamp<Real>(newWeight, 0, 1));
			if (newWeight >= 1) 
				_mFadingIn[i] = false;
		}
		else if (_mFadingOut[i])
		{
			Real newWeight = _mAnimationState[i]->getWeight() - deltaTime * ANIM_FADE_SPEED;
			_mAnimationState[i]->setWeight(Math::Clamp<Real>(newWeight, 0, 1));
			if (newWeight <= 0)
			{
				_mAnimationState[i]->setEnabled(false);
				_mFadingOut[i] = false;
			}
		}
	}
}

void Enemy::checkcollision()
{
	_mIsColliside = false;
	AxisAlignedBoxSceneQuery * pQuery;
	if(_mID =="E1")
		pQuery=_mSceneMgr->createAABBQuery(_mEnemy1Box);
	else if(_mID =="E2")
		pQuery=_mSceneMgr->createAABBQuery(_mEnemy2Box);
	else if(_mID =="E3")
		pQuery=_mSceneMgr->createAABBQuery(_mEnemy3Box);
	SceneQueryResult QResult=pQuery->execute();
	for (SceneQueryResultMovableList::iterator iter = QResult.movables.begin(); iter != QResult.movables.end();++iter)
	{
		MovableObject* pObject=static_cast<MovableObject*>(*iter);
		if(pObject)
		{
			if(pObject->getMovableType()=="Entity")
			{
				Entity* ent = static_cast<Entity*>(pObject);

				Ogre::String name = ent->getName();

				if(name=="CharacterBody"||name == "EnemyBody1"||name=="EnemyBody2"||name=="EnemyBody3"||name == "GroundEntity")
					continue;
	//			if(checkWalls(name))
	//				return;
	//			if(checkBombs(name))
	//				return;	
				if(checkBouns(name))
					return;
				
			}
		}
	}
}

bool Enemy::checkBombs(Ogre::String name)
{
	String subname = name.substr(0,4);
	if(subname=="Bomb")
	{
		Vector3 bpos = _mSceneMgr->getSceneNode(name)->getPosition();
		Vector3 cpos = _mSn->getPosition();
		cpos.y = cpos.y-CHAR_HEIGHT;
		Vector3 temp = bpos-cpos;
		Vector3 v = temp;

		if((v.x>1||v.x<-1)&&(v.z>1||v.z<-1)) //5-8
			return false;

		if(abs(v.x)>abs(v.z)) //方向
		{v.z = 0; v.x = v.x>0?1:-1;}
		else
		{v.x = 0; v.z = v.z>0?1:-1;}

		if((v.x == _mLastdir.z)&&(v.z == _mLastdir.x)&&(temp.length()>37.5)&&(temp.length()<65))
		{
			_mIsColliside = true;
			return true;
		}
	}
	return false;
}

bool Enemy::checkWalls(Ogre::String name)
{
	String subname = name.substr(0,4);
	if(subname == "Wall")
	{
		Vector3 bpos = _mSceneMgr->getSceneNode(name)->getPosition();
		Vector3 cpos = _mSn->getPosition();
		cpos.y = cpos.y-CHAR_HEIGHT;
		Vector3 temp = bpos-cpos;
		Vector3 v = temp;
		if((v.x>2||v.x<-2)&&(v.z>2||v.z<-2))
			return false;

		if(abs(v.x)>abs(v.z)) //方向
		{v.z = 0; v.x = v.x>0?1:-1;}
		else
		{v.x = 0; v.z = v.z>0?1:-1;}

		if((v.x == _mLastdir.z)&&(v.z == _mLastdir.x)&&(temp.length()>37.5)&&(temp.length()<60))
		{
			_mIsColliside = true;
			return true;
		}
	}
	return false;
}

bool Enemy::checkBouns(Ogre::String name)
{
	String subname = name.substr(0,5);
	if(subname == "Bonus")
	{
		Vector3 bpos = _mSceneMgr->getSceneNode(name)->getPosition();
		Vector3 cpos = _mSn->getPosition();
		cpos.y = cpos.y-CHAR_HEIGHT;
		Vector3 temp = bpos-cpos;
		Vector3 v = temp;

		if((v.x>1||v.x<-1)&&(v.z>1||v.z<-1))
			return false;

		if(abs(v.x)>abs(v.z)) //方向
		{v.z = 0; v.x = v.x>0?1:-1;}
		else
		{v.x = 0; v.z = v.z>0?1:-1;}

		if((v.x == _mLastdir.z)&&(v.z == _mLastdir.x)&&(temp.length()<20))
		{
			subname = name.substr(5,5);
			if(subname == "Speed")
			{
				if(_mWalkSpeed< MAX_SPEED)
				{
					_mWalkSpeed+=37.5;
					_mMeterPerS=75.0f/_mWalkSpeed;
				}
				pSysspeed->start(2);
				updateValueInt(bpos,1);
			}
			else
				if(subname ==  "BoNum")
				{
					if(_mBombNumber<MAX_BOMB_NUMBER)
						_mBombNumber++;
					pSysnum->start(2);
					updateValueInt(bpos,1);
				}
				else 
					if(subname ==  "Power")
					{
						if(_mBombList->_mPower<MAX_POWER)
							_mBombList->addPower();
						pSysbomb->start(2);
						updateValueInt(bpos,2);
					}

			_mSceneMgr->destroySceneNode(name);
			return true;
		}
	}
	return false;
}

void Enemy::updatePosition()  //定位到每个格子中央
{
	Vector3 temp = _mSn->getPosition();
	int i,j;
	if(temp.x<0)
		i=(temp.x-37.5)/75;
	else
		i=(temp.x+37.5)/75;
	if(temp.z<0)
		j=(temp.z-37.5)/75;
	else
		j=(temp.z+37.5)/75;
	Vector3 _pos(i*75,temp.y,j*75);
	_mSn->setPosition(_pos);
}

bool Enemy::Deceide()
{
	CaculateDir();
	return(FindPath());
}

void Enemy::CaculateDir()  //决定目的地
{
	ClearStackQueue();
	int x=-1,y=-1,value = 0;
	for(int i =_mCurPos2D.x-3;i<_mCurPos2D.x+4;i++)
		for(int j =_mCurPos2D.y-3;j<_mCurPos2D.y+4;j++)
			if(i>=0&&i<15&&j>=0&&j<15)
				if((!OnTheWall(i,j))&&((i!=_mCurPos2D.x)||(j!=_mCurPos2D.y)))
				{
					if(_mValueInterest[i][j]>value)
					{
							x=i;y=j;
							value = _mValueInterest[i][j];
					}
					else if(_mValueInterest[i][j]==value)
					{
						if(value!=0)
							if(rand()%2)
							{
								x=i;y=j;
								value = _mValueInterest[i][j];
							}
					}
				}
	if(x==-1&&y==-1)//没有匹配的就随便走吧不管了- -当然有时间的话弄成冲向玩家。。不过一般是没时间的
	{
		do{
		x=rand()%7+_mCurPos2D.x-3;
		y=rand()%7+_mCurPos2D.y-3;
		}
		while(OnTheWall(x,y)||x<0||x>=15||y<0||y>=15||(x==_mCurPos2D.x&&y==_mCurPos2D.y));
	}
	_mDirPos = To3D(x,y);
}

bool Enemy::FindPath()//从curpos到dirpos的走法
{
	Vector2 temp = To2D(_mDirPos);
	_mFootValue[int(temp.x)][int(temp.y)] = -1; //终点
	int num = SetValue(1);
	if(num==-1)
		return false;
	GetValue(temp,num);
	setupMap();
	return true;
}

int Enemy::SetValue(int i)//
{
	std::stack<Vector2> tempstack;
	if(_mFootValueStep.empty())
	{
		_mFootValue[int(_mCurPos2D.x)][int(_mCurPos2D.y)] = i;
		tempstack.push(Vector2(_mCurPos2D.x,_mCurPos2D.y));
	}
	else
	{
		Vector2 temp;
		bool x=false,y=false,z=false,w=false;
		for(;!_mFootValueStep.empty();)
		{
			temp = _mFootValueStep.top();
			_mFootValueStep.pop();
			if(!OnTheWall(temp.x+1,temp.y))
			{
				if(_mFootValue[int(temp.x)+1][int(temp.y)] !=-1)
				{
					if(_mFootValue[int(temp.x)+1][int(temp.y)] ==0)
					{
						_mFootValue[int(temp.x)+1][int(temp.y)] = i;
						tempstack.push(Vector2(temp.x+1,temp.y));
						x=true;
					}
				}
				else
				{
					_mFootValue[int(temp.x)+1][int(temp.y)] = i;
					tempstack.push(Vector2(temp.x+1,temp.y));
					return i;
				}
			}
			if(!OnTheWall(temp.x-1,temp.y))
			{
				if(_mFootValue[int(temp.x)-1][int(temp.y)] !=-1)
				{
					if(_mFootValue[int(temp.x)-1][int(temp.y)] ==0)
					{
						_mFootValue[int(temp.x)-1][int(temp.y)] = i;
						tempstack.push(Vector2(temp.x-1,temp.y));
						y=true;
					}
				}
				else
				{
					_mFootValue[int(temp.x)-1][int(temp.y)] = i;
					tempstack.push(Vector2(temp.x-1,temp.y));
					return i;
				}
			}
			if(!OnTheWall(temp.x,temp.y+1))
			{
				if(_mFootValue[int(temp.x)][int(temp.y+1)] !=-1)
				{
					if(_mFootValue[int(temp.x)][int(temp.y)+1] ==0)
					{
						_mFootValue[int(temp.x)][int(temp.y)+1] = i;
						tempstack.push(Vector2(temp.x,temp.y+1));
						z=true;
					}
				}
				else
				{
					_mFootValue[int(temp.x)][int(temp.y)+1] = i;
					tempstack.push(Vector2(temp.x,temp.y+1));
					return i;
				}
			}
			if(!OnTheWall(temp.x,temp.y-1))
			{
				if(_mFootValue[int(temp.x)][int(temp.y-1)] !=-1)
				{
					if(_mFootValue[int(temp.x)][int(temp.y)-1] ==0)
					{
						_mFootValue[int(temp.x)][int(temp.y)-1] = i;
						tempstack.push(Vector2(temp.x,temp.y-1));
						w=true;
					}
				}
				else
				{
					_mFootValue[int(temp.x)][int(temp.y)-1] = i;
					tempstack.push(Vector2(temp.x,temp.y-1));
					return i;
				}
			}
		}
		if(!(x||y||z||w))
			return -1;
	}
	if(tempstack.size() >25)
		return -1;
	_mFootValueStep = tempstack;
	return (SetValue(i+1));
};

bool Enemy::GetValue(Vector2 pos,int i)
{
	ClearStackQueue();
	if(pos == _mCurPos2D&&i==1)
		return true;
	if(_mFootValue[int(pos.x-1)][int(pos.y)] == i-1)
		if(GetValue(Vector2(pos.x-1,pos.y),i-1))
		{
			_mFootWay.push(Down);
			return true;
		}
	if(_mFootValue[int(pos.x+1)][int(pos.y)] == i-1)
		if(GetValue(Vector2(pos.x+1,pos.y),i-1))
		{
			_mFootWay.push(Up);
			return true;
		}
	if(_mFootValue[int(pos.x)][int(pos.y-1)] == i-1)
		if(GetValue(Vector2(pos.x,pos.y-1),i-1))
		{
			_mFootWay.push(Right);
			return true;
		}
	if(_mFootValue[int(pos.x)][int(pos.y+1)] == i-1)
		if(GetValue(Vector2(pos.x,pos.y+1),i-1))
		{
			_mFootWay.push(Left);
			return true;
		}
	return false;
}

void Enemy::ClearStackQueue()
{
	for(;!_mFootWay.empty();)
		_mFootWay.pop();
	for(;!_mFootValueStep.empty();)
		_mFootValueStep.pop();
}

float Enemy::IsSafe()//走每一步之前看一看是否安全
{
	int x = _mCurPos2D.x;
	int y = _mCurPos2D.y;
	if(_mLastdir.x==1)
		x+=1;
	else if(_mLastdir.x==-1)
		x-=1;
	else if(_mLastdir.z==1)
		y+=1;
	else if(_mLastdir.z==-1)//报错
		y-=1;
	if(_mValueDanger[int(_mCurPos2D.x)][int(_mCurPos2D.y)]!=0)//现在所站这点不安全
	{
		if(_mValueDanger[x][y]==0||_mWalkSpeed*_mValueDanger[x][y]>=150)//要去的这点安全，果断走
			return 0;
		if(_mFootWay.size()==1)//走到那点停下来不行，重新找目标
			return -1;
		if(GoTemp())//先找个位置避避
			return -2;//找到位置
		return 0;//走
	}
	if(_mValueDanger[x][y]!=0)//现在所站这点安全，要去的这点不安全
	{
		if(_mFootWay.size()==1)//走到那点停下来不行，重新找目标
			return -1;
	//	if(_mWalkSpeed*_mValueDanger[x][y]<150)//走到那点时间不够，要等
			return _mValueDanger[x][y];
	//	return 0;//走到那点时间够且继续走
	}
	return 0;//现在所站这点安全，要去这点安全
}

bool Enemy::GoTemp()
{
	if((_mValueDanger[int(_mCurPos2D.x+1)][int(_mCurPos2D.y)]==0)&&!(OnTheWall(_mCurPos2D.x+1,_mCurPos2D.y)))
	{
		std::queue<WalkStateID> temp;
		temp.push(Down);
		temp.push(Up);
		for(;_mTempNum>0;_mTempNum--)
		{
			_mFootWay.pop();
		}
		for(;!_mFootWay.empty();)
		{
			temp.push(_mFootWay.front());
			_mFootWay.pop();
		}
		_mFootWay = temp;
		_mTempNum = 2;
		return true;
	}
	if((_mValueDanger[int(_mCurPos2D.x-1)][int(_mCurPos2D.y)]==0)&&!(OnTheWall(_mCurPos2D.x-1,_mCurPos2D.y)))
	{
		std::queue<WalkStateID> temp;
		temp.push(Up);
		temp.push(Down);
		for(;_mTempNum>0;_mTempNum--)
		{
			_mFootWay.pop();
		}
		for(;!_mFootWay.empty();)
		{
			temp.push(_mFootWay.front());
			_mFootWay.pop();
		}
		_mTempNum = 2;
		_mFootWay = temp;
		return true;
	}
	if((_mValueDanger[int(_mCurPos2D.x)][int(_mCurPos2D.y+1)]==0)&&!(OnTheWall(_mCurPos2D.x,_mCurPos2D.y+1)))
	{
		std::queue<WalkStateID> temp;
		temp.push(Right);
		temp.push(Left);
		for(;_mTempNum>0;_mTempNum--)
		{
			_mFootWay.pop();
		}
		for(;!_mFootWay.empty();)
		{
			temp.push(_mFootWay.front());
			_mFootWay.pop();
		}
		_mTempNum = 2;
		_mFootWay = temp;
		return true;
	}
	if((_mValueDanger[int(_mCurPos2D.x)][int(_mCurPos2D.y-1)]==0)&&!(OnTheWall(_mCurPos2D.x,_mCurPos2D.y-1)))
	{
		std::queue<WalkStateID> temp;
		temp.push(Left);
		temp.push(Right);
		for(;_mTempNum>0;_mTempNum--)
		{
			_mFootWay.pop();
		}
		for(;!_mFootWay.empty();)
		{
			temp.push(_mFootWay.front());
			_mFootWay.pop();
		}
		_mTempNum = 2;
		_mFootWay = temp;
		return true;
	}
	return false;
}

bool Enemy::OnTheWall(int x ,int y)//判断这点是不是墙
{
	if(x>=0&&x<15&&y>=0&&y<15&&_mValueMap[x][y]==0)
		return false;
	return true;
}

Vector2 Enemy::To2D(Vector3 pos)//POD2D
{
	Vector2 temp;
	temp.x = (pos.z+525)/75;
	temp.y = (pos.x+525)/75;

	return temp;
}

Vector3 Enemy::To3D(int x,int y)//DIR
{
	Vector3 temp;//要颠倒！！！
	temp.z = x*75-525;
	temp.x = y*75-525;
	temp.y = CHAR_HEIGHT;

	return temp;
}

void Enemy::updateValueInt(Vector3 pos,int value) //减少那个
{
	int x = pos.x/75+7;
	int y = pos.z/75+7;
	_mValueInterest[y][x] -= 2*value;
	if(y-1>=0)
		_mValueInterest[y-1][x] -= value/2;
	if(x-1>=0)
		_mValueInterest[y][x-1] -= value/2;
	if(y+1<15)
		_mValueInterest[y+1][x] -= value/2;
	if(x+1<15)
		_mValueInterest[y][x+1] -= value/2;

}
