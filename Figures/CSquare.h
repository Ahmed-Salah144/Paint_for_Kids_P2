#ifndef CSQR_H
#define CSQR_H

#include"CFigure.h"

class CSquare : public CFigure
{
private:

	Point Center;

	int Size;

public:
	CSquare(CSquare*); //Copy Constructor

	CSquare(Point, GfxInfo SquareGfxInfo);//Drawing Action  Constructor

	CSquare(ifstream& InFile);//Loading Constructor

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