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

	if (pManager->GetSelectedFigureCount() == 0)//if there are no selected figures
	{
		pOut->PrintMessage("No Figures Selected");
	}
}

void DeleteAction::Execute()
{
	ReadActionParameters();

	int DeletedFigCount = 0;

	while (pManager->GetSelectedFigureCount() > 0) //delete figures while there are selected figures remaining
	{
		FigureToDelete = pManager->GetSelectedFigure();

		pManager->RemoveFigure(FigureToDelete->GetID());

		delete FigureToDelete;

		DeletedFigCount++;

	}
	if (DeletedFigCount > 0)//If figures have been deleted
		pManager->GetOutput()->PrintMessage(to_string(DeletedFigCount) + " figure(s) have been deleted");
}
