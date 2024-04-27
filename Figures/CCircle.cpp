#include"CCircle.h"
#include <fstream>
#include "../Utils.h"


CCircle::CCircle(Point P1,Point P2, GfxInfo CircleGfxInfo) :
	CFigure(CircleGfxInfo)
{
	Center = P1;
	OuterPoint = P2;
	FigType = CIRCLE;
	Radius = sqrt((P1.x - P2.x)* (P1.x - P2.x) + (P1.y - P2.y)* (P1.y - P2.y));
}

CCircle::CCircle(ifstream& InFile)
	: CFigure (InFile)
{
	Load(InFile);
}


void CCircle::Draw(Output* pOut) const
{
	pOut->DrawCircle(Center,OuterPoint,FigGfxInfo, Selected);
}

void CCircle::PrintInfo(Output* pOut)
{
	pOut->PrintMessage("Circle   ID: " + to_string(ID) + " ,Center : (" + to_string(Center.x) + "," + to_string(Center.y) + "),Radius : " + to_string(Radius));
}

bool CCircle::IsClicked(int x, int y)
{
	int distance= sqrt((Center.x - x)* (Center.x - x) + (Center.y - y)* (Center.y - y));
	if (distance <= Radius)
		return true;
	return false;
}

FigureType CCircle::GetFigType()
{
	return FigType;
}

void CCircle::Save(ofstream& OutFile)
{
	OutFile << "CIRCLE" << "\t" << "\t" << this->ID << "\t";
	OutFile << Center.x << "\t" << Center.y << "\t";
	OutFile << OuterPoint.x << "\t" << OuterPoint.y << "\t";
	OutFile << Radius << "\t";

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

	if(FigGfxInfo.isFilled == false) //prints figure's fill color
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

void CCircle::Load(ifstream& InFile)
{
	char input[30] = {};
	InFile >> Center.x >> Center.y >> OuterPoint.x >> OuterPoint.y >> Radius;
	FigType = CIRCLE;

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