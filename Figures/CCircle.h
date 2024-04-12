#ifndef CCirc_H
#define CCirc_H


#include"CFigure.h"

class CCircle : public CFigure
{
private:
	Point Center;
	Point OuterPoint;
public:
	CCircle(Point,Point, GfxInfo CircleGfxInfo);
	virtual void Draw(Output* pOut) const;
};

#endif