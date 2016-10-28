#include<irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace io;
using namespace gui;
using namespace video;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include<d3dx9.h>

int main()
{
	IrrlichtDevice *device = 
		createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
			false, false, false, 0);

	if(!device)
		return 1;


	device->setWindowCaption(L"Hello World");
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	guienv->addStaticText(L"Stop this",
		rect<s32>(10, 10, 260, 22), true);

	IAnimatedMesh* mesh = smgr->getMesh("sydney.md2");
	if(!mesh)
	{
		device->drop();
		return 1;
	}

	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
	if(node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("sydney.bmp"));

	}

	smgr->addCameraSceneNode(0, vector3df(0, 30, -30), vector3df(0 ,5, 0)); //camera

	while (device->run())
	{
		driver->beginScene(true, true, SColor(255, 100, 101, 140));

		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
	}

	device->drop();
	return 0;
}

