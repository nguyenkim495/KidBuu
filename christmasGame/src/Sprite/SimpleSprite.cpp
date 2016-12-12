#include "SimpleSprite.h"

SimpleSprite::SimpleSprite(IrrlichtDevice *device, char* filename, vector3df pos):
	m_device(device)
{
	//return;
	if(m_device)
		m_driver = m_device->getVideoDriver();
	m_texture = m_driver->getTexture(filename);
	m_position = pos;
	if(m_texture)
		m_textureRegion = m_texture->getOriginalSize();
}

SimpleSprite::~SimpleSprite()
{

}

void SimpleSprite::drawSprite()
{
	//core::rect<s32> upperLeft = core::rect<s32>(m_position.X, m_position.Y, 0, 0);
	video::IVideoDriver;// = 
	if(m_texture)
	{
		
		m_driver->draw2DImage(m_texture, m_textureRegion,
							core::rect<s32>(0, 0, 300, 300), 0,
							video::SColor(255, 255, 255, 255), true);
							
	}
}

void SimpleSprite::render()
{
	drawSprite();
}