//#include "FindByTypeAndColor.h"
//#include "...GUI\input.h"
//#include "...GUI\Output.h"
//#include "ApplicationManager.h"
//
//FindByTypeAndColor::FindByTypeAndColor(ApplicationManager* pApp) : Action(pApp) {
//	RightCount = 0;
//	WrongCount = 0;
//	rands = x.RandomShape();
//	randc = x.RandomColor();
//};
//
//
//void GenRandShapeAndColor() {
//	Output* pOut = pManager->GetOutput();
//	do {
//		rands = x.RandomShape();
//		randc = x.RandomColor();
//	} while ((rands == 0 && pManager->GetFigureCountByType(SQUARE) == 0 && randC == 0 && pManager->GetFigureByColor(COLOR_BLACK) == 0) ||
//		(rands == 0 && pManager->GetFigureCountByType(SQUARE) == 0 && randC == 1 && pManager->GetFigureByColor(COLOR_YELLOW) == 0) ||
//		(rands == 0 && pManager->GetFigureCountByType(SQUARE) == 0 && randC == 2 && pManager->GetFigureByColor(COLOR_ORANGE) == 0) ||
//		(rands == 0 && pManager->GetFigureCountByType(SQUARE) == 0 && randC == 3 && pManager->GetFigureByColor(COLOR_RED) == 0) ||
//		(rands == 0 && pManager->GetFigureCountByType(SQUARE) == 0 && randC == 4 && pManager->GetFigureByColor(COLOR_GREEN) == 0) ||
//		(rands == 0 && pManager->GetFigureCountByType(SQUARE) == 0 && randC == 5 && pManager->GetFigureByColor(COLOR_BLUE) == 0) ||
//		(rands == 1 && pManager->GetFigureCountByType(RECTANGLE) == 0 && randC == 0 && pManager->GetFigureByColor(COLOR_BLACK) == 0) ||
//		(rands == 1 && pManager->GetFigureCountByType(RECTANGLE) == 0 && randC == 1 && pManager->GetFigureByColor(COLOR_YELLOW) == 0) ||
//		(rands == 1 && pManager->GetFigureCountByType(RECTANGLE) == 0 && randC == 2 && pManager->GetFigureByColor(COLOR_ORANGE) == 0) ||
//		(rands == 1 && pManager->GetFigureCountByType(RECTANGLE) == 0 && randC == 3 && pManager->GetFigureByColor(COLOR_RED) == 0) ||
//		(rands == 1 && pManager->GetFigureCountByType(RECTANGLE) == 0 && randC == 4 && pManager->GetFigureByColor(COLOR_GREEN) == 0) ||
//		(rands == 1 && pManager->GetFigureCountByType(RECTANGLE) == 0 && randC == 5 && pManager->GetFigureByColor(COLOR_BLUE) == 0) ||
//		(rands == 2 && pManager->GetFigureCountByType(HEXAGON) == 0 && randC == 0 && pManager->GetFigureByColor(COLOR_BLACK) == 0) ||
//		(rands == 2 && pManager->GetFigureCountByType(HEXAGON) == 0 && randC == 1 && pManager->GetFigureByColor(COLOR_YELLOW) == 0) ||
//		(rands == 2 && pManager->GetFigureCountByType(HEXAGON) == 0 && randC == 2 && pManager->GetFigureByColor(COLOR_ORANGE) == 0) ||
//		(rands == 2 && pManager->GetFigureCountByType(HEXAGON) == 0 && randC == 3 && pManager->GetFigureByColor(COLOR_RED) == 0) ||
//		(rands == 2 && pManager->GetFigureCountByType(HEXAGON) == 0 && randC == 4 && pManager->GetFigureByColor(COLOR_GREEN) == 0) ||
//		(rands == 2 && pManager->GetFigureCountByType(HEXAGON) == 0 && randC == 5 && pManager->GetFigureByColor(COLOR_BLUE) == 0) ||
//		(rands == 3 && pManager->GetFigureCountByType(TRIANGLE) == 0 && randC == 0 && pManager->GetFigureByColor(COLOR_BLACK) == 0) ||
//		(rands == 3 && pManager->GetFigureCountByType(TRIANGLE) == 0 && randC == 1 && pManager->GetFigureByColor(COLOR_YELLOW) == 0) ||
//		(rands == 3 && pManager->GetFigureCountByType(TRIANGLE) == 0 && randC == 2 && pManager->GetFigureByColor(COLOR_ORANGE) == 0) ||
//		(rands == 3 && pManager->GetFigureCountByType(TRIANGLE) == 0 && randC == 3 && pManager->GetFigureByColor(COLOR_RED) == 0) ||
//		(rands == 3 && pManager->GetFigureCountByType(TRIANGLE) == 0 && randC == 4 && pManager->GetFigureByColor(COLOR_GREEN) == 0) ||
//		(rands == 3 && pManager->GetFigureCountByType(TRIANGLE) == 0 && randC == 5 && pManager->GetFigureByColor(COLOR_BLUE) == 0) ||
//		(rands == 4 && pManager->GetFigureCountByType(CIRCLE) == 0 && randC == 0 && pManager->GetFigureByColor(COLOR_BLACK) == 0)
//		(rands == 4 && pManager->GetFigureCountByType(CIRCLE) == 0 && randC == 1 && pManager->GetFigureByColor(COLOR_YELLOW) == 0)
//		(rands == 4 && pManager->GetFigureCountByType(CIRCLE) == 0 && randC == 2 && pManager->GetFigureByColor(COLOR_ORANGE) == 0)
//		(rands == 4 && pManager->GetFigureCountByType(CIRCLE) == 0 && randC == 3 && pManager->GetFigureByColor(COLOR_RED) == 0)
//		(rands == 4 && pManager->GetFigureCountByType(CIRCLE) == 0 && randC == 4 && pManager->GetFigureByColor(COLOR_GREEN) == 0)
//		(rands == 4 && pManager->GetFigureCountByType(CIRCLE) == 0 && randC == 5 && pManager->GetFigureByColor(COLOR_BLUE) == 0));
//
//	if (rands == 0 && randc ==0)
//	{
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all black squares");
//		SelectedShape = SQUARE;
//	}
//	else if (rands == 0 && randc == 1)
//	{
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all yellow squares");
//		SelectedShape = SQUARE;
//	}
//	else if (rands == 0 && randc == 2)
//	{
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all orange squares");
//		SelectedShape = SQUARE;
//	}
//	else if (rands == 0 && randc == 3)
//	{
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all red squares");
//		SelectedShape = SQUARE;
//	}
//	else if (rands == 0 && randc == 4)
//	{
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all green squares");
//		SelectedShape = SQUARE;
//	}
//	else if (rands == 0 && randc == 5)
//	{
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all blue squares");
//		SelectedShape = SQUARE;
//	}
//	else if (rands == 1&& randc == 0) {
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all black rectangles");
//		SelectedShape = RECTANGLE;
//	}
//	else if (rand == 2)
//	{
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all hexagons");
//		SelectedShape = HEXAGON;
//	}
//	else if (rand == 3)
//	{
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all triangles");
//		SelectedShape = TRIANGLE;
//	}
//	else if (rand == 4) {
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("select all circles");
//		SelectedShape = CIRCLE;
//	}
//	else if (rand == -1)
//	{
//		pOut->ClearStatusBar();
//		pOut->PrintMessage("error no shapes");
//	}
//
//
//
//
//
//
//
//
//
//
//
//
//
//};
//
//
//
//
//
//
//
//
//
//
//
//
//void FindByTypeAndColor() {
//
//
//
//
//
//};
//
//
//
//
//
//
//
//

