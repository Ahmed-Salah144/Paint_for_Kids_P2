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
};

#endif