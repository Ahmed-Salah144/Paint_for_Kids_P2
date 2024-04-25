#ifndef ADD_CIRC_ACTION_H
#define ADD_CIRC_ACTION_H

#include "Action.h"

//Add Circle Action class
class AddCircAction : public Action
{
private:
	Point P1,P2; //Circle Center and Outer Point
	GfxInfo CircGfxInfo;
public:
	AddCircAction(ApplicationManager* pApp);

	//Reads hexagon parameters
	virtual void ReadActionParameters();

	//Add hexagon to the ApplicationManager
	virtual void Execute();

};

#endif
