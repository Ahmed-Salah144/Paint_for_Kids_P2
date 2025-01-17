#include "CTriangle.h"
#include <fstream>

CTriangle::CTriangle(CTriangle* T) : CFigure(T->FigGfxInfo) {
	this->Vertex1 = T->Vertex1;
	this->Vertex2 = T->Vertex2;
	this->Vertex3 = T->Vertex3;
	FigType = TRIANGLE;
}

CTriangle::CTriangle(Point P1, Point P2,Point P3, GfxInfo TriangleGfxInfo) :
	CFigure(TriangleGfxInfo)
{
	Vertex1 = P1;
	Vertex2 = P2;
	Vertex3 = P3;
	FigType = TRIANGLE;
	FitInsideDrawArea();
}

CTriangle::CTriangle(ifstream& InFile)
	: CFigure(InFile)
{
	Load(InFile);
	if (CreatedFigCount < ID)
		CreatedFigCount = ID + 1;
}


void CTriangle::Draw(Output* pOut) const
{
	pOut->DrawTriangle(Vertex1, Vertex2, Vertex3, FigGfxInfo, Selected);
}

void CTriangle::MoveFigure(int x, int y)
{
	//Sets point as new centroid of the triangle and shifts all points accordingly
	int Centroidx = (Vertex1.x + Vertex2.x + Vertex3.x) / 3; 
	int Centroidy = (Vertex1.y + Vertex2.y + Vertex3.y) / 3;
	Vertex1.x += x - Centroidx;
	Vertex1.y += y - Centroidy;
	Vertex2.x += x - Centroidx;
	Vertex2.y += y - Centroidy;
	Vertex3.x += x - Centroidx;
	Vertex3.y += y - Centroidy;
	FitInsideDrawArea();
}

FigureType CTriangle::GetFigType() const
{
	return FigType;
}

void CTriangle::PrintInfo(Output* pOut)
{
	string Message = "Triangle   ID: " + to_string(ID) + " ,Vertex 1: (" + to_string(Vertex1.x) + "," + to_string(Vertex1.y) + ")" + " ,Vertex 2: (" + to_string(Vertex2.x) + "," + to_string(Vertex2.y) + "),Vertex 3: (" + to_string(Vertex3.x) + "," + to_string(Vertex3.y)+")";
	pOut->PrintMessage(Message);
}

bool CTriangle::IsClicked(int x, int y)
{
	//Defines Areas of 3 triangles around the clicked point and 3 combinations of vertices from the main triangle
	//Checks if the sum of areas of the 3 triangles is equal to the area of the triangle
	double A1, A2, A3, A;
	A1 = abs((x * (Vertex1.y - Vertex2.y) + Vertex1.x * (Vertex2.y - y) + Vertex2.x * (y - Vertex1.y)) / 2.0);
	A2 = abs((x * (Vertex2.y - Vertex3.y) + Vertex2.x * (Vertex3.y - y) + Vertex3.x * (y - Vertex2.y)) / 2.0);
	A3 = abs((x * (Vertex1.y - Vertex3.y) + Vertex1.x * (Vertex3.y - y) + Vertex3.x * (y - Vertex1.y)) / 2.0);
	A = abs((Vertex3.x * (Vertex1.y - Vertex2.y) + Vertex1.x * (Vertex2.y - Vertex3.y) + Vertex2.x * (Vertex3.y - Vertex1.y)) / 2.0);
	if (A == A1 + A2 + A3)//Compare area of 3 triangles around (x,y) and original area;
		return true;
	return false;
}

void CTriangle::Save(ofstream& OutFile)
{
	OutFile << "TRIANGLE" << "\t" << this->ID << "\t";
	OutFile << Vertex1.x << "\t" << Vertex1.y << "\t";
	OutFile << Vertex2.x << "\t" << Vertex2.y << "\t";
	OutFile << Vertex3.x << "\t" << Vertex3.y << "\t";
	FigType = TRIANGLE;
	CFigure::Save(OutFile);	//Saves Draw, Fill color
}

