#ifndef CLEARALL_ACTION_H
#define CLEARALL_ACTION_H

#include "Action.h"
#include"..\Figures\CFigure.h"
//Clear All Action
class ClearAllAction : public Action
{
public:
	ClearAllAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

};

#endif
