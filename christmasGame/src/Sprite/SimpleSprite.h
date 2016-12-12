#include <ITexture.h>
#include <IVideoDriver.h>
#include "IrrlichtDevice.h"
#include <irrList.h>


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

class SimpleSprite
{
public:

	SimpleSprite();
	SimpleSprite(IrrlichtDevice *device, char* filename, vector3df pos);
	
	virtual ~SimpleSprite();
	void drawSprite();
	void render();

private:
	
	ITexture* m_texture;
	vector3df m_position;
	dimension2d<s32> m_textureRegion;
	//temp
	IrrlichtDevice* m_device;
	IVideoDriver* m_driver;



};