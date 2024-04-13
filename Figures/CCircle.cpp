#include"CCircle.h"


CCircle::CCircle(Point P1,Point P2, GfxInfo CircleGfxInfo) :
	CFigure(CircleGfxInfo)
{
	Center = P1;
	OuterPoint = P2;
	FigType = CIRCLE;
	Radius = sqrt((P1.x - P2.x)* (P1.x - P2.x) + (P1.y - P2.y)* (P1.y - P2.y));
}


void CCircle::Draw(Output* pOut) const
{
	pOut->DrawCircle(Center,OuterPoint,FigGfxInfo, Selected);
}

void CCircle::PrintInfo(Output* pOut)
{
	pOut->PrintMessage("Circle   ID: " + to_string(ID) + " ,Center : (" + to_string(Center.x) + "," + to_string(Center.y) + "),Radius : " + to_string(Radius));
}

bool CCircle::IsClicked(int x, int y)
{
	int distance= sqrt((Center.x - x)* (Center.x - x) + (Center.y - y)* (Center.y - y));
	if (distance <= Radius)
		return true;
	return false;
}

FigureType CCircle::GetFigType()
{
	return FigType;
}
