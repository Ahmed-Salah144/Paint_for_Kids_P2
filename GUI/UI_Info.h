#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY	//Playing mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are **(ordered)** here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_RECT,		//Recangle item in menu

	//TODO: Add more items names here (Salem x Faseeh)
	ITM_SQUARE,		//Square item in menu

	ITM_TRIANGLE,		//Triangle item in menu

	ITM_CIRCLE,		//Circle item in menu

	ITM_HEXAGON,		//Hexagon item in menu

	ITM_BLACK,			//Colors Faseeh

	ITM_YELLOW,

	ITM_ORANGE,

	ITM_RED,

	ITM_GREEN,

	ITM_BLUE,

	ITM_SELECT,			//Select item

	ITM_FILL_COLOR,		//Fills selected item

	ITM_BORDER_COLOR,	//Colors Border of selected item

	ITM_DELETE,			//Delete Selected Items

	ITM_CLEAR,			//Clear All Drawings

	ITM_COPY,			//Copy Selected item

	ITM_CUT,			//Cut Selected item

	ITM_PASTE,			//Paste Selected item

	ITM_SEND_FRONT,		//Send Selected item to Front

	ITM_SEND_BACK,		//Send Selected item to back

	ITM_SAVE,

	ITM_LOAD,

	ITM_DOUBLE_SIZE,

	ITM_HALF_SIZE,

	ITM_VOICE,

	ITM_PLAY_MODE,

	ITM_EXIT,		//Exit item
	
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};

enum PlayMenuItem //The items of the Play menu (you should add more items) (osama elnaggar)
{
	//Note: Items are **(ordered)** here as they appear in menu
	//If you want to change the menu items order, change the order here
	
	//TODO: Add more items names here
	ITM_TYPE,

	ITM_COLOR,
	
	ITM_TYPE_AND_COLOR, //find type and color

	ITM_DRAW_MODE, //draw mode

	ITM_VOICE_2,

	ITM_EXIT2,

	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

	
};





__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	    //Window width and height
		wx , wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		LineUnderTBWidth,	//line Under the Toolbar Pen Width
		MenuItemWidth;		//Width of each item in toolbar menu
	

	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed
	
}UI;	//create a global object UI

#endif