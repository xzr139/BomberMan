#include "Bonus.h"
#include "CollisionsBox.h"

void Bonus::CreatBonus(Vector3 pos)
{
	srand((unsigned)_mRandnum);  
	int i =rand()%10;   //0-9
	if(i<=5)
	{
		switch(i)
		{
		case 0:
		case 4:
			IncreasePower(pos);
			break;
		case 1:
		case 3:
			IncreaseSpeed(pos);
			break;
		case 2:
		case 5:
			IncreaseBombNum(pos);
			break;
		}
	}
	srand((unsigned)time(NULL));  
	_mRandnum +=rand()%100; 
}

void Bonus::IncreasePower(Vector3 pos)
{
	pos.y+=10;
	Entity* ent = _mSceneMgr->createEntity("BonusPower"+StringConverter::toString(_mPowerID)+_mID,"fire.mesh");//penginee
	_mSn->createChildSceneNode("BonusPower"+StringConverter::toString(_mPowerID)+_mID,pos);
	_mSceneMgr->getSceneNode("BonusPower"+StringConverter::toString(_mPowerID)+_mID)->attachObject(ent);
	_mSceneMgr->getSceneNode("BonusPower"+StringConverter::toString(_mPowerID)+_mID)->setScale(0.75,0.75,0.75);
	updateValueInt(pos,2);
	_mPowerID++;
}
	
void Bonus::IncreaseSpeed(Vector3 pos)
{
	Entity* ent = _mSceneMgr->createEntity("BonusSpeed"+StringConverter::toString(_mSpeedID)+_mID,"shoes.mesh");//Barrel
	_mSn->createChildSceneNode("BonusSpeed"+StringConverter::toString(_mSpeedID)+_mID,pos)->scale(5,5,5);
	_mSceneMgr->getSceneNode("BonusSpeed"+StringConverter::toString(_mSpeedID)+_mID)->attachObject(ent);
	_mSceneMgr->getSceneNode("BonusSpeed"+StringConverter::toString(_mSpeedID)+_mID)->setScale(2,2,2);
	updateValueInt(pos,1);
	_mSpeedID++;
}

void Bonus::IncreaseBombNum(Vector3 pos)
{
	pos.y +=10;
	Entity* ent = _mSceneMgr->createEntity("BonusBoNum"+StringConverter::toString(_mBombNumID)+_mID,"bomb_bonus.mesh");//fish
	_mSn->createChildSceneNode("BonusBoNum"+StringConverter::toString(_mBombNumID)+_mID,pos)->scale(5,5,5);
	_mSceneMgr->getSceneNode("BonusBoNum"+StringConverter::toString(_mBombNumID)+_mID)->attachObject(ent);
	_mSceneMgr->getSceneNode("BonusBoNum"+StringConverter::toString(_mBombNumID)+_mID)->setScale(3.5,3.5,3.5);
	updateValueInt(pos,1);
	_mBombNumID++;
}

void Bonus::updateValueInt(Vector3 pos,int value)
{
	int x = pos.x/75+7;
	int y = pos.z/75+7;
	_mValueInterest[y][x] += 2*value;
	if(y-1>=0)
		_mValueInterest[y-1][x] += value/2;
	if(x-1>=0)
		_mValueInterest[y][x-1] += value/2;
	if(y+1<15)
		_mValueInterest[y+1][x] += value/2;
	if(x+1<15)
		_mValueInterest[y][x+1] += value/2;

}