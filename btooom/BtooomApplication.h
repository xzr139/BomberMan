#ifndef __BtooomApplication_H__
#define __BtooomApplication_H__

#include "ExampleApplication.h"
#include "BtooomFrameListener.h"
#include "SoundManager.h"

class BtooomApplication : public ExampleApplication
{
public:
    BtooomApplication()
    {
    }

    ~BtooomApplication() 
    {
	}

private:
	void chooseSceneManager(void);
	void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
	void createFrameListener(void);

	void loadResources(void)
 {
 // mLoadingBar.start(mWindow, 1, 1, 0.75);//加载工具条
  ResourceGroupManager::getSingleton().initialiseResourceGroup("Imagesets");//初始化Bootstrap资源（Bootstrap资源的目录在之前设置）
  ResourceGroupManager::getSingleton().initialiseResourceGroup("Layouts");
  ResourceGroupManager::getSingleton().initialiseResourceGroup("LookNFeel");
  ResourceGroupManager::getSingleton().initialiseResourceGroup("Schemes");
  ResourceGroupManager::getSingleton().initialiseResourceGroup("Fonts");

  _mInterface=new BtooomInterface();
  _mInterface->initialiseSample();
  mWindow->update();//更新窗口
  

  ResourceGroupManager::getSingleton().initialiseAllResourceGroups();//加载一般资源
 // mWindow->update();//加载后 到 画面出现时自动调用update
 // mLoadingBar.finish();//加载工具条
 }

private:
	BtooomInterface* _mInterface;
	BtooomManager* _mManager;

	int qplSoundIndex;
	int qplSoundChannel;
	SceneNode *soundNode; //声源位置

	int m_progressMeter;

};

#endif