#pragma once

#include <irrlicht.h>

enum StateID
{
	STATE_LOADING = 0,
	STATE_GAMEPLAY,
	STATE_ABOUT,
	STATE_SETTING
};

class State : public irr::IEventReceiver
{
protected:
	StateID m_stateID;
public:
	State(){}
	State(StateID);
	~State(){}
public:
	//static State* m_state;

	void		Init();
	void		Render();
	void		Update(float dt);
	void		Pause();
	void		Resume();
	void		Release();//

	bool		OnEvent(const irr::SEvent& event);

	StateID		GetStateID() const;
};