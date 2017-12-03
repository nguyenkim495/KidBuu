#pragma once

#include "State.h"

#define MAX_STATES 4

class StateMgr
{
public:
	StateMgr();
	~StateMgr();
	static StateMgr *m_StateMgr;

private:
	State* m_pStacks[4];
	State* m_pDeleteStacks[1];

public:
	void	PushState(State);
	void	PopState(State);
	State*	GetCurrentState() const;//state on top
	State*	GetPreviousState() const;
	void	Update(float dt);
	void	ChangeState(State, bool deleteState);
	void	MarkStateToDelete(State);

};

StateMgr::StateMgr()
{
}

StateMgr::~StateMgr()
{
}