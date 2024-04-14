#ifndef ADD_FIGURE_ACTION_H
#define ADD_FIGURE_ACTION_H

#include "Action.h"

#include "..\ApplicationManager.h"

//Add Circle Action class
class AddFigureAction : public Action
{
protected:
	int FigCount;
public:
	AddFigureAction(ApplicationManager* pApp) :Action(pApp) { FigCount = pApp->GetFigureCount(); };

	//Reads hexagon parameters
	virtual void ReadActionParameters()=0;

	//Add hexagon to the ApplicationManager
	virtual void Execute()=0;

};

#endif
