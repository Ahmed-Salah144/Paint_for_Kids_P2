#ifndef PASTE_ACTION_H
#define PASTE_ACTION_H

#include "Action.h"
#include "SelectionAction.h"
#include"..\Figures\CFigure.h"
#include"..\Figures\CCircle.h"
#include"..\Figures\CHexagon.h"
#include"..\Figures\CRectangle.h"
#include"..\Figures\CSquare.h"
#include"..\Figures\CTriangle.h"

class PasteAction : public Action
{
	Point Clicked;     
	CFigure* SelectedFig ;
	CFigure* ClipboardFigure;
public:
	PasteAction(ApplicationManager* pApp); 
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif

