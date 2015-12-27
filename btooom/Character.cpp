#include "Character.h"
#include "CollisionsBox.h"
#include "OgreParticle.h"
#include "CEGUI.h"

void Character::updateCharacter(float interval) 
{
//	if(_mAlive)
//	{
		updateTime(interval);
		checkcollision();
		updateBody(interval);
		updateAnimations(interval);
//	}
	updateBomb(interval);
}

void Character::injectKeyDown(const OIS::KeyEvent& evt)
{
	if (evt.key == OIS::KC_SPACE) //放炸弹
	{
		if(_mBombCurNumber<_mBombNumber)
			if(_mBombList->setBomb(_mSn->getPosition()))
				_mBombCurNumber++;
		return;
	}

	if(_mLastTime <= 0 && _mDirButtonPush == false) //延缓时间结束且没有其他键按着
	{
		switch(evt.key) //switch效率优于if-else
		{
		case OIS::KC_W:
		case OIS::KC_UP:
			_mDir.x = -1;_mDir.z = 0;_mTimer = 0;_mDirButtonPush = true;break;
		case OIS::KC_A:
		case OIS::KC_LEFT:
			_mDir.z = 1;_mDir.x = 0;_mTimer = 0;_mDirButtonPush = true;break;
		case OIS::KC_S:
		case OIS::KC_DOWN:
			_mDir.x = 1;_mDir.z = 0;_mTimer = 0;_mDirButtonPush = true;break;
		case OIS::KC_D:
		case OIS::KC_RIGHT:
			_mDir.z = -1;_mDir.x = 0;_mTimer = 0;_mDirButtonPush = true;break;
		}
		if (!_mDir.isZeroLength() && _mState == Idle)
			setupBaseAnimation(Walk,true);
	}
}

void Character::injectKeyUp(const OIS::KeyEvent& evt)
{
	switch(evt.key) //防止俩键一起摁- -
	{
	case OIS::KC_W:
	case OIS::KC_UP:
		if(_mDir.x == -1)
		{
			_mDir.x = 0;
			if(!_mIsColliside)
				_mLastTime=_mMeterPerS-fmod(_mTimer,_mMeterPerS);
			else 
			{
				_mIsLasting = true;
				_mLastTime = 0;
				updatePosition();
			}
			_mDirButtonPush=false;
		}
		break;
	case OIS::KC_A:
	case OIS::KC_LEFT:
		if(_mDir.z == 1)
		{
			_mDir.z = 0;
			if(!_mIsColliside)
				_mLastTime=_mMeterPerS-fmod(_mTimer,_mMeterPerS);
			else 
			{
				_mIsLasting = true;
				_mLastTime = 0;
				updatePosition();
			}
			_mDirButtonPush=false;
		}
		break;
	case OIS::KC_S:
	case OIS::KC_DOWN:
		if(_mDir.x == 1)
		{
			_mDir.x = 0;
			if(!_mIsColliside)
				_mLastTime=_mMeterPerS-fmod(_mTimer,_mMeterPerS);
			else
			{
				_mIsLasting = true;
				_mLastTime = 0;
				updatePosition();
			}
			_mDirButtonPush=false;
		}
		break;
	case OIS::KC_D:
	case OIS::KC_RIGHT:
		if(_mDir.z == -1)
		{
			_mDir.z = 0;
			if(!_mIsColliside)
				_mLastTime=_mMeterPerS-fmod(_mTimer,_mMeterPerS);
			else 
			{
				_mIsLasting = true;
				_mLastTime = 0;
				updatePosition();
			}
			_mDirButtonPush=false;
		}
		break;
	}
}

void Character::setupBody(SceneManager* sceneMgr)
{
	_mSceneMgr = sceneMgr;
	if(!_mSceneMgr->hasSceneNode("Character"))
		_mSn = _mSceneMgr->getRootSceneNode()->createChildSceneNode("Character");
	_mEnt = _mSceneMgr->createEntity("CharacterBody", "mario.mesh");
	_mSn->attachObject(_mEnt);
	_mSn->scale(12,12,12);
	_mDir = Vector3(0,0,0);
	_mLastdir = Vector3(1,0,0);
	_mCharacterBox = _mSn->_getWorldAABB();
	_mAlive = true;
	_mIsColliside = false;
	
	}

void Character::setupAnimations()
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

void Character::setupBomb(SceneManager* sceneMgr)
{
	_mBombList = new BombManager(sceneMgr, "Ch");
	_mBombCurNumber=0;
	_mBombNumber = 2;
	_mBombCh = _mBombList->_mBomb;
}

void Character::setupTime()
{
	_mTimer=0;
	_mLastTime=0;
	_mIsLasting=true;
	_mDirButtonPush=false;
}

void Character::setupSpeed()
{
	_mWalkSpeed=112.5f;
	_mMeterPerS=75.0f/_mWalkSpeed;
}

void Character::setupParticle()
{
	pSysbomb =  pManager->createParticleSystem("ChBomb","blackHole",_mSceneMgr);
	pSysspeed = pManager->createParticleSystem("ChSpeed","flareShield",_mSceneMgr);
	pSysnum = pManager->createParticleSystem("ChNum","atomicity",_mSceneMgr);
	pSysbomb->setScale(Vector3(8,8,8));
	pSysspeed->setScale(Vector3(8,8,8));
	pSysnum->setScale(Vector3(8,8,8));
	_mSn->attachObject(pSysbomb);
	_mSn->attachObject(pSysspeed);
	_mSn->attachObject(pSysnum);
}

void Character::setupPosition(Vector3 pos)
{
	pos.y+=CHAR_HEIGHT;
	_mCharacterBox.setExtents(Vector3(-37.5+pos.x,0,-37.5+pos.z),Vector3(37.5+pos.x,CHAR_HEIGHT,37.5+pos.y));
	_mSn->setPosition(pos);
	_mDir = Vector3(0,0,0);
	_mAlive = true;
	_mIsColliside = false;
	Vector3 temp(1,0,0);
	Radian i=Math::ATan2(_mLastdir.x,_mLastdir.z);
	Radian j=Math::ATan2(temp.x,temp.z);
	_mSn->yaw(j-i);
	_mLastdir=temp;
	setupBaseAnimation(Idle);
	setupTime();
	setupSpeed();
	setupBomb(_mSceneMgr);
}

void Character::setupBaseAnimation(StateID id, bool reset)
{
	if (_mState >= 0 && _mState < NUM_ANIMS)
	{
		_mFadingIn[_mState] = false;
		_mFadingOut[_mState] = true;
	}
	_mState = id;

	if (id != Idle)
	{
		_mAnimationState[id]->setEnabled(true);
		_mAnimationState[id]->setWeight(0);
		_mFadingOut[id] = false;
		_mFadingIn[id] = true;
		if (reset) 
			_mAnimationState[id]->setTimePosition(0);
	}
	if (id == Idle)
	{
		_mAnimationState[id]->setEnabled(true);
		_mAnimationState[id]->setWeight(0);
		_mFadingOut[id] = false;
		_mFadingIn[id] = true;
		if (reset) 
			_mAnimationState[id]->setTimePosition(0);
	}
}

void Character::updateBody(float interval)
{
	if (_mDir !=_mLastdir&&_mDir !=Vector3::ZERO)//转向
	{
		Radian i=Math::ATan2(_mLastdir.x,_mLastdir.z);
		Radian j=Math::ATan2(_mDir.x,_mDir.z);
		_mSn->yaw(j-i);
		_mLastdir=_mDir;
	}
	if(!_mIsColliside)
	{
		if(_mDir !=Vector3::ZERO)//走路
			_mSn->translate(0, 0, interval * _mWalkSpeed,Node::TS_LOCAL);
		else
		{
			if(_mLastTime <= 0)
			{
				_mLastTime = 0;
				_mIsLasting=true;
				updatePosition();
			}
			else
			{
				_mLastTime-=interval;
				_mIsLasting=false;
				_mSn->translate(0, 0, interval * _mWalkSpeed,Node::TS_LOCAL);
			}
		}
		Vector3 temp = _mSn->getPosition();
		_mCharacterBox.setExtents(Vector3(temp.x-37.5,0,temp.z-37.5),Vector3(temp.x+37.5,CHAR_HEIGHT,temp.z+37.5));
	}
	else
	{
		_mIsLasting = true;
		_mLastTime = 0;
		updatePosition();
	}
}

