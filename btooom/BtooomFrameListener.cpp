#include "BtooomFrameListener.h"
#include "CollisionsBox.h"

bool BtooomFrameListener::frameStarted(const FrameEvent &evt)
{
//	_msoundMgr->FrameStarted(_mcamNode,evt.timeSinceLastFrame);
	return ExampleFrameListener::frameStarted(evt);
}

bool BtooomFrameListener::frameEnded(const FrameEvent &evt)
{
	ExampleFrameListener::frameEnded(evt);
	if(_mStart)
	{
		if(pSysStart->getState() ==ParticleUniverse::ParticleSystem::ParticleSystemState::PSS_STOPPED)
			if(_mManager)
			{
				int result = _mManager->update(evt.timeSinceLastFrame);
				if(result == 1)
				{
					pSysWin->start(2.7);
					_mStart = false;
					_mWin = true;
				}
				if(result == -1)
				{
					pSysLose->start(2.7);
					_mStart = false;
					_mLose = true;
				}
			}
/*		if(_mBCharacter)
		{
			Vector3 temp = _mSceneMgr->getSceneNode("Character")->getPosition();
			mCamera->setPosition(temp.x,500,temp.z+500);
		}*/
	}
	else if(_mWin)
	{
		if(pSysWin->getState() ==ParticleUniverse::ParticleSystem::ParticleSystemState::PSS_STOPPED)
		{
			_mWin = false;

			for(int i = 0;i<15;i++)
				for(int j =0;j<15;j++)
				{
					_mValueDanger[i][j] = 0;
					_mValueInterest[i][j] = 0;
				}

	/*		for(int i = 1;i<15;i +=2)
				for(int j = 1;j<15;j +=2)
				{
					if(i==7&&j==7)
						continue;			
					_mValueMap[i][j] = 1;
				}*/

			CEGUI::WindowManager::getSingleton().destroyWindow("Bomb");
			CEGUI::WindowManager::getSingleton().destroyWindow("Speed");
			CEGUI::WindowManager::getSingleton().destroyWindow("Power");

			CEGUI::Window *myImageWindow = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","PrettyWindow" );//开始界面
			myImageWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
			CEGUI::ImagesetManager::getSingleton().createFromImageFile("imagesets", "jiemian.jpg");
			myImageWindow->setProperty("Image","set:imagesets image:full_image");
			_mInterface->mEditorGuiSheet->addChildWindow(myImageWindow);
			myImageWindow->setSize(CEGUI::UVector2(cegui_reldim(1.0f), cegui_reldim(1.0f)));
			myImageWindow->disable();

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
		}
	}
	else if(_mLose)
	{
		if(pSysLose->getState() ==ParticleUniverse::ParticleSystem::ParticleSystemState::PSS_STOPPED)
		{
			_mLose = false;

			for(int i = 0;i<15;i++)
				for(int j =0;j<15;j++)
				{
					_mValueDanger[i][j] = 0;
					_mValueInterest[i][j] = 0;
				}

	/*		for(int i = 1;i<15;i +=2)
				for(int j = 1;j<15;j +=2)
				{
					if(i==7&&j==7)
						continue;			
					_mValueMap[i][j] = 1;
				}*/

			CEGUI::WindowManager::getSingleton().destroyWindow("Bomb");
			CEGUI::WindowManager::getSingleton().destroyWindow("Speed");
			CEGUI::WindowManager::getSingleton().destroyWindow("Power");

			CEGUI::Window *myImageWindow = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","PrettyWindow" );//开始界面
			myImageWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
			CEGUI::ImagesetManager::getSingleton().createFromImageFile("imagesets", "jiemian.jpg");
			myImageWindow->setProperty("Image","set:imagesets image:full_image");
			_mInterface->mEditorGuiSheet->addChildWindow(myImageWindow);
			myImageWindow->setSize(CEGUI::UVector2(cegui_reldim(1.0f), cegui_reldim(1.0f)));
			myImageWindow->disable();

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
		}
	}
	return !_mExit;
}

bool BtooomFrameListener::keyPressed(const OIS::KeyEvent &arg)
{
	if(_mStart)
		_mManager->update_KeyDown(arg);
	return true;
}

