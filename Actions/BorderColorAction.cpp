#include "BorderColorAction.h"
#include "..\Figures\CFigure.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

BorderColorAction::BorderColorAction(ApplicationManager* pApp) :Action(pApp)
{
}

void BorderColorAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Input* pIn = pManager->GetInput();
	pManager->GetOutput()->PrintMessage("Select New Border Color");
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
		SelectedColor = SelectedFigure->GetDrawClr();
		pManager->GetOutput()->PrintMessage("No Color Selected");
	}
	}
}

//Execute the action
void BorderColorAction::Execute()
{
	ReadActionParameters();
	SelectedFigure->ChngDrawClr(SelectedColor);
	SelectedFigure->SetSelected(false);
	pManager->UpdateFigureData();
}
