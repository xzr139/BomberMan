#include "Bomb.h"
#include "ParticleUniverseSystemManager.h"
#include "CollisionsBox.h"

void Bomb::Start(SceneNode* sn)
{
	_mState=Alive;
	_mSn=sn;
	Vector3 temp = _mSn->getPosition();
	temp.y+=10;
	_mSn->setPosition(temp);
	_mSn->attachObject(_mEnt);
	_mSn->scale(2,2,2);
	_mEnt->setVisible(true);
	time=3.0f;
	Realtime = 3.0f;
	_mChecknum = Ogre::StringConverter::toString(_mNum);
	_mNum++;
	upadteValueInt(1);
	Find();
}

void Bomb::Find()//寻找realtime
{
	Vector3 pos = _mSn->getPosition();
	bool find = false;
	Bomb *b1 = NULL,*b2 = NULL,*b3 = NULL,*b4 = NULL;
	for(int j = 0;j<_mPower;j++)
	{
		AxisAlignedBox box;
		box.setExtents(Vector3(pos.x+j*75+70,pos.y,pos.z-5),Vector3(pos.x+80+j*75,pos.y+10,pos.z+5));
		AxisAlignedBoxSceneQuery * pQuery=_mSceneMgr->createAABBQuery(box);
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
					String subname = name.substr(0,4);
					if(subname=="Bomb")
					{
						b1 = FindBomb(name);
						if(b1->Realtime<Realtime)
							Realtime = b1->Realtime;
						find = true;
						break;
					}
				}
			}
		}
		if(find == true)
		{
			find = false;
			break;
		}
	}
	for(int j = 0;j<_mPower;j++)
	{
		AxisAlignedBox box;
		box.setExtents(Vector3(pos.x-5,pos.y,pos.z+70+j*75),Vector3(pos.x+5,pos.y+10,pos.z+80+j*75));
		AxisAlignedBoxSceneQuery * pQuery=_mSceneMgr->createAABBQuery(box);
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
					String subname = name.substr(0,4);
					if(subname=="Bomb")
					{
						b2 = FindBomb(name);
						if(b2->Realtime<Realtime)
							Realtime = b2->Realtime;
						find = true;
						break;
					}
				}
			}
		}
		if(find == true)
		{
			find = false;
			break;
		}
	}
	for(int j = 0;j<_mPower;j++)
	{
		AxisAlignedBox box;
		box.setExtents(Vector3(pos.x-j*75-80,pos.y,pos.z-5),Vector3(pos.x-70-j*75,pos.y+10,pos.z+5));
		AxisAlignedBoxSceneQuery * pQuery=_mSceneMgr->createAABBQuery(box);
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
					String subname = name.substr(0,4);
					if(subname=="Bomb")
					{
						b3 = FindBomb(name);
						if(b3->Realtime<Realtime)
							Realtime = b3->Realtime;
						find = true;
						break;
					}
				}
			}
		}
		if(find == true)
		{
			find = false;
			break;
		}
	}
	for(int j = 0;j<_mPower;j++)
	{
		AxisAlignedBox box;
		box.setExtents(Vector3(pos.x-5,pos.y,pos.z-80-j*75),Vector3(pos.x+5,pos.y+10,pos.z-70-j*75));
		AxisAlignedBoxSceneQuery * pQuery=_mSceneMgr->createAABBQuery(box);
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
					String subname = name.substr(0,4);
					if(subname=="Bomb")
					{
						b3 = FindBomb(name);
						if(b3->Realtime<Realtime)
							Realtime = b3->Realtime;
						find = true;
						break;
					}
				}
			}
		}
		if(find == true)
		{
			find = false;
			break;
		}
	}
	if(b1) //有误差不管了。。
		b1->updateRealtime(Realtime,_mChecknum);
	if(b2)
		b2->updateRealtime(Realtime,_mChecknum);
	if(b3)
		b3->updateRealtime(Realtime,_mChecknum);
	if(b4)
		b4->updateRealtime(Realtime,_mChecknum);
}

bool Bomb::update(float interval)
{
	time-=interval;
	Realtime-=interval;
	Vector3 temp = _mSn->getScale();
	temp.x = 2 + (3-time)/10*6;
	temp.y = 2 + (3-time)/10*6;
	temp.z = 2 + (3-time)/10*6;
	_mSn->setScale(temp);
	updateValueDan();
	if(time<=0.f)
	{
		_mEnt->setVisible(false);
		_mState=Dead;
		return false;
	}
	return true;
}

void Bomb::ClearValueDan()
{
	Vector3 temp = _mSn->getPosition();
	int x = temp.x/75+7;
	int y = temp.z/75+7;
	_mValueDanger[y][x] = 0.05;//
	for(int j = 0; j<_mPower;j++)
	{	
		int i = y-1-j;
		if(i>=0)
		{
			_mValueDanger[i][x] = 0.05;//
			if(_mValueMap[i][x]>0)
			{
				_mValueMap[i][x]--;
				if(_mValueMap[i][x]>0)
				{
					String m,n;
					if(i<10)
						m= "0"+ StringConverter::toString(i);
					else
						m= StringConverter::toString(i);
					if(x<10)
						n= "0"+ StringConverter::toString(x);
					else
						n= StringConverter::toString(x);
					SceneNode *temp = _mSceneMgr->getSceneNode("WallDes"+m+n);
					temp->detachObject("WallDes"+m+n);
					_mSceneMgr->destroyEntity("WallDes"+m+n);
					Entity * ent = _mSceneMgr->createEntity("WallDes"+m+n,"bucket.mesh");
					temp->attachObject(ent);
					temp->setScale(0.95,0.95,0.95);
				}
				break;
			}		
		}
		else
			break;
	}
	for(int j = 0; j<_mPower;j++)
	{	
		int i=x-1-j;
		if(i>=0)
		{
			_mValueDanger[y][i] = 0.05;//
			if(_mValueMap[y][i]>0)
			{
				_mValueMap[y][i]--;
				if(_mValueMap[y][i]>0)
				{
					String m,n;
					if(y<10)
						m= "0"+ StringConverter::toString(y);
					else
						m= StringConverter::toString(y);
					if(i<10)
						n= "0"+ StringConverter::toString(i);
					else
						n= StringConverter::toString(i);
			
					SceneNode *temp = _mSceneMgr->getSceneNode("WallDes"+m+n);
					temp->detachObject("WallDes"+m+n);
					_mSceneMgr->destroyEntity("WallDes"+m+n);
					Entity * ent = _mSceneMgr->createEntity("WallDes"+m+n,"bucket.mesh");
					temp->attachObject(ent);
					temp->setScale(0.95,0.95,0.95);
				}
				break;
			}
		}
		else
			break;
	}
	for(int j = 0; j<_mPower;j++)
	{	
		int i=y+1+j;
		if(i<15)
		{
			_mValueDanger[i][x] = 0.05;//
			if(_mValueMap[i][x]>0)
			{
				_mValueMap[i][x]--;
				if(_mValueMap[i][x]>0)
				{
					String m,n;
					if(i<10)
						m= "0"+ StringConverter::toString(i);
					else
						m= StringConverter::toString(i);
					if(x<10)
						n= "0"+ StringConverter::toString(x);
					else
						n= StringConverter::toString(x);
			
					SceneNode *temp = _mSceneMgr->getSceneNode("WallDes"+m+n);
					temp->detachObject("WallDes"+m+n);
					_mSceneMgr->destroyEntity("WallDes"+m+n);
					Entity * ent = _mSceneMgr->createEntity("WallDes"+m+n,"bucket.mesh");
					temp->attachObject(ent);
					temp->setScale(0.95,0.95,0.95);
				}
				break;
			}
		}
		else
			break;
	}
	for(int j = 0; j<_mPower;j++)
	{	
		int i=x+1+j;
		if(i<15)
		{
			_mValueDanger[y][i] = 0.05;//
			_mValueMap[y][i]--;
			if(_mValueMap[y][i]>0)
			{
				String m,n;
				if(y<10)
					m= "0"+ StringConverter::toString(y);
				else
					m= StringConverter::toString(y);
				if(i<10)
					n= "0"+ StringConverter::toString(i);
				else
					n= StringConverter::toString(i);		
				SceneNode *temp = _mSceneMgr->getSceneNode("WallDes"+m+n);
				temp->detachObject("WallDes"+m+n);
				_mSceneMgr->destroyEntity("WallDes"+m+n);
				Entity * ent = _mSceneMgr->createEntity("WallDes"+m+n,"bucket.mesh");
				temp->attachObject(ent);
				temp->setScale(0.95,0.95,0.95);
				break;
			}
		}
		else
			break;
	}
}

