#ifndef CTRI_H
#define CTRI_H

#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point Vertex1;
	Point Vertex2;
	Point Vertex3;
public:
	CTriangle(Point, Point, Point, GfxInfo TriangleGfxInfo);
	virtual void Draw(Output* pOut) const;
};

#endif
