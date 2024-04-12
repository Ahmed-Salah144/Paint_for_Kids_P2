#include "CTriangle.h"

CTriangle::CTriangle(Point P1, Point P2,Point P3, GfxInfo TriangleGfxInfo) :
	CFigure(TriangleGfxInfo)
{
	Vertex1 = P1;
	Vertex2 = P2;
	Vertex3 = P3;
	FigType = TRIANGLE;
}


void CTriangle::Draw(Output* pOut) const
{
	pOut->DrawTriangle(Vertex1, Vertex2, Vertex3, FigGfxInfo, Selected);
}

void CTriangle::PrintInfo(Output* pOut)
{
}

bool CTriangle::IsClicked(int x, int y)
{
	int s1p, s2p;
	if (Vertex1.x == x)
		 s1p = (y - Vertex1.y) /0.01;//slope of base point with click
	else
		 s1p = (y - Vertex1.y) / (x - Vertex1.x);//slope of base point with click
	if (Vertex2.x == x)
		 s2p = (y - Vertex2.y) /0.01;//slope of base point with click
	else
		s2p = (y - Vertex2.y) / (x - Vertex2.x);//slope of base point with click
	int s13 = (Vertex3.y - Vertex1.y) / (Vertex3.x - Vertex1.x);//slope of base
	int s23 = (Vertex3.y - Vertex2.y) / (Vertex3.x - Vertex2.x);//slope of side
	int s12 = (Vertex2.y - Vertex1.y) / (Vertex2.x - Vertex1.x);//slope of side

	if (s1p >= s13 && s1p <= s12|| (s1p <= s13 && s1p >= s12))	//circular sector between two lines
		if (s2p >= s12 && s2p <= s23 || (s2p <= s12 && s2p >= s23)) // another sector to get intersecion(triangle)
			return true;
	return false;
}

FigureType CTriangle::GetFigType()
{
	return FigType;
}
