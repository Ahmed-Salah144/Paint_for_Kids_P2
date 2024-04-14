#ifndef ADD_SQR_ACTION_H
#define ADD_SQR_ACTION_H

#include "AddFigureAction.h"

//Add Square Action class
class AddSqrAction : public AddFigureAction
{
private:
	Point P; //Square Center
	GfxInfo SqrGfxInfo;
public:
	AddSqrAction(ApplicationManager* pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();

};

#endif
