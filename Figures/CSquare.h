#ifndef CSQR_H
#define CSQR_H

#include"CFigure.h"

class CSquare : public CFigure
{
private:
	Point Center;
	int Size;
public:
	CSquare(Point, GfxInfo SquareGfxInfo);
	CSquare(ifstream& InFile);
	virtual void Draw(Output* pOut) const;
	virtual void MoveFigure(int, int);
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