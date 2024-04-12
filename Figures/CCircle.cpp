#include"CCircle.h"


CCircle::CCircle(Point P1,Point P2, GfxInfo CircleGfxInfo) :
	CFigure(CircleGfxInfo)
{
	Center = P1;
	OuterPoint = P2;
}


void CCircle::Draw(Output* pOut) const
{
	pOut->DrawCircle(Center,OuterPoint,FigGfxInfo, Selected);
}
