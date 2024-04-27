#include "CRectangle.h"
#include "fstream"
#include "../Utils.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	FigType = RECTANGLE;
	L = abs(P1.x - P2.x);
	W = abs(P1.y - P2.y);
}

CRectangle::CRectangle(ifstream& InFile)
	: CFigure(InFile) // initializes ID and CFigure::selected = false
{
	Load(InFile);
}
	

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

void CRectangle::PrintInfo(Output* pOut)
{
	string Message = "Rectangle   ID: " + to_string(ID) + " ,Corner 1: (" + to_string(Corner1.x) + "," + to_string(Corner1.y) + ")" + " ,Corner 2: (" + to_string(Corner2.x) + "," + to_string(Corner2.y) + ")";
	Message += ",Length: "+to_string(L)+",Width: "+to_string(W);
	pOut->PrintMessage(Message);
}

bool CRectangle::IsClicked(int x, int y)
{
	if (x >= Corner1.x && x <= Corner2.x || x <= Corner1.x && x >= Corner2.x)
		if (y >= Corner1.y && y <= Corner2.y || y <= Corner1.y && y >= Corner2.y)
		return true;
	return false;
}

FigureType CRectangle::GetFigType()
{
	return FigType;
}

void CRectangle::Save(ofstream& OutFile)
{
	OutFile << "RECTANGLE" << "\t" << this->ID << "\t";
	OutFile << Corner1.x << "\t" << Corner1.y << "\t";
	OutFile << Corner2.x << "\t" << Corner2.y << "\t";

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

void CRectangle::Load(ifstream& InFile)
{
	char input[30] = {};
	InFile >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y;
	FigType = RECTANGLE;

	InFile.ignore(30,'\t');
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