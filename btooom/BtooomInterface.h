#ifndef __BtooomInterface_H__
#define __BtooomInterface_H__

#include "CEGUIOgreRenderer.h"
//#include "CEGuiSample.h"
#include "CEGUI.h"
#include "Ogre.h"

class BtooomInterface//:public CEGuiSample
{
public:
	void cleanupSample(void);
	bool initialiseSample();

public:
	CEGUI::Window* mEditorGuiSheet; //纸
	CEGUI::OgreRenderer* mGUIRenderer;//这个其实没什么用啊貌似，不过姑且按教程放在这里
};

#endif
