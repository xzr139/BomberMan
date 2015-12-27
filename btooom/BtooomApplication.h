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
 // mLoadingBar.start(mWindow, 1, 1, 0.75);//���ع�����
  ResourceGroupManager::getSingleton().initialiseResourceGroup("Imagesets");//��ʼ��Bootstrap��Դ��Bootstrap��Դ��Ŀ¼��֮ǰ���ã�
  ResourceGroupManager::getSingleton().initialiseResourceGroup("Layouts");
  ResourceGroupManager::getSingleton().initialiseResourceGroup("LookNFeel");
  ResourceGroupManager::getSingleton().initialiseResourceGroup("Schemes");
  ResourceGroupManager::getSingleton().initialiseResourceGroup("Fonts");

  _mInterface=new BtooomInterface();
  _mInterface->initialiseSample();
  mWindow->update();//���´���
  

  ResourceGroupManager::getSingleton().initialiseAllResourceGroups();//����һ����Դ
 // mWindow->update();//���غ� �� �������ʱ�Զ�����update
 // mLoadingBar.finish();//���ع�����
 }

private:
	BtooomInterface* _mInterface;
	BtooomManager* _mManager;

	int qplSoundIndex;
	int qplSoundChannel;
	SceneNode *soundNode; //��Դλ��

	int m_progressMeter;

};

#endif