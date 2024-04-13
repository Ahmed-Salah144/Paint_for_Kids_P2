#ifndef FILLCOLOR_ACTION_H
#define FILLCOLOR_ACTION_H

#include "Action.h"
#include"..\Figures\CFigure.h"
#include"SelectionAction.h"
//Border Color changeAction(Salem)
class FillColorAction : public Action
{
private:
	CFigure* SelectedFigure;
	color SelectedColor;
public:
	FillColorAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif

