#ifndef __GAME__
#define __GAME__

#include <IVideoDriver.h>
#include "IrrlichtDevice.h"
#include <irrlicht.h>

using namespace irr;

class Game
{
private:
	
public:

	static Game* m_GameInstance;

	irr::IrrlichtDevice* m_device;
	irr::video::IVideoDriver* m_driver;

	static void CreateInstance();
	static Game* GetInstance();

	bool CreateIrrDevice();
	IrrlichtDevice* GetIrrDevice();

	bool CreateIrrVideoDriver();
	irr::video::IVideoDriver* GetIVideoDriver();

	void Render();
	void Update();

	bool OnKeyEvent(irr::EKEY_CODE);
	bool OnMouseEvent(irr::EMOUSE_INPUT_EVENT);

};
#endif