#ifndef SELECTION_ACTION_H
#define SELECTION_ACTION_H

#include "Action.h"
#include"..\Figures\CFigure.h"
//Selection Action
class SelectionAction : public Action
{
private:

	Point Click;//User Click Location

public:

	SelectionAction(ApplicationManager* pApp);

	bool DeselectFigure(CFigure*);//returns true if figure deselected successfully

	bool SelectFigure(CFigure*);//returns true if figure selected successfully

	void ClearAllSelection();//unselects all selected figures

	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif
