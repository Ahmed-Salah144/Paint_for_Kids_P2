#include "DeleteAction.h"
#include "..\Figures\CFigure.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

DeleteAction::DeleteAction(ApplicationManager* pApp) :Action(pApp)
{
}

void DeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	SelectedFigCount = pManager->GetSelectedFigureCount();
	if (SelectedFigCount == 0)
	{
		pOut->PrintMessage("No Figures Selected");
		return;
	}
	for (int i = 0; i < SelectedFigCount; i++)
	{
		SelectedFigList[i] = pManager->GetSelectedFigure(i);
	}
	pOut->PrintMessage(to_string(SelectedFigCount) + " figure(s) have been deleted");
}

void DeleteAction::Execute()
{
	ReadActionParameters();
	for (int i = 0; i < SelectedFigCount; i++)
	{
		pManager->RemoveFigure(SelectedFigList[i]);
		delete SelectedFigList[i];
		SelectedFigList[i] = NULL;
	}
}
