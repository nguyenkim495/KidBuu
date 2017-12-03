#pragma once
#include "State.h"
#include <Sprite\SimpleSprite.h>

class GS_LoadingMenu : public State

{
public:
	GS_LoadingMenu();
	~GS_LoadingMenu();
private:
	SimpleSprite *m_SpriteLogo;
public:
	void		Init();
	void		Render();
	void		Update(float dt);
	void		Pause();
	void		Resume();
	void		Release();//

};