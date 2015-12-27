#ifndef __Bomb_H__
#define __Bomb_H__

#include "Ogre.h"
#include "Bonus.h"
#include <stack>
#include "SoundManager.h"

using namespace Ogre;

#define FADETIME 0.5

class Bomb
{
public:
	enum State
	{
		Alive,
		Run,
		Dead
	};

public:
	Bomb(SceneManager* sm,Bonus* bonus,int num,String ID):_mSceneMgr(sm),_mBonus(bonus),_mID(ID)
	{
		_mState=Dead;
		if(!sm->hasEntity("Bomb"+_mID+Ogre::StringConverter::toString(num)))
			_mEnt=sm->createEntity("Bomb"+_mID+Ogre::StringConverter::toString(num),"bomb.mesh");
		else
			_mEnt=sm->getEntity("Bomb"+_mID+Ogre::StringConverter::toString(num));
		_mEnt->setVisible(false);
		_mCheck = false;
		_mChecknum = "";
		_mPower = 1;
		_mIsFade = false;
		_mFadeTime = 0;

		 //����Ƶ������ʼֵΪ��
	}
	~Bomb(void);
	 
	void Start(SceneNode* sn);                              //��ʼ
	void Find();                                            //��ʼ��Ѱ����������ը��

	void upadteValueInt(int value);                         //����int
	void updateValueDan(float time = 0);                    //����dan
	void updateRealtime(float time, String check);          //������ʵʱ��
	bool update(float interval);                            //ը������

	void ClearValueDan();                                   //��ը�����ʱ��
	void Explode(int power);                                //��ը
	void Play(Vector3 pos);                                            //��ը����
	void DestoryWall(String name);                          //�ƻ�ǽ
	void DestoryBomb(String name);                          //����
	void DestoryPlayer(String name);                        //�Լ�����
	void DestoryEnemy(String name);                         //��������

public:
	SceneNode* _mSn;
	State _mState;                                          //����״̬
	bool _mCheck;                                           //������ը���Ƿ��Ѽ�⵽
	String _mChecknum;                                      //��������ʱ�Ƿ��Ѽ��
	float time;                                             //����ĵ���ʱ
	float Realtime;                                         //�������������ʵ����ʱ
	int _mPower;                                            //����
	String _mID;                                            //����������һ��id
	bool _mIsFade;                                          //����Ч
	float _mFadeTime;                                       //����Ч��ʱ��
	std::stack<String> _mStack;                             //��Ч�ĵط�

private:
	SceneManager* _mSceneMgr;
	Entity* _mEnt;	
	Bonus* _mBonus;
	int qplSoundIndex;
	int qplSoundChannel;
};

#endif
