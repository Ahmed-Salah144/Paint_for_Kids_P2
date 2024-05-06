#include "FindByTypeAndColor.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <string>
#include"..\Actions\SaveAction.h"
#include"..\Actions\LoadAction.h"

FindByTypeAndColor::FindByTypeAndColor(ApplicationManager* pApp) : Action(pApp) {
	RightCount = 0;
	WrongCount = 0;
	SelectedColor = WHITE;
	srand(time(NULL));
	RandNum = rand() % 6;
	Restart = false;
	Exit = false;
};




void FindByTypeAndColor::GenRandColor2()
{
	int count = 0;
	string s1="nah";
	string s2="id win";

	Output* pOut = pManager->GetOutput();
	if (pManager->GetFigureCount() == 0)
	{
		pOut->PrintMessage("No Figures");
		return;
	}
	if (pManager->GetFigureByColor(YELLOW) == NULL &&
		pManager->GetFigureByColor(RED) == NULL &&
		pManager->GetFigureByColor(BLACK) == NULL &&
		pManager->GetFigureByColor(GREEN) == NULL &&
		pManager->GetFigureByColor(ORANGE) == NULL &&
		pManager->GetFigureByColor(BLUE) == NULL)
	{
		pOut->PrintMessage("No colored figures");
		return;
	}
	CFigure* TempFig;
	do {
		TempFig = pManager->GetRandomFigure();
		pOut->PrintMessage(to_string(count++));
	} while (!TempFig->IsFilled());

	SelectedColor = TempFig->GetFillClr();
	SelectedShape = TempFig->GetFigType();


	if (SelectedShape == TRIANGLE)
	{
		s2 = "triangle";
	}
	else if (SelectedShape == SQUARE)
	{
		s2 = "square";
	}
	else if (SelectedShape == CIRCLE)
	{
		s2 = "circle";
	}
	else if (SelectedShape == HEXAGON)
	{
		s2 = "hexagon";
	}
	else if (SelectedShape == RECTANGLE)
	{
		s2 = "rectangle";
	}

	if (SelectedColor == GREEN)
	{
		s1 = "green ";
	}
	else if (SelectedColor == BLACK)
	{
		s1 = "black ";
	}
	else if (SelectedColor == YELLOW)
	{
		s1 = "yellow ";
	}
	else if (SelectedColor == RED)
	{
		s1 = "red ";
	}
	else if (SelectedColor == BLUE) {
		s1 = "blue ";
	}
	else if (SelectedColor == ORANGE)
	{
		s1 = "ORANGE ";

	}




	pOut->PrintMessage("Select all " + s1 + s2 + "s");



	//if (SelectedColor == GREEN)
	//{

	//	SelectedColor = GREEN;
	//	SelectedShape = TempFig->GetFigType();
	//}
	//else if (SelectedColor == YELLOW)
	//{
	//	pOut->PrintMessage("Select all Yellow figures" + TempFig->GetFigType());
	//	SelectedColor = YELLOW;
	//	SelectedShape = TempFig->GetFigType();
	//}
	//else if (SelectedColor == ORANGE)
	//{
	//	pOut->PrintMessage("Select all Orange figures" + TempFig->GetFigType());
	//	SelectedColor = ORANGE;
	//	SelectedShape = TempFig->GetFigType();
	//}
	//else if (SelectedColor == BLUE)
	//{
	//	pOut->PrintMessage("Select all Blue " + TempFig->GetFigType());
	//	SelectedColor = BLUE;
	//	SelectedShape = TempFig->GetFigType();
	//}
	//else if (SelectedColor == RED)
	//{
	//	pOut->PrintMessage("Select all Red figures" + TempFig->GetFigType());
	//	SelectedColor = RED;
	//	SelectedShape = TempFig->GetFigType();
	//}
	//else if (SelectedColor == BLACK)
	//{
	//	pOut->PrintMessage("Select all Black figures" + TempFig->GetFigType());
	//	SelectedColor = BLACK;
	//	SelectedShape = TempFig->GetFigType();
	//}	//if (SelectedColor == GREEN)
	//{

	//	SelectedColor = GREEN;
	//	SelectedShape = TempFig->GetFigType();
	//}
	//else if (SelectedColor == YELLOW)
	//{
	//	pOut->PrintMessage("Select all Yellow figures" + TempFig->GetFigType());
	//	SelectedColor = YELLOW;
	//	SelectedShape = TempFig->GetFigType();
	//}
	//else if (SelectedColor == ORANGE)
	//{
	//	pOut->PrintMessage("Select all Orange figures" + TempFig->GetFigType());
	//	SelectedColor = ORANGE;
	//	SelectedShape = TempFig->GetFigType();
	//}
	//else if (SelectedColor == BLUE)
	//{
	//	pOut->PrintMessage("Select all Blue " + TempFig->GetFigType());
	//	SelectedColor = BLUE;
	//	SelectedShape = TempFig->GetFigType();
	//}
	//else if (SelectedColor == RED)
	//{
	//	pOut->PrintMessage("Select all Red figures" + TempFig->GetFigType());
	//	SelectedColor = RED;
	//	SelectedShape = TempFig->GetFigType();
	//}
	//else if (SelectedColor == BLACK)
	//{
	//	pOut->PrintMessage("Select all Black figures" + TempFig->GetFigType());
	//	SelectedColor = BLACK;
	//	SelectedShape = TempFig->GetFigType();
	//}




};


void FindByTypeAndColor::ReadActionParameters()
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
	else if (Click.x > UI.MenuItemWidth * 2 && Click.x < UI.MenuItemWidth * 3 && Click.y < UI.ToolBarHeight)
	{
		Exit = true;
		Restart = true;
	}
}

void FindByTypeAndColor::Execute()
{
	Action* pAct = new LoadAction(pManager, 1);
	pAct->Execute();
	delete pAct;
	Output* pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
	pManager->UpdateInterface();
	//pOut->PrintMessage("execute command");
	//CFigure* pFig = pManager->GetFigure(Click.x, Click.y);
	//GenRandShape();
	GenRandColor2();
	PickFigureAndColorAction();
	if (Restart)
	{
		RightCount = 0;
		WrongCount = 0;
		SelectedColor = WHITE;
		srand(time(NULL));
		RandNum = rand() % 6;
		Restart = false;
		Exit = false;
		this->Execute();
	}
}




void FindByTypeAndColor::PickFigureAndColorAction() {
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	while (pManager->GetFigureCountByType(SelectedShape) > 0 && pManager->GetFigureByColor(SelectedColor) != NULL)
	{
		ReadActionParameters();
		if (Exit)
		{
			pOut->ClearStatusBar();
			break;
		}
		PickedFigure = pManager->GetFigure(Click.x, Click.y);
		if (PickedFigure == NULL)
		{
			WrongCount++;
			pOut->PrintMessage("no figure Selected");
		}
		else if (!PickedFigure->IsFilled())
		{
			WrongCount++;
			pManager->RemoveFigure(PickedFigure->GetID());
			delete PickedFigure;
			pOut->PrintMessage("selected wrong figure");
			pManager->UpdateInterface();
		}
		else if (PickedFigure->GetFillClr() != SelectedColor)
		{

			pOut->PrintMessage("selected wrong figure");
			WrongCount++;
			pManager->RemoveFigure(PickedFigure->GetID());
			delete PickedFigure;
			pManager->UpdateInterface();
		}
		else if (PickedFigure->GetFigType() != SelectedShape)
		{
			pOut->PrintMessage("selected wrong figure");
			WrongCount++;
			pManager->RemoveFigure(PickedFigure->GetID());
			delete PickedFigure;
			pManager->UpdateInterface();
		}
		else if (PickedFigure->GetFillClr() == SelectedColor && PickedFigure->GetFigType() == SelectedShape)
		{
			pOut->PrintMessage("Selected right figure");
			PickedFigure = pManager->GetFigure(Click.x, Click.y);
			pManager->RemoveFigure(PickedFigure->GetID());
			delete PickedFigure;
			RightCount++;
			pManager->UpdateInterface();
		}
	}

	if (pManager->GetFigureCountByType(SelectedShape) == 0 || pManager->GetFigureByColor(SelectedColor) == NULL)
	{
		Action* pAct = new LoadAction(pManager, 1);
		pAct->Execute();
		delete pAct;
		//&& pManager->GetFigureByColor(SelectedColor) == NULL
		//pOut->ClearStatusBar();
		pOut->ClearStatusBar();
		pOut->PrintMessage("you got right times: " + to_string(RightCount) + " you got wrong times: " + to_string(WrongCount));
	}



};































