#pragma once
#include "Action.h"

class LoadAction : public Action
{
private:
	string file_name;

public:
	LoadAction(ApplicationManager* papp);

	virtual void ReadActionParameters();
	virtual void Execute();

};