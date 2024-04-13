#include"CHexagon.h"


CHexagon::CHexagon(Point P,GfxInfo HexagonGfxInfo):
	CFigure(HexagonGfxInfo)
{
	Center = P;
	FigType = HEXAGON;
}


void CHexagon::Draw(Output* pOut) const
{
	pOut->DrawHexagon(Center, FigGfxInfo, Selected);
}

void CHexagon::PrintInfo(Output* pOut)
{
	pOut->PrintMessage("Hexagon   ID: " + to_string(ID) + " ,Center : (" + to_string(Center.x) + "," + to_string(Center.y) + "),Side Length : " + to_string(100));
}

bool CHexagon::IsClicked(int x, int y)
{
	int s1p , s4p;
	if (x== Center.x+100)
		s1p = (Center.y - y) / 0.01;
	else
		s1p = (Center.y - y) / (Center.x + 100 - x);

	if (x == Center.x - 100)
		s4p =(Center.y - y) / 0.01;
	else
		s4p = (Center.y - y) /(Center.x-100 -x);

	if (x <= Center.x + 50 && x >= Center.x - 50)
		if (y <= Center.y + 50 * 1.732 && y >= Center.y - 50 * 1.732)
			return true;//inner rectangle check

	if (s1p <= 1.732 && s1p >= -1.732)	//circular sector between two lines
		if (x <= Center.x + 100 && x >= Center.x + 50) // another section to get intersecion(triangle)
			return true;//side triangle check 1

	if (s4p >= -1.732 && s4p <= 1.732)	//circular sector between two lines
		if (x >= Center.x - 100 && x <= Center.x - 50) // another section to get intersecion(triangle)
			return true;//side triangle check 2

	return false;
}

FigureType CHexagon::GetFigType()
{
	return FigType;
}
