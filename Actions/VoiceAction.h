#ifndef VOICE_ACTION_H
#define VOICE_ACTION_H

#include "Action.h"

class VoiceAction : public Action
{
public:
	enum Sound { RectangleAdded, SquareAdded, CircleAdded};
private:
	static bool sound_on;
public:
	VoiceAction(ApplicationManager* pApp);

	static bool GetVoiceOn();

	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif