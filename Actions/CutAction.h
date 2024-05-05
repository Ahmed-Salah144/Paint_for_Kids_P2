#ifndef CUT_ACTION_H
#define CUT_ACTION_H

#include "Action.h"
#include "SelectionAction.h"
#include"..\Figures\CFigure.h"
#include"..\Figures\CCircle.h"
#include"..\Figures\CHexagon.h"
#include"..\Figures\CRectangle.h"
#include"..\Figures\CSquare.h"
#include"..\Figures\CTriangle.h"

class CutAction : public Action
{
	CFigure* SelectedFig;
	char selected;


public:
	CutAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

};

#endif
