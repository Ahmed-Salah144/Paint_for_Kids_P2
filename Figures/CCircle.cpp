#include"CCircle.h"
#include <fstream>


CCircle::CCircle(Point P1,Point P2, GfxInfo CircleGfxInfo) :
	CFigure(CircleGfxInfo)
{
	Center = P1;
	OuterPoint = P2;
	FigType = CIRCLE;
	Radius = sqrt((P1.x - P2.x)* (P1.x - P2.x) + (P1.y - P2.y)* (P1.y - P2.y));
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
	OutFile << Center.x << "\t" << Center.y << "\t" << Radius << "\t";

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
