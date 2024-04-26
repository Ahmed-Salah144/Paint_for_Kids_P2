#pragma once
#include "Action.h"
#include <iostream>
#include <fstream>
class SaveAction : public Action
{
	string file_name;
public:
	SaveAction(ApplicationManager* papp);

	virtual void ReadActionParameters();
	virtual void Execute();
};

