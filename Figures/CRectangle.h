#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:

	Point Corner1;	

	Point Corner2;

	int L, W;//Length and width

public:
	CRectangle(CRectangle*); //Copy Constructor

	CRectangle(Point , Point, GfxInfo FigureGfxInfo );//Drawing Action Constructor

	CRectangle(ifstream& fin);// Load Constructor

	virtual void Draw(Output* pOut) const;

	virtual void MoveFigure(int, int);

	virtual FigureType GetFigType()const;

	virtual void PrintInfo(Output* pOut);

	virtual bool IsClicked(int x, int y);

	virtual void Save(ofstream& OutFile);

	virtual void Load(ifstream& InFile);

	virtual void FitInsideDrawArea();

	virtual bool DoubleSize();

	virtual bool HalfSize();
};

#endif