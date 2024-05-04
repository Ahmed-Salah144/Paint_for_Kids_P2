#include "AddCircAction.h"
#include "..\Figures\CCircle.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "VoiceAction.h"

AddCircAction::AddCircAction(ApplicationManager* pApp) :Action(pApp)
{}

void AddCircAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Circle: Click at center");

	//Read center and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Circle: Click at Outer Point");

	//Read Outer point and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);

	CircGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	CircGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddCircAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a circle with the parameters read from the user
	CCircle* C = new CCircle (P1, P2, CircGfxInfo);	
	if (VoiceAction::GetVoiceOn() == true)
	{
		PlaySound(TEXT("Voice/AddedCircle"), NULL, SND_FILENAME | SND_SYNC);
		PlaySound(TEXT("Voice/BGM"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
	//Add the circle to the list of figures
	pManager->AddFigure(C);
}
