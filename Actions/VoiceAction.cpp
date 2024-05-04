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
		PlaySound(TEXT("Voice/BGM"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
	else
	{
		pOut->PrintMessage("Voice Off!");
		PlaySound(0, 0, 0);
	}
}
