#include "SaveAction.h"
#include "../Figures/CFigure.h"
#include "../ApplicationManager.h"
#include "../GUI/input.h"
#include "../GUI/output.h"

SaveAction::SaveAction(ApplicationManager* papp)
	: Action(papp)
{
}

void SaveAction::ReadActionParameters()
{
	Input* pin = pManager->GetInput();
	Output* pout = pManager->GetOutput();
	pout->PrintMessage("Enter save file name:");
	file_name = ".\\\\Saves\\\\" + pin->GetString(pout);
}

void SaveAction::Execute()
{
	this->ReadActionParameters();

	ofstream OutFile(file_name);
	Output* pout = pManager->GetOutput();

	if (OutFile.is_open())
	{
		pManager->SaveAll(OutFile);
		OutFile.close();

		pout->PrintMessage("Saved successfuly!, to " + file_name);
	}
	else
		pout->PrintMessage("Error: Can't save, couldn't open File");
	
}