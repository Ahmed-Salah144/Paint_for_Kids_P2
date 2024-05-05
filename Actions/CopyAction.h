#ifndef COPY_ACTION_H
#define COPY_ACTION_H

#include "Action.h"
#include "SelectionAction.h"
#include"..\Figures\CFigure.h"
#include"..\Figures\CCircle.h"
#include"..\Figures\CHexagon.h"
#include"..\Figures\CRectangle.h"
#include"..\Figures\CSquare.h"
#include"..\Figures\CTriangle.h"



class CopyAction : public Action
{
	CFigure* SelectedFig;
	char selected;
	

public:
	CopyAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

};

#endif

