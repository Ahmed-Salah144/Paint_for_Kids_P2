#ifndef DELETE_ACTION_H
#define DELETE_ACTION_H

#include "Action.h"
#include"..\Figures\CFigure.h"
//Delete Action (Salem)
class DeleteAction : public Action
{
	CFigure* FigureToDelete;
public:
	DeleteAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

};

#endif

