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
	CEGUI::Window* mEditorGuiSheet; //ֽ
	CEGUI::OgreRenderer* mGUIRenderer;//�����ʵûʲô�ð�ò�ƣ��������Ұ��̷̳�������
};

#endif
