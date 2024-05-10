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
	CTriangle(CTriangle*); //Copy Constructor

	CTriangle(Point, Point, Point, GfxInfo TriangleGfxInfo); // Drawing Action Constructor

	CTriangle(ifstream& InFile); //Load Constructor

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
