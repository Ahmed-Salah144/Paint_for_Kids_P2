#ifndef ADD_TRI_ACTION_H
#define ADD_TRI_ACTION_H

#include "AddFigureAction.h"

//Add Triangle Action class
class AddTriAction : public AddFigureAction
{
private:
	Point P1, P2,P3; //Triangle Vertices
	GfxInfo TriGfxInfo;
public:
	AddTriAction(ApplicationManager* pApp);

	//Reads Triangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();

};

#endif
