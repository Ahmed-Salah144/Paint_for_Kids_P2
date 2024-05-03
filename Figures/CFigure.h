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
	FigureType FigType;
	static int CreatedFigCount;
	/// Add more parameters if needed.

public:
	CFigure(GfxInfo FigureGfxInfo);
	CFigure(ifstream& InFile);

	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	bool IsTheSame(CFigure*)const;		//check for selected figure(Salem)

	virtual void Draw(Output* pOut) const  = 0 ;		//Draw the figure
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	color GetDrawClr(); //(Salem)
	color GetFillClr();//(Salem)
	void SetID(int);//(salem)

	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	
	virtual bool IsClicked(int x, int y)=0;// (Salem to check area of click)


	virtual FigureType GetFigType()=0; //salem to check for figure type
	virtual bool DoubleSize() = 0;
	virtual bool HalfSize() = 0;
	virtual void FitInsideDrawArea() = 0;

	virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file
	virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
};

#endif