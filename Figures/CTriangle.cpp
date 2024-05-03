#include "CTriangle.h"
#include <fstream>
#include "../Utils.h"

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

void CTriangle::Save(ofstream& OutFile)
{
	OutFile << "TRIANGLE" << "\t" << this->ID << "\t";
	OutFile << Vertex1.x << "\t" << Vertex1.y << "\t";
	OutFile << Vertex2.x << "\t" << Vertex2.y << "\t";
	OutFile << Vertex3.x << "\t" << Vertex3.y << "\t";
	FigType = TRIANGLE;


	if (FigGfxInfo.DrawClr == BLACK) //prints figure's draw color
		OutFile << "BLACK" << "\t";
	else if (FigGfxInfo.DrawClr == YELLOW)
		OutFile << "YELLOW" << "\t";
	else if (FigGfxInfo.DrawClr == ORANGE)
		OutFile << "ORANGE" << "\t";
	else if (FigGfxInfo.DrawClr == RED)
		OutFile << "RED" << "\t";
	else if (FigGfxInfo.DrawClr == GREEN)
		OutFile << "GREEN" << "\t";
	else if (FigGfxInfo.DrawClr == BLUE)
		OutFile << "BLUE" << "\t";

	if (FigGfxInfo.isFilled == false) //prints figure's fill color
		OutFile << "NO_FILL" << "\n";
	else if (FigGfxInfo.FillClr == BLACK)
		OutFile << "BLACK" << "\n";
	else if (FigGfxInfo.FillClr == YELLOW)
		OutFile << "YELLOW" << "\n";
	else if (FigGfxInfo.FillClr == ORANGE)
		OutFile << "ORANGE" << "\n";
	else if (FigGfxInfo.FillClr == RED)
		OutFile << "RED" << "\n";
	else if (FigGfxInfo.FillClr == GREEN)
		OutFile << "GREEN" << "\n";
	else if (FigGfxInfo.FillClr == BLUE)
		OutFile << "BLUE" << "\n";

}

void CTriangle::Load(ifstream& InFile)
{
	char input[30] = {};
	InFile >> Vertex1.x >> Vertex1.y;
	InFile >> Vertex2.x >> Vertex2.y;
	InFile >> Vertex3.x >> Vertex3.y;
	FigType = TRIANGLE;

	InFile.ignore(30, '\t');
	InFile.getline(input, 30, '\t'); //Draw Collor
	switch (ParseColor(input))
	{
	case lOAD_BLACK:
		FigGfxInfo.DrawClr = BLACK;
		break;
	case LOAD_YELLOW:
		FigGfxInfo.DrawClr = YELLOW;
		break;
	case LOAD_ORANGE:
		FigGfxInfo.DrawClr = ORANGE;
		break;
	case LOAD_RED:
		FigGfxInfo.DrawClr = RED;
		break;
	case LOAD_GREEN:
		FigGfxInfo.DrawClr = GREEN;
		break;
	case LOAD_BLUE:
		FigGfxInfo.DrawClr = BLUE;
		break;
	default:
		exit(1);
		break;
	}

	InFile.getline(input, 30, '\n'); //Fill Color
	switch (ParseColor(input))
	{
	case lOAD_BLACK:
		FigGfxInfo.FillClr = BLACK;
		break;
	case LOAD_YELLOW:
		FigGfxInfo.FillClr = YELLOW;
		break;
	case LOAD_ORANGE:
		FigGfxInfo.FillClr = ORANGE;
		break;
	case LOAD_RED:
		FigGfxInfo.FillClr = RED;
		break;
	case LOAD_GREEN:
		FigGfxInfo.FillClr = GREEN;
		break;
	case LOAD_BLUE:
		FigGfxInfo.FillClr = BLUE;
		break;
	case LOAD_NO_FILL:
		FigGfxInfo.isFilled = false;
		FigGfxInfo.FillClr = UI.FillColor; //initiallizes it to the UI color
		break;
	default:
		exit(1);
		break;
	}
}