bool BtooomFrameListener::keyReleased(const OIS::KeyEvent &arg)
{
	if(_mStart)
		_mManager->update_KeyUp(arg);
	if(arg.key==OIS::KC_ESCAPE||arg.key==OIS::KC_Q)
		_mExit=true;
	return true;
}

bool BtooomFrameListener::mouseMoved(const OIS::MouseEvent &evt)
{ 
	CEGUI::System::getSingleton().injectMouseMove(evt.state.X.rel,evt.state.Y.rel); 
	return true; 
} 


bool BtooomFrameListener::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) 
{ 
	CEGUI::System::getSingleton().injectMouseButtonDown(convertOgreButtonToCegui(id)); 
	return true; 
} 

bool BtooomFrameListener::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id ) 
{
	CEGUI::System::getSingleton().injectMouseButtonUp(convertOgreButtonToCegui(id)); 
	return true; 
} 

bool BtooomFrameListener::handleQuit(const CEGUI::EventArgs& e)
{
	_mExit = true;
    return true;
}

bool BtooomFrameListener::handleStart(const CEGUI::EventArgs& e)
{
	CEGUI::WindowManager::getSingleton().getWindow("PrettyWindow")->setEnabled(false);
	CEGUI::WindowManager::getSingleton().getWindow("Start")->setEnabled(false);
	CEGUI::WindowManager::getSingleton().getWindow("Quit")->setEnabled(false);
	CEGUI::WindowManager::getSingleton().getWindow("About")->setEnabled(false);

	CEGUI::Window *myImageWindow2 = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","PrettyWindow2" );//开始界面
	myImageWindow2->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
	CEGUI::ImagesetManager::getSingleton().destroy("imagesets");
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("imagesets", "jiemian2.jpg");
	myImageWindow2->setProperty("Image","set:imagesets image:full_image");
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(myImageWindow2);
	myImageWindow2->setSize(CEGUI::UVector2(cegui_reldim(1.0f), cegui_reldim(1.0f)));
	myImageWindow2->disable();

	CEGUI::PushButton* level1Btn=(CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button",(CEGUI::utf8*)"Level1");
	level1Btn->setPosition(CEGUI::UVector2(cegui_reldim(0.2f), cegui_reldim(0.2f)));
	level1Btn->setText("LEVEL1");
	level1Btn->setSize(CEGUI::UVector2(cegui_reldim(0.25f), cegui_reldim(0.1f)));
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(level1Btn);
	level1Btn->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BtooomFrameListener::handleLevel1, this));

	CEGUI::PushButton* level2Btn=(CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button",(CEGUI::utf8*)"Level2");
	level2Btn->setPosition(CEGUI::UVector2(cegui_reldim(0.55f), cegui_reldim(0.2f)));
	level2Btn->setSize(CEGUI::UVector2(cegui_reldim(0.25f), cegui_reldim(0.1f)));
	level2Btn->setText("LEVEL2");
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(level2Btn);
	level2Btn->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BtooomFrameListener::handleLevel2, this));

	CEGUI::PushButton* level3Btn=(CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button",(CEGUI::utf8*)"Level3");
	level3Btn->setPosition(CEGUI::UVector2(cegui_reldim(0.2f), cegui_reldim(0.4f)));
	level3Btn->setSize(CEGUI::UVector2(cegui_reldim(0.25f), cegui_reldim(0.1f)));
	level3Btn->setText("LEVEL3");
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(level3Btn);
	level3Btn->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BtooomFrameListener::handleLevel3, this));

	CEGUI::PushButton* inputBtn=(CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button",(CEGUI::utf8*)"Input");
	inputBtn->setPosition(CEGUI::UVector2(cegui_reldim(0.55f), cegui_reldim(0.4f)));
	inputBtn->setSize(CEGUI::UVector2(cegui_reldim(0.25f), cegui_reldim(0.1f)));
	inputBtn->setText("INPUT");
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(inputBtn);
	inputBtn->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BtooomFrameListener::handleInput, this));

	CEGUI::PushButton* playBtn=(CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button",(CEGUI::utf8*)"Play");
	playBtn->setPosition(CEGUI::UVector2(cegui_reldim(0.375f), cegui_reldim(0.6f)));
	playBtn->setSize(CEGUI::UVector2(cegui_reldim(0.25f), cegui_reldim(0.1f)));
	playBtn->setText("PLAY");
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(playBtn);
	playBtn->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BtooomFrameListener::handlePlay, this));

	CEGUI::PushButton* returnBtn=(CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button",(CEGUI::utf8*)"Return");
	returnBtn->setPosition(CEGUI::UVector2(cegui_reldim(0.7f), cegui_reldim(0.8f)));
	returnBtn->setSize(CEGUI::UVector2(cegui_reldim(0.25f), cegui_reldim(0.1f)));
	returnBtn->setText("RETURN");
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(returnBtn);
	returnBtn->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BtooomFrameListener::handleReturn, this));

