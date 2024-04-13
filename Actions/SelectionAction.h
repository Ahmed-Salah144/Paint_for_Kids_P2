#ifndef SELECTION_ACTION_H
#define SELECTION_ACTION_H

#include "Action.h"
#include"..\Figures\CFigure.h"
//Selection Action(Salem)
class SelectionAction : public Action
{
private:
	Point Click;//Clicked Point
public:
	SelectionAction(ApplicationManager* pApp);
	bool DeselectFigure(CFigure*);
	bool SelectFigure(CFigure*);
	void ClearAllSelection();
	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif
