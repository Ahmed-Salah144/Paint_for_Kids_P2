#include "FindByType.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
//#include <string>
#include"..\Actions\SaveAction.h"
#include"..\Actions\LoadAction.h"

FindByType::FindByType(ApplicationManager* pApp) : Action(pApp) {
	RightCount = 0;
	WrongCount = 0;
	srand(time(NULL));
	RandNum =rand() % 5;
	Exit = false;
	Restart = false;
}

void FindByType::ReadActionParameters()
{
	//Output* pOut = pManager->GetOutput();
	//Input* pIn = pManager->GetInput();
	pManager->GetInput()->GetPointClicked(Click.x, Click.y);
	if (Click.x > UI.MenuItemWidth * 3 && Click.x < UI.MenuItemWidth * 4 && Click.y < UI.ToolBarHeight)
	{
		Exit = true;
		pManager->ExecuteAction(TO_DRAW);
		Action* pAct = new LoadAction(pManager, 1);
		pAct->Execute();
		delete pAct;
	}
	else if (Click.x > UI.MenuItemWidth * 5 && Click.x < UI.MenuItemWidth * 6 && Click.y < UI.ToolBarHeight)
	{
		Exit = true;
	}
	else if (Click.x > UI.MenuItemWidth * 0 && Click.x < UI.MenuItemWidth * 1 && Click.y < UI.ToolBarHeight)
	{
		Exit = true;
		Restart = true;
	}
	//else if (Click.x > UI.MenuItemWidth * 1 && Click.x < UI.MenuItemWidth * 3 && Click.y < UI.ToolBarHeight)
	//{
		//Exit = true;
	//}
}

void FindByType::Execute()
{
	Restart = false;
	Exit = false;
	Action* pAct = new LoadAction(pManager, 1);
	pAct->Execute();
	delete pAct;
	Output* pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
	pManager->UpdateInterface();
	//pOut->PrintMessage("execute command");
	//CFigure* pFig = pManager->GetFigure(Click.x, Click.y);
	//GenRandShape();
	GenRandShape2();
	PickFigureAction();
	if (Restart)
	{
		RightCount = 0;
		WrongCount = 0;
		srand(time(NULL));
		RandNum = rand() % 6;
		Restart = false;
		Exit = false;
		this->Execute();
	}
}

void FindByType::GenRandShape2()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->GetFigureCount() == 0)
	{
		pOut->PrintMessage("No Figures");
		return;
	}
	SelectedShape=pManager->GetRandomFigure()->GetFigType();
	switch (SelectedShape)
	{
	case SQUARE:pOut->PrintMessage("Select All Squares");break;
	case HEXAGON:pOut->PrintMessage("Select All Hexagons");break;
	case CIRCLE:pOut->PrintMessage("Select All Circles");break;
	case RECTANGLE:pOut->PrintMessage("Select All Rectangles");break;
	case TRIANGLE:pOut->PrintMessage("Select All Triangles");break;
	}
}


//8ayar le switch
//condition en lazem yekon fe figure
void FindByType::GenRandShape() {
	Output* pOut = pManager->GetOutput(); 
	Input* pIn = pManager->GetInput();
	if (pManager->GetFigureCount() == 0)
	{
		 pOut->PrintMessage("No Figures");
		 return;
	}
	//bool exit = true;
	while (true)
	{
		srand(time(NULL));
		RandNum = rand() % 5;
		if (RandNum == 0 && pManager->GetFigureCountByType(SQUARE) != 0)
		{
			//pOut->ClearStatusBar();
			pOut->PrintMessage("select all squares");
			SelectedShape = SQUARE;
			break;
		}
		else if (RandNum == 1 && pManager->GetFigureCountByType(RECTANGLE) != 0) {
			//pOut->ClearStatusBar();
			pOut->PrintMessage("select all rectangles");
			SelectedShape = RECTANGLE;
			break;
		}
		else if (RandNum == 2 && pManager->GetFigureCountByType(HEXAGON) != 0)
		{
			//pOut->ClearStatusBar();
			pOut->PrintMessage("select all hexagons");
			SelectedShape = HEXAGON;
			break;
		}
		else if (RandNum == 3 && pManager->GetFigureCountByType(TRIANGLE) != 0)
		{
			//pOut->ClearStatusBar();
			pOut->PrintMessage("select all triangles");
			SelectedShape = TRIANGLE;
			break;
		}
		else if (RandNum == 4 && pManager->GetFigureCountByType(CIRCLE) != 0) {
			//pOut->ClearStatusBar();
			pOut->PrintMessage("select all circles");
			SelectedShape = CIRCLE;
			break;
		}
	}
}


//lesa metab2y el save we el load
void FindByType::PickFigureAction() {
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	//Input* pIn = pManager->GetInput();
	//int x;
	//int y;
	while (pManager->GetFigureCountByType(SelectedShape) > 0)
	{
		ReadActionParameters();
		if (Exit)
		{
			pOut->ClearStatusBar();
			break;
		}
		//pIn->GetPointClicked(x, y);

		if (pManager->GetFigure(Click.x, Click.y) == NULL || pManager->GetFigure(Click.x, Click.y)->GetFigType() != SelectedShape)
		{
			//pOut->ClearStatusBar();
			pOut->PrintMessage("Selected wrong figure");
			WrongCount++;
			PickedFigure = pManager->GetFigure(Click.x, Click.y);
			if (pManager->GetFigure(Click.x, Click.y) == NULL)
				pOut->PrintMessage("No figure selected");
			else
			{
				pManager->RemoveFigure(PickedFigure->GetID());
				delete PickedFigure;
			}
			pManager->UpdateInterface();
		}
		else
		{
			//pOut->ClearStatusBar();
			pOut->PrintMessage("Selected right figure");
			PickedFigure = pManager->GetFigure(Click.x, Click.y);
			pManager->RemoveFigure(PickedFigure->GetID());
			delete PickedFigure;
			RightCount++;
			pManager->UpdateInterface();
		}
	}

	if (pManager->GetFigureCountByType(SelectedShape) == 0)
	{
		Action* pAct = new LoadAction(pManager, 1);
		pAct->Execute();
		delete pAct;
		//pOut->ClearStatusBar();
		pOut->PrintMessage("you got right times: " + to_string(RightCount) + " you got wrong times: " + to_string(WrongCount));
	}
}
