#ifndef SWITCH_TO_DRAWMODE_ACTION_H
#define SWITCH_TO_DRAWMODE_ACTION_H

#include "Action.h"
class SwitchToDrawModeAction : public Action
{
private:
public:
	SwitchToDrawModeAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif

