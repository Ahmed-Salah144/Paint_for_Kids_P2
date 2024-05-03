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
		for (int i = 0; i < pManager->SelectedFigCount; i++)
		{
			if (pFig->IsTheSame(pManager->SelectedFigList[i]))
			{
				pManager->SelectedFigList[i] = pManager->SelectedFigList[pManager->SelectedFigCount - 1];
				pManager->SelectedFigList[pManager->SelectedFigCount - 1] = NULL;
				break;
			}
		}
		pManager->SelectedFigCount--;
		pManager->UpdateNumOfFigures();
		return true;
	}
	return false;
}

bool SelectionAction::SelectFigure(CFigure* pFig)
{
	if (pFig == NULL)
		return false;
	if (pManager->SelectedFigCount < 200)
	{
		if (!(pFig->IsSelected()))
		{
			pFig->SetSelected(true);
			pManager->SelectedFigList[pManager->SelectedFigCount++] = pFig;
			pManager->UpdateNumOfFigures();
			return true;
		}
	}
	return false;
}
void SelectionAction::ClearAllSelection()
{
	for (int i = 0; i < pManager->SelectedFigCount; i++)
	{
		pManager->SelectedFigList[i]->SetSelected(false);
		pManager->SelectedFigList[i]=NULL;
	}
	pManager->SelectedFigCount = 0;;
	pManager->UpdateNumOfFigures();
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
	if (pManager->SelectedFigCount == 0)
		pOut->PrintMessage("No Selected Figures");
	else if (pManager->SelectedFigCount == 1)
		pManager->SelectedFigList[0]->PrintInfo(pOut);
	else
		pOut->PrintMessage("Selected: " + to_string(pManager->SelectedRects) + " Rectangle(s)," + to_string(pManager->SelectedTris) + " triangle(s)," + to_string(pManager->SelectedHexes) + " Hexagon(s), " + to_string(pManager->SelectedCircs) + " circle(s)," + to_string(pManager->SelectedSqrs) + " Square(s)");
}
