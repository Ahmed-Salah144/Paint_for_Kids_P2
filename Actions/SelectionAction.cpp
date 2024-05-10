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
	if (pFig == NULL)
		return false;
	if (pFig->IsSelected())
	{
		pFig->SetSelected(false);

		pManager->UpdateFigureData();
		return true;
	}
	return false;
}

bool SelectionAction::SelectFigure(CFigure* pFig)
{
	if (pFig == NULL)
		return false;
	if (!(pFig->IsSelected()))
	{
		pFig->SetSelected(true);
		pManager->UpdateFigureData();
		return true;
	}
	return false;
}
void SelectionAction::ClearAllSelection()
{
	while(pManager->GetSelectedFigureCount()>0)
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

	//Read center and store in point P1
	pIn->GetPointClicked(Click.x, Click.y);

	pOut->ClearStatusBar();
}

void SelectionAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	CFigure* pFig = pManager->GetFigure(Click.x, Click.y);
	Output* pOut = pManager->GetOutput();
	if (!(SelectFigure(pFig)))
		if (!DeselectFigure(pFig))
			ClearAllSelection();
	if (pManager->GetSelectedFigureCount() == 0)
		pOut->PrintMessage("No Selected Figures");
	else if (pManager->GetSelectedFigureCount() == 1)
		pManager->GetSelectedFigure()->PrintInfo(pOut);
	else
	{
		string Message = "Selected: ";
			if (pManager->GetSelectedFigureCountByType(RECTANGLE) > 0)
				Message = Message + to_string(pManager->GetSelectedFigureCountByType(RECTANGLE)) + " Rectangle(s),";
			if (pManager->GetSelectedFigureCountByType(TRIANGLE) > 0)
				Message = Message + to_string(pManager->GetSelectedFigureCountByType(TRIANGLE)) + " Triangle(s),";
			if (pManager->GetSelectedFigureCountByType(HEXAGON) > 0)
				Message = Message + to_string(pManager->GetSelectedFigureCountByType(HEXAGON)) + " Hexagon(s),";
			if (pManager->GetSelectedFigureCountByType(CIRCLE) > 0)
				Message = Message + to_string(pManager->GetSelectedFigureCountByType(CIRCLE)) + " Circle(s),";
			if (pManager->GetSelectedFigureCountByType(SQUARE) > 0)
				Message = Message + to_string(pManager->GetSelectedFigureCountByType(SQUARE)) + " Square(s),";
			pOut->PrintMessage(Message);
	}
}
