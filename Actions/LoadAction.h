#pragma once
#include "Action.h"

class LoadAction : public Action
{
private:
	string file_name;
	bool playmode;
public:
	LoadAction(ApplicationManager* papp);
	LoadAction(ApplicationManager* papp, int); //used in playmode

	virtual void ReadActionParameters();
	virtual void Execute();

};