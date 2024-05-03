#include"CSquare.h"
#include <fstream>

CSquare::CSquare(Point P, GfxInfo SquareGfxInfo) :
	CFigure(SquareGfxInfo)
{
	Center = P;
	FigType = SQUARE;
	//Size = 1;
	FitInsideDrawArea();
}

CSquare::CSquare(ifstream& InFile)
	: CFigure(InFile) // initializes ID and CFigure::selected = false
{
	Load(InFile);
}

void CSquare::Draw(Output* pOut) const
{
	pOut->DrawSquare(Center, FigGfxInfo,Selected);
}

void CSquare::PrintInfo(Output* pOut)
{
	pOut->PrintMessage("Square   ID: " + to_string(ID) + " ,Center : (" + to_string(Center.x) + "," + to_string(Center.y) + "),Length : " + to_string(160*((int)1)));
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

void CSquare::Save(ofstream& OutFile)
{
	OutFile << "SQUARE" << "\t" << "\t" << this->ID << "\t";	//extra tab to make file more readable for user
	OutFile << Center.x << "\t" << Center.y << "\t";
	CFigure::Save(OutFile);	//Saves Draw, Fill color
}

void CSquare::Load(ifstream& InFile)
{
	char input[30] = {};
	InFile >> Center.x >> Center.y;
	FigType = SQUARE;
	CFigure::Load(InFile);	//Loades Draw, Fill color
}
void CSquare::FitInsideDrawArea()
{
	if (Center.y + 1 * 80 > (UI.height - 100 - UI.StatusBarHeight)) //Bottomside Validation(Salem)
	{
		Center.y -= (Center.y + 1 * 80 - UI.height + 100 - UI.StatusBarHeight - 5); //Pushing Center Inside
	}
	if (Center.y - 1 * 80 < UI.ToolBarHeight)//Topside Validation(Salem)
	{
		Center.y += (-Center.y + 1 * 80 + UI.ToolBarHeight + 5);//Pushing Center Inside
	}
	if (Center.x + 1 * 80 > UI.width - 25) //Rightside Validation(Salem)
	{
		Center.x -= (Center.x + 1 * 80 - UI.width + 25 - 5);//Pushing Center Inside
	}
	if (Center.x - 1 * 80 < 0) //Leftside Validation(Salem)
	{
		Center.x += (-Center.x + 1 * 80 + 5);//Pushing Center Inside
	}
}

bool CSquare::DoubleSize()
{
	if ((1 * 80) > (UI.height - 200) / 2)
		return false;
	//1 *= 2;
	FitInsideDrawArea();
	return true;
}

bool CSquare::HalfSize()
{
	if (1 < 0.1)
		return false;
	//1 *= 0.5;
	FitInsideDrawArea();
	return true;
}
