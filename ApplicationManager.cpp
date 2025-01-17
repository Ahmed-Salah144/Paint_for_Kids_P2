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
#include "Actions\SwitchToDrawModeAction.h"
#include "Actions\SwitchToPlayModeAction.h"
#include <cstdlib> 
#include<iostream>

//Constructor

ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	//Initialize all data members
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
	switch (ActType)
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
	case TO_DRAW:
	{
		pAct = new SwitchToDrawModeAction(this);
		break;
	}
	case TO_PLAY:
	{
		pAct = new SwitchToPlayModeAction(this);
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
		ClearAll();
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

////////////////////////////////////////////////////////////////////////////////////

int ApplicationManager::GetFigureCount()const
{
	return FigCount;
}

////////////////////////////////////////////////////////////////////////////////////

void ApplicationManager::SwapFigure(int m,int n)
{
	CFigure* Temp = FigList[n];
	FigList[n] = FigList[m];
	FigList[m] = Temp;

}

////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////

CFigure* ApplicationManager::CheckTypeAndColor(color c,FigureType b)const
{
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->IsFilled())
		{
			if (FigList[i]->GetFillClr() == c)
			{
				if (FigList[i]->GetFigType() == b)
				{
					return FigList[i];
				}
			}
		}
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////

void ApplicationManager::RemoveFigure(int ID)
{
	int RemovedFigIndex=FigCount; //index of removed figure initialised
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->GetID()==ID)
		{
			RemovedFigIndex = i;
			FigCount--;
			break;
		}
	}
	for (int i = RemovedFigIndex; i < FigCount; i++) //sets array back in order
	{
		FigList[i] = FigList[i + 1];
	}
	FigList[FigCount] = NULL;
	UpdateFigureData();
}

////////////////////////////////////////////////////////////////////////////////////

int ApplicationManager::GetSelectedFigureCount() const
{
	return SelectedFigCount;
}

////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////

void ApplicationManager::ClearClipboard()
{
	delete Clipboard;
	Clipboard = NULL;
	CutFigureID = -1;//sets cutfigure ID by a value that cannot equal any ID
}

////////////////////////////////////////////////////////////////////////////////////

CFigure* ApplicationManager::GetRandomFigure(bool isFilled) const
{
	srand(time(NULL));
	int RandNum = rand() % FigCount;
	if (!isFilled)
		return FigList[RandNum];
	else
	{
		for (int i = RandNum; i < FigCount; i++)
			if (FigList[i]->IsFilled())
				return FigList[i];
		for (int i = RandNum; i >= 0; i--)
			if (FigList[i]->IsFilled())
				return FigList[i];
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////

CFigure* ApplicationManager::GetFigureByID(int ID)const 
{
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->GetID()==ID)
			return FigList[i];
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////

void ApplicationManager::SetClipboard(CFigure* CF) {
	Clipboard = CF;
}

////////////////////////////////////////////////////////////////////////////////////

CFigure* ApplicationManager::GetClipboard() {
	return Clipboard;
}

////////////////////////////////////////////////////////////////////////////////////

void ApplicationManager::SetCutFigureID(int i) {
	CutFigureID = i;
}

////////////////////////////////////////////////////////////////////////////////////

int ApplicationManager::GetCutFigureID() {
	return CutFigureID;
}

////////////////////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateFigureData()
{
	SelectedRects = 0, SelectedSqrs = 0, SelectedHexes = 0, SelectedTris = 0, SelectedCircs = 0;
	NumOfRect = 0, NumOfSqr = 0, NumOfHex = 0, NumOfTri = 0, NumOfCirc = 0; SelectedFigCount = 0;
	SelectedFigure = NULL;

	//Reset all figure numbers and count them again

	for (int i = 0; i < FigCount; i++)
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

////////////////////////////////////////////////////////////////////////////////////

void ApplicationManager::ClearAll()
{
	FigList[0]->ResetCreatedFigureCount();
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


//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface

void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();
	for (int i = 0; i < FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}

////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////

Input *ApplicationManager::GetInput() const
{	return pIn; }

//Return a pointer to the input
////////////////////////////////////////////////////////////////////////////////////

Output *ApplicationManager::GetOutput() const
{	return pOut; }

//Return a pointer to the output
////////////////////////////////////////////////////////////////////////////////////

//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
		delete FigList[i];
	delete Clipboard;
	delete pIn;
	delete pOut;
}