//	_mStart = true;

    return true;
}

bool BtooomFrameListener::handleCloseAbout(const CEGUI::EventArgs& e)
{
	CEGUI::WindowManager::getSingleton().destroyWindow("AboutDialog");

	CEGUI::WindowManager::getSingleton().getWindow("Start")->setEnabled(true);
	CEGUI::WindowManager::getSingleton().getWindow("Quit")->setEnabled(true);
	CEGUI::WindowManager::getSingleton().getWindow("About")->setEnabled(true);

	return true;
}

bool BtooomFrameListener::handleAbout(const CEGUI::EventArgs& e)
{
	CEGUI::DefaultWindow* temp = (CEGUI::DefaultWindow*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticText","AboutDialog");
	temp->setPosition(CEGUI::UVector2(cegui_reldim(0.0f), cegui_reldim(0.0f)));
	temp->setSize(CEGUI::UVector2(cegui_reldim(0.5f), cegui_reldim(0.5f)));
	
	temp->setHorizontalAlignment(CEGUI::HorizontalAlignment::HA_CENTRE);
	temp->setVerticalAlignment(CEGUI::VerticalAlignment::VA_CENTRE);
	temp->setText("                    BombMan\n                    Staff\n                     ShenYizhu");
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(temp);


	CEGUI::PushButton* okBtn=(CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button",(CEGUI::utf8*)"ok");
	okBtn->setPosition(CEGUI::UVector2(cegui_reldim(0.4f), cegui_reldim(0.85f)));
	okBtn->setSize(CEGUI::UVector2(cegui_reldim(0.2f), cegui_reldim(0.1f)));
	okBtn->setText("OK");
	temp->addChildWindow(okBtn);
	okBtn->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BtooomFrameListener::handleCloseAbout, this));

	CEGUI::WindowManager::getSingleton().getWindow("Start")->setEnabled(false);
	CEGUI::WindowManager::getSingleton().getWindow("Quit")->setEnabled(false);
	CEGUI::WindowManager::getSingleton().getWindow("About")->setEnabled(false);

	return true;
}

	
//	CEGUI::Font& mfont = CEGUI::FontManager::getSingleton().createFreeTypeFont("simsunb",10,true,"simsunb.ttf");
//	CEGUI::String str = (CEGUI::utf8*)Ogre::UTFString(L"你好，我的朋友！我是可爱的有着绿色环保肤色的Ogre先生，有什么可以帮忙的吗？").asUTF8_c_str();
//	temp->setText(str);

bool BtooomFrameListener::handleLevel1(const CEGUI::EventArgs& e)
{
	_mLevel1 = true;
	_mLevel2 =false;
	_mLevel3 = false;
	_mInput = false;
	_mBCharacter = true;
	_mBEnemy1 = true;
	_mBEnemy2 = true;
	_mBEnemy3 = true;
	CEGUI::WindowManager::getSingleton().getWindow("Level1")->setEnabled(false);
	CEGUI::WindowManager::getSingleton().getWindow("Level2")->setEnabled(true);
	CEGUI::WindowManager::getSingleton().getWindow("Level3")->setEnabled(true);
	CEGUI::WindowManager::getSingleton().getWindow("Input")->setEnabled(true);
	Read("Map1.xml");

	return true;
}

