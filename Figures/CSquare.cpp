#include"CSquare.h"

CSquare::CSquare(Point P, GfxInfo SquareGfxInfo) :
	CFigure(SquareGfxInfo)
{
	Center = P;
	FigType = SQUARE;
}

void CSquare::Draw(Output* pOut) const
{
	pOut->DrawSquare(Center, FigGfxInfo, Selected);
}

void CSquare::PrintInfo(Output* pOut)
{
	pOut->PrintMessage("Square   ID: " + to_string(ID) + " ,Center : (" + to_string(Center.x) + "," + to_string(Center.y) + "),Length : " + to_string(113));
}

bool CSquare::IsClicked(int x, int y)
{
	if (x >= Center.x - 80 && x <= Center.x + 80 && y >= Center.y - 80 && y <= Center.y + 80)
		return true;
	return false;
}

FigureType CSquare::GetFigType()
{
	return FigType;
}
