#include "ApplicationManager.h"
#include "Figures\CFigure.h"
#include "Figures\CSquare.h"
#include "Figures\CRectangle.h"
#include "Figures\CHexagon.h"
#include "Figures\CTriangle.h"
#include "Figures\CCircle.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddSqrAction.h"
#include "Actions\AddTriAction.h"
#include "Actions\AddHexAction.h"
#include "Actions\AddCircAction.h"
#include "Actions\SelectionAction.h"
#include "Actions\BorderColorAction.h"
#include "Actions\FillColorAction.h"
#include "Actions\ClearAllAction.h"
#include "Actions\DeleteAction.h"
#include "Actions\BringToFrontAction.h"
#include "Actions\SendToBackAction.h"
#include "Actions\SaveAction.h"
#include "Actions\LoadAction.h"
#include "Actions\HalfSizeAction.h"
#include "Actions\DoubleSizeAction.h"
#include "Actions\VoiceAction.h"
#include "Actions\CopyAction.h"
#include "Actions\CutAction.h"
#include "Actions\PasteAction.h"
#include "Actions\FindByColor.h"
#include "Actions\FindByType.h"
#include "Actions\FindByTypeAndColor.h"
#include <cstdlib> 
#include<iostream>

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	CutFigureID = -1;
	Clipboard = NULL;
	FigCount = 0;
	SelectedFigCount = 0;
	SelectedRects = 0; SelectedSqrs = 0; SelectedHexes = 0; SelectedTris = 0; SelectedCircs = 0;
	NumOfRect = 0; NumOfSqr = 0; NumOfHex = 0; NumOfTri = 0; NumOfCirc = 0;
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)   //(salem) 5adt el switch case men phase 1 we 3mlt implement le el Add figures
	{
	case DRAW_RECT:
	{
		pAct = new AddRectAction(this);
		break;
	}
	case DRAW_SQUARE:
	{
		pAct = new AddSqrAction(this);
		break;
	}
	case DRAW_TRIANGLE:
	{
		pAct = new AddTriAction(this);
		break;
	}

	case DRAW_CIRCLE:
	{
		pAct = new AddCircAction(this);
		break;
	}

	case DRAW_HEXAGON:
	{
		pAct = new AddHexAction(this);
		break;
	}

	/*	case COLOR_BLACK:
		{
			pOut->PrintMessage("Action: Black Color , Click anywhere");
			break;
		}

		case COLOR_YELLOW:
		{
			pOut->PrintMessage("Action: Yellow Color , Click anywhere");
			break;
		}

		case COLOR_ORANGE:
		{
			pOut->PrintMessage("Action: Orange Color , Click anywhere");
			break;
		}

		case COLOR_RED:
		{
			pOut->PrintMessage("Action: Red Color , Click anywhere");
			break;
		}

		case COLOR_GREEN:
		{
			pOut->PrintMessage("Action: Green Color , Click anywhere");
			break;
		}

		case COLOR_BLUE:
		{
			pOut->PrintMessage("Action: Blue Color , Click anywhere");
			break;
		}
*/
	case SELECTED:
	{
		pAct = new SelectionAction(this);
		break;
	}
	case COLOR_FILLED:
	{
		if (SelectedFigCount == 1)
			pAct = new FillColorAction(this);
		else
			pOut->PrintMessage("Error! You have to select one shape to change fill color");
		break;
	}
	case COLOR_BORDERED:
	{
		if (SelectedFigCount == 1)
			pAct = new BorderColorAction(this);
		else
			pOut->PrintMessage("Error! You have to select one shape to change border color");
		break;
	}
	case DELETED:
	{
		pAct = new DeleteAction(this);
		break;
	}
	case CLEARED:
	{
		pAct = new ClearAllAction(this);
		break;
	}
	case COPIED:
	{
		if (SelectedFigCount == 1)
			pAct = new CopyAction(this);
		else
			pOut->PrintMessage("Error! You have to select one figure to copy");
		break;
	}
	case CUT:
	{
		if (SelectedFigCount == 1)
			pAct = new CutAction(this);
		else
			pOut->PrintMessage("Error! You have to select one figure to cut");
		break;
	}
	case PASTED:
	{
		pAct = new PasteAction(this);
		break;
	}
	case FRONT_SENT:
	{
		if (SelectedFigCount == 1)
			pAct = new BringToFrontAction(this);
		else
			pOut->PrintMessage("Error! You have to select one figure to bring to front");
		break;
	}
	case BACK_SENT:
	{
		if (SelectedFigCount == 1)
			pAct = new SendToBackAction(this);
		else
			pOut->PrintMessage("Error! You have to select one figure to send to back");
		break;
	}
	case SAVED:
	{
		pAct = new SaveAction(this);
		break;
	}
	case LOADED:
	{
		pAct = new LoadAction(this);
		break;
	}
	case DOUBLE_SIZE:
	{
		if (SelectedFigCount == 1)
			pAct = new DoubleSizeAction(this);
		else
			pOut->PrintMessage("Error! You can only resize one figure at a time");
		break;
	}
	case HALF_SIZE:
	{
		if (SelectedFigCount == 1)
			pAct = new HalfSizeAction(this);
		else
			pOut->PrintMessage("Error! You can only resize one figure at a time");
		break;
	}
	case VOICE:
	{
		pAct = new VoiceAction(this);
		break;
	}
	/*	case STATUS:
		{
			pOut->PrintMessage("Action: a click on the Status Bar, Click anywhere");
			break;
		}
		case DRAWING_AREA:
		{
			pOut->PrintMessage("Action: a click on the Drawing Area, Click anywhere");
			break;
		}
		case EMPTY:
		{
			pOut->PrintMessage("Action: a click on empty area in the Tool Bar, Click anywhere");
			break;
		}
	*/
	case TO_DRAW:
	{
		LoadAction* pLoad = new LoadAction(this, 1);
		pLoad->Execute();
		delete pLoad;
		pOut->PrintMessage("Action: Switch to Draw Mode");
		pOut->CreateDrawToolBar();
		break;
	}
	case TO_PLAY:
	{
		SaveAction* pSave = new SaveAction(this, 1);
		pSave->Execute();
		delete pSave;
		pOut->PrintMessage("Action: Switch to Play Mode");
		pOut->CreatePlayToolBar();
		break;
	}
	case TYPE:
	{
		pAct = new FindByType(this);
		break;
	}
	case TYPE_AND_COLOR:
	{
		pAct = new FindByTypeAndColor(this);
		break;
	}
	case COLOR:
	{
		pAct = new FindByColor(this);
		break;
	}
	case EXIT:
		break;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//You may need to change this line depending to your implementation
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
	{
		FigList[FigCount++] = pFig;
	}
}
int ApplicationManager::GetFigureCount()const
{
	return FigCount;
}
void ApplicationManager::SwapFigure(int m,int n)
{
	CFigure* Temp = FigList[n];
	FigList[n] = FigList[m];
	FigList[m] = Temp;

}
CFigure* ApplicationManager::GetSelectedFigure()const
{
		return SelectedFigure;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.

	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->IsClicked(x, y))
			return FigList[i];
	}
	return NULL;
}