void CTriangle::FitInsideDrawArea()
{
	//First Corner

	if (Vertex1.y > (UI.height - 100 - UI.StatusBarHeight)) //Bottomside Validation(Salem) 
	{
		Vertex3.y -= (Vertex1.y - UI.height + 100 - UI.StatusBarHeight - 5); //Pushing Corner 2 Inside
		Vertex2.y -= (Vertex1.y - UI.height + 100 - UI.StatusBarHeight - 5); //Pushing Corner 2 Inside
		Vertex1.y -= (Vertex1.y - UI.height + 100 - UI.StatusBarHeight - 5); //Pushing Corner 1 Inside
	}
	if (Vertex1.y < UI.ToolBarHeight)//Topside Validation(Salem)
	{
		Vertex3.y += (-Vertex1.y + UI.ToolBarHeight + 5);//Pushing Corner 3 Inside
		Vertex2.y += (-Vertex1.y + UI.ToolBarHeight + 5);//Pushing Corner 2 Inside
		Vertex1.y += (-Vertex1.y + UI.ToolBarHeight + 5);//Pushing Corner 1 Inside
	}
	if (Vertex1.x > UI.width - 25) //Rightside Validation(Salem)
	{
		Vertex3.x -= (Vertex1.x - UI.width + 25 - 5);//Pushing Corner 3 Inside
		Vertex2.x -= (Vertex1.x - UI.width + 25 - 5);//Pushing Corner 2 Inside
		Vertex1.x -= (Vertex1.x - UI.width + 25 - 5);//Pushing Corner 1 Inside
	}
	if (Vertex1.x < 0) //Leftside Validation(Salem)
	{
		Vertex3.x += (-Vertex1.x + 5);//Pushing Corner 3 Inside
		Vertex2.x += (-Vertex1.x + 5);//Pushing Corner 2 Inside
		Vertex1.x += (-Vertex1.x + 5);//Pushing Corner 1 Inside
	}
	//Second Corner

	if (Vertex2.y > (UI.height - 100 - UI.StatusBarHeight)) //Bottomside Validation(Salem) 
	{
		Vertex3.y -= (Vertex2.y - UI.height + 100 - UI.StatusBarHeight - 5); //Pushing Corner 3 Inside
		Vertex1.y -= (Vertex2.y - UI.height + 100 - UI.StatusBarHeight - 5); //Pushing Corner 1 Inside
		Vertex2.y -= (Vertex2.y - UI.height + 100 - UI.StatusBarHeight - 5); //Pushing Corner 2 Inside
	}
	if (Vertex2.y < UI.ToolBarHeight)//Topside Validation(Salem)
	{
		Vertex3.y += (-Vertex2.y + UI.ToolBarHeight + 5);//Pushing Corner 3 Inside
		Vertex1.y += (-Vertex2.y + UI.ToolBarHeight + 5);//Pushing Corner 1 Inside
		Vertex2.y += (-Vertex2.y + UI.ToolBarHeight + 5);//Pushing Corner 2 Inside
	}
	if (Vertex2.x > UI.width - 25) //Rightside Validation(Salem)
	{
		Vertex3.x -= (Vertex2.x - UI.width + 25 - 5);//Pushing Corner 3 Inside
		Vertex1.x -= (Vertex2.x - UI.width + 25 - 5);//Pushing Corner 1 Inside
		Vertex2.x -= (Vertex2.x - UI.width + 25 - 5);//Pushing Corner 2 Inside
	}
	if (Vertex2.x < 0) //Leftside Validation(Salem)
	{
		Vertex3.x += (-Vertex2.x + 5);//Pushing Corner 3 Inside
		Vertex1.x += (-Vertex2.x + 5);//Pushing Corner 1 Inside
		Vertex2.x += (-Vertex2.x + 5);//Pushing Corner 2 Inside
	}
	//Third Corner

	if (Vertex3.y > (UI.height - 100 - UI.StatusBarHeight)) //Bottomside Validation(Salem) 
	{
		Vertex1.y -= (Vertex3.y - UI.height + 100 - UI.StatusBarHeight - 5); //Pushing Corner 1 Inside
		Vertex2.y -= (Vertex3.y - UI.height + 100 - UI.StatusBarHeight - 5); //Pushing Corner 2 Inside
		Vertex3.y -= (Vertex3.y - UI.height + 100 - UI.StatusBarHeight - 5); //Pushing Corner 3 Inside
	}
	if (Vertex3.y < UI.ToolBarHeight)//Topside Validation(Salem)
	{
		Vertex1.y += (-Vertex3.y + UI.ToolBarHeight + 5);//Pushing Corner 1 Inside
		Vertex2.y += (-Vertex3.y + UI.ToolBarHeight + 5);//Pushing Corner 2 Inside
		Vertex3.y += (-Vertex3.y + UI.ToolBarHeight + 5);//Pushing Corner 3 Inside
	}
	if (Vertex3.x > UI.width - 25) //Rightside Validation(Salem)
	{
		Vertex1.x -= (Vertex3.x - UI.width + 25 - 5);//Pushing Corner 1 Inside
		Vertex2.x -= (Vertex3.x - UI.width + 25 - 5);//Pushing Corner 2 Inside
		Vertex3.x -= (Vertex3.x - UI.width + 25 - 5);//Pushing Corner 3 Inside
	}
	if (Vertex3.x < 0) //Leftside Validation(Salem)
	{
		Vertex1.x += (-Vertex3.x + 5);//Pushing Corner 1 Inside
		Vertex2.x += (-Vertex3.x + 5);//Pushing Corner 2 Inside
		Vertex3.x += (-Vertex3.x + 5);//Pushing Corner 3 Inside
	}
}

