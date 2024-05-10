#include"CHexagon.h"
#include <fstream>

CHexagon::CHexagon(CHexagon* H) :CFigure(H->FigGfxInfo) {
	this->Center = H->Center;
	FigType = HEXAGON;
	this->Size = H->Size;
}

CHexagon::CHexagon(Point P,GfxInfo HexagonGfxInfo):
	CFigure(HexagonGfxInfo)
{
	Center = P;
	FigType = HEXAGON;
	Size = 64;
	FitInsideDrawArea();
}

CHexagon::CHexagon(ifstream& InFile)
	: CFigure(InFile)
{
	Load(InFile);
	if (CreatedFigCount < ID)
		CreatedFigCount = ID + 1;
}

void CHexagon::Draw(Output* pOut) const
{
	pOut->DrawHexagon(Center, FigGfxInfo, Size, Selected);
}

void CHexagon::PrintInfo(Output* pOut)
{
	pOut->PrintMessage("Hexagon   ID: " + to_string(ID) + " ,Center : (" + to_string(Center.x) + "," + to_string(Center.y) + "),Side Length : " + to_string(2* Size));
}

void CHexagon::MoveFigure(int x, int y)
{
	Center.x = x;
	Center.y = y;
	FitInsideDrawArea();
}

FigureType CHexagon::GetFigType() const
{
	return FigType;
}

bool CHexagon::IsClicked(int x, int y)
{
	//This Check Works by splitting the hexagon into 3 regions of 2 triangles and a rectangle
	//the 2 triangles are checked by making sure the slope of the line between the clicked point and the side vertex
	//is below the upper edge and above the lower edge


	int s1p , s4p;//Slopes between Vertex1 and the point,Vertex4 and the point

	if (x== Center.x + 2 * Size) // Avoiding Division by zero in case the X values are too close
		s1p = (Center.y - y) / 0.01; 
	else
		s1p = (Center.y - y) / (Center.x + 2* Size - x); //Slope Calculation

	if (x == Center.x - 2 * Size) // Avoiding Division by zero in case the Y values are too close
		s4p =(Center.y - y) / 0.01;
	else
		s4p = (Center.y - y) /(Center.x- 2 * Size -x); //Slope Calculation

	if (x <= Center.x + Size && x >= Center.x - Size)
		if (y <= Center.y + Size * 1.732 && y >= Center.y - Size * 1.732)
			return true;//inner rectangle check

	if (s1p <= 1.732 && s1p >= -1.732)	//circular sector between two lines
		if (x <= Center.x + 2* Size && x >= Center.x + Size) // another rectangular section to get intersection(triangle)
			return true;//side triangle check 1

	if (s4p >= -1.732 && s4p <= 1.732)	//circular sector between two lines
		if (x >= Center.x - 2* Size && x <= Center.x - Size) // another rectangular section to get intersection(triangle)
			return true;//side triangle check 2

	return false;
}

void CHexagon::Save(ofstream& OutFile)
{
	OutFile << "HEXAGON" << "\t" << "\t" << this->ID << "\t"; //extra tab to make file more readable for user
	OutFile << Center.x << "\t" << Center.y << "\t"<< Size<<"\t";
	CFigure::Save(OutFile);
}

void CHexagon::Load(ifstream& InFile)
{
	char input[30] = {};
	InFile >> Center.x >> Center.y >> Size;
	FigType = HEXAGON;
	CFigure::Load(InFile);
}

void CHexagon::FitInsideDrawArea()
{
	if (Center.y + 2* Size *0.866 > (UI.height - 100 - UI.StatusBarHeight)) //Bottomside Validation
	{
		Center.y -= (Center.y + 2 * Size * 0.866 - UI.height + 100 - UI.StatusBarHeight - 5); //Pushing Center Inside
	}
	if (Center.y - 2 * Size * 0.866 < UI.ToolBarHeight)//Topside Validation
	{
		Center.y += (-Center.y + 2 * Size * 0.866 + UI.ToolBarHeight + 5);//Pushing Center Inside
	}
	if (Center.x + 2* Size > UI.width - 25) //Rightside Validation
	{
		Center.x -= (Center.x + 2 * Size - UI.width + 25 - 5);//Pushing Center Inside
	}
	if (Center.x - 2 * Size < 0) //Leftside Validation
	{
		Center.x += (-Center.x + 2 * Size + 5);//Pushing Center Inside
	}
}

bool CHexagon::DoubleSize()
{
	if ((2 * Size) > (UI.height - UI.ToolBarHeight-UI.StatusBarHeight-50) / 2) //if hexagon is too large 
		return false;
	Size *= 2;
	FitInsideDrawArea();
	return true;
}

bool CHexagon::HalfSize()
{
	if (Size <8)   //if Hexagon is too small
		return false;
	Size *= 0.5;
	FitInsideDrawArea();
	return true;
}

