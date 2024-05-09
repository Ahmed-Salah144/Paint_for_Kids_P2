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




void FindByTypeAndColor::GenRandColor2() //generates a random color and type uses the same function since if we dont have a filled color we wont run the program
{
	//int count = 0;
	string s1;
	string s2;

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
		//pOut->PrintMessage(to_string(count++));
	} while (!TempFig->IsFilled());

	SelectedColor = TempFig->GetFillClr();
	SelectedShape = TempFig->GetFigType();


	if (SelectedShape == TRIANGLE) //converts the selected shape into a string
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


	if (SelectedColor == GREEN)  //converts the selected color into a string
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
	else if (true)
	{

	}

	pOut->PrintMessage("Select all " + s1 + s2 + "s");
};


void FindByTypeAndColor::ReadActionParameters()      //reads user input
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
	else if (Click.x > UI.MenuItemWidth * 5 && Click.x < UI.MenuItemWidth * 6 && Click.y < UI.ToolBarHeight)
	{
		Exit = true;
	}
	else if (Click.x > UI.MenuItemWidth * 2 && Click.x < UI.MenuItemWidth * 3 && Click.y < UI.ToolBarHeight) //restarts when clicked on again
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
	while (pManager->CheckTypeAndColor(SelectedColor, SelectedShape) != NULL)      //if there exists a figure with the picked color and type
	{
		ReadActionParameters();
		if (Exit)
		{
			pOut->ClearStatusBar();
			break;
		}
		PickedFigure = pManager->GetFigure(Click.x, Click.y); //if the kid clicked on the background
		if (PickedFigure == NULL)
		{
			WrongCount++;
			pOut->PrintMessage("no figure Selected");
		}
		else if (!PickedFigure->IsFilled())   //if the kid clicked on a non filled figure
		{
			WrongCount++;
			pManager->RemoveFigure(PickedFigure->GetID());
			delete PickedFigure;
			pOut->PrintMessage("selected wrong figure");
			pManager->UpdateInterface();
		}
		else if (PickedFigure->GetFillClr() != SelectedColor) //if the kid clicked on a color that was not chosen
		{

			pOut->PrintMessage("selected wrong figure");
			WrongCount++;
			pManager->RemoveFigure(PickedFigure->GetID());
			delete PickedFigure;
			pManager->UpdateInterface();
		}
		else if (PickedFigure->GetFigType() != SelectedShape)  //is the kid clicked on a shape that was not selected
		{
			pOut->PrintMessage("selected wrong figure");
			WrongCount++;
			pManager->RemoveFigure(PickedFigure->GetID());
			delete PickedFigure;
			pManager->UpdateInterface();
		}
		else if (PickedFigure->GetFillClr() == SelectedColor && PickedFigure->GetFigType() == SelectedShape)  //if the selected figure has the shape and color chosen
		{
			pOut->PrintMessage("Selected right figure");
			PickedFigure = pManager->GetFigure(Click.x, Click.y);
			pManager->RemoveFigure(PickedFigure->GetID());
			delete PickedFigure;
			RightCount++;
			pManager->UpdateInterface();
		}
	}

	if (pManager->CheckTypeAndColor(SelectedColor,SelectedShape) == NULL) //when all shapes with the chosen color and type are picked end the game and display the score
	{
		Action* pAct = new LoadAction(pManager, 1);
		pAct->Execute();
		delete pAct;
;
		pOut->ClearStatusBar();
		pOut->PrintMessage("you got right times: " + to_string(RightCount) + " you got wrong times: " + to_string(WrongCount));
	}



};































