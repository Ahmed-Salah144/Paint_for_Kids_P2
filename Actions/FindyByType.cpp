#include "FindByType.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include"..\Actions\SaveAction.h"
#include"..\Actions\LoadAction.h"

FindByType::FindByType(ApplicationManager* pApp) : Action(pApp) {     //constructor
	RightCount = 0;
	WrongCount = 0;
	srand(time(NULL));
	RandNum =rand() % 5;
	Exit = false;
	Restart = false;
}

void FindByType::ReadActionParameters()   // reading parameters from the user
{
	pManager->GetInput()->GetPointClicked(Click.x, Click.y);
	if (Click.x > UI.MenuItemWidth * 3 && Click.x < UI.MenuItemWidth * 4 && Click.y < UI.ToolBarHeight)
	{
		Exit = true;
		pManager->ExecuteAction(TO_DRAW);
		Action* pAct = new LoadAction(pManager, 1);
		pAct->Execute();
		delete pAct;
	}
	else if (Click.x > UI.MenuItemWidth * 5 && Click.x < UI.MenuItemWidth * 6 && Click.y < UI.ToolBarHeight) //exiting find by type
	{
		Exit = true;
	}
	else if (Click.x > UI.MenuItemWidth * 0 && Click.x < UI.MenuItemWidth * 1 && Click.y < UI.ToolBarHeight) // restarting game
	{
		Exit = true;
		Restart = true;
	}

}

void FindByType::Execute() //running fucntions on execute
{
	Restart = false;
	Exit = false;
	Action* pAct = new LoadAction(pManager, 1);
	pAct->Execute();
	delete pAct;
	Output* pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
	pManager->UpdateInterface();
	GenRandShape();
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

void FindByType::GenRandShape() //making sure a figure exists and generating random shape from the list
{
	Output* pOut = pManager->GetOutput(); //cheking the existence of the figure
	if (pManager->GetFigureCount() == 0)
	{
		pOut->PrintMessage("No Figures");
		return;
	}
	SelectedShape=pManager->GetRandomFigure(false)->GetFigType(); // selecting a random figure
	switch (SelectedShape)
	{
	case SQUARE:pOut->PrintMessage("Select All Squares");break;
	case HEXAGON:pOut->PrintMessage("Select All Hexagons");break;
	case CIRCLE:pOut->PrintMessage("Select All Circles");break;
	case RECTANGLE:pOut->PrintMessage("Select All Rectangles");break;
	case TRIANGLE:pOut->PrintMessage("Select All Triangles");break;
	}
}



void FindByType::PickFigureAction() {
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	while (pManager->GetFigureCountByType(SelectedShape) > 0) // while there exists a shape of the picked type
	{
		ReadActionParameters(); // if the user clicks on exit while running the program it exits find by type not the program
		if (Exit)
		{
			pOut->PrintMessage("exited find by type");
			break;
		}


		if (pManager->GetFigure(Click.x, Click.y) == NULL || pManager->GetFigure(Click.x, Click.y)->GetFigType() != SelectedShape) // if the user clicks on a figure other than the one required or clicks on the background
		{
			pOut->PrintMessage("Selected wrong figure");
			WrongCount++;
			PickedFigure = pManager->GetFigure(Click.x, Click.y);
			if (pManager->GetFigure(Click.x, Click.y) == NULL)
				pOut->PrintMessage("No figure selected");
			else
			{
				pManager->RemoveFigure(PickedFigure->GetID()); //removes the figure clicked on
				delete PickedFigure;
			}
			pManager->UpdateInterface();
		}
		else
		{
			pOut->PrintMessage("Selected right figure");             //if not selected wrong figure then selected right figure
			PickedFigure = pManager->GetFigure(Click.x, Click.y);
			pManager->RemoveFigure(PickedFigure->GetID());
			delete PickedFigure;
			RightCount++;
			pManager->UpdateInterface();
		}
	}

	if (pManager->GetFigureCountByType(SelectedShape) == 0)          //exits program when no figures of the picked type are left
	{
		Action* pAct = new LoadAction(pManager, 1);
		pAct->Execute();
		delete pAct;
		pOut->PrintMessage("you got right times: " + to_string(RightCount) + " you got wrong times: " + to_string(WrongCount));
	}
}
