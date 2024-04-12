#ifndef SELECTION_ACTION_H
#define SELECTION_ACTION_H

#include "Action.h"
#include"..\Figures\CFigure.h"
//Selection Action(Salem)
class SelectionAction : public Action
{
private:
	Point Click;//Clicked Point
	CFigure* SelectedFigs[200];
	int NumOfFigures=0;
	int NumOfRect=0, NumOfSqr=0, NumOfHex=0, NumOfTri=0, NumOfCirc=0;
public:
	SelectionAction(ApplicationManager* pApp);
	void UpdateNumOfFigures();
	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif
