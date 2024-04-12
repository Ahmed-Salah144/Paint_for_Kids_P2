#ifndef CSQR_H
#define CSQR_H

#include"CFigure.h"

class CSquare : public CFigure
{
private:
	Point Center;
public:
	CSquare(Point, GfxInfo SquareGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual void PrintInfo(Output* pOut);	//print all figure info on the status bar
	virtual bool IsClicked(int x, int y);
	virtual FigureType GetFigType();
};

#endif