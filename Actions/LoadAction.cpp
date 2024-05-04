#include "LoadAction.h"
#include "../Figures/CFigure.h"
#include "../ApplicationManager.h"
#include "../GUI/input.h"
#include "../GUI/output.h"
#include <fstream>
#include "../Figures/CFigure.h"
#include "../Figures/CCircle.h"
#include "../Figures/CHexagon.h"
#include "../Figures/CRectangle.h"
#include "../Figures/CSquare.h"
#include "../Figures/CTriangle.h"

LoadAction::LoadAction(ApplicationManager * papp)
	: Action(papp)
{
}

void LoadAction::ReadActionParameters()
{
	Input* pin = pManager->GetInput();
	Output* pout = pManager->GetOutput();
	pout->PrintMessage("Enter load file name: ");
	file_name = ".\\\\Saves\\\\" + pin->GetString(pout);
}

void LoadAction::Execute()
{
	this->ReadActionParameters();	//Reads file_name from user
	ifstream fin(file_name);		//file input
	Output* pout = pManager->GetOutput();

	if (fin.is_open() == false)
	{
		pout->PrintMessage("Error: Can't load, couldn't open File");
		return;
	}
	
	pManager->ExecuteAction(CLEARED);	//clears draw area before loading
	char input[30] = {};				//array of characters to store user's input
	fin.getline(input, 30, '\t');		//Current_Draw_Color
	if (strcmp(input, "BLACK") == 0)	//Sets Current_Draw_Color
		UI.DrawColor = BLACK;
	else if (strcmp(input, "YELLOW") == 0)
		UI.DrawColor = YELLOW;
	else if (strcmp(input, "ORANGE") == 0)
		UI.DrawColor = ORANGE;
	else if (strcmp(input, "RED") == 0)
		UI.DrawColor = RED;
	else if (strcmp(input, "GREEN") == 0)
		UI.DrawColor = GREEN;
	else if (strcmp(input, "BLUE") == 0)
		UI.DrawColor = BLUE;
	else
		exit(1);	//exit file if load file is corrupted

	fin.getline(input, 30, '\n');		// Current_Fill_Color
	if (strcmp(input, "BLACK") == 0)	//Sets Current_Fill_Color
		UI.FillColor = BLACK;
	else if (strcmp(input, "YELLOW") == 0)
		UI.FillColor = YELLOW;
	else if (strcmp(input, "ORANGE") == 0)
		UI.FillColor = ORANGE;
	else if (strcmp(input, "RED") == 0)
		UI.FillColor = RED;
	else if (strcmp(input, "GREEN") == 0)
		UI.FillColor = GREEN;
	else if (strcmp(input, "BLUE") == 0)
		UI.FillColor = BLUE;
	else
		exit(1);	//exit file if load file is corrupted

	int num_figures; 
	fin >> num_figures; // Number_of_Figures_n
	fin.ignore();

	CFigure* Figure;
	// exits program with code 1 if file is corrupted (Draw color or Fill color not one of the 6 colors or NO_FILL)
	for (int i = 0; i < num_figures && fin.eof() == false; i++) //loops on each line loading and adding the figure
	{
		fin.getline(input, 30, '\t');

		if (strcmp(input, "RECTANGLE") == 0)
		{
			Figure = new CRectangle(fin);
			pManager->AddFigure(Figure);
		}
		else if (strcmp(input, "SQUARE") == 0)
		{
			Figure = new CSquare(fin);
			pManager->AddFigure(Figure);
		}
		else if (strcmp(input, "TRIANGLE") == 0)
		{
			Figure = new CTriangle(fin);
			pManager->AddFigure(Figure);
		}
		else if (strcmp(input, "CIRCLE") == 0)
		{
			Figure = new CCircle(fin);
			pManager->AddFigure(Figure);
		}
		else if (strcmp(input, "HEXAGON") == 0)
		{
			Figure = new CHexagon(fin);
			pManager->AddFigure(Figure);
		}
	}
	pout->PrintMessage("Loaded Successfully, from " + file_name);
}