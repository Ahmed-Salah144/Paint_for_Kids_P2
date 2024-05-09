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
	SelectedFig=pManager->GetSelectedFigure();
}

void BringToFrontAction::Execute()
{
	ReadActionParameters();
	pManager->RemoveFigure(SelectedFig->GetID());
	pManager->AddFigure(SelectedFig);
}
