/** Example 005 User Interface

This tutorial shows how to use the built in User Interface of
the Irrlicht Engine. It will give a brief overview and show
how to create and use windows, buttons, scroll bars, static
texts, and list boxes.

As always, we include the header files, and use the irrlicht
namespaces. We also store a pointer to the Irrlicht device,
a counter variable for changing the creation position of a window,
and a pointer to a listbox.
*/
#include <irrlicht.h>
#include "driverChoice.h"
#include "irrKlang.h"
#include "Sprite\SimpleSprite.h"
#include "Sound\Sound.h"
#include "Sound\SoundManager.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace irrklang;

#ifdef _IRR_WINDOWS_
//#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib")
#endif

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
	IrrlichtDevice *device;
	s32				counter;
	IGUIListBox*	listbox;
};


//class MyEventReceiver : public IEventReceiver
//{
//public:
//	MyEventReceiver(SAppContext & context) : Context(context) { }
//
//	virtual bool OnEvent(const SEvent& event)
//	{
//		if (event.EventType == EET_GUI_EVENT)
//		{
//			s32 id = event.GUIEvent.Caller->getID();
//			IGUIEnvironment* env = Context.device->getGUIEnvironment();
//
//			switch(event.GUIEvent.EventType)
//			{
//
//			/*
//			If a scrollbar changed its scroll position, and it is
//			'our' scrollbar (the one with id GUI_ID_TRANSPARENCY_SCROLL_BAR), then we change
//			the transparency of all gui elements. This is a very
//			easy task: There is a skin object, in which all color
//			settings are stored. We simply go through all colors
//			stored in the skin and change their alpha value.
//			*/
//			case EGET_SCROLL_BAR_CHANGED:
//				if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
//				{
//					s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
//					setSkinTransparency(pos, env->getSkin());
//				}
//				break;
//
//			/*
//			If a button was clicked, it could be one of 'our'
//			three buttons. If it is the first, we shut down the engine.
//			If it is the second, we create a little window with some
//			text on it. We also add a string to the list box to log
//			what happened. And if it is the third button, we create
//			a file open dialog, and add also this as string to the list box.
//			That's all for the event receiver.
//			*/
//			case EGET_BUTTON_CLICKED:
//				switch(id)
//				{
//				case GUI_ID_QUIT_BUTTON:
//					Context.device->closeDevice();
//					return true;
//
//				case GUI_ID_NEW_WINDOW_BUTTON:
//					{
//					Context.listbox->addItem(L"Window created");
//					Context.counter += 30;
//					if (Context.counter > 200)
//						Context.counter = 0;
//
//					IGUIWindow* window = env->addWindow(
//						rect<s32>(100 + Context.counter, 100 + Context.counter, 300 + Context.counter, 200 + Context.counter),
//						false, // modal?
//						L"Test window");
//
//					env->addStaticText(L"Please close me",
//						rect<s32>(35,35,140,50),
//						true, // border?
//						false, // wordwrap?
//						window);
//					}
//					return true;
//
//				case GUI_ID_FILE_OPEN_BUTTON:
//					Context.listbox->addItem(L"File open");
//					// There are some options for the file open dialog
//					// We set the title, make it a modal window, and make sure
//					// that the working directory is restored after the dialog
//					// is finished.
//					env->addFileOpenDialog(L"Please choose a file.", true, 0, -1, true);
//					return true;
//
//				default:
//					return false;
//				}
//				break;
//
//			case EGET_FILE_SELECTED:
//				{
//					// show the model filename, selected in the file dialog
//					IGUIFileOpenDialog* dialog =
//						(IGUIFileOpenDialog*)event.GUIEvent.Caller;
//					Context.listbox->addItem(dialog->getFileName());
//				}
//				break;
//
//			default:
//				break;
//			}
//		}
//
//		return false;
//	}
//
//private:
//	SAppContext & Context;
//};


int main()
{
	IrrlichtDevice* device = createDevice(EDT_OPENGL, core::dimension2d<u32>(640, 480));
	if(SoundManager::createSingleton())
	{
		SoundManager::getSingleton()->Init();
	}
	Sound* soundtest = new Sound("../res/sound/getout.ogg", true);

	//irrklang::ISoundEngine* engineSound = irrklang::createIrrKlangDevice();


	if (device == 0)// || !engineSound)
		return 1; // could not create selected driver.


	device->setWindowCaption(L"Irrlicht Engine - User Interface Demo");
	device->setResizable(true);

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	scene::IAnimatedMesh* mesh = smgr->getMesh("../res/sampleTest/cube.dae");
	//scene::ISceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
	scene::IAnimatedMeshSceneNode* nodeAnimation = smgr->addAnimatedMeshSceneNode(mesh);

	if(nodeAnimation)
	{
		scene::ISceneNodeAnimator* anim = smgr->createFlyStraightAnimator(core::vector3df(10,0,6),
            core::vector3df(-10,0,6), 3500, true);
		if(anim)
		{
			nodeAnimation->addAnimator(anim);
			anim->drop();
		}

		nodeAnimation->setMaterialFlag(EMF_LIGHTING, false);
		nodeAnimation->setFrameLoop(0, 80);
		nodeAnimation->setAnimationSpeed(15);
	}


	SimpleSprite* sprite = new SimpleSprite(device, "../res/sydney.bmp", core::vector3df(0, 0, 0));

	smgr->addCameraSceneNode(0, vector3df(13, 15, 15), vector3df(0, 0, 0));
	soundtest->play();


	int k = 5000;

	while(device->run() && driver)
	if (device->isWindowActive())
	{
		driver->beginScene(true, true, SColor(0,200,200,200));
		//sprite->render();
		smgr->drawAll();
		driver->endScene();

		k--;
		if(k == 1500)
			soundtest->pause();
		else if(k == 0)
			soundtest->resume();
	}

	device->drop();

	return 0;
}

/*
**/
