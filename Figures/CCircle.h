#ifndef CCirc_H
#define CCirc_H


#include"CFigure.h"

class CCircle : public CFigure
{
private:
	Point Center;
	Point OuterPoint;
	int Radius;
public:
	CCircle(Point,Point, GfxInfo CircleGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual void PrintInfo(Output* pOut);	//print all figure info on the status bar
	virtual bool IsClicked(int x, int y);
	virtual FigureType GetFigType();
};

#endif