void Bomb::Explode(int power)
{
	Vector3 pos = _mSn->getPosition();
	bool find = false;
	_mCheck = true;
	Play(pos);
	_mIsFade = true;
	_mFadeTime = FADETIME;
	for(int j = 0;j<power;j++)
	{
		AxisAlignedBox box;
		box.setExtents(Vector3(pos.x+j*75+70,pos.y,pos.z-5),Vector3(pos.x+80+j*75,pos.y+10,pos.z+5));
		AxisAlignedBoxSceneQuery * pQuery=_mSceneMgr->createAABBQuery(box);
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
					String subname = name.substr(0,7);
					if(subname=="WallDes")
					{
						DestoryWall(name);
						find = true;
						break;
					}
					subname = name.substr(0,4);
					if(subname=="Bomb")
					{
						DestoryBomb(name);
						find = true;
						break;
					}
					if(name == "CharacterBody")
					{
						DestoryPlayer(name);
						find = true;
						break;
					}
					subname = name.substr(0,9);
					if(subname == "EnemyBody")
					{
						DestoryEnemy(name);
						find = true;
						break;
					}
				}
			}
		}
		Play(Vector3(pos.x+j*75+75,pos.y,pos.z));
		if(find == true)
		{
			find = false;
			break;
		}
	}
	for(int j = 0;j<power;j++)
	{
		AxisAlignedBox box;
		box.setExtents(Vector3(pos.x-5,pos.y,pos.z+70+j*75),Vector3(pos.x+5,pos.y+10,pos.z+80+j*75));
		AxisAlignedBoxSceneQuery * pQuery=_mSceneMgr->createAABBQuery(box);
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
					String subname = name.substr(0,7);
					if(subname=="WallDes")
					{
						DestoryWall(name);
						find = true;
						break;
					}
					subname = name.substr(0,4);
					if(subname=="Bomb")
					{
						DestoryBomb(name);
						find = true;
						break;
					}
					if(name == "CharacterBody")
					{
						DestoryPlayer(name);
						find = true;
						break;
					}
					subname = name.substr(0,9);
					if(subname == "EnemyBody")
					{
						DestoryEnemy(name);
						find = true;
						break;
					}
				}
			}
		}
		Play(Vector3(pos.x,pos.y,pos.z+75+j*75));
		if(find == true)
		{
			find = false;
			break;
		}
	}
	for(int j = 0;j<power;j++)
	{
		AxisAlignedBox box;
		box.setExtents(Vector3(pos.x-j*75-80,pos.y,pos.z-5),Vector3(pos.x-70-j*75,pos.y+10,pos.z+5));
		AxisAlignedBoxSceneQuery * pQuery=_mSceneMgr->createAABBQuery(box);
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
					String subname = name.substr(0,7);
					if(subname=="WallDes")
					{
						DestoryWall(name);
						find = true;
						break;
					}
					subname = name.substr(0,4);
					if(subname=="Bomb")
					{
						DestoryBomb(name);
						find = true;
						break;
					}
					if(name == "CharacterBody")
					{
						DestoryPlayer(name);
						find = true;
						break;
					}
					subname = name.substr(0,9);
					if(subname == "EnemyBody")
					{
						DestoryEnemy(name);
						find = true;
						break;
					}
				}
			}
		}
		Play(Vector3(pos.x-j*75-75,pos.y,pos.z));
		if(find == true)
		{
			find = false;
			break;
		}
	}
	for(int j = 0;j<power;j++)
	{
		AxisAlignedBox box;
		box.setExtents(Vector3(pos.x-5,pos.y,pos.z-80-j*75),Vector3(pos.x+5,pos.y+10,pos.z-70-j*75));
		AxisAlignedBoxSceneQuery * pQuery=_mSceneMgr->createAABBQuery(box);
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
					String subname = name.substr(0,7);
					if(subname=="WallDes")
					{
						DestoryWall(name);
						find = true;
						break;
					}
					subname = name.substr(0,4);
					if(subname=="Bomb")
					{
						DestoryBomb(name);
						find = true;
						break;
					}
					if(name == "CharacterBody")
					{
						DestoryPlayer(name);
						find = true;
						break;
					}
					subname = name.substr(0,9);
					if(subname == "EnemyBody")
					{
						DestoryEnemy(name);
						find = true;
						break;
					}
				}
			}
		}
		Play(Vector3(pos.x,pos.y,pos.z-75-j*75));
		if(find == true)
		{
			find = false;
			break;
		}
	}
	ClearValueDan();
	upadteValueInt(-1);
	_mValueMap[int((pos.z+525)/75)][int((pos.x+525)/75)] = 0;
	_mSn->setVisible(false);
	//_mSceneMgr->destroySceneNode(_mSn);//
