#include "CutAction.h"
#include "..\Figures\CFigure.h"

#include "..\ApplicationManager.h"
#include "SelectionAction.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

CutAction::CutAction(ApplicationManager* pApp) :Action(pApp)
{
}

void CutAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Selected Fig Cut");
	SelectedFig = pManager->GetSelectedFigure();
}

void CutAction::Execute()
{
	ReadActionParameters();
	CFigure* CopiedFig = NULL;
	switch (SelectedFig->GetFigType()) {
	case HEXAGON: CopiedFig = new CHexagon((CHexagon*)SelectedFig); break;
	case CIRCLE: CopiedFig = new CCircle((CCircle*)SelectedFig); break;
	case TRIANGLE: CopiedFig = new CTriangle((CTriangle*)SelectedFig); break;
	case SQUARE: CopiedFig = new CSquare((CSquare*)SelectedFig); break;
	case RECTANGLE: CopiedFig = new CRectangle((CRectangle*)SelectedFig); break;
	}
	SelectedFig->SetSelected(false);
	SelectedFig->ChngDrawClr(GRAY);
	pManager->SetClipboardID(SelectedFig->GetID());
}