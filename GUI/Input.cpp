#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetString(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check which Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RECT: return DRAW_RECT;
			case ITM_SQUARE: return DRAW_SQUARE;			//abdo commands 
			case ITM_TRIANGLE: return DRAW_TRIANGLE;		//abdo commands 
			case ITM_CIRCLE: return DRAW_CIRCLE;			//abdo commands 
			case ITM_HEXAGON: return DRAW_HEXAGON;			//abdo commands 
			case ITM_BLACK: return COLOR_BLACK;				//abdo commands 
			case ITM_YELLOW: return COLOR_YELLOW;			//abdo commands 
			case ITM_ORANGE: return COLOR_ORANGE;			//abdo commands 
			case ITM_RED: return COLOR_RED;					//abdo commands 
			case ITM_GREEN: return COLOR_GREEN;				//abdo commands 
			case ITM_BLUE: return COLOR_BLUE;				//abdo commands  
			case ITM_SELECT: return SELECTED;				//abdo commands 
			case ITM_FILL_COLOR: return COLOR_FILLED;				//abdo commands 
			case ITM_BORDER_COLOR: return COLOR_BORDERED;				//abdo commands 
			case ITM_DELETE: return DELETED;				//abdo commands 
			case ITM_CLEAR: return CLEARED;				//abdo commands 
			case ITM_COPY: return COPIED;				//abdo commands 
			case ITM_CUT: return CUT;				//abdo commands 
			case ITM_PASTE: return PASTED;				//abdo commands 
			case ITM_SEND_FRONT: return FRONT_SENT;				//abdo commands 
			case ITM_SEND_BACK: return BACK_SENT;				//abdo commands 
			case ITM_SAVE: return SAVED;				//abdo commands 
			case ITM_LOAD: return LOADED;				//abdo commands 
			case ITM_PLAY_MODE: return TO_PLAY;				//abdo commands 
			case ITM_EXIT: return EXIT;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action	
		if (y >= 0 && y < UI.ToolBarHeight){
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			switch (ClickedItemOrder)
		{
		case ITM_DRAW_MODE: 
			return TO_DRAW;
		case ITM_TYPE: 
			return TYPE;
		case ITM_COLOR: 
			return COLOR;
		case ITM_TYPE_AND_COLOR: 
			return TYPE_AND_COLOR;
		case ITM_EXIT2: 
			return EXIT;
		default:
			return EMPTY;
		}
	}
	}	

}
/////////////////////////////////
	
Input::~Input()
{
}
