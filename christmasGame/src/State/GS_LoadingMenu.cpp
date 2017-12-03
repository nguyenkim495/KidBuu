#include "GS_LoadingMenu.h"

using namespace irr;

///////////////////////////////////////////////////////////////////////////////////////////
GS_LoadingMenu::GS_LoadingMenu()
{
	State::m_stateID = StateID::STATE_LOADING;
}

///////////////////////////////////////////////////////////////////////////////////////////
GS_LoadingMenu::~GS_LoadingMenu()
{

}

///////////////////////////////////////////////////////////////////////////////////////////
void GS_LoadingMenu::Init()
{
	core::vector3df pos = core::vector3df(0.0, 0.0, 0.0);
	m_SpriteLogo = new SimpleSprite("", pos);
}

///////////////////////////////////////////////////////////////////////////////////////////
void GS_LoadingMenu::Render()
{
	m_SpriteLogo->Render();
}

///////////////////////////////////////////////////////////////////////////////////////////
void GS_LoadingMenu::Update(float dt)
{
	Render();
}