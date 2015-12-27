#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Ogre.h"
#include "OIS.h"
#include "BombManager.h"
#include <stack>
#include <queue>
#include "ParticleUniverseSystemManager.h"

using namespace Ogre;

#define NUM_ANIMS 2             // ������
#define CHAR_HEIGHT 50          // �߶�
#define ANIM_FADE_SPEED 7.5f    // �����ٶ�
#define MAX_BOMB_NUMBER 3       // ���ը����
#define MAX_SPEED 225.0f        //�����·�ٶ�
#define MAX_POWER 3             //���ը������

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

	int _mBombCurNumber;              //��ǰը������
	BombManager* _mBombList;          //��ϻ
	bool _mAlive;                     //����û

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
	Entity* _mEnt;                          //����
	SceneNode* _mSn;                        //������
	StateID _mState;                        //��ǰ״̬
	ParticleUniverse::ParticleSystem* pSysbomb;
	ParticleUniverse::ParticleSystem* pSysspeed;
	ParticleUniverse::ParticleSystem* pSysnum;

	Vector3 _mLastdir;                      //��ǰ����
	float _mWalkSpeed;                      //��ǰ�ٶ�
	float _mMeterPerS;                      //��һ����Ҫ��ʱ��

	int _mBombNumber;                       //�ɷ���ը������
	int _mTempNum;                          //�Ǹ�

	bool _mIsColliside;                     //��ǰ�Ƿ�����ײ

	Vector3 _mDirPos;                       //Ŀ��λ��
	Vector2 _mCurPos2D;                     //ƽ�棨0-15��

	int _mFootValue[15][15];                //Ѱ·������ֵ
	std::stack<Vector2> _mFootValueStep;    //Ѱ·������ջ
	std::queue<WalkStateID> _mFootWay;      //·������

	bool _mIsFinish;                        //�Ƿ�����һ������
	float _mLastTime;                       //���в�ʱ
	bool _mIsStop;                          //�Ƿ�վ��
	float _mStopTime;                       //�ȴ�ʱ��
	
	AnimationState*   _mAnimationState[NUM_ANIMS];
	Bone* _manuallyControlledBone;
	bool _mFadingIn[NUM_ANIMS]; 
	bool _mFadingOut[NUM_ANIMS];
};

#endif