//	_mSn =NULL;
	_mCheck = false;
	_mChecknum = "";	
	qplSoundIndex=soundMgr->CreateStream(Ogre::String("Bomb.mp3")); //加载声音
	qplSoundChannel=INVALID_SOUND_CHANNEL;
	soundMgr->PlaySound(qplSoundIndex,_mSn,&qplSoundChannel);
}

void Bomb::Play(Vector3 pos)
{	
	int x = (pos.z+525)/75;
	int y = (pos.x+525)/75;
	if(x>=15||x<0||y>=15||y<0)
		return;
	String m,n;
	if(x<10)
		m = "0"+Ogre::StringConverter::toString(x);
	else
		m = Ogre::StringConverter::toString(x);
	if(y<10)
		n = "0"+Ogre::StringConverter::toString(y);
	else
		n = Ogre::StringConverter::toString(y);
	if(!_mSceneMgr->hasSceneNode(m+n))
	{
		ParticleUniverse::ParticleSystem* pSys = pManager->createParticleSystem(m+n,"fireplace_01",_mSceneMgr);
		_mSceneMgr->getRootSceneNode()->createChildSceneNode(m+n,pos)->attachObject(pSys);
		pSys->setScale(Vector3(25,25,25));
//		pSys->startAndStopFade(FADETIME);
//		pSys->stopFade(FADETIME);
		pSys->start(FADETIME);
		_mStack.push(m+n);
	}
}

void Bomb::DestoryWall(String name)
{
	Vector3 temp = _mSceneMgr->getSceneNode(name)->getPosition();
	int i,j;
	i = (temp.z+525)/75; j = (temp.x+525)/75;
	if(_mValueMap[i][j]==1)
	{
		_mValueInterest[i+1][j]-=0.5;
		_mValueInterest[i-1][j]-=0.5;
		_mValueInterest[i][j+1]-=0.5;
		_mValueInterest[i][j-1]-=0.5;
		_mBonus->CreatBonus(temp);	
		_mSceneMgr->destroySceneNode(name);
	}
}

void Bomb::DestoryBomb(String name)
{
	String subname = name.substr(4,2);
	if(subname == "Ch")
	{
		subname = name.substr(6,1);
		for(int i = 0;i<3;i++)
		{
			if(subname == Ogre::StringConverter::toString(i))
			{
				if(!_mBombCh[i]->_mCheck)
				{
					_mBombCh[i]->_mEnt->setVisible(false);
					_mBombCh[i]->_mState=Dead;
					_mBombCh[i]->Explode(_mBombCh[i]->_mPower);
					if(_mManagerP->_mCharacter)
						_mManagerP->_mCharacter->_mBombCurNumber--;
					_mBombChBox[i].setNull();
				}				
				break;
			}
		}
	}
	else if(subname == "E1")
	{
		subname = name.substr(6,1);
		for(int i = 0;i<3;i++)
		{
			if(subname == Ogre::StringConverter::toString(i))
			{
				if(!_mBombE1[i]->_mCheck)
				{
					_mBombE1[i]->_mEnt->setVisible(false);
					_mBombE1[i]->_mState=Dead;
					_mBombE1[i]->Explode(_mBombE1[i]->_mPower);
					if(_mBEnemy1)
						_mManagerP->_mEnemy1->_mBombCurNumber--;
					_mBombE1Box[i].setNull();
				}				
				break;
			}
		}
	}
	else if(subname == "E2")
	{
		subname = name.substr(6,1);
		for(int i = 0;i<3;i++)
		{
			if(subname == Ogre::StringConverter::toString(i))
			{
				if(!_mBombE2[i]->_mCheck)
				{
					_mBombE2[i]->_mEnt->setVisible(false);
					_mBombE2[i]->_mState=Dead;
					_mBombE2[i]->Explode(_mBombE2[i]->_mPower);
					if(_mBEnemy2)
						_mManagerP->_mEnemy2->_mBombCurNumber--;
					_mBombE2Box[i].setNull();					
				}				
				break;	
			}
		}
	}
	else if(subname == "E3")
	{
		subname = name.substr(6,1);
		for(int i = 0;i<3;i++)
		{
			if(subname == Ogre::StringConverter::toString(i))
			{
				if(!_mBombE3[i]->_mCheck)
				{
					_mBombE3[i]->_mEnt->setVisible(false);
					_mBombE3[i]->_mState=Dead;
					_mBombE3[i]->Explode(_mBombE3[i]->_mPower);
					if(_mBEnemy3)				
						_mManagerP->_mEnemy3->_mBombCurNumber--;
					_mBombE3Box[i].setNull();
				}				
				break;
			}
		}
	}
}

