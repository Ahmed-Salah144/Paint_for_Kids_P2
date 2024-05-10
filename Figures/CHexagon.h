#ifndef CHEX_H
#define CHEX_H


#include"CFigure.h"

class CHexagon : public CFigure
{
private:

	Point Center;

	int Size;

public:
	CHexagon(CHexagon*); //Copy Constructor

	CHexagon(Point ,GfxInfo HexagonGfxInfo);//Drawing Action Constructor

	CHexagon(ifstream& InFile);//Load Constructor

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