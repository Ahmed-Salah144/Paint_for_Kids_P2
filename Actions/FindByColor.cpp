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

void FindByColor::GenRandColor2()  //generates random color
{
	int count = 0;
	Output* pOut = pManager->GetOutput();
	if (pManager->GetFigureCount() == 0)
	{
		pOut->PrintMessage("No Figures");
		return;
	}
	if (pManager->GetFigureByColor(YELLOW) == NULL &&         //checks that there are colored figures on the screen
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
	do { TempFig = pManager->GetRandomFigure();               //gets random color from the user
	pOut->PrintMessage(to_string(count++));
	} while (!TempFig->IsFilled());

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


void FindByColor::ReadActionParameters()
{
	pManager->GetInput()->GetPointClicked(Click.x, Click.y);
	if (Click.x > UI.MenuItemWidth * 3 && Click.x < UI.MenuItemWidth * 4 && Click.y < UI.ToolBarHeight) // switch to draw mode
	{
		Exit = true;
		pManager->ExecuteAction(TO_DRAW);
		Action* pAct = new LoadAction(pManager, 1);
		pAct->Execute();
		delete pAct;
	}
	else if (Click.x > UI.MenuItemWidth * 5 && Click.x < UI.MenuItemWidth * 6 && Click.y < UI.ToolBarHeight) // exits the program
	{
		Exit = true;
	}
	else if (Click.x > UI.MenuItemWidth * 0 && Click.x < UI.MenuItemWidth * 1 && Click.y < UI.ToolBarHeight) // switches to find by type
	{
		Exit = true;
		Restart = true;
		pManager->ExecuteAction(TYPE);
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


	while (pManager->GetFigureByColor(SelectedColor) != NULL) // while a colored figure from the picked color exists 
	{
		ReadActionParameters(); // if the user clicks on exit while running the program exits find by color
		if (Exit)
		{
			pOut->PrintMessage("Exited find by color");
			break;
		}
		PickedFigure = pManager->GetFigure(Click.x, Click.y);
		if (PickedFigure== NULL)    //checks if the kid clicked on the background
		{
			WrongCount++;
			pOut->PrintMessage("no figure Selected");
		}
		else if (!PickedFigure->IsFilled())   //checks if the kid clicked on a non filleed figure
		{
			WrongCount++;
			pManager->RemoveFigure(PickedFigure->GetID());
			delete PickedFigure;
			pOut->PrintMessage("selected wrong figure");
			pManager->UpdateInterface();
		}
		else if (PickedFigure->GetFillClr() != SelectedColor) //checks if the kid clicked on the non picked color
		{

			pOut->PrintMessage("selected wrong figure");
			WrongCount++;
			pManager->RemoveFigure(PickedFigure->GetID());
			delete PickedFigure;
			pManager->UpdateInterface();
		}
		else
		{
			pOut->PrintMessage("Selected right figure");  //checks if the figure clicked is correct and increments the counter
			PickedFigure = pManager->GetFigure(Click.x, Click.y);
			pManager->RemoveFigure(PickedFigure->GetID());
			delete PickedFigure;
			RightCount++;
			pManager->UpdateInterface();
		}
	}

	if (pManager->GetFigureByColor(SelectedColor) == NULL)  //if no more of the selected color exists exit from the program and restart the program
	{
		Action* pAct = new LoadAction(pManager, 1);
		pAct->Execute();
		delete pAct;
		pOut->ClearStatusBar();
		pOut->PrintMessage("You got right times: " + to_string(RightCount) + " You got wrong times: " + to_string(WrongCount));

	}


};