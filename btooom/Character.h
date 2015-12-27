#ifndef __Character_H__
#define __Character_H__

#include "Ogre.h"
#include "OIS.h"
#include "BombManager.h"
#include "ParticleUniverseSystemManager.h"


using namespace Ogre;

#define NUM_ANIMS 2             // 动画数
#define CHAR_HEIGHT 50          // 高度
#define ANIM_FADE_SPEED 7.5f    // 动画速度
#define MAX_BOMB_NUMBER 3       // 最大炸弹数
#define MAX_SPEED 225.0f        //最大走路速度
#define MAX_POWER 3             //最大炸弹威力


class Character
{
private:
	enum StateID
	{
		Idle,
		Walk
	};

public:
	Character(SceneManager* sm)
	{
		setupBody(sm);
		setupAnimations();
		setupParticle();
		
	};
	virtual ~Character(void)
	{
	};
	void updateCharacter(float deltaTime);
	void injectKeyDown(const OIS::KeyEvent& evt);
	void injectKeyUp(const OIS::KeyEvent& evt);
	void setupPosition(Vector3 pos);

	BombManager* _mBombList;
	int _mBombCurNumber;              //当前炸弹数量
	bool _mAlive;
	int _mBombNumber;                  //可放置炸弹数量  
	float _mWalkSpeed;                //当前速度

private:
	void setupBody(SceneManager* sceneMgr);
	void setupAnimations();
	void setupBomb(SceneManager* sceneMgr);
	void setupTime();
	void setupParticle();
	void setupSpeed();
	void setupBaseAnimation(StateID id, bool reset = false);

	void updateBody(float interval);
	void updateAnimations(float interval);
	void updateBomb(float interval);
	void updateTime(float interval);
	void fadeAnimations(float interval);

	void updatePosition();

	void checkcollision();
	bool checkBombs(Ogre::String name);
	bool checkBouns(Ogre::String name);
	bool checkWalls(Ogre::String name);

	void updateValueInt(Vector3 pos,int value);

private:
	SceneManager* _mSceneMgr;
	Entity* _mEnt;                    //物体
	SceneNode* _mSn;                  //场景点
	StateID _mState;                  //当前状态
	ParticleUniverse::ParticleSystem* pSysbomb;
	ParticleUniverse::ParticleSystem* pSysspeed;
	ParticleUniverse::ParticleSystem* pSysnum;

	Vector3 _mDir;                    //行走方向
	Vector3 _mLastdir;                //当前朝向

	bool _mIsLasting;                 //补时是否完成
	bool _mDirButtonPush;             //方向键是否被按下
	float _mTimer;                    //按键从按下松开经历的时间
	float _mLastTime;                 //步行补时

	
	float _mMeterPerS;                //走一格需要的时间

	

	bool _mIsColliside;               //当前是否已碰撞

	AnimationState*   _mAnimationState[NUM_ANIMS];
	Bone* _manuallyControlledBone;
	bool _mFadingIn[NUM_ANIMS]; 
	bool _mFadingOut[NUM_ANIMS];
};

#endif
