#pragma once
#include "Action.h"

class VoiceAction : public Action
{
public:
	enum Audio {PLAY_OFF, PLAY_DRAW_RECTANGLE, PLAY_DRAW_SQUARE, PLAY_DRAW_CIRCLE, PLAY_DRAW_TRIANGLE, PLAY_DRAW_HEXAGON, PLAY_BGM};
private:
	static bool sound_on;
public:
	VoiceAction(ApplicationManager* pApp);

	static bool GetVoiceOn();
	void PlayAudio(Audio);

	virtual void ReadActionParameters();
	virtual void Execute();

};