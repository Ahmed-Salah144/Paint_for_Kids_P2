#ifndef SWITCH_TO_PLAYMODE_ACTION_H
#define SWITCH_TO_PLAYMODE_ACTION_H

#include "Action.h"
class SwitchToPlayModeAction : public Action
{
private:
public:
	SwitchToPlayModeAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif
