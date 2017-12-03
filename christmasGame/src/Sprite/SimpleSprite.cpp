#include "SimpleSprite.h"
#include "Game.h"

///////////////////////////////////////////////////////////////////////////////////////////
SimpleSprite::SimpleSprite(char* filename, vector3df pos)
{
	//return;
	m_texture = Game::GetInstance()->GetIVideoDriver()->getTexture(filename);
	m_position = pos;
	if (m_texture)
	{
		m_textureRegion = m_texture->getOriginalSize();
		m_isVisible = true;
	}
	
}

///////////////////////////////////////////////////////////////////////////////////////////
SimpleSprite::~SimpleSprite()
{
	
}

///////////////////////////////////////////////////////////////////////////////////////////
void SimpleSprite::DrawSprite()
{
	//core::rect<s32> upperLeft = core::rect<s32>(m_position.X, m_position.Y, 0, 0);video::IVideoDriver;// = 
	if(m_texture)
	{
		irr::video::IVideoDriver* m_driver = Game::GetInstance()->GetIVideoDriver(); //?performance
		if(m_driver)
			m_driver->draw2DImage(m_texture, m_textureRegion,
							core::rect<s32>(0, 0, 300, 300), 0,
							video::SColor(255, 255, 255, 255), true);
							
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
void SimpleSprite::Render()
{
	if(m_isVisible)
		DrawSprite();
}