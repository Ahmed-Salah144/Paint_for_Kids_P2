#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
	int L, W;//Length an width(needed in selection)
public:
	CRectangle(CRectangle*); //overriding constructor (needed for clipboard copy)// (abdo)
	CRectangle(Point , Point, GfxInfo FigureGfxInfo );
	CRectangle(ifstream& fin);
	virtual void Draw(Output* pOut) const;
	virtual void PrintInfo(Output* pOut);	//print all figure info on the status bar
	virtual bool IsClicked(int x, int y);
	virtual FigureType GetFigType();
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
	virtual void FitInsideDrawArea();
	virtual bool DoubleSize();
	virtual bool HalfSize();
};

#endif