#ifndef SENDTOBACK_ACTION_H
#define SENDTOBACK_ACTION_H

#include "Action.h"
#include"..\Figures\CFigure.h"
class SendToBackAction : public Action
{

	CFigure* SelectedFig;

public:
	SendToBackAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif

