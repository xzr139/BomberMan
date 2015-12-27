#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Ogre.h"
#include "OIS.h"
#include "BombManager.h"
#include <stack>
#include <queue>
#include "ParticleUniverseSystemManager.h"

using namespace Ogre;

#define NUM_ANIMS 2             // 动画数
#define CHAR_HEIGHT 50          // 高度
#define ANIM_FADE_SPEED 7.5f    // 动画速度
#define MAX_BOMB_NUMBER 3       // 最大炸弹数
#define MAX_SPEED 225.0f        //最大走路速度
#define MAX_POWER 3             //最大炸弹威力

class Enemy
{
private:
	enum StateID
	{
		Idle,
		Walk
	};

	enum WalkStateID
	{
		Left,
		Right,
		Up,
		Down
	};

public:
	Enemy(SceneManager* sm, String ID):_mID(ID),_mSceneMgr(sm)
	{
		setupBody(sm);
		setupAnimations();
		setupParticle();
//		setupBomb(sm);
	//	setupSpeed();
//		setupTime();
	//	setupMap();
//		Deceide();
	};
	virtual ~Enemy(void)
	{
	};
	void updateEnemy(float deltaTime);
	void setupPosition(Vector3 pos);

	int _mBombCurNumber;              //当前炸弹数量
	BombManager* _mBombList;          //弹匣
	bool _mAlive;                     //死了没

private:
	void setupBody(SceneManager* sceneMgr);
	void setupAnimations();
	void setupBomb(SceneManager* sceneMgr);
	void setupSpeed();
	void setupParticle();
	void setupBaseAnimation(StateID id, bool reset = false);
	void setupMap();
	void setupTime();
	
	void updateBody(float interval);
	void Turn(WalkStateID dir);
	void Stop(float time);
	void PutBomb();
	void updateTime(float interval);
	void updateBomb(float interval);
	void updateAnimations(float interval);
	void fadeAnimations(float interval);

	void updatePosition();

	void checkcollision();
	bool checkBombs(Ogre::String name);
	bool checkBouns(Ogre::String name);
	bool checkWalls(Ogre::String name);

	void updateValueInt(Vector3 pos,int value);

	bool Deceide();
	void CaculateDir();
	bool FindPath();
	int SetValue(int i);
	bool GetValue(Vector2 pos,int i);
	void ClearStackQueue();

	bool OnTheWall(int x ,int y);
	float IsSafe();
	bool GoTemp();

	Vector2 To2D(Vector3 pos);
	Vector3 To3D(int x,int y);

private:
	SceneManager* _mSceneMgr;
	String _mID;
	Entity* _mEnt;                          //物体
	SceneNode* _mSn;                        //场景点
	StateID _mState;                        //当前状态
	ParticleUniverse::ParticleSystem* pSysbomb;
	ParticleUniverse::ParticleSystem* pSysspeed;
	ParticleUniverse::ParticleSystem* pSysnum;

	Vector3 _mLastdir;                      //当前朝向
	float _mWalkSpeed;                      //当前速度
	float _mMeterPerS;                      //走一格需要的时间

	int _mBombNumber;                       //可放置炸弹数量
	int _mTempNum;                          //那个

	bool _mIsColliside;                     //当前是否已碰撞

	Vector3 _mDirPos;                       //目标位置
	Vector2 _mCurPos2D;                     //平面（0-15）

	int _mFootValue[15][15];                //寻路径所用值
	std::stack<Vector2> _mFootValueStep;    //寻路径所用栈
	std::queue<WalkStateID> _mFootWay;      //路径队列

	bool _mIsFinish;                        //是否走完一个动作
	float _mLastTime;                       //步行补时
	bool _mIsStop;                          //是否站着
	float _mStopTime;                       //等待时间
	
	AnimationState*   _mAnimationState[NUM_ANIMS];
	Bone* _manuallyControlledBone;
	bool _mFadingIn[NUM_ANIMS]; 
	bool _mFadingOut[NUM_ANIMS];
};

#endif