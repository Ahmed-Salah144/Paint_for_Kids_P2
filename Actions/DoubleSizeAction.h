#ifndef DOUBLE_SIZE_ACTION_H
#define DOUBLE_SIZE_ACTION_H

#include "Action.h"
#include "..\Figures\CFigure.h"

class DoubleSizeAction : public Action
{
private:

	CFigure* SelectedFig;

public:

	DoubleSizeAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif