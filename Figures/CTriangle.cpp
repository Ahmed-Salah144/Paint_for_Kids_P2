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
	string Message = "Triangle   ID: " + to_string(ID) + " ,Vertex 1: (" + to_string(Vertex1.x) + "," + to_string(Vertex1.y) + ")" + " ,Vertex 2: (" + to_string(Vertex2.x) + "," + to_string(Vertex2.y) + "),Vertex 3: (" + to_string(Vertex3.x) + "," + to_string(Vertex3.y)+")";
	pOut->PrintMessage(Message);
}

bool CTriangle::IsClicked(int x, int y)
{
	double A1, A2, A3, A;
	A1 = GetArea(x, y, Vertex1.x, Vertex1.y, Vertex2.x, Vertex2.y);
	A2 = GetArea(x, y, Vertex2.x, Vertex2.y, Vertex3.x, Vertex3.y);
	A3 = GetArea(x, y, Vertex1.x, Vertex1.y, Vertex3.x, Vertex3.y);
	A = GetArea(Vertex1.x, Vertex1.y, Vertex2.x, Vertex2.y, Vertex3.x, Vertex3.y);
	if (A == A1 + A2 + A3)//Compare area of 3 triangles around (x,y) and original area;
		return true;
	return false;
}

double CTriangle::GetArea(int Ax, int Ay, int Bx, int By, int Cx, int Cy)
{
	return abs((Ax * (By - Cy) + Bx * (Cy - Ay) + Cx * (Ay - By)) / 2.0);//Calculate Area using 3 Vertices of a triangle
}

FigureType CTriangle::GetFigType()
{
	return FigType;
}