bool BtooomFrameListener::handleLevel2(const CEGUI::EventArgs& e)
{
	_mLevel1 = false;
	_mLevel2 =true;
	_mLevel3 = false;
	_mInput = false;
	_mBCharacter = true;
	_mBEnemy1 = true;
	_mBEnemy2 = true;
	_mBEnemy3 = false;
	CEGUI::WindowManager::getSingleton().getWindow("Level1")->setEnabled(true);
	CEGUI::WindowManager::getSingleton().getWindow("Level2")->setEnabled(false);
	CEGUI::WindowManager::getSingleton().getWindow("Level3")->setEnabled(true);
	CEGUI::WindowManager::getSingleton().getWindow("Input")->setEnabled(true);
	Read("Map2.xml");
	return true;
}

bool BtooomFrameListener::handleLevel3(const CEGUI::EventArgs& e)
{
	_mLevel1 = false;
	_mLevel2 =false;
	_mLevel3 = true;
	_mInput = false;
	_mBCharacter = true;
	_mBEnemy1 = true;
	_mBEnemy2 = true;
	_mBEnemy3 = true;
	CEGUI::WindowManager::getSingleton().getWindow("Level1")->setEnabled(true);
	CEGUI::WindowManager::getSingleton().getWindow("Level2")->setEnabled(true);
	CEGUI::WindowManager::getSingleton().getWindow("Level3")->setEnabled(false);
	CEGUI::WindowManager::getSingleton().getWindow("Input")->setEnabled(true);
	Read("Map3.xml");
	return true;
}

bool BtooomFrameListener::handleInput(const CEGUI::EventArgs& e)
{
	_mLevel1 = false;
	_mLevel2 =false;
	_mLevel3 = false;
	_mInput = true;
	_mBCharacter = true;
	_mBEnemy1 = true;
	_mBEnemy2 = true;
	_mBEnemy3 = true;
	CEGUI::WindowManager::getSingleton().getWindow("Level1")->setEnabled(true);
	CEGUI::WindowManager::getSingleton().getWindow("Level2")->setEnabled(true);
	CEGUI::WindowManager::getSingleton().getWindow("Level3")->setEnabled(true);
	CEGUI::WindowManager::getSingleton().getWindow("Input")->setEnabled(false);
	Read("Map7.xml");

	return true;
}

