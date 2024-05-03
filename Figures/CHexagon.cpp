#include"CHexagon.h"
#include <fstream>
#include "../Utils.h"

CHexagon::CHexagon(Point P,GfxInfo HexagonGfxInfo):
	CFigure(HexagonGfxInfo)
{
	Center = P;
	FigType = HEXAGON;
	//Size = 1;
	FitInsideDrawArea();
}

CHexagon::CHexagon(ifstream& InFile)
	: CFigure(InFile)
{
	Load(InFile);
}


void CHexagon::Draw(Output* pOut) const
{
	pOut->DrawHexagon(Center, FigGfxInfo, Selected);
}

void CHexagon::PrintInfo(Output* pOut)
{
	pOut->PrintMessage("Hexagon   ID: " + to_string(ID) + " ,Center : (" + to_string(Center.x) + "," + to_string(Center.y) + "),Side Length : " + to_string(100));
}

bool CHexagon::IsClicked(int x, int y)
{
	int s1p , s4p;
	if (x== Center.x+100)
		s1p = (Center.y - y) / 0.01;
	else
		s1p = (Center.y - y) / (Center.x + 100 - x);

	if (x == Center.x - 100)
		s4p =(Center.y - y) / 0.01;
	else
		s4p = (Center.y - y) /(Center.x-100 -x);

	if (x <= Center.x + 50 && x >= Center.x - 50)
		if (y <= Center.y + 50 * 1.732 && y >= Center.y - 50 * 1.732)
			return true;//inner rectangle check

	if (s1p <= 1.732 && s1p >= -1.732)	//circular sector between two lines
		if (x <= Center.x + 100 && x >= Center.x + 50) // another section to get intersecion(triangle)
			return true;//side triangle check 1

	if (s4p >= -1.732 && s4p <= 1.732)	//circular sector between two lines
		if (x >= Center.x - 100 && x <= Center.x - 50) // another section to get intersecion(triangle)
			return true;//side triangle check 2

	return false;
}

FigureType CHexagon::GetFigType()
{
	return FigType;
}

void CHexagon::Save(ofstream& OutFile)
{
	OutFile << "HEXAGON" << "\t" << "\t" << this->ID << "\t";
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

void CHexagon::Load(ifstream& InFile)
{
	char input[30] = {};
	InFile >> Center.x >> Center.y;
	FigType = HEXAGON;

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

void CHexagon::FitInsideDrawArea()
{
	if (Center.y + 1*86.6 > (UI.height - 100 - UI.StatusBarHeight)) //Bottomside Validation(Salem)
	{
		Center.y -= (Center.y + 1 * 86.6 - UI.height + 100 - UI.StatusBarHeight - 5); //Pushing Center Inside
	}
	if (Center.y - 1 * 86.6 < UI.ToolBarHeight)//Topside Validation(Salem)
	{
		Center.y += (-Center.y + 1 * 86.6 + UI.ToolBarHeight + 5);//Pushing Center Inside
	}
	if (Center.x + 1*100 > UI.width - 25) //Rightside Validation(Salem)
	{
		Center.x -= (Center.x + 1 * 100 - UI.width + 25 - 5);//Pushing Center Inside
	}
	if (Center.x - 1 * 100 < 0) //Leftside Validation(Salem)
	{
		Center.x += (-Center.x + 1 * 100 + 5);//Pushing Center Inside
	}
}

bool CHexagon::DoubleSize()
{
	if ((1 * 100) > (UI.height - 200) / 2)
		return false;
	//Size *= 2;
	FitInsideDrawArea();
	return true;
}

bool CHexagon::HalfSize()
{
	if (1<0.1)
		return false;
	//Size *= 0.5;
	FitInsideDrawArea();
	return true;
}
