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
	CFigure* CutFig = NULL;
	switch (SelectedFig->GetFigType()) {
	case HEXAGON: CutFig = new CHexagon((CHexagon*)SelectedFig); break;
	case CIRCLE: CutFig = new CCircle((CCircle*)SelectedFig); break;
	case TRIANGLE: CutFig = new CTriangle((CTriangle*)SelectedFig); break;
	case SQUARE: CutFig = new CSquare((CSquare*)SelectedFig); break;
	case RECTANGLE: CutFig = new CRectangle((CRectangle*)SelectedFig); break;
	}
	if (pManager->GetFigureByID(pManager->GetCutFigureID()) != NULL)
	{
		if (pManager->GetCutFigureID() != -1)
		{
			CFigure* PreviouslyCutFigure = pManager->GetFigureByID(pManager->GetCutFigureID());
			CFigure* Clipboard = pManager->GetClipboard();
			PreviouslyCutFigure->ChngDrawClr(Clipboard->GetDrawClr());
			if (Clipboard->IsFilled())
				PreviouslyCutFigure->ChngFillClr(Clipboard->GetFillClr());
			else
				PreviouslyCutFigure->UnFill();
			if (SelectedFig->GetID() == PreviouslyCutFigure->GetID())
			{
				CutFig->ChngDrawClr(Clipboard->GetDrawClr());
				if (Clipboard->IsFilled())
					CutFig->ChngFillClr(Clipboard->GetFillClr());
				else
					CutFig->UnFill();
			}
		}
	}
	SelectedFig->SetSelected(false);
	SelectedFig->ChngDrawClr(GRAY);
	SelectedFig->ChngFillClr(GRAY);
	pManager->ClearClipboard();
	pManager->SetCutFigureID(SelectedFig->GetID());
	pManager->SetClipboard(CutFig);
	pManager->UpdateFigureData();
}