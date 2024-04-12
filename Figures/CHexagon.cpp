#include"CHexagon.h"


CHexagon::CHexagon(Point P,GfxInfo HexagonGfxInfo):
	CFigure(HexagonGfxInfo)
{
	Center = P;
}


void CHexagon::Draw(Output* pOut) const
{
	pOut->DrawHexagon(Center, FigGfxInfo, Selected);
}