void CTriangle::Load(ifstream& InFile)
{
	char input[30] = {};
	InFile >> Vertex1.x >> Vertex1.y;
	InFile >> Vertex2.x >> Vertex2.y;
	InFile >> Vertex3.x >> Vertex3.y;
	FigType = TRIANGLE;
	CFigure::Load(InFile);	//Loads Draw, Fill color
}

void CTriangle::FitInsideDrawArea()
{
	//We have to Validate that all 3 vertecies are inside the draw area from all 4 sides

	//First Vertex

	if (Vertex1.y > (UI.height  - UI.StatusBarHeight)) //Bottomside Validation
	{
		Vertex3.y -= (Vertex1.y - UI.height + UI.StatusBarHeight); //Pushing Vertex 3 Inside
		Vertex2.y -= (Vertex1.y - UI.height  + UI.StatusBarHeight); //Pushing Vertex 2 Inside
		Vertex1.y -= (Vertex1.y - UI.height + UI.StatusBarHeight); //Pushing Vertex 1 Inside
	}
	if (Vertex1.y < UI.ToolBarHeight)//Topside Validation
	{
		Vertex3.y += (-Vertex1.y + UI.ToolBarHeight + 5);//Pushing Vertex 3 Inside
		Vertex2.y += (-Vertex1.y + UI.ToolBarHeight + 5);//Pushing Vertex 2 Inside
		Vertex1.y += (-Vertex1.y + UI.ToolBarHeight + 5);//Pushing Vertex 1 Inside
	}
	if (Vertex1.x > UI.width - 25) //Rightside Validation
	{
		Vertex3.x -= (Vertex1.x - UI.width + 25 - 5);//Pushing Vertex 3 Inside
		Vertex2.x -= (Vertex1.x - UI.width + 25 - 5);//Pushing Vertex 2 Inside
		Vertex1.x -= (Vertex1.x - UI.width + 25 - 5);//Pushing Vertex 1 Inside
	}
	if (Vertex1.x < 0) //Leftside Validation
	{
		Vertex3.x += (-Vertex1.x + 5);//Pushing Vertex 3 Inside
		Vertex2.x += (-Vertex1.x + 5);//Pushing Vertex 2 Inside
		Vertex1.x += (-Vertex1.x + 5);//Pushing Vertex 1 Inside
	}
	//Second Vertex

	if (Vertex2.y > (UI.height - UI.StatusBarHeight)) //Bottomside Validation
	{
		Vertex3.y -= (Vertex2.y - UI.height  + UI.StatusBarHeight); //Pushing Vertex 3 Inside
		Vertex1.y -= (Vertex2.y - UI.height  + UI.StatusBarHeight); //Pushing Vertex 1 Inside
		Vertex2.y -= (Vertex2.y - UI.height  + UI.StatusBarHeight); //Pushing Vertex 2 Inside
	}
	if (Vertex2.y < UI.ToolBarHeight)//Topside Validation
	{
		Vertex3.y += (-Vertex2.y + UI.ToolBarHeight + 5);//Pushing Vertex 3 Inside
		Vertex1.y += (-Vertex2.y + UI.ToolBarHeight + 5);//Pushing Vertex 1 Inside
		Vertex2.y += (-Vertex2.y + UI.ToolBarHeight + 5);//Pushing Vertex 2 Inside
	}
	if (Vertex2.x > UI.width - 25) //Rightside Validation
	{
		Vertex3.x -= (Vertex2.x - UI.width + 25 - 5);//Pushing Vertex 3 Inside
		Vertex1.x -= (Vertex2.x - UI.width + 25 - 5);//Pushing Vertex 1 Inside
		Vertex2.x -= (Vertex2.x - UI.width + 25 - 5);//Pushing Vertex 2 Inside
	}
	if (Vertex2.x < 0) //Leftside Validation
	{
		Vertex3.x += (-Vertex2.x + 5);//Pushing Vertex 3 Inside
		Vertex1.x += (-Vertex2.x + 5);//Pushing Vertex 1 Inside
		Vertex2.x += (-Vertex2.x + 5);//Pushing Vertex 2 Inside
	}
	//Third Vertex

	if (Vertex3.y > (UI.height - UI.StatusBarHeight)) //Bottomside Validation
	{
		Vertex1.y -= (Vertex3.y - UI.height  + UI.StatusBarHeight); //Pushing Vertex 1 Inside
		Vertex2.y -= (Vertex3.y - UI.height  + UI.StatusBarHeight); //Pushing Vertex 2 Inside
		Vertex3.y -= (Vertex3.y - UI.height  + UI.StatusBarHeight); //Pushing Vertex 3 Inside
	}
	if (Vertex3.y < UI.ToolBarHeight)//Topside Validation
	{
		Vertex1.y += (-Vertex3.y + UI.ToolBarHeight + 5);//Pushing Vertex 1 Inside
		Vertex2.y += (-Vertex3.y + UI.ToolBarHeight + 5);//Pushing Vertex 2 Inside
		Vertex3.y += (-Vertex3.y + UI.ToolBarHeight + 5);//Pushing Vertex 3 Inside
	}
	if (Vertex3.x > UI.width - 25) //Rightside Validation
	{
		Vertex1.x -= (Vertex3.x - UI.width + 25 - 5);//Pushing Vertex 1 Inside
		Vertex2.x -= (Vertex3.x - UI.width + 25 - 5);//Pushing Vertex 2 Inside
		Vertex3.x -= (Vertex3.x - UI.width + 25 - 5);//Pushing Vertex 3 Inside
	}
	if (Vertex3.x < 0) //Leftside Validation
	{
		Vertex1.x += (-Vertex3.x + 5);//Pushing Vertex 1 Inside
		Vertex2.x += (-Vertex3.x + 5);//Pushing Vertex 2 Inside
		Vertex3.x += (-Vertex3.x + 5);//Pushing Vertex 3 Inside
	}
}

