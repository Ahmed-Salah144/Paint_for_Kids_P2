#include "FindByType.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <string>

FindByType::FindByType(ApplicationManager* pApp) : Action(pApp) {
	RightCount = 0;
	WrongCount = 0;
	srand(time(NULL));
	RandNum =rand() % 5;
}

void FindByType::ReadActionParameters() 
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pIn->GetPointClicked(Click.x, Click.y);
}

void FindByType::Execute()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("execute command");
	CFigure* pFig = pManager->GetFigure(Click.x, Click.y);
	GenRandShape();
	PickFigureAction(pFig);
}


//8ayar le switch
//condition en lazem yekon fe figure
void FindByType::GenRandShape() {
	Output* pOut = pManager->GetOutput();
	if (pManager->GetFigureCount() == 0)
	{
		 pOut->PrintMessage("no figures");
		 return;
	}
	bool exit = true;
	while (true) {
		srand(time(NULL));
		RandNum = rand() % 5;
		if (RandNum == 0 && pManager->GetFigureCountByType(SQUARE)!=0)
		{
			pOut->ClearStatusBar();
			pOut->PrintMessage("select all squares");
			SelectedShape = SQUARE;
			break;
		}
		else if (RandNum == 1 && pManager->GetFigureCountByType(RECTANGLE) != 0) {
			pOut->ClearStatusBar();
			pOut->PrintMessage("select all rectangles");
			SelectedShape = RECTANGLE;
			break;
		}
		else if (RandNum == 2 && pManager->GetFigureCountByType(HEXAGON) != 0)
		{
			pOut->ClearStatusBar();
			pOut->PrintMessage("select all hexagons");
			SelectedShape = HEXAGON;
			break;
		}
		else if (RandNum == 3 && pManager->GetFigureCountByType(TRIANGLE) != 0)
		{
			pOut->ClearStatusBar();
			pOut->PrintMessage("select all triangles");
			SelectedShape = TRIANGLE;
			break;
		}
		else if (RandNum == 4 && pManager->GetFigureCountByType(CIRCLE) != 0) {
			pOut->ClearStatusBar();
			pOut->PrintMessage("select all circles");
			SelectedShape = CIRCLE;
			break;
		}
	}

}

//lesa metab2y el save we el load
void FindByType:: PickFigureAction(CFigure* pFig) {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int x;
	int y;

	while (pManager->GetFigureCountByType(SelectedShape) > 0)
	{
		ReadActionParameters();
		pIn->GetPointClicked(x, y);

		if (pManager->GetFigure(x, y) == NULL || pManager->GetFigure(x, y)->GetFigType() != SelectedShape)
		{
			pOut->ClearStatusBar();
			pOut->PrintMessage("selected wrong figure");
			WrongCount++;
		}
		else
		{
			FigureToDelete = pManager->GetFigure(x, y);
			pManager->RemoveFigure(FigureToDelete->GetID());
			delete FigureToDelete;
			RightCount++;
			pManager->UpdateInterface();
		}
	}

	if (pManager->GetFigureCountByType(SelectedShape) == 0)
	{
		pOut->PrintMessage("you got right times: " + to_string(RightCount)+ " you got wrong times: " + to_string(WrongCount));

	}



}