CFigure* ApplicationManager::GetFigureByColor(color c)const 
{
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if(FigList[i]->IsFilled())
			if (FigList[i]->GetFillClr() == c)
				return FigList[i];
	}
	return NULL;
}


void ApplicationManager::RemoveFigure(int ID)
{
	int RemovedFigIndex=FigCount;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->GetID()==ID)
		{
			RemovedFigIndex = i;
			FigCount--;
			break;
		}
	}
	for (int i = RemovedFigIndex; i < FigCount; i++)
	{
		FigList[i] = FigList[i + 1];
	}
	FigList[FigCount] = NULL;
	UpdateFigureData();
}
int ApplicationManager::GetSelectedFigureCount() const
{
	return SelectedFigCount;
}

void ApplicationManager::ClearClipboard()
{
	delete Clipboard;
	Clipboard = NULL;
	CutFigureID = -1;
}

CFigure* ApplicationManager::GetRandomFigure() const
{
	srand(time(NULL));
	int RandNum = rand() % FigCount;
	return FigList[RandNum];
}
CFigure* ApplicationManager::GetFigureByID(int ID) 
{
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->GetID()==ID)
			return FigList[i];
	}
	return NULL;
}

void ApplicationManager::SetClipboard(CFigure* CF) {
	Clipboard = CF;
}
CFigure* ApplicationManager::GetClipboard() {
	return Clipboard;
}
void ApplicationManager::SetCutFigureID(int i) {
	CutFigureID = i;
}
int ApplicationManager::GetCutFigureID() {
	return CutFigureID;
}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();//Salem
	for (int i = 0; i < FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}