bool CTriangle::DoubleSize()
{
	//checks if any of the triangle sides will get too wide or too tall

	if (2 * abs(Vertex1.x - Vertex2.x) > UI.width-30) //horizontal validation
		return false;
	if (2 * abs(Vertex2.x - Vertex3.x) > UI.width-30) //horizontal validation
		return false;
	if (2 * abs(Vertex1.x - Vertex3.x) > UI.width-30) //horizontal validation
		return false;
	if (2 * abs(Vertex1.y - Vertex2.y) > UI.height - UI.StatusBarHeight-UI.ToolBarHeight-50) //vertical validation
		return false;
	if (2 * abs(Vertex2.y - Vertex3.y) > UI.height - UI.StatusBarHeight-UI.ToolBarHeight-50) //vertical validation
		return false;
	if (2 * abs(Vertex1.y - Vertex3.y) > UI.height - UI.StatusBarHeight-UI.ToolBarHeight-50) //vertical validation
		return false;

	Point Center{};//Defines center in order to stretch the triangle around it
	Center.x = (Vertex1.x + Vertex2.x+Vertex3.x) / 3;
	Center.y = (Vertex2.y + Vertex2.y+Vertex3.y) / 3;

	//Vertex 1
	if (Vertex1.x > Center.x)//Vertex 1 is to the right of the center
		Vertex1.x += (Vertex1.x - Center.x);
	if (Vertex1.x < Center.x)//Vertex 1 is to the left of the center
		Vertex1.x -= (Center.x - Vertex1.x);
	if (Vertex1.y > Center.y)//Vertex 1 is below of the center
		Vertex1.y += (Vertex1.y - Center.y);
	if (Vertex1.y < Center.y)//Vertex 1 is above of the center
		Vertex1.y -= (Center.y - Vertex1.y);
	//Vertex 2
	if (Vertex2.x > Center.x)//Vertex 2 is to the right of the center
		Vertex2.x += (Vertex2.x - Center.x);
	if (Vertex2.x < Center.x)//Vertex 2 is to the left of the center
		Vertex2.x -= (Center.x - Vertex2.x);
	if (Vertex2.y > Center.y)//Vertex 2 is below of the center
		Vertex2.y += (Vertex2.y - Center.y);
	if (Vertex2.y < Center.y)//Vertex 2 is above of the center
		Vertex2.y -= (Center.y - Vertex2.y);
	//Vertex 3
	if (Vertex3.x > Center.x)//Vertex 3 is to the right of the center
		Vertex3.x += (Vertex3.x - Center.x);
	if (Vertex3.x < Center.x)//Vertex 3 is to the left of the center
		Vertex3.x -= (Center.x - Vertex3.x);
	if (Vertex3.y > Center.y)//Vertex 3 is below of the center
		Vertex3.y += (Vertex3.y - Center.y);
	if (Vertex3.y < Center.y)//Vertex 3 is above of the center
		Vertex3.y -= (Center.y - Vertex3.y);
	FitInsideDrawArea();
	return true;
}

