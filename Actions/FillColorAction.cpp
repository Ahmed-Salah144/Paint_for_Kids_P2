#include "FillColorAction.h"
#include "..\Figures\CFigure.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

FillColorAction::FillColorAction(ApplicationManager* pApp) :Action(pApp)
{
}

void FillColorAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Select New Fill Color");
	SelectedFigure = pManager->GetSelectedFigure();
	switch (pIn->GetUserAction())
	{
	case COLOR_BLACK:
	{
		SelectedColor = BLACK;
		break;
	}
	case COLOR_YELLOW:
	{
		SelectedColor = YELLOW;
		break;
	}
	case COLOR_ORANGE:
	{
		SelectedColor = ORANGE;
		break;
	}
	case COLOR_RED:
	{
		SelectedColor = RED;
		break;
	}
	case COLOR_GREEN:
	{
		SelectedColor = GREEN;
		break;
	}
	case COLOR_BLUE:
	{
		SelectedColor = BLUE;
		break;
	}

	default:
	{	
		SelectedColor = SelectedFigure->GetFillClr();
		pOut->PrintMessage("No Color Selected");
	}
	}
}

//Execute the action
void FillColorAction::Execute()
{
	ReadActionParameters();
	SelectedFigure->ChngFillClr(SelectedColor);
	SelectionAction* pAct = new SelectionAction(pManager);
	pAct->DeselectFigure(SelectedFigure);
	delete pAct;
}
