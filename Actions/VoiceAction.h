#ifndef VOICE_ACTION_H
#define VOICE_ACTION_H

#include "Action.h"

class VoiceAction : public Action
{
private:

public:
	VoiceAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif