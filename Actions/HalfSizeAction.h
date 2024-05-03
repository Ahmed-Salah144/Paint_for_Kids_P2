#ifndef HALF_SIZE_ACTION_H
#define HALF_SIZE_ACTION_H

#include "Action.h"
#include "..\Figures\CFigure.h"
class HalfSizeAction : public Action
{
private:
	CFigure* SelectedFig;
public:
	HalfSizeAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif
