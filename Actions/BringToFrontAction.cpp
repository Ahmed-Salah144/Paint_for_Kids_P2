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

	pManager->RemoveFigure(SelectedFig->GetID());//removes figure from list

	pManager->AddFigure(SelectedFig); // adds figure to the top of the list

	pManager->GetOutput()->PrintMessage("Figure brought to front");

	pManager->UpdateFigureData();
}
