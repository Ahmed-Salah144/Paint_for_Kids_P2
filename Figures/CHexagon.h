#ifndef CHEX_H
#define CHEX_H


#include"CFigure.h"

class CHexagon : public CFigure
{
private:
	Point Center;
	int Size;
public:
	CHexagon(CHexagon*); //overriding constructor (needed for clipboard copy)// (abdo)
	CHexagon(Point ,GfxInfo HexagonGfxInfo);
	CHexagon(ifstream& InFile);
	virtual void Draw(Output* pOut) const;
	virtual void PrintInfo(Output* pOut);	//print all figure info on the status bar
	virtual bool IsClicked(int x, int y);
	virtual FigureType GetFigType();
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
	virtual void FitInsideDrawArea();
	virtual bool DoubleSize();
	virtual bool HalfSize();
};

#endif