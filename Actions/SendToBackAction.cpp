#include "SendToBackAction.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

SendToBackAction::SendToBackAction(ApplicationManager* pApp) :Action(pApp)
{
}

void SendToBackAction::ReadActionParameters()
{
	SelectedFig = pManager->GetSelectedFigure();
}

void SendToBackAction::Execute()
{
	ReadActionParameters();

	pManager->RemoveFigure(SelectedFig->GetID());//remove figure from list

	pManager->AddFigure(SelectedFig);//adds figure to the top of the list

	for (int i = pManager->GetFigureCount()-1; i > 0; i--) //swaps figure from top of the list to the bottom
	{
		pManager->SwapFigure(i,i-1);
	}

	pManager->GetOutput()->PrintMessage("Figure sent to back");
}
