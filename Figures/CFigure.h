#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\Output.h"

//Base class for all figures
class CFigure
{
protected:

	int ID;		//Each figure has an ID

	bool Selected;	//true if the figure is selected.

	GfxInfo FigGfxInfo;	//Figure graphis info

	FigureType FigType; //Rectangle,triangle,square,circle or hexagon

	static int CreatedFigCount;//Assigns IDs of figures

	/// Add more parameters if needed.

public:
	CFigure(GfxInfo FigureGfxInfo);	//Constructor Called by drawing actions

	CFigure(ifstream& InFile); // Constructor Called by Load Actions

	void SetSelected(bool s);	//select or unselect the figure

	bool IsSelected() const;	//returns true if figure is selected

	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the figure


	void ChngDrawClr(color Dclr);	//changes the figure's drawing color

	void ChngFillClr(color Fclr);	//changes the figure's filling color

	color GetDrawClr(); // Returns Figure Draw Color

	color GetFillClr(); // Returns Figure Fill Color

	bool IsFilled(); //Returns true if figure is filled

	void UnFill(); //Unfills Figure

	int GetID() ; //returns Figure ID

	virtual FigureType GetFigType() const = 0; //Returns  figure type

	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	

	virtual bool IsClicked(int x, int y)=0;// returns true if a click is inside the figure

	virtual void MoveFigure(int x, int y) = 0;		// Move the Center of the Figure to a new position

	virtual bool DoubleSize() = 0;		//returns true if figure size doubled successfully

	virtual bool HalfSize() = 0;		//returns true if figure size halfed successfully

	virtual void FitInsideDrawArea() = 0; //Fixes figure inside Draw Area

	virtual void Save(ofstream &OutFile);	//Save the figure parameters to the file

	virtual void Load(ifstream &InFile);	//Load the figure parameters to the file

	virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar

	void ResetCreatedFigureCount();		//Resets Figure IDs

	virtual ~CFigure();
};

#endif