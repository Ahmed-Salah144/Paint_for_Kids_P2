#ifndef DELETE_ACTION_H
#define DELETE_ACTION_H

#include "Action.h"
#include"..\Figures\CFigure.h"
//Delete Action
class DeleteAction : public Action
{

	CFigure* FigureToDelete;//Pointer to figure to be deleted

public:

	DeleteAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif

