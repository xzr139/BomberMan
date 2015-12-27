#ifndef __BtooomFrameListener_H__
#define __BtooomFrameListener_H__

#include "exampleframelistener.h"
#include "BtooomManager.h"
#include "BtooomInterface.h"
#include "CEGUI.h"
#include "CollisionsBox.h"
#include "SoundManager.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

class BtooomFrameListener :
	public ExampleFrameListener,public OIS::KeyListener,public OIS::MouseListener
{
private:
	CEGUI::MouseButton convertOgreButtonToCegui(int buttonID) 
	{ 
		switch (buttonID) 
		{ 
		case OIS::MB_Left: 
			return CEGUI::LeftButton; 
		case OIS::MB_Right: 
			return CEGUI::RightButton; 
		case OIS::MB_Middle: 
			return CEGUI::MiddleButton; 
		default: 
			return CEGUI::LeftButton; 
		}
	}

public:
	BtooomFrameListener(SceneManager *mSceneMgr,RenderWindow* win,Camera* cam,BtooomInterface* inter,bool bufferedKeys,bool bufferedMouse,bool bufferedJoy):
	  ExampleFrameListener(win,cam,bufferedKeys,bufferedMouse,bufferedJoy),_mSceneMgr(mSceneMgr),_mInterface(inter)
	  {
		  mKeyboard->setEventCallback(this);
		  mMouse->setEventCallback(this);

		  CEGUI::PushButton* startBtn=(CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button",(CEGUI::utf8*)"Start");
		  startBtn->setPosition(CEGUI::UVector2(cegui_reldim(0.7f), cegui_reldim(0.4f)));
		  startBtn->setText("START");
		  startBtn->setSize(CEGUI::UVector2(cegui_reldim(0.25f), cegui_reldim(0.1f)));
		  _mInterface->mEditorGuiSheet->addChildWindow(startBtn);
		  startBtn->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BtooomFrameListener::handleStart, this));

		  CEGUI::PushButton* quitBtn=(CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button",(CEGUI::utf8*)"Quit");
		  quitBtn->setPosition(CEGUI::UVector2(cegui_reldim(0.7f), cegui_reldim(0.8f)));
		  quitBtn->setSize(CEGUI::UVector2(cegui_reldim(0.25f), cegui_reldim(0.1f)));
		  quitBtn->setText("QUIT");
		  _mInterface->mEditorGuiSheet->addChildWindow(quitBtn);
		  quitBtn->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BtooomFrameListener::handleQuit, this));

		  CEGUI::PushButton* aboutBtn=(CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button",(CEGUI::utf8*)"About");
		  aboutBtn->setPosition(CEGUI::UVector2(cegui_reldim(0.7f), cegui_reldim(0.6f)));
		  aboutBtn->setSize(CEGUI::UVector2(cegui_reldim(0.25f), cegui_reldim(0.1f)));
		  aboutBtn->setText("ABOUT");
		  _mInterface->mEditorGuiSheet->addChildWindow(aboutBtn);
		  aboutBtn->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BtooomFrameListener::handleAbout, this));

		  _mExit = false;
		  _mStart = false;
		  _mLevel1 = false;
		  _mLevel2 =false;
		  _mLevel3 = false;
		  _mInput = false;
		  _mLose = false;
		  _mWin = false;

		  pSysStart = pManager->createParticleSystem("start","start",_mSceneMgr);
		  SceneNode * temp= _mSceneMgr->getRootSceneNode()->createChildSceneNode();
		  temp->yaw(Radian::Radian(270));
		  temp->attachObject(pSysStart);
		  pSysStart->setScale(Vector3(25,25,25));
		  pSysWin = pManager->createParticleSystem("win","win",_mSceneMgr);
		  temp = _mSceneMgr->getRootSceneNode()->createChildSceneNode();
		  temp->yaw(Radian::Radian(270));
		  temp->attachObject(pSysWin);
		  pSysWin->setScale(Vector3(25,25,25));
		  pSysLose = pManager->createParticleSystem("lose","lose",_mSceneMgr);
		  temp = _mSceneMgr->getRootSceneNode()->createChildSceneNode();
		  temp->yaw(Radian::Radian(270));
		  temp->attachObject(pSysLose);
		  pSysLose->setScale(Vector3(25,25,25));
	  };
	  
	  virtual ~BtooomFrameListener(void)
	  {
	  };
private:
	  bool keyPressed(const OIS::KeyEvent &arg);
	  bool keyReleased(const OIS::KeyEvent &arg);

	  bool frameStarted(const FrameEvent &evt);
	  bool frameEnded(const FrameEvent &evt);

	  bool mouseMoved(const OIS::MouseEvent &evt);
	  bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	  bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id );

	  bool handleQuit(const CEGUI::EventArgs& e);
	  bool handleStart(const CEGUI::EventArgs& e);
	  bool handleAbout(const CEGUI::EventArgs& e);
	  bool handleCloseAbout(const CEGUI::EventArgs& e);
	  bool handleLevel1(const CEGUI::EventArgs& e);
	  bool handleLevel2(const CEGUI::EventArgs& e);
	  bool handleLevel3(const CEGUI::EventArgs& e);
	  bool handleInput(const CEGUI::EventArgs& e);
	  bool handlePlay(const CEGUI::EventArgs& e);
	  bool handleReturn(const CEGUI::EventArgs& e);

	  void Read(char* name);
private:
		bool _mExit;
		bool _mStart;
		bool _mWin;
		bool _mLose;
		bool _mLevel1;
		bool _mLevel2;
		bool _mLevel3;
		bool _mInput;
		SceneManager* _mSceneMgr; 
		BtooomManager* _mManager;
		BtooomInterface* _mInterface;


		ParticleUniverse::ParticleSystem* pSysStart;
		ParticleUniverse::ParticleSystem* pSysWin;
		ParticleUniverse::ParticleSystem* pSysLose;

};

#endif