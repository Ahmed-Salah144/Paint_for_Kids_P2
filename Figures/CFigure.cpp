#include "CFigure.h"
#include <fstream>

int CFigure::CreatedFigCount = 0;

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	ID =++CreatedFigCount;
}

CFigure::CFigure(ifstream& InFile) // initialize id and selected
	: Selected(false)
{
	InFile >> ID;
	++CreatedFigCount;
	InFile.ignore(30, '\t');
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

bool CFigure::IsTheSame(CFigure* pFig) const
{
	if (pFig == NULL)
		return false;
	if (pFig->ID == this->ID)
		return true;
	return false;
}

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

color CFigure::GetDrawClr()
{
	return FigGfxInfo.DrawClr;
}

color CFigure::GetFillClr()
{
	if (IsFilled())
		return FigGfxInfo.FillClr;
	return SNOW;
}

bool CFigure::IsFilled()
{
	return FigGfxInfo.isFilled;
}

void CFigure::SetID(int id)
{
	ID = id;
}
int CFigure::GetID() {
	return ID;
}
void CFigure::Save(ofstream& OutFile)
{
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

void CFigure::Load(ifstream& InFile)
{
	char input[30];
	InFile.ignore(30, '\t');
	InFile.getline(input, 30, '\t');	//Draw Collor
	if (strcmp(input, "BLACK") == 0)	
		ChngDrawClr(BLACK);
	else if (strcmp(input, "YELLOW") == 0)
		ChngDrawClr(YELLOW);
	else if (strcmp(input, "ORANGE") == 0)
		ChngDrawClr(ORANGE);
	else if (strcmp(input, "RED") == 0)
		ChngDrawClr(RED);
	else if (strcmp(input, "GREEN") == 0)
		ChngDrawClr(GREEN);
	else if (strcmp(input, "BLUE") == 0)
		ChngDrawClr(BLUE);

	InFile.getline(input, 30, '\n'); //Fill Color
	if (strcmp(input, "BLACK") == 0)
		ChngFillClr(BLACK);
	else if (strcmp(input, "YELLOW") == 0)
		ChngFillClr(YELLOW);
	else if (strcmp(input, "ORANGE") == 0)
		ChngFillClr(ORANGE);
	else if (strcmp(input, "RED") == 0)
		ChngFillClr(RED);
	else if (strcmp(input, "GREEN") == 0)
		ChngFillClr(GREEN);
	else if (strcmp(input, "BLUE") == 0)
		ChngFillClr(BLUE);
	else if (strcmp(input, "NO_FILL") == 0)
	{
		ChngFillClr(UI.FillColor); //initiallizes it to the UI color
		FigGfxInfo.isFilled = false;
	}
}

CFigure::~CFigure()
{
}