void Bomb::DestoryPlayer(String name)
{
	_mSceneMgr->getSceneNode("Character")->setVisible(false);
	_mManagerP->_mCharacter->_mAlive = false;
}

void Bomb::DestoryEnemy(String name)
{
	if(name == "EnemyBody1")
	{
		_mSceneMgr->getSceneNode("Enemy1")->setVisible(false);
		_mManagerP->_mEnemy1->_mAlive = false;
	}
	else if(name == "EnemyBody2")
	{
		_mSceneMgr->getSceneNode("Enemy2")->setVisible(false);
		_mManagerP->_mEnemy2->_mAlive = false;
	}
	else if(name == "EnemyBody3")
	{
		_mSceneMgr->getSceneNode("Enemy3")->setVisible(false);
		_mManagerP->_mEnemy3->_mAlive = false;
	}
}

void Bomb::updateRealtime(float time, String name)
{
	if(_mChecknum == name||Realtime<=time) //左，已搜过，右，最小时间无需搜
		return;
	Realtime = time;
	_mChecknum = name;
	Find();
}

void Bomb::updateValueDan(float time )
{
	Vector3 temp = _mSn->getPosition();
	int x = temp.x/75+7;
	int y = temp.z/75+7;
	if(_mValueDanger[y][x] == 0) 
		_mValueDanger[y][x] = Realtime;
	else
		if(_mValueDanger[y][x]>Realtime)
			_mValueDanger[y][x] = Realtime;
	for(int j = 0; j<_mPower;j++)
	{	
		if(y-1-j>=0)
		{
			if(_mValueDanger[y-1-j][x] == 0) 
				_mValueDanger[y-1-j][x] = Realtime;
			else
				if(_mValueDanger[y-1-j][x]>Realtime)
					_mValueDanger[y-1-j][x] = Realtime;
			if(_mValueMap[y-1-j][x]>0)
				break;
		}
	}
	for(int j = 0; j<_mPower;j++)
	{	
		if(x-1-j>=0)
		{
			if(_mValueDanger[y][x-1-j] == 0) 
				_mValueDanger[y][x-1-j] = Realtime;
			else
				if(_mValueDanger[y][x-1-j]>Realtime)
					_mValueDanger[y][x-1-j] = Realtime;
			if(_mValueMap[y][x-1-j]>0)
				break;
		}
	}
	for(int j = 0; j<_mPower;j++)
	{	
		if(y+1+j<15)
		{
			if(_mValueDanger[y+1+j][x] == 0) 
				_mValueDanger[y+1+j][x] = Realtime;
			else
				if(_mValueDanger[y+1+j][x]>Realtime)
					_mValueDanger[y+1+j][x] = Realtime;
			if(_mValueMap[y+1+j][x]>0)
				break;
		}
	}
	for(int j = 0; j<_mPower;j++)
	{	
		if(x+1+j<15)
		{
			if(_mValueDanger[y][x+1+j] == 0) 
				_mValueDanger[y][x+1+j] = Realtime;
			else
				if(_mValueDanger[y][x+1+j]>Realtime)
					_mValueDanger[y][x+1+j] = Realtime;
			if(_mValueMap[y][x+1+j]>0)
				break;
		}
	}

}

void Bomb::upadteValueInt(int value)
{
	Vector3 temp = _mSn->getPosition();
	int x = temp.x/75+7;
	int y = temp.z/75+7;
	_mValueInterest[y][x] -= value;
	if(y-1>=0)
		_mValueInterest[y-1][x] -= value/2;
	if(x-1>=0)
		_mValueInterest[y][x-1] -= value/2;
	if(y+1<15)
		_mValueInterest[y+1][x] -= value/2;
	if(x+1<15)
		_mValueInterest[y][x+1] -= value/2;
}