bool BtooomFrameListener::handlePlay(const CEGUI::EventArgs& e)
{
	if(_mLevel1||_mLevel2||_mLevel3||_mInput)
		_mStart = true;
	_mManager = _mManagerP;

	_mManager->_mCharacter->setupPosition(_mPosCh);
	_mManager->_mEnemy1->setupPosition(_mPosE1);
	_mManager->_mEnemy2->setupPosition(_mPosE2);
	_mManager->_mEnemy3->setupPosition(_mPosE3);
	_mManager->_mWallMgr->setupWall();

	if(!_mBCharacter)
		_mSceneMgr->getSceneNode("Character")->setVisible(false);
	else
		_mSceneMgr->getSceneNode("Character")->setVisible(true);
	if(!_mBEnemy1)
		_mSceneMgr->getSceneNode("Enemy1")->setVisible(false);
	else
		_mSceneMgr->getSceneNode("Enemy1")->setVisible(true);
	if(!_mBEnemy2)
		_mSceneMgr->getSceneNode("Enemy2")->setVisible(false);
	else
		_mSceneMgr->getSceneNode("Enemy1")->setVisible(true);
	if(!_mBEnemy3)
		_mSceneMgr->getSceneNode("Enemy3")->setVisible(false);
	else
		_mSceneMgr->getSceneNode("Enemy1")->setVisible(true);

	pSysStart->start(2.7);

	CEGUI::DefaultWindow* temp = (CEGUI::DefaultWindow*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticText","Bomb");
	temp->setPosition(CEGUI::UVector2(cegui_reldim(0.125f), cegui_reldim(0.92f)));
	temp->setSize(CEGUI::UVector2(cegui_reldim(0.15f), cegui_reldim(0.05f)));
	temp->setText("Bomb : "+Ogre::StringConverter::toString(_mManager->_mCharacter->_mBombNumber));
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(temp);

	temp = (CEGUI::DefaultWindow*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticText","Speed");
	temp->setPosition(CEGUI::UVector2(cegui_reldim(0.425f), cegui_reldim(0.92f)));
	temp->setSize(CEGUI::UVector2(cegui_reldim(0.15f), cegui_reldim(0.05f)));
	temp->setText("Speed : "+Ogre::StringConverter::toString(int((_mManager->_mCharacter->_mWalkSpeed-75)/37.5)));
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(temp);

	temp = (CEGUI::DefaultWindow*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticText","Power");
	temp->setPosition(CEGUI::UVector2(cegui_reldim(0.725f), cegui_reldim(0.92f)));
	temp->setSize(CEGUI::UVector2(cegui_reldim(0.15f), cegui_reldim(0.05f)));
	temp->setText("Power : "+Ogre::StringConverter::toString(_mManager->_mCharacter->_mBombList->_mPower));
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(temp);

	CEGUI::WindowManager::getSingleton().destroyWindow("Start");
	CEGUI::WindowManager::getSingleton().destroyWindow("Quit");
	CEGUI::WindowManager::getSingleton().destroyWindow("About");
	CEGUI::WindowManager::getSingleton().destroyWindow("PrettyWindow");
	CEGUI::WindowManager::getSingleton().destroyWindow("Level1");
	CEGUI::WindowManager::getSingleton().destroyWindow("Level2");
	CEGUI::WindowManager::getSingleton().destroyWindow("Level3");
	CEGUI::WindowManager::getSingleton().destroyWindow("Input");
	CEGUI::WindowManager::getSingleton().destroyWindow("Return");
	CEGUI::WindowManager::getSingleton().destroyWindow("Play");
	CEGUI::WindowManager::getSingleton().destroyWindow("PrettyWindow2");

	return true;
}

bool BtooomFrameListener::handleReturn(const CEGUI::EventArgs& e)
{
	CEGUI::WindowManager::getSingleton().destroyWindow("Level1");
	CEGUI::WindowManager::getSingleton().destroyWindow("Level2");
	CEGUI::WindowManager::getSingleton().destroyWindow("Level3");
	CEGUI::WindowManager::getSingleton().destroyWindow("Input");
	CEGUI::WindowManager::getSingleton().destroyWindow("Return");
	CEGUI::WindowManager::getSingleton().destroyWindow("Play");
	CEGUI::WindowManager::getSingleton().destroyWindow("PrettyWindow2");

	CEGUI::ImagesetManager::getSingleton().destroy("imagesets");
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("imagesets", "jiemian.jpg");
	CEGUI::WindowManager::getSingleton().getWindow("PrettyWindow")->setProperty("Image","set:imagesets image:full_image");
	CEGUI::WindowManager::getSingleton().getWindow("PrettyWindow")->setEnabled(true);
	CEGUI::WindowManager::getSingleton().getWindow("Start")->setEnabled(true);
	CEGUI::WindowManager::getSingleton().getWindow("Quit")->setEnabled(true);
	CEGUI::WindowManager::getSingleton().getWindow("About")->setEnabled(true);

	return true;
}
using namespace rapidxml;

void BtooomFrameListener::Read(char* name)
{
	 file<> fdoc(name);
     xml_document<>  doc;    
     doc.parse<0>(fdoc.data()); 
     
     //! 获取根节点
     xml_node<>* root = doc.first_node();

     //! 获取根节点第一个节点preview
     xml_node<>* preview = root->first_node();

	 //! 获取preview节点第一个节点Playerposition
     xml_node<>* Playerposition = preview->first_node();
	 xml_attribute<char> * attr1 = Playerposition->first_attribute("X");  
	 char *playerX=attr1->value();   //玩家的X坐标
	 _mPosCh.z = atoi(playerX)*75-525;
	 xml_attribute<char> * attr2 = Playerposition->last_attribute("Y");  
	 char *playerY=attr2->value();   //玩家的Y坐标
	 _mPosCh.x = atoi(playerY)*75-525;

	  //! 获取preview节点第二个节点enemy
	 xml_node<>* enemy = Playerposition->next_sibling(); 
	 xml_node<>* enemy1 = enemy->first_node();   //第一种敌人
	 xml_attribute<char> * cate1 = enemy1->first_attribute("category");
	 xml_attribute<char> * count1 = cate1->next_attribute("count");
	 char*temp1 = count1->value();
	 int tempp1 = atoi(temp1);
	 if(tempp1==0)
	 {
		 _mBEnemy1 = false;
	 }

	 for(xml_node<char> * node = enemy1->first_node("enemy1Position"); node != NULL; node = node->next_sibling())
	 {
		 xml_attribute<char> * attr1 = node->first_attribute("id");
		 char *enemy1ID=attr1->value();  //enemy1的ID
		 xml_attribute<char> * attr2 = attr1->next_attribute("X");
		 char *enemy1X=attr2->value();   //敌人的X坐标
	     _mPosE1.z = atoi(enemy1X)*75-525;
		 xml_attribute<char> * attr3 = attr2->next_attribute("Y");
		 char *enemy1Y=attr3->value();    //敌人的Y坐标
	     _mPosE1.x = atoi(enemy1Y)*75-525;
	 }
	 xml_node<>* enemy2 = enemy1->next_sibling();   //第二种敌人
	 xml_attribute<char> * cate2 = enemy2->first_attribute("category");
	 xml_attribute<char> * count2 = cate2->next_attribute("count");
	 char*temp2 = count2->value();
	 int tempp2 = atoi(temp2);
	 if(tempp2==0)
	 {
		 _mBEnemy2 = false;
	 }
	 for(xml_node<char> * node = enemy2->first_node("enemy2Position"); node != NULL; node = node->next_sibling())
	 {
		 xml_attribute<char> * attr1 = node->first_attribute("id");
		 char *enemy2ID=attr1->value();  //enemy2的ID
		 xml_attribute<char> * attr2 = attr1->next_attribute("X");
		 char *enemy2X=attr2->value();   //敌人的X坐标
	     _mPosE2.z = atoi(enemy2X)*75-525;
		 xml_attribute<char> * attr3 = attr2->next_attribute("Y");
		 char *enemy2Y=attr3->value();    //敌人的Y坐标
	     _mPosE2.x = atoi(enemy2Y)*75-525;
	 }
	 xml_node<>* enemy3 = enemy2->next_sibling();   //第三种敌人
	 xml_attribute<char> * cate3 = enemy3->first_attribute("category");
	 xml_attribute<char> * count3 = cate3->next_attribute("count");
	 char*temp3 = count3->value();
	 int tempp3 = atoi(temp3);
	 if(tempp3==0)
	 {
		 _mBEnemy3 = false;
	 }
	 for(xml_node<char> * node = enemy3->first_node("enemy3Position"); node != NULL; node = node->next_sibling())
	 {
		 xml_attribute<char> * attr1 = node->first_attribute("id");
		 char *enemy3ID=attr1->value();  //enemy3的ID
		 xml_attribute<char> * attr2 = attr1->next_attribute("X");
		 char *enemy3X=attr2->value();   //敌人的X坐标
	     _mPosE3.z = atoi(enemy3X)*75-525;
		 xml_attribute<char> * attr3 = attr2->next_attribute("Y");
		 char *enemy3Y=attr3->value();    //敌人的Y坐标
	     _mPosE3.x = atoi(enemy3Y)*75-525;
	 }
	  //! 获取preview节点第三个节点cellPosition
	 xml_node<>* cellPosition = enemy->next_sibling(); 
	 for(xml_node<char> * node = cellPosition->first_node(); node != NULL; node = node->next_sibling())
	 {
		 xml_attribute<char> * attr1 = node->first_attribute("X");
		 char *CellX=attr1->value();   //X坐标
	     int x = atoi(CellX);
		 xml_attribute<char> * attr2 = attr1->next_attribute("Y");
		 char *CellY=attr2->value();    //Y坐标
	     int y = atoi(CellY);
		 if(strcmp( node->name(), "grassCellPos" )==0)
		 {
			 _mValueMap[x][y] = 0;
		 }
		 if(strcmp( node->name(), "softCellPos" )==0)
		 {
			 _mValueMap[x][y] = 1;
		 }
		 if(strcmp( node->name(), "hardCellPos")==0)
		 {
			 _mValueMap[x][y] = 2;
		 }
		 if(strcmp( node->name(), "iceCellPos")==0)
		 {
			 _mValueMap[x][y] = -1;
		 }
	 }
}