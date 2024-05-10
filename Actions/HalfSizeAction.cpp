#include "HalfSizeAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

HalfSizeAction::HalfSizeAction(ApplicationManager* pApp) :Action(pApp)
{
}

void HalfSizeAction::ReadActionParameters()
{
	SelectedFig = pManager->GetSelectedFigure();
}

void HalfSizeAction::Execute()
{
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();

	if (SelectedFig->HalfSize()) //Calls half size and checks if it returned true

		pOut->PrintMessage("Figure Size Halfed");

	else

		pOut->PrintMessage("Figure Too Small");
}
