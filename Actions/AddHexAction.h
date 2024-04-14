#ifndef ADD_HEX_ACTION_H
#define ADD_HEX_ACTION_H

#include "AddFigureAction.h"

//Add Hexagon Action class
class AddHexAction : public AddFigureAction
{
private:
	Point P; //Hexagon Center
	GfxInfo HexGfxInfo;
public:
	AddHexAction(ApplicationManager* pApp);

	//Reads hexagon parameters
	virtual void ReadActionParameters();

	//Add hexagon to the ApplicationManager
	virtual void Execute();

};

#endif
