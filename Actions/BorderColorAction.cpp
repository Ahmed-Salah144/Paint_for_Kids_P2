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
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Select Border Color");

	SelectedFigure = pManager->GetSelectedFigure();
	switch (pIn->GetUserAction())
	{
	case COLOR_BLACK:
		SelectedColor = BLACK;
		pOut->PrintMessage("Selected Black");
		break;
	case COLOR_YELLOW:
		SelectedColor = YELLOW;
		pOut->PrintMessage("Selected Yellow");
		break;
	case COLOR_ORANGE:
		SelectedColor = ORANGE;
		pOut->PrintMessage("Selected Orange");
		break;
	case COLOR_RED:
		SelectedColor = RED;
		pOut->PrintMessage("Selected Red");
		break;
	case COLOR_GREEN:
		SelectedColor = GREEN;
		pOut->PrintMessage("Selected Green");
		break;
	case COLOR_BLUE:
		SelectedColor = BLUE;
		pOut->PrintMessage("Selected Blue");
		break;
	default:
		//Sets it to the current draw color so no changes happen if user doesn't select any color
		SelectedColor = SelectedFigure->GetDrawClr();	
		pOut->PrintMessage("No Color Selected");
		break;
	}
}

//Execute the action
void BorderColorAction::Execute()
{
	ReadActionParameters();
	SelectedFigure->ChngDrawClr(SelectedColor);
	SelectedFigure->SetSelected(false);			//Removes Selection to see Changed border color
	pManager->UpdateFigureData();
}
