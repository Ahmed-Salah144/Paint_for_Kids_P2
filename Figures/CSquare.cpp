#include"CSquare.h"
#include <fstream>

CSquare::CSquare(Point P, GfxInfo SquareGfxInfo) :
	CFigure(SquareGfxInfo)
{
	Center = P;
	FigType = SQUARE;
}

void CSquare::Draw(Output* pOut) const
{
	pOut->DrawSquare(Center, FigGfxInfo, Selected);
}

void CSquare::PrintInfo(Output* pOut)
{
	pOut->PrintMessage("Square   ID: " + to_string(ID) + " ,Center : (" + to_string(Center.x) + "," + to_string(Center.y) + "),Length : " + to_string(113));
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
	OutFile << "SQUARE" << "\t" << "\t" << this->ID << "\t";
	OutFile << Center.x << "\t" << Center.y << "\t";

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