bool CTriangle::DoubleSize()
{
	if (2 * abs(Vertex1.x-Vertex2.x) > UI.width) //horizontal validation
		return false;
	if (2 * abs(Vertex2.x - Vertex3.x) > UI.width) //horizontal validation
		return false;
	if (2 * abs(Vertex1.x - Vertex3.x) > UI.width) //horizontal validation
		return false;
	if (2 * abs(Vertex1.y - Vertex2.y) > UI.height - UI.StatusBarHeight) //vertical validation
		return false;
	if (2 * abs(Vertex2.y - Vertex3.y) > UI.height - UI.StatusBarHeight) //vertical validation
		return false;
	if (2 * abs(Vertex1.y - Vertex3.y) > UI.height - UI.StatusBarHeight) //vertical validation
		return false;

	Point Center{};
	Center.x = (Vertex1.x + Vertex2.x+Vertex3.x) / 3;
	Center.y = (Vertex2.y + Vertex2.y+Vertex3.y) / 3;

	//Corner 1
	if (Vertex1.x > Center.x)//Corner 1 is to the right of the center
		Vertex1.x += (Vertex1.x - Center.x);
	if (Vertex1.x < Center.x)//Corner 1 is to the left of the center
		Vertex1.x -= (Center.x - Vertex1.x);
	if (Vertex1.y > Center.y)//Corner 1 is below of the center
		Vertex1.y += (Vertex1.y - Center.y);
	if (Vertex1.y < Center.y)//Corner 1 is above of the center
		Vertex1.y -= (Center.y - Vertex1.y);
	//Corner 2
	if (Vertex2.x > Center.x)//Corner 2 is to the right of the center
		Vertex2.x += (Vertex2.x - Center.x);
	if (Vertex2.x < Center.x)//Corner 2 is to the left of the center
		Vertex2.x -= (Center.x - Vertex2.x);
	if (Vertex2.y > Center.y)//Corner 2 is below of the center
		Vertex2.y += (Vertex2.y - Center.y);
	if (Vertex2.y < Center.y)//Corner 2 is above of the center
		Vertex2.y -= (Center.y - Vertex2.y);
	//Corner 3
	if (Vertex3.x > Center.x)//Corner 3 is to the right of the center
		Vertex3.x += (Vertex3.x - Center.x);
	if (Vertex3.x < Center.x)//Corner 3 is to the left of the center
		Vertex3.x -= (Center.x - Vertex3.x);
	if (Vertex3.y > Center.y)//Corner 3 is below of the center
		Vertex3.y += (Vertex3.y - Center.y);
	if (Vertex3.y < Center.y)//Corner 3 is above of the center
		Vertex3.y -= (Center.y - Vertex3.y);
	FitInsideDrawArea();
	return true;
}

bool CTriangle::HalfSize()
{
	if (2 * abs(Vertex1.x - Vertex2.x) <10) //horizontal validation
		return false;
	if (2 * abs(Vertex2.x - Vertex3.x) < 10) //horizontal validation
		return false;
	if (2 * abs(Vertex1.x - Vertex3.x) < 10) //horizontal validation
		return false;
	if (2 * abs(Vertex1.y - Vertex2.y) < 10) //vertical validation
		return false;
	if (2 * abs(Vertex2.y - Vertex3.y) < 10) //vertical validation
		return false;
	if (2 * abs(Vertex1.y - Vertex3.y) < 10) //vertical validation
		return false;
	Point Center{};
	Center.x = (Vertex1.x + Vertex2.x + Vertex3.x) / 3;
	Center.y = (Vertex2.y + Vertex2.y + Vertex3.y) / 3;
	//Corner 1
	if (Vertex1.x > Center.x)//Corner 1 is to the right of the center
		Vertex1.x -= 0.5 * (Vertex1.x - Center.x);
	if (Vertex1.x < Center.x)//Corner 1 is to the left of the center
		Vertex1.x += 0.5 * (Center.x - Vertex1.x);
	if (Vertex1.y > Center.y)//Corner 1 is below of the center
		Vertex1.y -= 0.5 * (Vertex1.y - Center.y);
	if (Vertex1.y < Center.y)//Corner 1 is above of the center
		Vertex1.y += 0.5 * (Center.y - Vertex1.y);

	//Corner 2
	if (Vertex2.x > Center.x)//Corner 2 is to the right of the center
		Vertex2.x -= 0.5 * (Vertex2.x - Center.x);
	if (Vertex2.x < Center.x)//Corner 2 is to the left of the center
		Vertex2.x += 0.5 * (Center.x - Vertex2.x);
	if (Vertex2.y > Center.y)//Corner 2 is below of the center
		Vertex2.y -= 0.5 * (Vertex2.y - Center.y);
	if (Vertex2.y < Center.y)//Corner 2 is above of the center
		Vertex2.y += 0.5 * (Center.y - Vertex2.y);

	//Corner 2
	if (Vertex3.x > Center.x)//Corner 3 is to the right of the center
		Vertex3.x -= 0.5 * (Vertex3.x - Center.x);
	if (Vertex3.x < Center.x)//Corner 3 is to the left of the center
		Vertex3.x += 0.5 * (Center.x - Vertex3.x);
	if (Vertex3.y > Center.y)//Corner 3 is below of the center
		Vertex3.y -= 0.5 * (Vertex3.y - Center.y);
	if (Vertex3.y < Center.y)//Corner 3 is above of the center
		Vertex3.y += 0.5 * (Center.y - Vertex3.y);
	FitInsideDrawArea();
	return true;
}
