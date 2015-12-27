#ifndef __Character_H__
#define __Character_H__

#include "Ogre.h"
#include "OIS.h"
#include "BombManager.h"
#include "ParticleUniverseSystemManager.h"


using namespace Ogre;

#define NUM_ANIMS 2             // ������
#define CHAR_HEIGHT 50          // �߶�
#define ANIM_FADE_SPEED 7.5f    // �����ٶ�
#define MAX_BOMB_NUMBER 3       // ���ը����
#define MAX_SPEED 225.0f        //�����·�ٶ�
#define MAX_POWER 3             //���ը������


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
	int _mBombCurNumber;              //��ǰը������
	bool _mAlive;
	int _mBombNumber;                  //�ɷ���ը������  
	float _mWalkSpeed;                //��ǰ�ٶ�

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
	Entity* _mEnt;                    //����
	SceneNode* _mSn;                  //������
	StateID _mState;                  //��ǰ״̬
	ParticleUniverse::ParticleSystem* pSysbomb;
	ParticleUniverse::ParticleSystem* pSysspeed;
	ParticleUniverse::ParticleSystem* pSysnum;

	Vector3 _mDir;                    //���߷���
	Vector3 _mLastdir;                //��ǰ����

	bool _mIsLasting;                 //��ʱ�Ƿ����
	bool _mDirButtonPush;             //������Ƿ񱻰���
	float _mTimer;                    //�����Ӱ����ɿ�������ʱ��
	float _mLastTime;                 //���в�ʱ

	
	float _mMeterPerS;                //��һ����Ҫ��ʱ��

	

	bool _mIsColliside;               //��ǰ�Ƿ�����ײ

	AnimationState*   _mAnimationState[NUM_ANIMS];
	Bone* _manuallyControlledBone;
	bool _mFadingIn[NUM_ANIMS]; 
	bool _mFadingOut[NUM_ANIMS];
};

#endif
