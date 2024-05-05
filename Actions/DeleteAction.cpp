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

}

void DeleteAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if (pManager->GetSelectedFigureCount() == 0)
	{
		pOut->PrintMessage("No Figures Selected");
		return;
	}
	int DeletedFigCount = 0;
	while (pManager->GetSelectedFigureCount() > 0)
	{
		FigureToDelete = pManager->GetSelectedFigure();
		pManager->RemoveFigure(FigureToDelete->GetID());
		delete FigureToDelete;
		DeletedFigCount++;

	}
	pOut->PrintMessage(to_string(DeletedFigCount) + " figure(s) have been deleted");
}
