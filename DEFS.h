#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	DRAW_RECT,		//Draw Rectangle

	DRAW_SQUARE,    //shaped declaration abdo

	DRAW_TRIANGLE,	

	DRAW_CIRCLE,	

	DRAW_HEXAGON,	

	COLOR_BLACK,	// colors declaration abdo

	COLOR_YELLOW,	

	COLOR_ORANGE,	

	COLOR_RED,		

	COLOR_GREEN,	

	COLOR_BLUE,		

	SELECTED,		// features declaration abdo

	COLOR_FILLED,  

	COLOR_BORDERED,

	DELETED,

	CLEARED, 

	COPIED, 

	CUT,

	PASTED,

	FRONT_SENT,

	BACK_SENT,

	SAVED,

	LOADED,

	TO_PLAY,		//Switch interface to Play mode

	EXIT,			//Exit 

	TO_DRAW,		//Switch interface to Draw mode

	EMPTY,			//A click on empty place in the toolbar

	DRAWING_AREA,	//A click on the drawing area

	STATUS,			//A click on the status bar

	TYPE,

	COLOR,

	TYPE_AND_COLOR,

	DRAW_MODE


	///TODO: Add the other action types of the two modes
};

struct Point	//To be used for figures points
{ int x,y; };

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif