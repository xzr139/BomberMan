#include "BtooomInterface.h"

using namespace CEGUI;

bool BtooomInterface::initialiseSample()
{
	//mGUIRenderer = &OgreRenderer::bootstrapSystem();
	//CEGUI::OgreRenderer::bootstrapSystem();
	mGUIRenderer=&CEGUI::OgreRenderer::bootstrapSystem();  

	SchemeManager::getSingleton().create("TaharezLook.scheme");//主题
	System::getSingleton().setDefaultMouseCursor("TaharezLook","MouseArrow");//鼠标
	CEGUI::Font& mfont = CEGUI::FontManager::getSingleton().createFreeTypeFont("TaharezLook",15,true,"DejaVuSans.ttf");
//	CEGUI::Font& mfont = CEGUI::FontManager::getSingleton().get("DejaVuSans-10");
//	mfont.setProperty("PointSize","15");
	System::getSingleton().setDefaultFont(&mfont); //字体
	
	mEditorGuiSheet =(CEGUI::Window*)WindowManager::getSingleton().createWindow("DefaultWindow","Sheet"); //主窗
	System::getSingleton().setGUISheet(mEditorGuiSheet); //设为主窗


	Window *myImageWindow = WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","PrettyWindow" );//开始界面
	myImageWindow->setPosition(UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
	ImagesetManager::getSingleton().createFromImageFile("imagesets", "jiemian.jpg");
	myImageWindow->setProperty("Image","set:imagesets image:full_image");
	mEditorGuiSheet->addChildWindow(myImageWindow);
	myImageWindow->setSize(UVector2(cegui_reldim(1.0f), cegui_reldim(1.0f)));
	myImageWindow->disable();

	return true;
}

void BtooomInterface::cleanupSample()
{
	if(mEditorGuiSheet)
		WindowManager::getSingleton().destroyWindow(mEditorGuiSheet);
	OgreRenderer::destroySystem();  
}



/*	WindowManager& winMgr = WindowManager::getSingleton();

    FrameWindow* wnd = (FrameWindow*)winMgr.createWindow("TaharezLook/FrameWindow", "Demo Window");

    mEditorGuiSheet->addChildWindow(wnd);

    wnd->setPosition(UVector2(cegui_reldim(0.25f), cegui_reldim( 0.25f)));
    wnd->setSize(UVector2(cegui_reldim(0.5f), cegui_reldim( 0.5f)));

    wnd->setMaxSize(UVector2(cegui_reldim(1.0f), cegui_reldim( 1.0f)));
    wnd->setMinSize(UVector2(cegui_reldim(0.1f), cegui_reldim( 0.1f)));

    wnd->setText("Hello World!");*/

/*	PushButton* startBtn=(PushButton*)WindowManager::getSingleton().createWindow("TaharezLook/Button",(CEGUI::utf8*)"Start");
	startBtn->setPosition(UVector2(cegui_reldim(0.7f), cegui_reldim(0.6f)));
	startBtn->setText((utf8*)"START");
	startBtn->setSize(UVector2(cegui_reldim(0.25f), cegui_reldim(0.1f)));
	mEditorGuiSheet->addChildWindow(startBtn);
	CEGUI::System::getSingleton();

	startBtn->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&BtooomInterface::handleStart, this));*///启用start
//	