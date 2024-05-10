#include "DoubleSizeAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

DoubleSizeAction::DoubleSizeAction(ApplicationManager* pApp) :Action(pApp)
{
}

void DoubleSizeAction::ReadActionParameters()
{
	SelectedFig = pManager->GetSelectedFigure();
}

void DoubleSizeAction::Execute()
{
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();

	if (SelectedFig->DoubleSize())//Calls double size and checks if it returns true then it succeeded

		pOut->PrintMessage("Figure Size Doubled");

	else

		pOut->PrintMessage("Figure Too Large");
}