void ApplicationManager::UpdateFigureData()
{
	SelectedRects = 0, SelectedSqrs = 0, SelectedHexes = 0, SelectedTris = 0, SelectedCircs = 0;
	NumOfRect = 0, NumOfSqr = 0, NumOfHex = 0, NumOfTri = 0, NumOfCirc = 0; SelectedFigCount = 0;
	SelectedFigure = NULL;
	for (int i = 0; i <FigCount; i++)
	{
		if (FigList[i] != NULL)
		{
			switch (FigList[i]->GetFigType())
			{
			case HEXAGON:
				NumOfHex++;
				if (FigList[i]->IsSelected())
				{
					SelectedFigCount++;
					SelectedHexes++;
					SelectedFigure = FigList[i];
				}
				break;
			case CIRCLE:
				NumOfCirc++;
				if (FigList[i]->IsSelected())
				{
					SelectedFigCount++;
					SelectedCircs++;
					SelectedFigure = FigList[i];
				}
				break;
			case TRIANGLE:
				NumOfTri++;
				if (FigList[i]->IsSelected())
				{
					SelectedFigCount++;
					SelectedTris++;
					SelectedFigure = FigList[i];
				}
				break;
			case SQUARE:
				NumOfSqr++;
				if (FigList[i]->IsSelected())
				{
					SelectedFigCount++;
					SelectedSqrs++;
					SelectedFigure = FigList[i];
				}
				break;
			case RECTANGLE:
				NumOfRect++;
				if (FigList[i]->IsSelected())
				{
					SelectedFigCount++;
					SelectedRects++;
					SelectedFigure = FigList[i];
				}
				break;
			}
		}
	}
}

void ApplicationManager::SaveAll(ofstream& OutFile) const
{
	Output* pout = this->GetOutput();
	Input* pin = this->GetInput();	

	if (UI.DrawColor == BLACK) //prints UI's draw color
		OutFile << "BLACK" << "\t";
	else if (UI.DrawColor == YELLOW)
		OutFile << "YELLOW" << "\t";
	else if (UI.DrawColor == ORANGE)
		OutFile << "ORANGE" << "\t";
	else if (UI.DrawColor == RED)
		OutFile << "RED" << "\t";
	else if (UI.DrawColor == GREEN)
		OutFile << "GREEN" << "\t";
	else if (UI.DrawColor == BLUE)
		OutFile << "BLUE" << "\t";

	if (UI.FillColor == BLACK)	//prints UI's fill color
		OutFile << "BLACK" << "\n";
	else if (UI.FillColor == YELLOW)
		OutFile << "YELLOW" << "\n";
	else if (UI.FillColor == ORANGE)
		OutFile << "ORANGE" << "\n";
	else if (UI.FillColor == RED)
		OutFile << "RED" << "\n";
	else if (UI.FillColor == GREEN)
		OutFile << "GREEN" << "\n";
	else if (UI.FillColor == BLUE)
		OutFile << "BLUE" << "\n";

	
	OutFile << this->FigCount << "\n";

	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(OutFile);
	}
}

void ApplicationManager::ClearAll()
{
	for (int i = 0; i < FigCount; i++)
	{
		delete FigList[i];
		FigList[i] = NULL;
	}
	delete Clipboard;
	Clipboard = NULL;
	FigCount = 0;
	UpdateFigureData();
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
void ApplicationManager::SetSelectedFigure(CFigure* pFig)
{
	SelectedFigure = pFig;
}
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
int ApplicationManager::GetSelectedFigureCountByType(FigureType Fig) const
{
	switch (Fig)
	{
	case HEXAGON:return SelectedHexes;
	case CIRCLE:return SelectedCircs;
	case TRIANGLE:return SelectedTris;
	case SQUARE:return SelectedSqrs;
	case RECTANGLE:return SelectedRects;
	default: return 0;
	}
}
int ApplicationManager::GetFigureCountByType(FigureType Fig)
{
	UpdateFigureData();
	switch (Fig)
	{
	case HEXAGON:return NumOfHex;
	case CIRCLE:return NumOfCirc;
	case TRIANGLE:return NumOfTri;
	case SQUARE:return NumOfSqr;
	case RECTANGLE:return NumOfRect;
	default: return 0;
	}
}

int ApplicationManager::GetFigureCountByColor(ActionType Fig) //dh temporarly le 7d ma yet3melo implment
{
	UpdateFigureData();
	switch (Fig)
	{
	case COLOR_BLACK:return NumOfBlack;
	case COLOR_YELLOW:return NumOfYellow;
	case COLOR_ORANGE:return NumOfOrange;
	case COLOR_RED:return NumOfRed;
	case COLOR_GREEN:return NumOfGreen;
	case COLOR_BLUE:return NumOfBlue;
	default: return 0;
	}
}




////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
		delete FigList[i];//ERROR!
	delete Clipboard;
	delete pIn;
	delete pOut;
}
