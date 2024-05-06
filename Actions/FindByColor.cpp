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
	srand(time(NULL));
	RandNum = rand() % 6;
}

void FindByColor::GenRandColor() {
	Output* pOut = pManager->GetOutput();
	if (pManager->GetFigureByColor(SelectedColor) == NULL)
	{
		pOut->PrintMessage("no colored figures");
		return;
	}

	while (true)
	{
		srand(time(NULL));
		RandNum = rand() % 6;

		if (RandNum == 0 && pManager->GetFigureByColor(SelectedColor) != NULL)
		{
			pOut->ClearStatusBar();
			pOut->PrintMessage("select all black figures");
			SelectedColor = BLACK;
			break;
		}
		else if (RandNum == 1 && pManager->GetFigureByColor(SelectedColor) != NULL) {
			pOut->ClearStatusBar();
			pOut->PrintMessage("select all yellow figures");
			SelectedColor = YELLOW;
			break;
		}
		else if (RandNum == 2 && pManager->GetFigureByColor(SelectedColor) != NULL)
		{
			pOut->ClearStatusBar();
			pOut->PrintMessage("select all orange figures");
			SelectedColor = ORANGE;
			break;
		}
		else if (RandNum == 3 && pManager->GetFigureByColor(SelectedColor) != NULL)
		{
			pOut->ClearStatusBar();
			pOut->PrintMessage("select all red figures");
			SelectedColor = RED;
			break;
		}
		else if (RandNum == 4 && pManager->GetFigureByColor(SelectedColor) != NULL) {
			pOut->ClearStatusBar();
			pOut->PrintMessage("select all green FIGURES");
			SelectedColor = GREEN;
			break;
		}
		else if (RandNum == 5 && pManager->GetFigureByColor(SelectedColor) != NULL) {
			pOut->ClearStatusBar();
			pOut->PrintMessage("select all blue figures");
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
	Restart = false;
	Output* pOut = pManager->GetOutput();
	//pOut->PrintMessage("execute command");
	//CFigure* pFig = pManager->GetFigure(Click.x, Click.y);
	Action* pAct = new SaveAction(pManager, 1);
	pAct->Execute();
	delete pAct;
	pOut->ClearStatusBar();
	GenRandColor();
	PickColorAction();
	if (Restart)
	{
		Action* pAct = new LoadAction(pManager, 1);
		pAct->Execute();
		delete pAct;
		pOut->ClearStatusBar();
		FindByColor::Execute();
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
			break;
		}
		if (pManager->GetFigure(Click.x, Click.y) == NULL || pManager->GetFigure(Click.x, Click.y)->GetDrawClr() != SelectedColor)
		{

			pOut->PrintMessage("selected wrong figure");
			WrongCount++;
			if (pManager->GetFigure(Click.x, Click.y) == NULL)
			{
				pOut->PrintMessage("no figure Selected");
			}
			else
			{
				pManager->RemoveFigure(PickedFigure->GetID());
				delete PickedFigure;
			}
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
		pOut->PrintMessage("you got right times: " + to_string(RightCount) + " you got wrong times: " + to_string(WrongCount));

	}


};