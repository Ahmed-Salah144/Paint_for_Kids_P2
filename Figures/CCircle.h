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
	CCircle(CCircle*); //overriding constructor (needed for clipboard copy)// (abdo)
	CCircle(Point,Point, GfxInfo CircleGfxInfo);
	CCircle(ifstream& InFile);
	virtual void Draw(Output* pOut) const;
	virtual void MoveFigure(int, int);
	virtual void PrintInfo(Output* pOut);	//print all figure info on the status bar
	virtual bool IsClicked(int x, int y);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
	virtual void FitInsideDrawArea();
	virtual bool DoubleSize() ;
	virtual bool HalfSize();
};

#endif