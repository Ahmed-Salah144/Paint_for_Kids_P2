#ifndef SENDTOBACK_ACTION_H
#define SENDTOBACK_ACTION_H

#include "Action.h"
#include"..\Figures\CFigure.h"
//Send to back Action (Salem)
class SendToBackAction : public Action
{
	CFigure* SelectedFig;
	int FigCount;
public:
	SendToBackAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

};

#endif

