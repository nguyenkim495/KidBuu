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
#include <time.h>
#include <string>

////
#include <SceneNode\SceneNode.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace irrklang;

#ifdef _IRR_WINDOWS_
//#pragma comment(lib, "Irrlicht.lib")
//#pragma comment(lib, "irrKlang.lib")
#endif

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
	IrrlichtDevice *device;
	s32				counter;
	IGUIListBox*	listbox;
};


class MyEventReceiver : public IEventReceiver
{

};
//{
//public:h
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

const std::string& GetXXX(int number)
{
	std::string a = nullptr;
	return a;
}


const wchar_t* to_wide(const float fps)
{
	std::wstring FPS;
	FPS = std::to_wstring(fps);
	return FPS.c_str();
}

int mainf()
{	

	//std::string test = GetXXX(1);

	IrrlichtDevice* device = createDevice(EDT_OPENGL, core::dimension2d<u32>(1366, 768), 32);// , true, false, true);
	
	wchar_t *fps = L"0";
	clock_t start, end;

	if (device == 0)
		return 1;

	device->setWindowCaption(L"Irrlicht Engine - User Interface Demo");
	device->setResizable(true);

	
	video::IVideoDriver* driver = device->getVideoDriver();
	
	scene::ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	

	//guienv->addStaticText(fps, core::rect<s32>(10, 10, 260, 22), false);// , 0, 0, -1, true);
	//guienv->addEditBox(fps, core::rect<s32>(600, 300, 860, 322), false);// , 0, 0, -1, true);

	IGUIStaticText *fpsShow = guienv->addStaticText(fps, core::rect<s32>(100, 100, 360, 122), false, false, 0);
	

	

	//scene::IAnimatedMesh* mesh = smgr->getMesh("../res/sydney.md2");
	scene::IAnimatedMesh* meshCube = smgr->getMesh("../res/cubemakewrong.md2");
	scene::IAnimatedMeshSceneNode* nodeCube = smgr->addAnimatedMeshSceneNode(meshCube);
	if (nodeCube)
	{
		nodeCube->setMaterialFlag(EMF_LIGHTING, false);
		//nodeCube->setScale(core::vector3df(0.1, 0.1, 0.1));
		nodeCube->setMaterialTexture(0, driver->getTexture("../res/sydney.bmp"));
		//node->setMD2Animation(scene::EMAT_STAND);

		//node->setMaterialTexture(0, driver->getTexture("../res/sydney.bmp"));

	}

	scene::IAnimatedMesh* meshSydney = smgr->getMesh("../res/sydney.md2");
	scene::ISceneNode* nodeSydney = nullptr; // ->addAnimatedMeshSceneNode(meshSydney);
	if (nodeSydney)
	{
		nodeSydney->setMaterialFlag(EMF_LIGHTING, false);
		nodeSydney->setPosition(core::vector3df(30, 0, 0));
		nodeSydney->setMaterialTexture(0, driver->getTexture("../res/sydney.bmp"));

	}
	
	scene::IAnimatedMesh* ground = smgr->getMesh("../res/ground.md2");
	//scene::ISceneNode* nodeGround = smgr->addAnimatedMeshSceneNode(ground);
	if (ground)
	{
		scene::ISceneNode* nodeGround = nullptr;// smgr->addOctreeSceneNode(ground->getMesh(0), 0, -1, 1024);//draw invisible 
		if (nodeGround)
		{
			nodeGround->setPosition(core::vector3df(0, 0, -100));
			nodeGround->setMaterialTexture(0, driver->getTexture("../res/sydney.bmp"));
			//nodeGround->set
		}
			
	}
		

	//scene::ISceneNode *staticNode = smgr->addSceneNode("../res/cube.dae");
	
	//scene node custom
	CSampleSceneNode* triangle = new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 1);
	CSampleSceneNode* triangle2 = new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 1);
	scene::ISceneNodeAnimator* aim = smgr->createRotationAnimator(core::vector3df(0.8f, 0, 0.8f));
	scene::ISceneNodeAnimator* aim2 = smgr->createRotationAnimator(core::vector3df(-0.8f, 0, -0.8f));
	if (aim)
	{
		//triangle->addAnimator(aim);
		triangle2->addAnimator(aim);
		triangle2->setPosition(core::vector3df(10, 1, 1));
		aim->drop();
		aim = 0;
	}
	
	triangle->drop();
	triangle = 0;
	
	triangle2->drop();
	triangle2 = 0;

	
	


	

	smgr->addCameraSceneNode(0, vector3df(0, 90, 120), vector3df(0, 30, 0));
	//soundtest->play();


	
	driver->beginScene(true, true, SColor(0, 0, 200, 200));
	while(device->run())
	{

		int fpsInside = driver->getFPS();
		core::stringw str = L"FPS: ";
		str += fpsInside;
		start = clock();
		driver->beginScene(true, true, SColor(0,200,200,200));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
		end = clock();
		const wchar_t* fps =  to_wide((float)end - start);
		fpsShow->setText(str.c_str());
	}

	device->drop();

	return 0;
}

/*
**/
