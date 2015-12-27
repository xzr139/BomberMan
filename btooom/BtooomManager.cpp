#include "BtooomManager.h"
#include "CollisionsBox.h"
#include "ParticleUniverseSystemManager.h"

void BtooomManager::update_KeyUp(const OIS::KeyEvent& evt)
{
	if(_mCharacter)
		_mCharacter->injectKeyUp(evt);
}

void BtooomManager::update_KeyDown(const OIS::KeyEvent& evt)
{
	if(_mCharacter)
		_mCharacter->injectKeyDown(evt);
}

int BtooomManager::update(float interval)
{
	if(_mBCharacter)
		if(!_mCharacter->_mAlive)
		{
			_mCharacter->_mAlive = true;
			return -1;//Êä
		}
		else
			_mCharacter->updateCharacter(interval);

	if(!_mBEnemy1||!_mEnemy1->_mAlive)
		if(!_mBEnemy2||!_mEnemy2->_mAlive)
			if(!_mBEnemy3||!_mEnemy3->_mAlive)
			{
				_mEnemy1->_mAlive = true;
				_mEnemy2->_mAlive = true;
				_mEnemy3->_mAlive = true;
				return 1;//Ó®
			}
	if(_mBEnemy1)
		_mEnemy1->updateEnemy(interval);
	if(_mBEnemy2)
		_mEnemy2->updateEnemy(interval);
	if(_mBEnemy3)
		_mEnemy3->updateEnemy(interval);
	return 0;

}
