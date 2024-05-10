#include "SelectionAction.h"
#include "..\Figures\CTriangle.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CHexagon.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

SelectionAction::SelectionAction(ApplicationManager* pApp) :Action(pApp)
{
}


bool SelectionAction::DeselectFigure(CFigure*pFig)
{
	if (pFig == NULL)//if no figure clicked

		return false;

	if (pFig->IsSelected()) // if clicked figure is selected
	{

		pFig->SetSelected(false);

		pManager->UpdateFigureData(); //Update Selected Figures

		return true;
	}

	return false;
}

bool SelectionAction::SelectFigure(CFigure* pFig)
{
	if (pFig == NULL)

		return false;

	if ((pFig->IsSelected())==false)//if figure is not selected
	{

		pFig->SetSelected(true);

		pManager->UpdateFigureData(); //Update Number of selected figures

		return true;
	}

	return false;
}

void SelectionAction::ClearAllSelection()
{
	while(pManager->GetSelectedFigureCount()>0) //Deselect all figures until there are none left
	{
		DeselectFigure(pManager->GetSelectedFigure());
	}
}

void SelectionAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Click any figure to select");

	//Read input and store in point Click

	pIn->GetPointClicked(Click.x, Click.y);

	pOut->ClearStatusBar();
}

void SelectionAction::Execute()
{
	ReadActionParameters();

	CFigure* pFig = pManager->GetFigure(Click.x, Click.y);

	Output* pOut = pManager->GetOutput();

	if ((SelectFigure(pFig))==false)//calls SelectFigure and if it returns false attempts next condition

		if (DeselectFigure(pFig)==false)//calls DeselectFigure and if it returns false attempts next condition

			ClearAllSelection();

	if (pManager->GetSelectedFigureCount() == 0)

		pOut->PrintMessage("No Selected Figures");

	else if (pManager->GetSelectedFigureCount() == 1)//If exactly one figure is selected

		pManager->GetSelectedFigure()->PrintInfo(pOut);

	else
	{
		//Builds display message based on available figure types

		string Message = "Selected: ";

		if (pManager->GetSelectedFigureCountByType(RECTANGLE) > 0)//if there are no selected rectangles do not print this line

			Message = Message + to_string(pManager->GetSelectedFigureCountByType(RECTANGLE)) + " Rectangle(s),";

		if (pManager->GetSelectedFigureCountByType(TRIANGLE) > 0)//if there are no selected triangles do not print this line

			Message = Message + to_string(pManager->GetSelectedFigureCountByType(TRIANGLE)) + " Triangle(s),";

		if (pManager->GetSelectedFigureCountByType(HEXAGON) > 0)//if there are no selected hexagons do not print this line

			Message = Message + to_string(pManager->GetSelectedFigureCountByType(HEXAGON)) + " Hexagon(s),";

		if (pManager->GetSelectedFigureCountByType(CIRCLE) > 0)//if there are no selected circles do not print this line

			Message = Message + to_string(pManager->GetSelectedFigureCountByType(CIRCLE)) + " Circle(s),";

		if (pManager->GetSelectedFigureCountByType(SQUARE) > 0)//if there are no selected squares do not print this line

			Message = Message + to_string(pManager->GetSelectedFigureCountByType(SQUARE)) + " Square(s),";

		pOut->PrintMessage(Message);
	}
}
