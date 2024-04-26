#ifndef CHEX_H
#define CHEX_H


#include"CFigure.h"

class CHexagon : public CFigure
{
private:
	Point Center;
public:
	CHexagon(Point ,GfxInfo HexagonGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual void PrintInfo(Output* pOut);	//print all figure info on the status bar
	virtual bool IsClicked(int x, int y);
	virtual FigureType GetFigType();
	virtual void Save(ofstream& OutFile);
};

#endif