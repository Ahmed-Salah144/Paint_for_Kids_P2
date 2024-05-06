//#include "FindByColor.h"
//#include "..\Figures\CFigure.h"
//#include "..\ApplicationManager.h"
//#include "..\GUI\input.h"
//#include "..\GUI\Output.h"
//#include <string>
//
//
//
//FindByColor::FindByColor(ApplicationManager* pApp) : Action(pApp) {
//	RightCount = 0;
//	WrongCount = 0;
//	srand(time(NULL));
//	RandNum = rand() % 5;
//}
//
//void FindByColor::GenRandColor() {
//	Output* pOut = pManager->GetOutput();
//	if (pManager->GetFigureCountByColor(SelectedColor) == 0)
//	{
//		pOut->PrintMessage("no colored figures");
//		return;
//	}
//
//
//	if (RandNum == 0)
//	{
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all black figures");
//		SelectedColor = COLOR_BLACK;
//	}
//	else if (RandNum == 1) {
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all yellow figures");
//		SelectedColor = COLOR_YELLOW;
//	}
//	else if (RandNum == 2)
//	{
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all orange figures");
//		SelectedColor = COLOR_ORANGE;
//	}
//	else if (RandNum == 3)
//	{
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all red figures");
//		SelectedColor = COLOR_RED;
//	}
//	else if (RandNum == 4) {
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all green FIGURES");
//		SelectedColor = COLOR_GREEN;
//	}
//	else if (RandNum == 5) {
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all blue figures");
//		SelectedColor = COLOR_BLUE;
//	}
//	
//
//};
//
//
//
//void FindByColor::PickColorAction(CFigure* pFig) {
//	Output* pOut = pManager->GetOutput();
//	Input* pIn = pManager->GetInput();
//	int x;
//	int y;
//
//	while (pManager->GetFigureCountByColor(SelectedColor) > 0)
//	{
//		ReadActionParameters();
//		pIn->GetPointClicked(x, y);
//
//		if (pManager->GetFigure(x, y) == NULL || pManager->GetFigure(x, y)->GetDrawClr() != SelectedColor)
//		{
//			pOut->ClearStatusBar();
//			pOut->PrintMessage("selected wrong figure");
//			WrongCount++;
//		}
//		else
//		{
//			FigureToDelete = pManager->GetFigure(x, y);
//			pManager->RemoveFigure(FigureToDelete->GetID());
//			delete FigureToDelete;
//			RightCount++;
//			pManager->UpdateInterface();
//		}
//	}
//
//	if (pManager->GetFigureCountByColor(SelectedColor) == 0)
//	{
//		pOut->PrintMessage("you got right times: " + to_string(RightCount) + " you got wrong times: " + to_string(WrongCount));
//
//	}
//
//
//};
