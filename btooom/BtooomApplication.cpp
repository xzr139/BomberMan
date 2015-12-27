#include "BtooomApplication.h"
#include "CollisionsBox.h"
#include "ParticleUniverseSystemManager.h"
#include "fmod.h"



void BtooomApplication::chooseSceneManager(void)
{
	m_progressMeter = 0;
//	LoadingProgressListener listener(m_progressMeter);
//	ResourceGroupManager::getSingleton().addResourceGroupListener(&listener);
	mSceneMgr = mRoot->createSceneManager(ST_EXTERIOR_CLOSE);
	
	//ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void BtooomApplication::createScene(void)
{

//	_mInterface=new BtooomInterface();
//	_mInterface->initialiseSample();

	mSceneMgr->setAmbientLight(ColourValue(0.5f,0.5f,0.5f));
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	mSceneMgr->setShadowColour(ColourValue(0.5, 0.5, 0.5));
	mSceneMgr->setShadowTextureSize(1024);
	mSceneMgr->setShadowTextureCount(1);

	Light* light = mSceneMgr->createLight("Light1");
	light->setType(Light::LT_POINT);
	light->setPosition(Vector3(0, 150, 250));
	light->setDiffuseColour(1.0, 1.0, 1.0);
	light->setSpecularColour(1.0, 1.0, 1.0);

	Plane plane;
	plane.d = 1000;
	plane.normal = Vector3::NEGATIVE_UNIT_Y;
	mSceneMgr->setSkyPlane( true, plane, "Examples/CloudySky", 1500, 40, true, 1.5f, 150, 150  );
	pManager = ParticleUniverse::ParticleSystemManager::getSingletonPtr();
/*	Entity* _mEnt = mSceneMgr->createEntity("ggg", "win.mesh");
	SceneNode* n = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	n->attachObject(_mEnt);
	n->setScale(5,5,5);*/

	_mBCharacter = true;
	_mBEnemy1 = true;
	_mBEnemy2 = true;
	_mBEnemy3 = true;
	_mBombCh = NULL;
	_mBombE1 = NULL;
	_mBombE2 = NULL;
	_mBombE3 = NULL;
	_mNum = 0;

	_mPosCh = Vector3(0,0,0);  //Ҫ�����75
	_mPosE1 = Vector3(0,0,0);
	_mPosE2 = Vector3(0,0,0);
	_mPosE3 = Vector3(0,0,0);

	for(int i = 0;i<15;i++)
		for(int j =0;j<15;j++)
		{
			_mValueDanger[i][j] = 0;
			_mValueInterest[i][j] = 0;
		}

	for(int i = 1;i<15;i +=2)
		for(int j = 1;j<15;j +=2)
		{
			if(i==7&&j==7)
				continue;
			_mValueMap[i][j] = 2;
		}

	_mManager=new BtooomManager(mSceneMgr,_mBCharacter,_mBEnemy1,_mBEnemy2,_mBEnemy3);
	_mManagerP = _mManager;

	soundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	soundMgr=new SoundManager(); //�½�SoundMananger��
	soundMgr->Initialize();  //��ʼ���࣬�޷Ǿ��ǽ���fmodsystem��channel��Fmod��Init��
	qplSoundIndex=soundMgr->CreateLoopedSound(Ogre::String("BGM.mp3")); //��������
	qplSoundChannel=INVALID_SOUND_CHANNEL; //����Ƶ������ʼֵΪ��
	soundMgr->PlaySound(qplSoundIndex,soundNode,&qplSoundChannel); //��������������������soundNode
     //��λ���ϣ������ղŵ�Ƶ����ֵ

    }

void BtooomApplication::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Vector3(0,700,900));
	mCamera->lookAt(Vector3(0,0,220));
}

void BtooomApplication::createViewports(void)
{
	Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(ColourValue(0,0,0));
	mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight())); 
}

void BtooomApplication::createFrameListener(void)
{
	mFrameListener = new BtooomFrameListener(mSceneMgr,mWindow, mCamera,_mInterface,true,true,true);
	mFrameListener->showDebugOverlay(true);
	mRoot->addFrameListener(mFrameListener);
}

