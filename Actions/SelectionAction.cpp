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

void SelectionAction::UpdateNumOfFigures()
{
	NumOfHex = 0;
	NumOfCirc = 0;
	NumOfRect = 0;
	NumOfSqr = 0;
	NumOfTri = 0;
	for (int i = 0; i < NumOfFigures; i++)
	{
		switch (SelectedFigs[i]->GetFigType())
		{
		case HEXAGON:NumOfHex++; break;
		case CIRCLE:NumOfCirc++; break;
		case TRIANGLE:NumOfRect++; break;
		case SQUARE:NumOfSqr++; break;
		case RECTANGLE:	NumOfTri++; break;
		}
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
	if ( pFig == NULL)
	{
		for (int i = NumOfFigures; i >= 0; i--)
			SelectedFigs[i] = NULL;
		NumOfFigures = 0;
	}
	else if(NumOfFigures<200)
	{
		pFig->SetSelected(true);
		SelectedFigs[NumOfFigures++];
		if (NumOfFigures == 1)
			pFig->PrintInfo(pOut);
		else
		{
			UpdateNumOfFigures();
			pOut->PrintMessage("Selected: " + to_string(NumOfRect) + " Rectangle(s)," + to_string(NumOfTri) + " triangle(s)," + to_string(NumOfHex) + " Hexagon(s), " + to_string(NumOfCirc) + " circle(s)," + to_string(NumOfSqr) + " Square(s)");
		}
	}

}
