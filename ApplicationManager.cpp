#include "ApplicationManager.h"
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

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FigCount = 0;
	SelectedFigCount = 0;
	SelectedRects = 0; SelectedSqrs = 0; SelectedHexes = 0; SelectedTris = 0; SelectedCircs = 0;
	NumOfRect = 0; NumOfSqr = 0; NumOfHex = 0; NumOfTri = 0; NumOfCirc = 0;
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
	for (int i = 0; i < MaxFigCount; i++)
		SelectedFigList[i] = NULL;
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
			pOut->PrintMessage("Action: Copy Tool , Click anywhere");
			break;
		}
		case CUT:
		{
			pOut->PrintMessage("Action: Cut Tool , Click anywhere");
			break;
		}
		case PASTED:
		{
			pOut->PrintMessage("Action: Paste Tool , Click anywhere");
			break;
		}
		case FRONT_SENT:
		{
			if (SelectedFigCount == 1)
				pAct = new BringToFrontAction(this);
			else
				pOut->PrintMessage("Error! You have to select one shape to bring to front");
			break;
		}
		case BACK_SENT:
		{
			if (SelectedFigCount == 1)
				pAct = new SendToBackAction(this);
			else
				pOut->PrintMessage("Error! You have to select one shape to send to back");
			break;
		}
		case SAVED:
		{
			pOut->PrintMessage("Action: Save Tool , Click anywhere");
			break;
		}
		case LOADED:
		{
			pOut->PrintMessage("Action: Load Tool , Click anywhere");
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
			pOut->PrintMessage("Action: Switch to Draw Mode");
			pOut->CreateDrawToolBar();
			break;
		}
		case TO_PLAY:
		{
			pOut->PrintMessage("Action: Switch to Play Mode");
			pOut->CreatePlayToolBar();
			break;
		}
		case TYPE:
		{
			pOut->PrintMessage("Action: click on find by type");
			break;
		}
		case TYPE_AND_COLOR:
		{
			pOut->PrintMessage("Action: click on find by type and color");
			break;
		}
		case COLOR:
		{
			pOut->PrintMessage("Action: click on find by color");
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
void ApplicationManager::SwapFigure(int m,int n)
{
	CFigure* Temp = FigList[n];
	FigList[n] = FigList[m];
	FigList[m] = Temp;

}
CFigure* ApplicationManager::GetSelectedFigure(int i)const
{
	return SelectedFigList[i];
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


void ApplicationManager::RemoveFigure(CFigure* pFig)
{
	int RemovedFigIndex{};
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsTheSame(pFig))
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
	int RemovedSelectedFigIndex{};
	for (int i = 0; i < SelectedFigCount; i++)
	{
		if (SelectedFigList[i]->IsTheSame(pFig))
		{
			RemovedSelectedFigIndex = i;
			SelectedFigCount--;
			break;
		}
	}
	for (int i = RemovedSelectedFigIndex; i < SelectedFigCount; i++)
	{
		SelectedFigList[i] = SelectedFigList[i + 1];
	}
	SelectedFigList[SelectedFigCount] = NULL;
	//pOut->ClearDrawArea();
	UpdateNumOfFigures();
}
int ApplicationManager::GetSelectedFigureCount() const
{
	return SelectedFigCount;
}
int ApplicationManager::GetFigureCount()const
{
	return FigCount;
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

void ApplicationManager::UpdateNumOfFigures()
{
	SelectedRects = 0, SelectedSqrs = 0, SelectedHexes = 0, SelectedTris = 0, SelectedCircs = 0;
	NumOfRect = 0, NumOfSqr = 0, NumOfHex = 0, NumOfTri = 0, NumOfCirc = 0;
	for (int i = 0; i <FigCount; i++)
	{
		if (FigList[i] != NULL)
		{
			switch (FigList[i]->GetFigType())
			{
			case HEXAGON:NumOfHex++; break;
			case CIRCLE:NumOfCirc++; break;
			case TRIANGLE:NumOfTri++; break;
			case SQUARE:NumOfSqr++; break;
			case RECTANGLE:	NumOfRect++; break;
			}
		}
	}
	for (int i = 0; i < SelectedFigCount; i++)
	{
		if (SelectedFigList[i] != NULL)
		{
			switch (SelectedFigList[i]->GetFigType())
			{
			case HEXAGON:SelectedHexes++; break;
			case CIRCLE:SelectedCircs++; break;
			case TRIANGLE:SelectedTris++; break;
			case SQUARE:SelectedSqrs++; break;
			case RECTANGLE:SelectedRects++; break;
			}
		}
	}
}

void ApplicationManager::ClearAll()
{	
	for (int i = 0; i < FigCount; i++)
	{
		//delete FigList[i]; T_T MEMORY MANAGMENT
		FigList[i] = NULL;
	}		
	FigCount = 0;
	for (int i = 0; i < MaxFigCount; i++)
		SelectedFigList[i] = NULL;
	SelectedFigCount = 0;
	UpdateNumOfFigures();
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	//for (int i = 0; i < FigCount; i++)
		//delete FigList[i];//ERROR!
	delete pIn;
	delete pOut;
}