bool CTriangle::HalfSize()
{
	//Defines center in order to shrink the triangle around it
	Point Center{};
	Center.x = (Vertex1.x + Vertex2.x + Vertex3.x) / 3;
	Center.y = (Vertex2.y + Vertex2.y + Vertex3.y) / 3;

	if (abs(Center.x - Vertex1.x) < 5 && abs(Center.y - Vertex1.y) < 5) //Vertex 1 validation
		return false;
	if (abs(Center.x - Vertex2.x) < 5 && abs(Center.y - Vertex2.y) < 5) //Vertex 2 validation
		return false;
	if (abs(Center.x - Vertex3.x) < 5 && abs(Center.y - Vertex3.y) < 5) //Vertex 3 validation
		return false;

	//Vertex 1
	if (Vertex1.x > Center.x)//Vertex 1 is to the right of the center
		Vertex1.x -= 0.5 * (Vertex1.x - Center.x);
	if (Vertex1.x < Center.x)//Vertex 1 is to the left of the center
		Vertex1.x += 0.5 * (Center.x - Vertex1.x);
	if (Vertex1.y > Center.y)//Vertex 1 is below of the center
		Vertex1.y -= 0.5 * (Vertex1.y - Center.y);
	if (Vertex1.y < Center.y)//Vertex 1 is above of the center
		Vertex1.y += 0.5 * (Center.y - Vertex1.y);

	//Vertex 2
	if (Vertex2.x > Center.x)//Vertex 2 is to the right of the center
		Vertex2.x -= 0.5 * (Vertex2.x - Center.x);
	if (Vertex2.x < Center.x)//Vertex 2 is to the left of the center
		Vertex2.x += 0.5 * (Center.x - Vertex2.x);
	if (Vertex2.y > Center.y)//Vertex 2 is below of the center
		Vertex2.y -= 0.5 * (Vertex2.y - Center.y);
	if (Vertex2.y < Center.y)//Vertex 2 is above of the center
		Vertex2.y += 0.5 * (Center.y - Vertex2.y);

	//Vertex 3
	if (Vertex3.x > Center.x)//Vertex 3 is to the right of the center
		Vertex3.x -= 0.5 * (Vertex3.x - Center.x);
	if (Vertex3.x < Center.x)//Vertex 3 is to the left of the center
		Vertex3.x += 0.5 * (Center.x - Vertex3.x);
	if (Vertex3.y > Center.y)//Vertex 3 is below of the center
		Vertex3.y -= 0.5 * (Vertex3.y - Center.y);
	if (Vertex3.y < Center.y)//Vertex 3 is above of the center
		Vertex3.y += 0.5 * (Center.y - Vertex3.y);
	FitInsideDrawArea();
	return true;
}
