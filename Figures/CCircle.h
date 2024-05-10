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
	CCircle(CCircle*); //Copy Constructor

	CCircle(Point,Point, GfxInfo CircleGfxInfo);//Drawing Action Constructor

	CCircle(ifstream& InFile);//Load Constructor

	virtual void Draw(Output* pOut) const;

	virtual void MoveFigure(int, int);

	virtual FigureType GetFigType()const;

	virtual void PrintInfo(Output* pOut);

	virtual bool IsClicked(int x, int y);

	virtual void Save(ofstream& OutFile);

	virtual void Load(ifstream& InFile);

	virtual void FitInsideDrawArea();

	virtual bool DoubleSize() ;

	virtual bool HalfSize();
};

#endif