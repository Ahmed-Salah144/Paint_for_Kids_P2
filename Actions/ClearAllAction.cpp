#include "ClearAllAction.h"
#include "..\Figures\CFigure.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ClearAllAction::ClearAllAction(ApplicationManager* pApp):Action(pApp)
{
}

void ClearAllAction::ReadActionParameters()
{
}

void ClearAllAction::Execute()
{
	pManager->ClearAll();
	Output* pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
	pOut->ClearDrawArea();
	pOut->PrintMessage("All Cleared");
}
