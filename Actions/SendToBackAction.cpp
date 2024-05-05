#include "SendToBackAction.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

SendToBackAction::SendToBackAction(ApplicationManager* pApp) :Action(pApp)
{
	FigCount = pManager->GetFigureCount();
}

void SendToBackAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	SelectedFig = pManager->GetSelectedFigure();
}

void SendToBackAction::Execute()
{
	ReadActionParameters();
	pManager->RemoveFigure(SelectedFig);
	pManager->AddFigure(SelectedFig);
	for (int i = FigCount-1; i > 0; i--)
	{
		pManager->SwapFigure(i,i-1);
	}
	SelectedFig->SetSelected(false);
}
