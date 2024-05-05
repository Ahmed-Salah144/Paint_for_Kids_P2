#pragma once
#include "Action.h"
#include <iostream>
#include <fstream>
class SaveAction : public Action
{
	string file_name;
	bool playmode;
public:
	SaveAction(ApplicationManager* papp);
	SaveAction(ApplicationManager* papp, int);	//used in playmode

	virtual void ReadActionParameters();
	virtual void Execute();
};

