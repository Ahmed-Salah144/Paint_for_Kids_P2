#include "BringToFrontAction.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

BringToFrontAction::BringToFrontAction(ApplicationManager* pApp) :Action(pApp)
{
}

void BringToFrontAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	SelectedFig=pManager->GetSelectedFigure(0);
}

void BringToFrontAction::Execute()
{
	ReadActionParameters();
	pManager->RemoveFigure(SelectedFig);
	pManager->AddFigure(SelectedFig);
	SelectedFig->SetSelected(false);
}
