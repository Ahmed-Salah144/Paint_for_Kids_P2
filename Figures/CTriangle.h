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
	CTriangle(CTriangle*); //overriding constructor (needed for clipboard copy)// (abdo)
	CTriangle(Point, Point, Point, GfxInfo TriangleGfxInfo);
	CTriangle(ifstream& InFile);
	virtual void Draw(Output* pOut) const;
	virtual void MoveFigure(int, int);
	virtual void PrintInfo(Output* pOut);	//print all figure info on the status bar
	virtual bool IsClicked(int x, int y);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
	virtual void FitInsideDrawArea();
	virtual bool DoubleSize();
	virtual bool HalfSize();
};

#endif
