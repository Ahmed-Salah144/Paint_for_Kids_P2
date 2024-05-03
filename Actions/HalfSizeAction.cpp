#include "HalfSizeAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

HalfSizeAction::HalfSizeAction(ApplicationManager* pApp) :Action(pApp)
{
}

void HalfSizeAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	SelectedFig = pManager->GetSelectedFigure(0);
}

void HalfSizeAction::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (SelectedFig->HalfSize())
		pOut->PrintMessage("Figure Size Halfed");
	else
		pOut->PrintMessage("Figure Too Small");
}
