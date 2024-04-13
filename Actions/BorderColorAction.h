#ifndef BORDERCOLOR_ACTION_H
#define BORDERCOLOR_ACTION_H

#include "Action.h"
#include"..\Figures\CFigure.h"
#include"SelectionAction.h"
//Border Color changeAction(Salem)
class BorderColorAction : public Action
{
private:
	CFigure* SelectedFigure;
	color SelectedColor;
public:
	BorderColorAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif
