#ifndef CSQR_H
#define CSQR_H

#include"CFigure.h"

class CSquare :
	CFigure
{
private:
	Point Center;
public:
	CSquare(Point, GfxInfo SquareGfxInfo);
	virtual void Draw(Output* pOut) const;
};

#endif