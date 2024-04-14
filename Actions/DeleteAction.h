#ifndef DELETE_ACTION_H
#define DELETE_ACTION_H

#include "Action.h"
#include"..\Figures\CFigure.h"
//Delete Action (Salem)
class DeleteAction : public Action
{
	CFigure* SelectedFigList[200];
	int SelectedFigCount;
public:
	DeleteAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

};

#endif

