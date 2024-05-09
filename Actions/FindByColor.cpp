#include "FindByColor.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <string>
#include"..\Actions\SaveAction.h"
#include"..\Actions\LoadAction.h"



FindByColor::FindByColor(ApplicationManager* pApp) : Action(pApp) {
	RightCount = 0;
	WrongCount = 0;
	SelectedColor = WHITE;
	srand(time(NULL));
	RandNum = rand() % 6;
	Restart = false;
	Exit = false;
}

void FindByColor::GenRandColor2()
{
	int count = 0;
	Output* pOut = pManager->GetOutput();
	if (pManager->GetFigureCount() == 0)
	{
		pOut->PrintMessage("No Figures");
		return;
	}
/*	if (pManager->GetFigureByColor(YELLOW) == NULL &&
		pManager->GetFigureByColor(RED) == NULL &&
		pManager->GetFigureByColor(BLACK) == NULL &&
		pManager->GetFigureByColor(GREEN) == NULL &&
		pManager->GetFigureByColor(ORANGE) == NULL &&
		pManager->GetFigureByColor(BLUE) == NULL)
	{
		pOut->PrintMessage("No colored figures");
		return;
	}*/
	CFigure* TempFig = NULL;
	//do {
	TempFig = pManager->GetRandomFigure(true);
	//pOut->PrintMessage(to_string(count++));
//} while (!TempFig->IsFilled());

	if (TempFig == NULL)
	{
		pOut->PrintMessage("No colored figures");
		return;
	}


	SelectedColor = TempFig->GetFillClr();
	if (SelectedColor==GREEN)
	{
		pOut->PrintMessage("Select all Green figures");
		SelectedColor = GREEN;
	}
	else if (SelectedColor == YELLOW)
	{
		pOut->PrintMessage("Select all Yellow figures");
		SelectedColor = YELLOW;
	}
	else if (SelectedColor == ORANGE)
	{
		pOut->PrintMessage("Select all Orange figures");
		SelectedColor = ORANGE;
	}
	else if (SelectedColor == BLUE)
	{
		pOut->PrintMessage("Select all Blue figures");
		SelectedColor = BLUE;
	}
	else if (SelectedColor == RED)
	{
		pOut->PrintMessage("Select all Red figures");
		SelectedColor = RED;
	}
	else if (SelectedColor == BLACK)
	{
		pOut->PrintMessage("Select all Black figures");
		SelectedColor = BLACK;
	}
}
void FindByColor::GenRandColor() {
	Output* pOut = pManager->GetOutput();
	//color Colors[6] = { GREEN ,RED,BLUE,BLACK,YELLOW,ORANGE };

	if (pManager->GetFigureByColor(YELLOW) == NULL && pManager->GetFigureByColor(RED) == NULL && pManager->GetFigureByColor(BLACK) == NULL && pManager->GetFigureByColor(GREEN) == NULL && pManager->GetFigureByColor(ORANGE) == NULL && pManager->GetFigureByColor(RED) == NULL)
	{
		pOut->PrintMessage("No colored figures");
		return;
	}
	//int count = 0;
	while (true)
	{
		srand(time(NULL));
		RandNum = rand() % 6;
		//pOut->PrintMessage(to_string(count++));

		if (RandNum == 0 && pManager->GetFigureByColor(SelectedColor) != NULL)
		{
			pOut->ClearStatusBar();
			pOut->PrintMessage("Select all black figures");
			SelectedColor = BLACK;
			break;
		}
		else if (RandNum == 1 && pManager->GetFigureByColor(SelectedColor) != NULL) {
			pOut->ClearStatusBar();
			pOut->PrintMessage("Select all yellow figures");
			SelectedColor = YELLOW;
			break;
		}
		else if (RandNum == 2 && pManager->GetFigureByColor(SelectedColor) != NULL)
		{
			pOut->ClearStatusBar();
			pOut->PrintMessage("Select all orange figures");
			SelectedColor = ORANGE;
			break;
		}
		else if (RandNum == 3 && pManager->GetFigureByColor(SelectedColor) != NULL)
		{
			pOut->ClearStatusBar();
			pOut->PrintMessage("Select all red figures");
			SelectedColor = RED;
			break;
		}
		else if (RandNum == 4 && pManager->GetFigureByColor(SelectedColor) != NULL) {
			pOut->ClearStatusBar();
			pOut->PrintMessage("Select all green figures");
			SelectedColor = GREEN;
			break;
		}
		else if (RandNum == 5 && pManager->GetFigureByColor(SelectedColor) != NULL) {
			pOut->ClearStatusBar();
			pOut->PrintMessage("Select all blue figures");
			SelectedColor = BLUE;
			break;
		}
	}

};

void FindByColor::ReadActionParameters()
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
	else if (Click.x > UI.MenuItemWidth * 1 && Click.x < UI.MenuItemWidth * 2 && Click.y < UI.ToolBarHeight)
	{
		Exit = true;
		Restart = true;
	}
}


void FindByColor::Execute()
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
	PickColorAction();
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




void FindByColor::PickColorAction() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


	while (pManager->GetFigureByColor(SelectedColor) != NULL)
	{
		ReadActionParameters();
		if (Exit)
		{
			pOut->ClearStatusBar();
			break;
		}
		PickedFigure = pManager->GetFigure(Click.x, Click.y);
		if (PickedFigure== NULL)
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
		else
		{
			pOut->PrintMessage("Selected right figure");
			PickedFigure = pManager->GetFigure(Click.x, Click.y);
			pManager->RemoveFigure(PickedFigure->GetID());
			delete PickedFigure;
			RightCount++;
			pManager->UpdateInterface();
		}
	}

	if (pManager->GetFigureByColor(SelectedColor) == NULL)
	{
		Action* pAct = new LoadAction(pManager, 1);
		pAct->Execute();
		delete pAct;
		pOut->ClearStatusBar();
		pOut->PrintMessage("You got right times: " + to_string(RightCount) + " You got wrong times: " + to_string(WrongCount));

	}


};