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

		 //播放频道，初始值为空
	}
	~Bomb(void);
	 
	void Start(SceneNode* sn);                              //开始
	void Find();                                            //开始后寻找能连爆的炸弹

	void upadteValueInt(int value);                         //更新int
	void updateValueDan(float time = 0);                    //更新dan
	void updateRealtime(float time, String check);          //更新真实时间
	bool update(float interval);                            //炸弹运行

	void ClearValueDan();                                   //爆炸后清除时间
	void Explode(int power);                                //爆炸
	void Play(Vector3 pos);                                            //爆炸动画
	void DestoryWall(String name);                          //破坏墙
	void DestoryBomb(String name);                          //连爆
	void DestoryPlayer(String name);                        //自己死了
	void DestoryEnemy(String name);                         //别人死了

public:
	SceneNode* _mSn;
	State _mState;                                          //三种状态
	bool _mCheck;                                           //连续爆炸中是否已检测到
	String _mChecknum;                                      //连续更新时是否已检测
	float time;                                             //本身的倒计时
	float Realtime;                                         //算上连爆后的真实倒计时
	int _mPower;                                            //威力
	String _mID;                                            //方便连爆的一个id
	bool _mIsFade;                                          //关特效
	float _mFadeTime;                                       //关特效的时间
	std::stack<String> _mStack;                             //特效的地方

private:
	SceneManager* _mSceneMgr;
	Entity* _mEnt;	
	Bonus* _mBonus;
	int qplSoundIndex;
	int qplSoundChannel;
};

#endif
