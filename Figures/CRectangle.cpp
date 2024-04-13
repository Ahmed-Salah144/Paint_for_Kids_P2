#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	FigType = RECTANGLE;
	L = abs(P1.x - P2.x);
	W = abs(P1.y - P2.y);
}
	

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

void CRectangle::PrintInfo(Output* pOut)
{
	string Message = "Rectangle   ID: " + to_string(ID) + " ,Corner 1: (" + to_string(Corner1.x) + "," + to_string(Corner1.y) + ")" + " ,Corner 2: (" + to_string(Corner2.x) + "," + to_string(Corner2.y) + ")";
	Message += ",Length: "+to_string(L)+",Width: "+to_string(W);
	pOut->PrintMessage(Message);
}

bool CRectangle::IsClicked(int x, int y)
{
	if (x >= Corner1.x && x <= Corner2.x || x <= Corner1.x && x >= Corner2.x)
		if (y >= Corner1.y && y <= Corner2.y || y <= Corner1.y && y >= Corner2.y)
		return true;
	return false;
}

FigureType CRectangle::GetFigType()
{
	return FigType;
}