void Character::updateAnimations(float interval)
{
	Real baseAnimSpeed = 3;

	if (_mState != Idle) 
		_mAnimationState[_mState]->addTime(interval * baseAnimSpeed);
	fadeAnimations(interval);

	if(_mDir.isZeroLength() && _mState == Walk)
		if(_mIsLasting==true)
	{
		setupBaseAnimation(Idle);
//		_mIsLasting=false;
	}
}

void Character::updateBomb(float interval)
{
	if(!_mBombList->update(interval))
		_mBombCurNumber--;
}

void Character::updateTime(float interval)
{
	_mTimer+=interval;
}

void Character::fadeAnimations(Real deltaTime)
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

void Character::checkcollision()
{
	_mIsColliside = false;
	AxisAlignedBoxSceneQuery * pQuery=_mSceneMgr->createAABBQuery(_mCharacterBox);
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
				if(checkWalls(name))
					return;
				if(checkBombs(name))
					return;	
				if(checkBouns(name))
					return;
				
			}
		}
	}
}

bool Character::checkBombs(Ogre::String name)
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

		if((v.x == -_mLastdir.z)&&(v.z == _mLastdir.x)&&(temp.length()>37.5))
		{
			_mIsColliside = true;
			_mTimer = 0;
			return true;
		}
	}
	return false;
}

bool Character::checkWalls(Ogre::String name)
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

		if((v.x == -_mLastdir.z)&&(v.z == _mLastdir.x)&&(temp.length()>37.5))
		{
			_mIsColliside = true;
			_mTimer = 0;
			return true;
		}
	}
	return false;
}

bool Character::checkBouns(Ogre::String name)
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

		if((v.x == -_mLastdir.z)&&(v.z == _mLastdir.x)&&(temp.length()<20))
		{
			subname = name.substr(5,5);
			if(subname == "Speed")
			{
				if(_mWalkSpeed< MAX_SPEED)
				{
					_mWalkSpeed+=37.5;
					_mMeterPerS=75.0f/_mWalkSpeed;
					CEGUI::DefaultWindow* temp = (CEGUI::DefaultWindow*)CEGUI::WindowManager::getSingleton().getWindow("Speed");
					temp->setText("Speed : "+Ogre::StringConverter::toString(int((_mWalkSpeed-75)/37.5)));				
				}
				pSysspeed->start(2);
				updateValueInt(bpos,1);
			}
			else if(subname ==  "BoNum")
			{
				if(_mBombNumber<MAX_BOMB_NUMBER)
				{
					_mBombNumber++;
					CEGUI::DefaultWindow* temp = (CEGUI::DefaultWindow*)CEGUI::WindowManager::getSingleton().getWindow("Bomb");
					temp->setText("Bomb : "+Ogre::StringConverter::toString(_mBombNumber));
				}
				pSysnum->start(2);
				updateValueInt(bpos,1);
			}
			else if(subname ==  "Power")
			{
				if(_mBombList->_mPower<MAX_POWER)
				{
					_mBombList->addPower();
					CEGUI::DefaultWindow* temp = (CEGUI::DefaultWindow*)CEGUI::WindowManager::getSingleton().getWindow("Power");
					temp->setText("Power : "+Ogre::StringConverter::toString(_mBombList->_mPower));
				}
				pSysbomb->start(2);
				updateValueInt(bpos,2);
			}
			_mSceneMgr->destroySceneNode(name);
			return true;
		}
	}
	return false;
}

void Character::updatePosition()  //定位到每个格子中央
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

void Character::updateValueInt(Vector3 pos,int value) //减少那个
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