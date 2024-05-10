#include "VoiceAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

bool VoiceAction::sound_on = false;

VoiceAction::VoiceAction(ApplicationManager* pApp)
	: Action(pApp)
{
}

bool VoiceAction::GetVoiceOn()
{
	return sound_on;
}

void VoiceAction::PlayAudio(Audio input_audio)
{
	if (sound_on == false && input_audio != PLAY_OFF)	// if the sound is off continues only if the input is play_off
		return;


	// SND_ASYNC : doesn't need to pause program (used for BGM)
	// SND_SYNC : pauses program to play audio then resumes (used in figures because you can't have 2 Async playing at the same time)
	// When playing audio that isn't BGM play audio first (which pauses the program until audio is finished) then resume and play BGM again
	switch (input_audio)
	{
	case PLAY_OFF:
		PlaySound(0, 0, 0);
		break;
	case PLAY_DRAW_RECTANGLE:
		PlaySound(TEXT("Voice/RectangleAdded"), NULL, SND_FILENAME | SND_SYNC);
		PlaySound(TEXT("Voice/BGM"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		break;
	case PLAY_DRAW_SQUARE:
		PlaySound(TEXT("Voice/SquareAdded"), NULL, SND_FILENAME | SND_SYNC);
		PlaySound(TEXT("Voice/BGM"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		break;
	case PLAY_DRAW_CIRCLE:
		PlaySound(TEXT("Voice/AddedCircle"), NULL, SND_FILENAME | SND_SYNC);
		PlaySound(TEXT("Voice/BGM"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		break;
	case PLAY_DRAW_TRIANGLE:
		PlaySound(TEXT("Voice/Triangle"), NULL, SND_FILENAME | SND_SYNC);
		PlaySound(TEXT("Voice/BGM"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		break;
	case PLAY_DRAW_HEXAGON:
		PlaySound(TEXT("Voice/Hexagon"), NULL, SND_FILENAME | SND_SYNC);	
		PlaySound(TEXT("Voice/BGM"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		break;
	case PLAY_BGM:
		PlaySound(TEXT("Voice/BGM"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		break;
	default:
		// does nothing if input is wrong
		break;
	}
}

void VoiceAction::ReadActionParameters()
{
}

void VoiceAction::Execute()
{
	//each time button is pressed if sound was on it turns off and vice versa
	sound_on = !sound_on;
	Output* pOut = pManager->GetOutput();
	if (sound_on == true)
	{
		pOut->PrintMessage("Voice On!");
		PlayAudio(PLAY_BGM);
	}
	else
	{
		pOut->PrintMessage("Voice Off!");
		PlayAudio(PLAY_OFF);
	}
}
