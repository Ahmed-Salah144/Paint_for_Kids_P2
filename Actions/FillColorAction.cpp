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
	pOut->PrintMessage("Select Fill Color");

	SelectedFigure = pManager->GetSelectedFigure();	//Gets Selected Figure
	switch (pIn->GetUserAction())					//Gets user's color choice
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
		SelectedColor = WHITE;		//Temp color to check if user didn't choose any colors
		pOut->PrintMessage("No Color Selected, Removing Fill Color");
		break;
	}
}

//Execute the action
void FillColorAction::Execute()
{
	ReadActionParameters();
	if (SelectedColor != WHITE)		//White is used to check if user didnt choose any colors
		SelectedFigure->ChngFillClr(SelectedColor);
	else
		SelectedFigure->UnFill();	//If no color was chosen then unfill the figure

	SelectedFigure->SetSelected(false);
	pManager->UpdateFigureData();

}
