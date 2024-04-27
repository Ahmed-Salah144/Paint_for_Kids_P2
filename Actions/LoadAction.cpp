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
#include "../Utils.h"

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
	this->ReadActionParameters();
	pManager->ExecuteAction(CLEARED);

	ifstream fin(file_name); //file input
	Output* pout = pManager->GetOutput();

	if (fin.is_open() == false)
	{
		pout->PrintMessage("Error: Can't load, couldn't open File");
		return;
	}
		
	char input[30] = {};		// array of characters to store user's input
	fin.getline(input, 20, '\t');	// Current_Draw_Color
	switch (ParseColor(input))
	{
	case lOAD_BLACK:
		UI.DrawColor = BLACK;
		break;
	case LOAD_YELLOW:
		UI.DrawColor = YELLOW;
		break;
	case LOAD_ORANGE:
		UI.DrawColor = ORANGE;
		break;
	case LOAD_RED:
		UI.DrawColor = RED;
		break;
	case LOAD_GREEN:
		UI.DrawColor = GREEN;
		break;
	case LOAD_BLUE:
		UI.DrawColor = BLUE;
		break;
	}

	fin.getline(input, 20, '\n');	// Current_Fill_Color
	switch (ParseColor(input))
	{
	case lOAD_BLACK:
		UI.FillColor = BLACK;
		break;
	case LOAD_YELLOW:
		UI.FillColor = YELLOW;
		break;
	case LOAD_ORANGE:
		UI.FillColor = ORANGE;
		break;
	case LOAD_RED:
		UI.FillColor = RED;
		break;
	case LOAD_GREEN:
		UI.FillColor = GREEN;
		break;
	case LOAD_BLUE:
		UI.FillColor = BLUE;
		break;
	}

	int num_figures; 
	fin >> num_figures; // Number_of_Figures_n
	fin.ignore();

	CFigure* Figure;
	for (int i = 0; i < num_figures && fin.eof() == false; i++) // exit program with code 1 if file is corrupted (Draw color or Fill color not one of the 6 colors)
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