#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddSqrAction.h"
#include "Actions\AddTriAction.h"
#include "Actions\AddHexAction.h"
#include "Actions\AddCircAction.h"
#include "Actions\SelectionAction.h"


//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FigCount = 0;
		
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

		case COLOR_BLACK:
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

		case SELECTED:
		{
			pOut->PrintMessage("Action: Selection Tool , Click to select");
			pAct = new SelectionAction(this);
			break;
		}
		case COLOR_FILLED:
		{
			pOut->PrintMessage("Action: Color Fill Tool , Click anywhere");
			break;
		}
		case COLOR_BORDERED:
		{
			pOut->PrintMessage("Action: Color Border Tool , Click anywhere");
			break;
		}
		case DELETED:
		{
			pOut->PrintMessage("Action: Delete Tool , Click anywhere");
			break;
		}
		case CLEARED:
		{
			pOut->PrintMessage("Action: Clear Tool , Click anywhere");
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
			pOut->PrintMessage("Action: Send to Front Tool , Click anywhere");
			break;
		}
		case BACK_SENT:
		{
			pOut->PrintMessage("Action: Send to Back Tool , Click anywhere");
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
		case STATUS:
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
		pFig->SetID(FigCount);//(salem)
	}
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

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	for(int i=0; i<FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
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
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
	
}
