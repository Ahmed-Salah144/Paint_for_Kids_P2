#ifndef BRINGTOFRONT_ACTION_H
#define BRINGTOFRONT_ACTION_H

#include "Action.h"
#include"..\Figures\CFigure.h"
//Bring to front Action
class BringToFrontAction : public Action
{

	CFigure* SelectedFig;

public:

	BringToFrontAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif


